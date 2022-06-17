/*
    Author: Mohamed Wx
    Date: 6/13/2022
    Why : This h file for the global general use functions.
*/
//=============================> .START
#ifndef _GLOBAL_H
#define _GLOBAL_H
//=============================> .INC
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

//====> Made Headers.
#include "MATRIX.h"
#include "ANN.h"
//=============================> .STRUCTS

// Private struct for private variables.
typedef struct _Private_t
{
    // Used for the init range & float factor & randomizing.
    const uint16_t range;
    const float    factor;
    bool randoming;
    
    // const uint16_t x, y, z; // For general purpose using.
}Privates_t;

//=============================> .DEFINES

//=============================> .FUNC

void vector_init(Type_t *);
void matrix_init(Type_t *);
void print_vector(Type_t *);
void print_matrix(Type_t *);
Type_t *create_vector(const uint16_t, bool );
Type_t *create_matrix(const uint16_t , const uint16_t, bool );

void free_vector(Type_t *);
void free_matrix(Type_t *);

//void mallocValidity(void *);
void error_exit(const char *, const char *);

//=============================> .END
#endif //_GLOBAL_H
