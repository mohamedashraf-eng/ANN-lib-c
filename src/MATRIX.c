/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This c file contains the global general use functions.
*/
//=============================> .START
//=============================> .INC
#include "Global.h"

#define CURRENT_H "MATRIX.H"
#define CURRENT_C "MATRIX.C"
//=============================> .FUNC

// Function to perform the dot product.
//double *Matrix_X_Vector(Type_t *, Type_t *);

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
double *VxM_DotProduct(Type_t *vector, Type_t *matrix)
{
    // Error handeling function.
    dotProduct_Validity(vector, matrix);
    
    // Allocating heap memory for the result vector.
    double *vector_result = (double *) malloc(sizeof(double) * matrix->Matrix_t.row);
    //static vector_result[vector->len];
    
    /*
        // Allocate memory for the union (New Vector)
        Type_t *vector_result = (Type_t *) malloc(sizeof(Type_t));
        
        // Set the new vector parameters.
        vector_result->len = vector->len;
        // Allocacte memory for the Vector data.
        vector_result->Vector = (double *) malloc(sizeof(double) * vector_result->len);
        
    */
    
    double sum = 0.0;
    
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

//====================================> [SUB FUNCTIONS]
// Sub function for error handeling.
void dotProduct_Validity(Type_t *vector, Type_t *matrix)
{
    // - Error Handeling:
    // Check if ethier the Vector or the Matrix is NULL.
    if( (vector == NULL) || (matrix == NULL) )
        error_exit(CURRENT_C, "VECTOR_MATRIX:NULL");
    // assert(vector != NULL); assert(matrix != NULL); // For strictly exit.
    
    // Data Checking.
    // 1- Check the vector elements.
    // Check the vector data.
    if((vector->Vector_t.Vector) == NULL)
        error_exit(CURRENT_C, "VECTOR->VECTOR:NULL");
    // assert(vector->Vector != NULL); // For strictly exit.
    
    // Check the vector length & stricts.
    if(vector->Vector_t.len <= 0)
    error_exit(CURRENT_C, "VECTOR_LEN:INVALID");
    // assert(vector->len > 0) // For strictly exit.
    
    // Check the vector length (MAX_VECTOR_LENGTH)
    if(vector->Vector_t.len > MAX_VECTOR_LEN)
        error_exit(CURRENT_C, "VECTOR_LEN:MAX_LIMIT");
    // assert(vector->len <= MAX_VECTOR_LEN); // For strictly exit.
    
    // 2- Check the matrix elements.
    if((matrix->Matrix_t.Matrix) == NULL)
        error_exit(CURRENT_C, "MATRIX->MATRIX:NULL");
    // assert(matrix->Matrix != NULL) // For strictly exit.
    
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
        error_exit(CURRENT_C, "MATRIX_ROW_COL:INVALID");
    // assert(matrix->row > 0); assert(matrix->col > 0); // For strictly exit.
    
    if( (matrix->Matrix_t.row > MAX_MATRIX_ROW) || (matrix->Matrix_t.col > MAX_MATRIX_COL) )
        error_exit(CURRENT_C, "MATRIX_ROW_COL:MAX_LIMIT");
    // assert(matrix->row < MAX_MATRIX_ROW); assert(matrix->col < MAX_MATRIX_COL); // For strictly exit.
    
    // Dot product math validity conditions.
    if(matrix->Matrix_t.col != vector->Vector_t.len)
        error_exit(CURRENT_C, "VECTOR_LEN_MATRIX_COL:INVALID");
    // assert(matrix->col == vector->len); // For strictly exit.
}//end dotProduct_Validity.