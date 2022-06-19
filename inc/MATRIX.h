/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This h file for the linear algebra math operations.
*/
//=============================> .START
#ifndef _MATRIX_H
#define _MATRIX_H
//=============================> .INC
#include "Global.h"
//=============================> .DEFINES

// Define strict ranges to prevent virtual memory overflow. (Memory dying)
#define MAX_VECTOR_LEN ((const uint8_t) 200)
#define MAX_MATRIX_ROW ((const uint8_t) 200)
#define MAX_MATRIX_COL ((const uint8_t) 200)

//=============================> .STRUCTS

// Define abstracted union.
typedef union _Type_t
{
    // Struct to save the vector elements.
    struct 
    {
        uint8_t len;
        
        double *Vector;
    }Vector_t;
    
    // Struct to save the matrix elements.
    struct
    {
        uint8_t row; 
        uint8_t col;
        
        double **Matrix;
    }Matrix_t;
    
}Type_t; // End Union. (Type_t)



//=============================> .FUNC

// Function to perform the dot product.
double *VxM_DotProduct(Type_t *, Type_t *);
// void matrix_inverse(Type_t *);
// void vector_inverse(Type_t *);

void dotProduct_Validity(Type_t *, Type_t *);
//=============================> .END
#endif //_MATRIX_H
