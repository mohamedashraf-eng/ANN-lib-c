//=============================> .INC
#include "Global.h"
//=============================> .DATA




//=============================> .MAIN

int main(void)
{
    // Change terimnal color: GREEN.
    system("COLOR 0A");
    
    
    const uint16_t len = 3;
    Type_t *vector  = create_vector(len, true);

    const uint16_t row = 5, col = 3;
    Type_t *matrix  = create_matrix(row, col, true); 

    // print the vector & the matrix.
    print_vector(vector);
    print_matrix(matrix);

    // perform dot product.
    float *dp = VxM_DotProduct(vector, matrix);

    Type_t *result = create_vector(row, false);

    result->Vector_t.Vector = dp;
    print_vector(result);

    free_vector(result);
    free_vector(vector); 
    free_matrix(matrix);
    free(dp);

    printf("\n");
    return 0;
}

//=============================> .FUNC
