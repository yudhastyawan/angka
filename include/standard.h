/**
 * \file standard.h
 * @brief the standard library for reusing the C library.
 * 
 * */

#ifndef __STANDARD_H
#define __STANDARD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief quick version of rand() in C
 * @param min the minimum value
 * @param max the maximum value
 **/
double agx_random(double min, double max);

/**
 * @brief deleting memory in pointer
 * @details it has a similar function with free()
 **/
void agx_data_delete(void *__ptr);

#ifdef __cplusplus
}
#endif

#endif