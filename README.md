# Open_Source_ANN_In_C
## About Library
This library is essentialy made for Embedded Machine Learning. It's based on memory management (Not fully secured yet).

# Complete Functions
## Public Functions
* Create_Network
* forward_propagation

## Activation Functions
* ReLU
* ELU
* Sigmoid
* Tanh
* Softmax

## Loss Functions
* MSE
* MAE

# How to use
## Setting your network parameters
### Topology
'''
Network_Topology_t MyNetworkTopology = {.input_layer_dense  = 2, 
                                        .hidden_layer_dense = 5,
                                        .hidden_layer_num   = 2,
                                        .output_layer_dense = 4,
                                        .activation_function        = &ELU,
                                        .output_activation_function = &SoftMax,
                                        .loss_function              = &MSE,
                                        .optimizer_function         = &GradientDescent};
'''
### System Confiurations
'''
Network_Config_t MyNetworkConfig = {.learning_rate = 0.1332,
                                    .dropout = false,
                                    .epochs = 10};
'''

## Functions to use
By calling the "Create_Network()" function after setting all the parameters
'''
DNN_Network *myNetwork = Create_Network(&MyNetworkTopology, &MyNetworkConfig);

'''
This line creating like _Cpp Class_  to your ANN network.
