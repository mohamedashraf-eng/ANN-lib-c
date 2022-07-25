# Open_Source_ANN_In_C
## About Library
This library is essentialy made for Embedded Machine Learning. It's based on memory management (Not fully secured yet).
____

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
____

# How to use
## Setting your network parameters
### Network Topology
```C
Network_Topology_t MyNetworkTopology = {.input_layer_dense  = 2, 
                                        .hidden_layer_dense = 5,
                                        .hidden_layer_num   = 2,
                                        .output_layer_dense = 4,
                                        .activation_function        = &ELU,
                                        .output_activation_function = &SoftMax,
                                        .loss_function              = &MSE,
                                        .optimizer_function         = &GradientDescent};
```
### System Confiurations
```C
Network_Config_t MyNetworkConfig = {.learning_rate = 0.1332,
                                    .dropout = false,
                                    .epochs = 10};
```

## Functions to use
By calling the "Create_Network()" function after setting all the parameters
```C
DNN_Network *myNetwork = Create_Network(&MyNetworkTopology, &MyNetworkConfig);
```
This line creating like _Cpp Class_  to your ANN network.

After creating your network with your parameters. To feed forward through the network
```C
forward_propagation(myNetwork);
```
This line call the forward propagation algorithm to your created network

____
## Useful resources
* [Neural Networks](https://www.youtube.com/watch?v=Ih5Mr93E-2c&t=2910s).
* [Backward Propagation](https://www.youtube.com/watch?v=nz3NYD73H6E).
* [Algorithms](https://rimstar.org/science_electronics_projects/backpropagation_neural_network_software_3_layer.htm).
* [Visual](https://playground.tensorflow.org/#activation=tanh&batchSize=10&dataset=circle&regDataset=reg-plane&learningRate=0.03&regularizationRate=0&noise=0&networkShape=4,2&seed=0.46243&showTestData=false&discretize=false&percTrainData=50&x=true&y=true&xTimesY=false&xSquared=false&ySquared=false&cosX=false&sinX=false&cosY=false&sinY=false&collectStats=false&problem=classification&initZero=false&hideText=false).
