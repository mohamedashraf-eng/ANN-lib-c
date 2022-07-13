/**
 * @file ANN.h
 * @author Mohamed Wx (gtlyco205@gmail.com)
 * @brief Artificial Neural Network header.
 * @version 0.3
 * @date 2022-06-13
 * 
 * @copyright Copyright Mohamed Wx (c) 2022
 * 
 */
//!=============================> .START
#ifndef _ANN_H
#define _ANN_H

#ifdef _cplusplus
    extern "C"{
#endif

/*
----------------------------------------------------------------
!-                       INCLUDED HEADERS                      -
----------------------------------------------------------------
*/

#include "Global.h"

/*
----------------------------------------------------------------
!-                       DEFINED VARIABLES                     -
----------------------------------------------------------------
*/

/** @defgroup Deep Network parameters limitations */
#define MAX_INPUT_LAYER_DENSE  ((const uint16_t) 200)
#define MAX_HIDDEN_LAYER_DENSE ((const uint16_t) 200)
#define MAX_OUTPUT_LAYER_DENSE ((const uint16_t) 200)
#define MAX_HIDDEN_LAYER_NUM   ((const uint16_t) 010)

/*
----------------------------------------------------------------
!-                       DEFINED STRUCTS                       -
----------------------------------------------------------------
*/

/**
 * @brief Struct for the input layer
 * 
 */
typedef struct 
{
    Type_t *input_layer;
}Input_Layer;

/**
 * @brief Struct for the hidden layer
 * 
 */
typedef struct 
{   
    Type_t *hidden_layer;
}Hidden_Layer;

/**
 * @brief Struct for the output layer
 * 
 */
typedef struct
{
    Type_t *output_layer;
}Output_Layer;

/**
 * @brief Struct for the weights
 * 
 */
typedef struct
{
    Type_t *layer_weights;
}Layer_Weights;

/**
 * @brief Struct for the biases
 * 
 */
typedef struct
{
    Type_t *layers_biases;
}Layers_Biases;

/**
 * @brief Struct for deep neural network parameters.
 * 
 */
#pragma pack(1)
typedef struct _Layer_t
{
    Input_Layer *Input_layer;
    Output_Layer *Output_layer;
    
    uint16_t hidden_layer_num;
    Hidden_Layer *Hidden_layer;

    Layer_Weights *Layer_weights;

    Layers_Biases *Layers_biases;
}Layer_t;

/**
 * @brief Struct for network parameters configurations
 * 
 */
#pragma pack(1)
typedef struct _Netowrk_Config_t
{
    // Learning rate.
    const double learning_rate;

    // Active/Inactive dropout.
    const bool dropout; 

    const uint16_t epochs;
}Network_Config_t;

/**
 * @brief Struct for the network topology parameters
 * 
 */
#pragma pack(1)
typedef struct _Network_Topology_t
{
    //===> NN Paramaeters:
    // The input layer number of neurons.
    const uint16_t input_layer_dense;

    // The output layer number of neurons.
    const uint16_t output_layer_dense;

    // Number of hidden layers.
    const uint16_t hidden_layer_num;

    // The hidden layers number of neurons.
    const uint16_t hidden_layer_dense;   

    //===> System Parameters:
    // The Activation Function.
    double * (*activation_function) (Type_t *); // Activation function for the basic layers.
    double * (*output_activation_function) (Type_t *); // Activation function for the output layer.

    // The Loss Function.
    double * (*loss_function) (Type_t *, Type_t *);
    double * (*loss_function_array) (Type_t *);

    // The Optimizer Function.
    double * (*optimizer_function) (Type_t *);

}Network_Topology_t;

/**
 * @brief Struct encapsulating all the network things
 * 
 */
#pragma pack(1)
typedef struct _DNN_Network
{
    Network_Config_t   *network_config;
    Network_Topology_t *network_topology;
    Layer_t            *network_layers;
}DNN_Network;

/*
----------------------------------------------------------------
!-                       DEFINED FUNCTIONS                     -
----------------------------------------------------------------
*/

/** @defgroup Deep Neural Network Activation Functions Main Functions */
void network_topology_validity(Network_Topology_t *);
DNN_Network *Create_Network(Network_Topology_t *, Network_Config_t *);

void Set_Input(DNN_Network * ,Type_t *);
void Set_Output(DNN_Network * ,Type_t *);

//void Get_Error(DNN_Network *);
//void Get_Accuracy(DNN_Network *);

/** @defgroup Deep Neural Network Functions */
void forward_propagation(DNN_Network *);
void back_propgation(DNN_Network *);

/** @defgroup Deep Neural Network Activation Functions - Hidden Layer */
double *ReLU(Type_t *);
double *ELU(Type_t *);
double *Sigmoid(Type_t *);
double *Tanh(Type_t *);

/** @defgroup Deep Neural Network Activation Functions - Drevative */
double *ReLU_D(Type_t *);
double *ELU_D(Type_t *);
double *Sigmoid_D(Type_t *);
double *Tanh_D(Type_t *);

/** @defgroup Deep Neural Network Activation Functions - Output Layer */
double *SoftMax(Type_t *);

/** @defgroup  Deep Neural Network Loss Functions */
double *MSE(Type_t *, Type_t *);         // Mean Square Error.
double *MAE(Type_t *, Type_t *);        // Mean Absolute Error.
//double *BC(Type_t *, Type_t *);      // Binary Classification Error.
//double *BCE(Type_t *, Type_t *);    // Binary Cross Entropy Error.
//double *MCC(Type_t *, Type_t *);   // Multi Class Classification Error.
//double *MCCE(Type_t *, Type_t *); // Multi Class Cross Entropy Error.

/** @defgroup Deep Nueral Network Optimization Functions*/
double *GradientDescent(Type_t *);

/** @defgroup Deep Neural Network Sub Functions */
void print_network(DNN_Network *);
void ApplyBiases(Type_t *, Type_t *, uint8_t );

#ifdef __cplusplus
    }
#endif
//!=============================> .END

#endif /*_ANN_H*/

