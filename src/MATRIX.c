/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This c file contains the global general use functions.
*/
//=============================> .START
//=============================> .INC
#include "../inc/Global.h"
//=============================> .FUNC

// Function to perform the dot product.
//float *Matrix_X_Vector(Type_t *, Type_t *);

//=============================> .IMP

// Function to multiply Vetor[n]xM[n][m].
/*
- Quick Math Recap:
[1, 2, 3][2] => [(1*2) + (2*4) + (3*8)] = [X] 
[2, 3, 4][4] => [(2*2) + (3*4) + (4*8)] = [Y]
[3, 5, 6][8] => [(3*2) + (5*4) + (6*8)] = [Z]

- Data Block:
    (Hidden_Layer[LAYER]->Vector * Weights[LAYER]->Matrix) = HIDDEN_LAYER[LAYER->NEXT]->Vector.
*/
float *VxM_DotProduct(Type_t *vector, Type_t *matrix)
{
    // - Error Handeling:
    
    // Check if ethier the Vector or the Matrix is NULL.
    if( (vector == NULL) || (matrix == NULL) )
    {printf("\n MATRIX.C|ERROR. VECTOR, MATRIX: NULL\n"); exit(-1);}
    // assert(vector != NULL); assert(matrix != NULL); // For strictly exit.
    
    // Data Checking.
    // 1- Check the vector elements.
    // Check the vector data.
    if((vector->Vector_t.Vector) == NULL)
    {printf("\n MATRIX.C|ERROR. VECTOR: NULL\n"); exit(-1);}
    // assert(vector->Vector != NULL); // For strictly exit.
    
    // Check the vector length & stricts.
    if(vector->Vector_t.len <= 0)
    {printf("\n MATRIX.C|ERROR. VECTOR LEN\n"); exit(-1);}
    // assert(vector->len > 0) // For strictly exit.
    
    // Check the vector length (MAX_VECTOR_LENGTH)
    if(vector->Vector_t.len > MAX_VECTOR_LEN)
    {printf("\n MATRIX.C|ERROR. VECTOR LEN > MAX_VECTOR_LEN\n"); exit(-1);}
    // assert(vector->len <= MAX_VECTOR_LEN); // For strictly exit.
    
    // 2- Check the matrix elements.
    if((matrix->Matrix_t.Matrix) == NULL)
    {printf("\n MATRIX.C|ERROR. MATRIX: NULL\n"); exit(-1);}
    // assert(matrix->Matrix != NULL) // For strictly exit.
    
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
    {printf("\n MATRIX.C|ERROR. MATRIX_COL_ROW\n"); exit(-1);}
    // assert(matrix->row > 0); assert(matrix->col > 0); // For strictly exit.
    
    if( (matrix->Matrix_t.row > MAX_MATRIX_ROW) || (matrix->Matrix_t.col > MAX_MATRIX_COL) )
    {printf("\n MATRIX.C|ERROR. MATRIX_COL_ROW > MAX_STRICTS\n"); exit(-1);}
    // assert(matrix->row < MAX_MATRIX_ROW); assert(matrix->col < MAX_MATRIX_COL); // For strictly exit.
    
    // Dot product math validity conditions.
    if(matrix->Matrix_t.col != vector->Vector_t.len)
    {printf("\n MATRIX.C|ERROR. VECTOR[LEN] != MATRIX[COL]"); exit(-1);}
    // assert(matrix->col == vector->len); // For strictly exit.
    
    
    // Allocating heap memory for the result vector.
    float *vector_result = (float *) malloc(sizeof(float) * matrix->Matrix_t.row);
    //static vector_result[vector->len];
    
    /*
        // Allocate memory for the union (New Vector)
        Type_t *vector_result = (Type_t *) malloc(sizeof(Type_t));
        
        // Set the new vector parameters.
        vector_result->len = vector->len;
        // Allocacte memory for the Vector data.
        vector_result->Vector = (float *) malloc(sizeof(float) * vector_result->len);
        
    */
    
    float sum = 0.0;
    
    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++)
    {
        for(uint16_t j = 0; j < matrix->Matrix_t.col; j++)
        {
            // Get the dot product of first row.
            sum += matrix->Matrix_t.Matrix[i][j] * vector->Vector_t.Vector[j];
        }
        // Store the sum in first row of result vector.
        vector_result[i] = sum;
        // Restart the sum for the next products.
        sum = 0.0;
    }
    
    // Return the result vector as union.
    return vector_result;
}//end Matrix_X_Vector.
