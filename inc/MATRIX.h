/**
 * @file MATRIX.h
 * @author Mohamed Wx (gtlyco205@gmail.com)
 * @brief Matrix header file
 * @version 0.3
 * @date 2022-06-13
 * 
 * @copyright Copyright Mohamed Wx (c) 2022
 * 
 */
//!=============================> .START
#ifndef _MATRIX_H
#define _MATRIX_H

#ifdef _cplusplus
    extern "C"{
#endif

/*
----------------------------------------------------------------
!-                       DEFINED HEADERS                       -
----------------------------------------------------------------
*/

#include "Global.h"

/*
----------------------------------------------------------------
!-                       DEFINED VARIABLES                     -
----------------------------------------------------------------
*/

// Define strict ranges to prevent virtual memory overflow. (Memory dying)
#define MAX_VECTOR_LEN ((const uint8_t) 200)
#define MAX_MATRIX_ROW ((const uint8_t) 200)
#define MAX_MATRIX_COL ((const uint8_t) 200)

/*
----------------------------------------------------------------
!-                       DEFINED STRUCTS                       -
----------------------------------------------------------------
*/

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



/*
----------------------------------------------------------------
!-                       DEFINED FUNCTIONS                     -
----------------------------------------------------------------
*/

/** @defgroup Matrix Main Functions */
double *VxM_DotProduct(Type_t *, Type_t *);
// void matrix_inverse(Type_t *);
// void vector_inverse(Type_t *);

/** @defgroup Matrix Sub Functions */
void dotProduct_Validity(Type_t *, Type_t *);

#ifdef __cplusplus
    }
#endif
//!=============================> .END
#endif //_MATRIX_H
