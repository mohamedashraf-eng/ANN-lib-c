/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This c file for the neural network functions.
*/
//=============================> .START
//=============================> .INC
#include "../inc/Global.h"

#define CURRENT_H "ANN.H"
#define CURRENT_C "ANN.C"
//=============================> .FUNC
/* 
    - Algorithm overview:
        1- Setting the n.network topology parameters.
        2- Forward propagation.
        3- Calculating the network loss.
        4- Backward propagation.

    - General formulas:
        Number of layers in a network: Input_Layer + Output Layer + Hidden Layers.
        NOL: N + 2. (N: Hidden_Layers)

        Number of weights metrices in a network: 
                Input_Layer -> N_Hidden_Layers -> Output_Layer.
                [I] -1- [H[0]] -2- [H[N]] -n- [O]
        NOM: NOL - 1. (NOL: Number Of Layers)

        Transient states in a network: Input -> Hidden[0],  Hidden[N] -> Output
*/

//=============================> .STRUCTS

Network_Config_t general_network_config = {.learning_rate = 0.2549, .dropout = false};

//=============================> .DEFINES



//=============================> .FUNC

//====================================> [MAIN FUNCTIONS]

// Function to create a network with specific topology configs.
DNN_Network *Create_Network(Network_Topology_t *network_topology_settings, Network_Config_t *network_config)
{
    // Check the validity of a given network topology.
    network_topology_validity(network_topology_settings);

    // Create a new Deep Neural Network - Network struct.
    DNN_Network *new_dnnNetwork = (DNN_Network *) malloc(sizeof(DNN_Network));
   
    if(new_dnnNetwork == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Set the network settings:
    // Set the network configs. (general by default. User can change it)
    if(network_config == NULL)
        new_dnnNetwork->network_config = &general_network_config;
    else
        new_dnnNetwork->network_config = network_config;

    // Set the network topology. (Pre defined by the user)
    new_dnnNetwork->network_topology = network_topology_settings;

    // Set the Nerual Network settings:
    // Create new network layers struct in heap.
    new_dnnNetwork->network_layers = (Layer_t *) malloc(sizeof(Layer_t));
    
    if(new_dnnNetwork->network_layers == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Input Layer:
    // Create new vector in heap & Set the input layer dense. (Initalize: True)
    const uint16_t ilDense = new_dnnNetwork->network_topology->input_layer_dense; // Temporary variable for readability.
    // Create input layer struct memory in heap.
    new_dnnNetwork->network_layers->Input_layer = (Input_Layer *) malloc(sizeof(Input_Layer));
    // Create input layer vector data in heap.
    new_dnnNetwork->network_layers->Input_layer->input_layer = create_vector(ilDense, true);

    // Hidden Layer:
    // Set the hidden layers num.
    new_dnnNetwork->network_layers->hidden_layer_num = new_dnnNetwork->network_topology->hidden_layer_num;
    // Create the hidden layers. (x num)
    const uint16_t hlNum = new_dnnNetwork->network_layers->hidden_layer_num; // Temporary variable for readability.
    new_dnnNetwork->network_layers->Hidden_layer = (Hidden_Layer *) malloc(sizeof(Hidden_Layer) * hlNum);
    
    if(new_dnnNetwork->network_layers->Hidden_layer == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    //Hidden_Layer hidden_layers[hlNum];
    //new_dnnNetwork->network_layers->Hidden_layer = hidden_layers;

    // Create layer dense for each hidden layer.
    const uint16_t hlDense = new_dnnNetwork->network_topology->hidden_layer_dense; // Temporary variable for readability.

    for(uint16_t i = 0; i < hlNum; i++)
    {   
        // Creat new hidden layers vector. (Initalize: True)
        new_dnnNetwork->network_layers->Hidden_layer[i].hidden_layer = create_vector(hlDense, true);
    }

    // Output Layer:
    // Create the output layer & set its dense. (Initalize: True)
    const uint16_t olDense = new_dnnNetwork->network_topology->output_layer_dense;
    // Create heap memory for the output struct
    new_dnnNetwork->network_layers->Output_layer = (Output_Layer *) malloc(sizeof(Output_Layer));
    
    if(new_dnnNetwork->network_layers->Output_layer == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Create heap memory and assign data to the output layer vector.
    new_dnnNetwork->network_layers->Output_layer->output_layer = create_vector(olDense ,true);


    // Layer Weights: (Number of layers = hidden_layer_num + 2)
    /*
        row of the weights matrix: the output  vector dense.
        col of the weights matrix: the input   vector dense.
        Layer_Weights_Matrix       Input_Vector Output_Vector
        [00, 01, 0j]               [0, 1, n] => [0] 
        [10, 11, 1j]                         => [1]
        [20, 21, 2j]                         => [2]
        [i0, i1, ij]                         => [m]
    */
   
    // Create layers weights (N_LAYERS - 1)
    const uint16_t number_of_layers = new_dnnNetwork->network_topology->hidden_layer_num + 2; // temporary variable for readability.
    const uint16_t number_of_matrices = number_of_layers - 1;

    new_dnnNetwork->network_layers->Layer_weights = (Layer_Weights *) malloc(sizeof(Layer_Weights) * (number_of_matrices));
   
    if(new_dnnNetwork->network_layers->Layer_weights == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Set the Weights(INPUT<=>HIDDEN[0]): (Layer_weights[0]) <> (Transient states excpetion)
    uint16_t row = new_dnnNetwork->network_topology->hidden_layer_dense;
    uint16_t col = new_dnnNetwork->network_topology->input_layer_dense;
    new_dnnNetwork->network_layers->Layer_weights[0].layer_weights = create_matrix(row, col, true); // (Initalize: True).


    // Set the Weights(HIDDEN[0]<=>HIDDEN[N])
    row = new_dnnNetwork->network_topology->hidden_layer_dense;
    col = new_dnnNetwork->network_topology->hidden_layer_dense;

    for(uint16_t i = 1; i < number_of_matrices-1; i++) 
    {
        new_dnnNetwork->network_layers->Layer_weights[i].layer_weights = create_matrix(row, col, true); // (Initalize: True).
    }

    // Set the Weights(HIDDEN[N]<=>OUTPUT): (Layer_weights[n-1]) <> (Transient states excpetion)
    row = new_dnnNetwork->network_topology->output_layer_dense;
    col = new_dnnNetwork->network_topology->hidden_layer_dense;
    new_dnnNetwork->network_layers->Layer_weights[number_of_matrices-1].layer_weights = create_matrix(row, col, true); // (Initalize: True).
    
    // Layers_Biases:
    // Create Layer Biases vector. (Initalize: True)
    const uint16_t biases_vector_length = number_of_layers - 1; // Temporary variable for readability.
    // Create Layers_Biases struct in heap.
    new_dnnNetwork->network_layers->Layers_biases = (Layers_Biases *) malloc(sizeof(Layers_Biases));
    
    if(new_dnnNetwork->network_layers->Layers_biases == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Create heap memory for the biases vector & assign the vector of biases.
    new_dnnNetwork->network_layers->Layers_biases->layers_biases = create_vector(biases_vector_length, true);

    // Return the new created network.
    return new_dnnNetwork;
}//end Create_Network.

//====================================> [DNN FUNCTIONS]

// Function to perform the forward propagation on the network.
/*
- Forward Propagation Algorithms:
    1- Input_Layer (dot product) Weights_Layer[0] & Store the result in Hidden[0].
*/
void forward_propagation(DNN_Network *dnn_network)
{
    /// Check if the passed network isn't created yet.
    if(dnn_network == NULL)
        error_exit(CURRENT_C, "DNN_NETWORK: NULL");

    // First the dot product of input & weights_layer[0].
    // Do the dot product and store it in it.
    Type_t *input_layer = dnn_network->network_layers->Input_layer->input_layer; // (Temporary variable for readbility).
    Type_t *weights_layer_0 = dnn_network->network_layers->Layer_weights[0].layer_weights; // (Temporary variable for readbility).
    
    // Perform the dot product and save it into the hidden layer 0.
    //free(hidden_layer_0); // Free the previous array.
    dnn_network->network_layers->Hidden_layer[0].hidden_layer->Vector_t.Vector = VxM_DotProduct(input_layer, weights_layer_0);
    // Apply the activation function.
    dnn_network->network_layers->Hidden_layer[0].hidden_layer->Vector_t.Vector = 
    dnn_network->network_topology->activation_function(dnn_network->network_layers->Hidden_layer[0].hidden_layer);

    // Do the dot product from hidden layer [0] to hidden layer [n].
    const uint16_t hidden_layers_num = dnn_network->network_topology->hidden_layer_num;

    uint16_t temporary_counter = 0; // Temporary counter for the number of multiplications.
    uint16_t hidden_layer_counter = 1; // Temporary counter for iterating through the hidden layers.
    uint16_t layer_weights_counter = 1; // Temporary counter for iterating through the weights.

    while(temporary_counter < (hidden_layers_num-1))
    {
        Type_t *hidden_layer_current = dnn_network->network_layers->Hidden_layer[hidden_layer_counter-1].hidden_layer;
        Type_t *weights_layer_current = dnn_network->network_layers->Layer_weights[layer_weights_counter].layer_weights;
        
        // Free the previous allocated array.
        //free(hidden_layer_next);
        // Store the dot product result.
        dnn_network->network_layers->Hidden_layer[hidden_layer_counter].hidden_layer->Vector_t.Vector = VxM_DotProduct(hidden_layer_current, weights_layer_current);
        // Apply the activation function.
        dnn_network->network_layers->Hidden_layer[hidden_layer_counter].hidden_layer->Vector_t.Vector = 
        dnn_network->network_topology->activation_function(dnn_network->network_layers->Hidden_layer[hidden_layer_counter].hidden_layer);

        temporary_counter++; 
        hidden_layer_counter++; 
        layer_weights_counter++; 
    }//end while.
    
    // Do the dot product for hidden layer [n] and output layer.
    Type_t *hidden_layer_n = dnn_network->network_layers->Hidden_layer[hidden_layers_num-1].hidden_layer;
    const uint16_t layer_weights_num = hidden_layers_num; // ((+ 2 - 1) = (+ 1 - 1) = (0)).
    Type_t *layer_weights_n = dnn_network->network_layers->Layer_weights[layer_weights_num].layer_weights;

    // Free the previous allocated array.
    //free(output_layer);
    // Store the dot product result.
    dnn_network->network_layers->Output_layer->output_layer->Vector_t.Vector = VxM_DotProduct(hidden_layer_n, layer_weights_n);
    // Apply the activation function.
    dnn_network->network_layers->Output_layer->output_layer->Vector_t.Vector = 
    dnn_network->network_topology->output_activation_function(dnn_network->network_layers->Output_layer->output_layer);

    return;
}//end forward_propagation.


// Function to perform the backward propagation on the network.
void back_propagation(DNN_Network *dnn_network)
{


    return;
}//end back_propagation.

//====================================> [ACTIVATION FUNCTIONS]

// The Linear Activation Function.


// The Exponentinal Linear Unit Activation Function. 
double *ELU(Type_t *vector)
{   
    const uint16_t vector_len = vector->Vector_t.len;

    double alpha = 1.0f;
    double Exponentinal_Leak = 0.0f;

    for(uint16_t i = 0; i < vector_len; i++)
    {
        Exponentinal_Leak = alpha * (exp(vector->Vector_t.Vector[i]) - 1);
        vector->Vector_t.Vector[i] = (vector->Vector_t.Vector[i] < 0) ? 
                                     (Exponentinal_Leak) : (vector->Vector_t.Vector[i]);
    }

    return vector->Vector_t.Vector;
}//end ReLU.

// The Sigmoid Activation Function.


// The Tanh Activation Function.


// The Softmax Activation Function.
double *SoftMax(Type_t *vector)
{
    const uint16_t vector_len = vector->Vector_t.len;

    // Calculate the exponential sum of the given vector.
    double exponential_sum = 0.0f;

    for(uint16_t i = 0; i < vector_len; i++)
    {
        exponential_sum += exp(vector->Vector_t.Vector[i]);
    }

    // Convert the regression vector to classification vector.
    for(uint16_t j = 0; j < vector_len; j++)
    {
        vector->Vector_t.Vector[j] = (vector->Vector_t.Vector[j] / exponential_sum); 
    }

    return vector->Vector_t.Vector;
}//end SoftMax.

//====================================> [LOSS FUNCTIONS]

// Function to perform the square error loss function.

double *SquareError(Type_t *vector)
{

    return NULL;
}//end SqureError.

//====================================> [OPTIMIZER FUNCTIONS]

// Function to do the optimization with gradient decent.

double *GradientDescent(Type_t *vector)
{

    return NULL;
}//end GradientDescent.


//====================================> [SUB FUNCTIONS]

// Function to check the validity & restrections of a given network topology.
void network_topology_validity(Network_Topology_t *network_topology)
{
    //Check if the passed newtork_topology is valid.
    if(network_topology == NULL)
        error_exit(CURRENT_C, "NETWORK_TOPOLOGY:NULL");
    // assert(network_topology != NULL); // For strictly exit.

    // First check the layers.
    if((network_topology->input_layer_dense  <= 0) ||
       (network_topology->hidden_layer_dense <= 0) ||
       (network_topology->output_layer_dense <= 0) ||
       (network_topology->hidden_layer_num   <= 1)
      )
        error_exit(CURRENT_C, "NETWORK_TOPOLOGY_PARAMS:INVALID");

    // assert(network_topology->input_layer_dense > 0);
    // assert(network_topology->hidden_layer_dense > 0);
    // assert(network_topology->output_layer_dense > 0);
    // assert(hidden_layer_num > 0);

    // Check the restrections.
    if(network_topology->input_layer_dense  > MAX_INPUT_LAYER_DENSE)
        error_exit(CURRENT_C, "INPUT_LAYER_DENSE:MAX_LIMIT");
    // assert(network_topology->input_layer_dense < MAX_INPUT_LAYER_DENSE);

    if(network_topology->hidden_layer_dense > MAX_HIDDEN_LAYER_DENSE)
        error_exit(CURRENT_C, "HIDDEN_LAYER_DENSE:MAX_LIMIT");
    // assert(network_topology->hidden_layer_dense < MAX_HIDDEN_LAYER_DENSE);

    if(network_topology->output_layer_dense > MAX_OUTPUT_LAYER_DENSE)
        error_exit(CURRENT_C, "OUTPUT_LAYER_DENSE:MAX_LIMIT");
    // assert(network_topology->outputlayer_dense < MAX_OUTPUT_LAYER_DENSE);

    if(network_topology->hidden_layer_num   > MAX_HIDDEN_LAYER_NUM)
        error_exit(CURRENT_C, "HIDDEN_LAYER_NUM:MAX_LIMIT");
    // assert(network_topology->hidden_layer_num < MAX_HIDDEN_LAYER_NUM);

    // Check the functions pointer.
    // Check the activation function pointer.
    if(network_topology->activation_function == NULL)
        error_exit(CURRENT_C, "NETWORK_TOPOLOGY_AF:NULL");
    // assert(network_topology->activation_function != NULL);

    // Check the loss function pointer.
    if(network_topology->loss_function == NULL)
        error_exit(CURRENT_C, "NETWORK_TOPOLOGY_LF:NULL");
    // assert(network_topology->loss_function != NULL);

    // Check the optimizer function pointer.
    if(network_topology->optimizer_function == NULL)
        error_exit(CURRENT_C, "NETWORK_TOPOLOGY_OF:NULL");
    // assert(network_topology->optimizer_function != NULL);

    return;
}//end network_topology_validity.


// Function to print network (for debugging purposes)
void print_network(DNN_Network *myNetwork)
{
    if(myNetwork == NULL)
        error_exit(CURRENT_C, "MY_NETWORK:NULL");

    // Printing the input layer.
    printf("\n Input_Layer: \n");
    print_vector(myNetwork->network_layers->Input_layer->input_layer);

    // Printing hidden layers.
    const uint16_t hNum = myNetwork->network_topology->hidden_layer_num;

    for(uint16_t i = 0; i < hNum; i++)
    {
        printf("\n Hidden_Layer[%d]: \n", i);
        print_vector(myNetwork->network_layers->Hidden_layer[i].hidden_layer);
    }  

    // Printing the output layer.
    printf("\n Output_Layer: \n");
    print_vector(myNetwork->network_layers->Output_layer->output_layer);

    // Printing all the weights.
    const uint16_t NoW = myNetwork->network_topology->hidden_layer_num + 1;
   
    for(uint16_t i = 0; i < NoW; i++)
    {    
        printf("\n Layer_Weights[%d]: \n", i);
        print_matrix(myNetwork->network_layers->Layer_weights[i].layer_weights);
    }

    return;
}//end print_network.

//=============================> .END