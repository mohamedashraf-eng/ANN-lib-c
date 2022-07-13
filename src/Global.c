/**
 * @file Global.c
 * @author Mohamed Wx (gtlyco205@gmail.com)
 * @brief Global usage functions
 * @version 0.3
 * @date 2022-06-13
 * 
 * @copyright Copyright Mohamed Wx (c) 2022
 * 
 */
//!=============================> .START
#include "Global.h"

#define CURRENT_C "Global.c"
#define CURRENT_H "Global.h"

/*
----------------------------------------------------------------
!-                       DEFINED STRUCTS                       -
----------------------------------------------------------------
*/

Privates_t private = {.range = 10.0f, .factor = 0.1332f, .randoming = true};

/*
----------------------------------------------------------------
!-                       MAIN FUNCTIONS                        -
----------------------------------------------------------------
*/

/**
 * @brief Function to make a 1D array in heap
 * 
 * @param vector_len 
 * @param init 
 * @return Type_t* 
 */
Type_t *create_vector(const uint16_t vector_len, bool init)
{
    // Check if the input length isn't valid.
    if(vector_len <= 0)
        error_exit(CURRENT_C, "VECTOR_LEN:INVALID");

    // Check if input length is greater than the max allowed.
    if(vector_len > MAX_VECTOR_LEN)
        error_exit(CURRENT_C, "VECTOR_LEN:MAX_LEN_IMIT");
   
    // Create vector in the heap.
    Type_t *new_vector = (Type_t *) malloc(sizeof(Type_t));

    if(new_vector == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Modify the new vector parameters.
    // Vector length.
    new_vector->Vector_t.len = vector_len;
    // Vector array.
    new_vector->Vector_t.Vector = (double *) malloc(sizeof(double) * new_vector->Vector_t.len);
    
    if(new_vector->Vector_t.Vector == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Initialize the new vector.
    init ? 
        vector_init(new_vector) : false;

    // Return the created vector.
    return new_vector; 
}//end create_vector.


/**
 * @brief Function to create 2D array in heap.
 *          - Heap visual view:
                nROWS
                [0]=>[0]->[1]->..[m] mCOLS
                [1]=>[0]->[1]->..[m] mCOLS
                [2]=>[0]->[1]->..[m] mCOLS
                .
                .
                [n]=>[0]->[1]->..[m] mCOLS
 * @param row 
 * @param col 
 * @param init 
 * @return Type_t* 
 */
Type_t *create_matrix(const uint16_t row, const uint16_t col, bool init)
{
    // Error Handler.
    // Check if row & col are valid.
    if( (row <= 0) || (col <= 0) )
        error_exit(CURRENT_C, "MATRIX_ROW_COL:INVALID");
    // assert(row > 0); assert(col > 0); // For strictly exit.

    // Check if row & col > MAX.
    if( (row > MAX_MATRIX_ROW) || (col > MAX_MATRIX_COL) )
        error_exit(CURRENT_C, "MATRIX_ROW_COL:MAX_LENGTH_LIMIT");
    // assert(row < MAX_MATRIX_ROW); assert(col < MAX_MATRIX_COL); // For strictly exit.

    // Create the matrix struct
    Type_t *new_matrix = (Type_t *) malloc(sizeof(Type_t));
    if(new_matrix == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Set the matrix parameters.
    new_matrix->Matrix_t.row = row;
    new_matrix->Matrix_t.col = col;

    //printf("\n col: %d", new_matrix->Matrix_t.col);
    //printf("\n row: %d", new_matrix->Matrix_t.row);

    // Allocating the 2d array in heap (matrix)
    new_matrix->Matrix_t.Matrix = (double **) malloc(sizeof(double **) * new_matrix->Matrix_t.row);
    if(new_matrix->Matrix_t.Matrix == NULL)
        error_exit(CURRENT_C, "MALLOC_FAILED:NULL");

    // Start creating the links.
    for(uint16_t i = 0; i < new_matrix->Matrix_t.row; i++)
    {   
        // Allocating N Links (N=col).
        new_matrix->Matrix_t.Matrix[i] = (double *) malloc(sizeof(double) * new_matrix->Matrix_t.col);
        if(new_matrix->Matrix_t.Matrix[i] == NULL)
            error_exit(CURRENT_C, "MALLOC_FAILED:NULL");
    }

    // Initalize the new matrix.
    init ? 
        matrix_init(new_matrix) : false;

    // Return the allocated matrix.
    return new_matrix;

}//end create_matrix.


/**
 * @brief Function to initalzie an 1D array.
 * 
 * @param vector 
 */
void vector_init(Type_t *vector)
{
    // Error Handler.
    // Check if vector struct is valid.
    if(vector == NULL)
        error_exit(CURRENT_C, "VECTOR:NULL"); 
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
        error_exit(CURRENT_C, "VECTOR->VECTOR:NULL");
    // assert(vector->Vector_t.Vector != NULL); // For Strictly exit.

    // Check if vector length isn't valid.
    if(vector->Vector_t.len <= 0)
        error_exit(CURRENT_C, "VECTOR_LEN:INVALID");
    // assert(vector->Vector_t.len > 0) // For strictly exit.

    // Init the array.
    if(private.randoming == true)
        srand(GetTickCount());

    for(uint16_t i = 0; i < vector->Vector_t.len; i++)
    {
        vector->Vector_t.Vector[i] = rand()%private.range * private.factor;
    }
    
    return;
}//end vector_init.

/**
 * @brief Function to init a 2D array.
 * 
 * @param matrix 
 */
void matrix_init(Type_t *matrix)
{
    // Error Handler.
    // Check if matrix struct isn't valid.
    if(matrix == NULL)
        error_exit(CURRENT_C, "MATRIX:NULL");
    // assert(matrix != NULL) // For strictly exit.

    // Check if matrix data is valid.
    if(matrix->Matrix_t.Matrix == NULL)
        error_exit(CURRENT_C, "MATRIX->MATRIX:NULL");
    // assert(matrix->Matrix_t.Matrix != NULL) // For strictly exit.

    // Check matrix elements.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
        error_exit(CURRENT_C, "MATRIX_ROW_COL:INVALID");
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0);  // For strictly exit.

    // Init the matrix.
    if(private.randoming == true)
        srand(GetTickCount());

    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++)
    {
        for(uint16_t j = 0; j < matrix->Matrix_t.col ; j++)
        {
            matrix->Matrix_t.Matrix[i][j] = rand()%private.range * private.factor;
        }
    }

    return;
}//end matrix_init.

/*
----------------------------------------------------------------
!-                       SUB FUNCTIONS                         -
----------------------------------------------------------------
*/

/**
 * @brief Function print 1D array
 * 
 * @param vector 
 */
void print_vector(Type_t *vector)
{
    // Error Handler.
    // Check if vector struct is valid.
    if(vector == NULL)
        error_exit(CURRENT_C, "VECTOR:NULL");
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
        error_exit(CURRENT_C, "Vector->Vector:NULL");
    // assert(vector->Vector_t.Vector != NULL); // For Strictly exit.

    // Check if vector length isn't valid.
    if(vector->Vector_t.len <= 0)
        error_exit(CURRENT_C, "VECTOR_LEN:INVALID");
    // assert(vector->Vector_t.len > 0) // For strictly exit.

    // Print the vector.
    for(uint16_t i = 0; i < vector->Vector_t.len; i++)
    {
        printf("\n%.4f", vector->Vector_t.Vector[i]);
    }
    
    printf("\n");
    return;
}//end print_vector.

/**
 * @brief Function print 2D array
 * 
 * @param matrix 
 */
void print_matrix(Type_t *matrix)
{
    // Error Handler.
    // Check if matrix struct isn't valid.
    if(matrix == NULL)
        error_exit(CURRENT_C, "MATRIX:NULL");
    // assert(matrix != NULL) // For strictly exit.

    // Check if matrix data is valid.
    if(matrix->Matrix_t.Matrix == NULL)
        error_exit(CURRENT_C, "MATRIX->Matrix:NULL");
    // assert(matrix->Matrix_t.Matrix != NULL) // For strictly exit.

    // Check matrix elements.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
     error_exit(CURRENT_C, "MATRIX_COL_ROW:INVALID");
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0);  // For strictly exit.

    // Init the matrix.
    if(private.randoming == true)
        srand(time(NULL));

    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++)
    {
        for(uint16_t j = 0; j < matrix->Matrix_t.col ; j++)
        {
            printf("%.4f ", matrix->Matrix_t.Matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    return;
}//end print_matrix.

/**
 * @brief Function free 1D array
 * 
 * @param vector 
 */
void free_vector(Type_t *vector)
{
    // Error Handeling.
    // Check if vector struct is valid.
    if(vector == NULL)
        error_exit(CURRENT_C, "VECTOR:NULL");
    // assert(vector != NULL); // For strictly exit.

    // Check if vector data is valid.
    if(vector->Vector_t.Vector == NULL)
        error_exit(CURRENT_C, "Vector->Vector:NULL");
    // assert(vector->Vector_t.Vector != NULL); // For strictly exit.

    // Check if length is valid.
    if(vector->Vector_t.len <= 0)
        error_exit(CURRENT_C, "VECTOR_LEN:INVALID");
    // assert(vector->Vector_t.len > 0); // For strictly exit.

    // Free the vector.
    free(vector->Vector_t.Vector);
    // Free the struct.
    free(vector);

    // Indicator message.
    //printf("\n VECTOR_FREE: SUCCESSFUL\n");
    
    return;
}//end free_vector.

/**
 * @brief Function to free 2D array
 * 
 * @param matrix 
 */
void free_matrix(Type_t *matrix)
{
    // Error Handeling.
    // Check if matrix struct is valid.
    if(matrix == NULL)
        error_exit(CURRENT_C, "MATRIX: NULL");
    // assert(matrix != NULL); // For strictly exit.

    // Check the matrix data.
    if(matrix->Matrix_t.Matrix == NULL)
        error_exit(CURRENT_C, "MATRIX->Matrix_t: NULL");
    // assert(matrix->Matrix_t.Matrix != NULL); // For strictly exit.

    // Check the matrix parameters.
    if( (matrix->Matrix_t.row <= 0) || (matrix->Matrix_t.col <= 0) )
        error_exit(CURRENT_C, "MATRIX_COL_ROW: INVALID");
    // assert(matrix->Matrix_t.row > 0); assert(matrix->Matrix_t.col > 0); // For strictly exit.
    
    // Free the heap matrix.
    for(uint16_t i = 0; i < matrix->Matrix_t.row; i++) 
    {
        // Free the mCOLS pointers.
        free(matrix->Matrix_t.Matrix[i]);
    }
    // Free the nROWS double pointers.
    free(matrix->Matrix_t.Matrix);

    // Free the struct.
    free(matrix);

    // Indicator message.
    //printf("\n MATRIX_FREE: SUCCESSFUL\n");

    return;
}//end free_matrix.

//!=============================> .END