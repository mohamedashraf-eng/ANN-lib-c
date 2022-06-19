//=============================> .INC
#include "Global.h"
//=============================> .DATA




//=============================> .MAIN
Network_Topology_t MyNetworkTopology = {.input_layer_dense  = 2, 
                                        .hidden_layer_dense = 5,
                                        .hidden_layer_num   = 2,
                                        .output_layer_dense = 4,
                                        .activation_function        = &ELU,
                                        .output_activation_function = &SoftMax,
                                        .loss_function              = &SquareError,
                                        .optimizer_function         = &GradientDescent};

Network_Config_t MyNetworkConfig = {.learning_rate = 0.1332,
                                    .dropout = false,
                                    .epochs = 10};


int main(void)
{
    // Change terimnal color: GREEN.
    system("COLOR 0A");
    
    
    DNN_Network *myNetwork = Create_Network(&MyNetworkTopology, &MyNetworkConfig);

    print_network(myNetwork);

    forward_propagation(myNetwork);

    print_network(myNetwork);

    printf("\n");
    return 0;
}

//=============================> .FUNC
