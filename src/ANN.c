/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This c file for the neural network functions.
*/
//=============================> .START
//=============================> .INC
#include "../inc/Global.h"

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

    // Input Layer:
    // Create new vector in heap & Set the input layer dense. (Initalize: True)
    const uint16_t ilDense = new_dnnNetwork->network_topology->input_layer_dense; // Temporary variable for readability.
    new_dnnNetwork->network_layers->Input_layer->input_layer = create_vector(ilDense, true);

    // Hidden Layer:
    // Set the hidden layers num.
    new_dnnNetwork->network_layers->hidden_layer_num = new_dnnNetwork->network_topology->hidden_layer_num;
    // Create the hidden layers. (x num)
    const uint16_t hlNum = new_dnnNetwork->network_layers->hidden_layer_num; // Temporary variable for readability.
    new_dnnNetwork->network_layers->Hidden_layer = (Hidden_Layer *) malloc(sizeof(Hidden_Layer) * hlNum);

    // Create layer dense for each hidden layer.
    const uint16_t N = new_dnnNetwork->network_layers->hidden_layer_num; // Temporary variable for readability.
    const uint16_t hlDense = new_dnnNetwork->network_topology->hidden_layer_dense; // Temporary variable for readability.
   
    for(uint16_t i = 0; i < N; i++)
    {   
        // Creat new hidden layers vector. (Initalize: True)
        
        new_dnnNetwork->network_layers->Hidden_layer[i].hidden_layer = create_vector(hlDense, true);
    }

    // Output Layer:
    // Create the output layer & set its dense. (Initalize: True)
    const uint16_t olDense = new_dnnNetwork->network_topology->output_layer_dense;
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
    
    // Set the Weights(INPUT<=>HIDDEN[0]): (Layer_weights[0]) <> (Transient states excpetion)
    uint16_t row = new_dnnNetwork->network_topology->hidden_layer_dense;
    uint16_t col = new_dnnNetwork->network_topology->input_layer_dense;

    new_dnnNetwork->network_layers->Layer_weights[0].layer_weights = create_matrix(row, col, true); // (Initalize: True)

    // Set the Weights(HIDDEN[0]<=>HIDDEN[N-1]):
    // Re set the row & col for the current position. (Square matrix)
    row = new_dnnNetwork->network_topology->hidden_layer_dense;
    col = new_dnnNetwork->network_topology->hidden_layer_dense;
    for(uint16_t i = 1; i <  (number_of_matrices-1); i++) 
    {
        new_dnnNetwork->network_layers->Layer_weights[i].layer_weights = create_matrix(row, col, true); // (Initalize: True)
    }

    // Set the Weights(HIDDEN[N]<=>OUTPUT)
    // Re set the row & col for the current position. 
    row = new_dnnNetwork->network_topology->output_layer_dense;
    col = new_dnnNetwork->network_topology->hidden_layer_dense;

    new_dnnNetwork->network_layers->Layer_weights[number_of_matrices-1].layer_weights = create_matrix(row, col, true); // (Initalize: True)
    
    // Layers_Biases:
    // Create Layer Biases vector. (Initalize: True)
    const uint16_t biases_vector_length = number_of_layers - 1; // Temporary variable for readability.
    new_dnnNetwork->network_layers->Layers_biases->layers_biases = create_vector(biases_vector_length, true);


    // Return the new created network.
    return new_dnnNetwork;

}//end Create_Network.

//====================================> [DNN FUNCTIONS]

// Function to perform the forward propagation on the network.
void forward_propagation(DNN_Network *dnn_network)
{


    return;
}//end forward_propagation.


// Function to perform the backward propagation on the network.
void back_propagation(DNN_Network *dnn_network)
{


    return;
}//end back_propagation.

//====================================> [ACTIVATION FUNCTIONS]

// The Linear Activation Function.


// The ReLU Activation Function. 
float *ReLU(Type_t *vector)
{

    return NULL;
}//end ReLU.

// The Sigmoid Activation Function.


// The Tanh Activation Function.


// The Softmax Activation Function.


//====================================> [LOSS FUNCTIONS]

// Function to perform the square error loss function.

float *SquareError(Type_t *vector)
{

    return NULL;
}//end SqureError.

//====================================> [OPTIMIZER FUNCTIONS]

// Function to do the optimization with gradient decent.

float *GradientDescent(Type_t *vector)
{

    return NULL;
}//end GradientDescent.


//====================================> [SUB FUNCTIONS]

// Function to check the validity & restrections of a given network topology.
void network_topology_validity(Network_Topology_t *network_topology)
{
    //Check if the passed newtork_topology is valid.
    if(network_topology == NULL)
    {printf("\n ANN.c|ERROR. network_topology: NULL\n"); exit(-1);}
    // assert(network_topology != NULL); // For strictly exit.

    // First check the layers.
    if((network_topology->input_layer_dense  <= 0) ||
       (network_topology->hidden_layer_dense <= 0) ||
       (network_topology->output_layer_dense <= 0) ||
       (network_topology->hidden_layer_num   <= 1)
      )
    {printf("\n ANN.c|ERROR. network_topology_validity: false\n"); exit(-1);}

    // assert(network_topology->input_layer_dense > 0);
    // assert(network_topology->hidden_layer_dense > 0);
    // assert(network_topology->output_layer_dense > 0);
    // assert(hidden_layer_num > 0);

    // Check the restrections.
    if(network_topology->input_layer_dense  > MAX_INPUT_LAYER_DENSE)
    {printf("\n ANN.c|ERROR. input_layer_dense: invalid\n"); exit(-1);}
    // assert(network_topology->input_layer_dense < MAX_INPUT_LAYER_DENSE);

    if(network_topology->hidden_layer_dense > MAX_HIDDEN_LAYER_DENSE)
    {printf("\n ANN.c|ERROR. hidden_layer_dense: invalid\n"); exit(-1);}
    // assert(network_topology->hidden_layer_dense < MAX_HIDDEN_LAYER_DENSE);

    if(network_topology->output_layer_dense > MAX_OUTPUT_LAYER_DENSE)
    {printf("\n ANN.c|ERROR. output_layer_dense: invalid\n"); exit(-1);}
    // assert(network_topology->outputlayer_dense < MAX_OUTPUT_LAYER_DENSE);

    if(network_topology->hidden_layer_num   > MAX_HIDDEN_LAYER_NUM)
    {printf("\n ANN.c|ERROR. hidden_layer_num: invalid\n"); exit(-1);}
    // assert(network_topology->hidden_layer_num < MAX_HIDDEN_LAYER_NUM);

    // Check the functions pointer.
    // Check the activation function pointer.
    if(network_topology->activation_function == NULL)
    {printf("\n ANN.|ERROR. Activation_Function: NULL\n"); exit(-1);}
    // assert(network_topology->activation_function != NULL);

    // Check the loss function pointer.
    if(network_topology->loss_function == NULL)
    {printf("\n ANN.|ERROR. Loss_Function: NULL\n"); exit(-1);}
    // assert(network_topology->loss_function != NULL);

    // Check the optimizer function pointer.
    if(network_topology->optimizer_function == NULL)
    {printf("\n ANN.|ERROR. Optimizer_Function: NULL\n"); exit(-1);}
    // assert(network_topology->optimizer_function != NULL);

    return;
}//end network_topology_validity.

//=============================> .END