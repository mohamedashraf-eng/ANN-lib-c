/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This h file contains the neural network settings.
*/
//=============================> .START
#ifndef _ANN_H
#define _ANN_H
//=============================> .INC
#include "Global.h"
//=============================> .DEFINES

#define MAX_INPUT_LAYER_DENSE  ((const uint16_t) 200)
#define MAX_HIDDEN_LAYER_DENSE ((const uint16_t) 200)
#define MAX_OUTPUT_LAYER_DENSE ((const uint16_t) 200)
#define MAX_HIDDEN_LAYER_NUM   ((const uint16_t) 10)

//=============================> .STRUCTS
// Struct for the input layer.
typedef struct 
{
    Type_t *input_layer;
}Input_Layer;

// Struct for the hidden layer.
typedef struct 
{   
    Type_t *hidden_layer;
}Hidden_Layer;

// Struct for the output layer vector.
typedef struct
{
    Type_t *output_layer;
}Output_Layer;

// Struct for the layer weights matrix.
typedef struct
{
    Type_t *layer_weights;
}Layer_Weights;

typedef struct
{
    Type_t *layers_biases;
}Layers_Biases;


// Struct to store the neural network parameters.
typedef struct _Layer_t
{
    Input_Layer *Input_layer;
    Output_Layer *Output_layer;
    
    uint16_t hidden_layer_num;
    Hidden_Layer *Hidden_layer;

    Layer_Weights *Layer_weights;

    Layers_Biases *Layers_biases;
}Layer_t;

// Network parameter confiuration
typedef struct _Netowrk_Config_t
{
    // Learning rate.
    float learning_rate;

    // Active/Inactive dropout.
    bool dropout; 
}Network_Config_t;

// Network topology parameters.
typedef struct _Network_Topology_t
{
    //===> NN Paramaeters:
    // The input layer number of neurons.
    uint16_t input_layer_dense;

    // The output layer number of neurons.
    uint16_t output_layer_dense;

    // Number of hidden layers.
    uint16_t hidden_layer_num;

    // The hidden layers number of neurons.
    uint16_t hidden_layer_dense;   

    //===> System Parameters:
    // The Activation Function.
    float * (*activation_function) (Type_t *);

    // The Loss Function.
    float * (*loss_function) (Type_t *);

    // The Optimizer Function.
    float * (*optimizer_function) (Type_t *);

}Network_Topology_t;

typedef struct _DNN_Network
{
    Network_Config_t   *network_config;
    Network_Topology_t *network_topology;
    Layer_t            *network_layers;
    
}DNN_Network;
//=============================> .FUNC

void network_topology_validity(Network_Topology_t *);
DNN_Network *Create_Network(Network_Topology_t *, Network_Config_t *);

void forward_propagation(DNN_Network *);
void back_propgation(DNN_Network *);

//void Linear(Type_t *);
float *ReLU(Type_t *);
//void Sigmoid(Type_t *);
//void Tanh(Type_t *);
//void SoftMax(Type_t *);

float *SquareError(Type_t *);

float *GradientDescent(Type_t *);

void print_network(DNN_Network *);
//=============================> .END
#endif /*_ANN_H*/

