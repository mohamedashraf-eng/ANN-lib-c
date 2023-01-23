/**
 * @file Global.h
 * @author Mohamed Wx (gtlyco205@gmail.com)
 * @brief Global functions header file.
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright Mohamed Wx (c) 2022
 * 
 */
//!=============================> .START
#ifndef _GLOBAL_H
#define _GLOBAL_H

#ifdef _cplusplus
    extern "C"{
#endif

/*
----------------------------------------------------------------
!-                       INCLUDED HEADERS                      -
----------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <assert.h>
#include <time.h>
//#include <crtdbg>

//====> Made Headers.
#include "MATRIX.h"
#include "ANN.h"

/*
----------------------------------------------------------------
!-                       DEFINED STRUCTS                       -
----------------------------------------------------------------
*/

// Private struct for private variables.

/**
 * @brief Struct for the private variables
 * 
 */
typedef struct _Private_t
{
    // Used for the init range & double factor & randomizing.
    const uint16_t range;
    const double factor;
    const bool randoming;
    
    // const uint16_t x, y, z; // For general purpose using.
}Privates_t;

/*
----------------------------------------------------------------
!-                       DEFINED VARIABLES                     -
----------------------------------------------------------------
*/

/**
 * @brief Standard error macro function for error handeling.
 * 
 */
#define error_exit(CURRENT_FILE, ERROR_TYPE) \
({fprintf(stderr, "ERROR (File: %s -- Function: %s -- Line: %d -- Type: %s)", \
                          __FILE__,__func__,__LINE__,ERROR_TYPE); \
                          exit(-1);}) 

/**
 * @brief Standard macro function for unimplemented functions
 * 
 */
#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)               
                                    
/*
----------------------------------------------------------------
!-                       DEFINED FUNCTIONS                     -
----------------------------------------------------------------
*/

/** @defgroup Global Usage Main Functions */
void vector_init(Type_t *);
void matrix_init(Type_t *);
void print_vector(Type_t *);
void print_matrix(Type_t *);

Type_t *create_vector(const uint16_t, bool );
Type_t *create_matrix(const uint16_t , const uint16_t, bool );

void free_vector(Type_t *);
void free_matrix(Type_t *);

//uint16_t get_vector_length(double *);

//void mallocValidity(void *);

#ifdef __cplusplus
    }
#endif
//!=============================> .END
#endif //_GLOBAL_H
