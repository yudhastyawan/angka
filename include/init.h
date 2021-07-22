/**
 * \file init.h
 * @brief the standard library for manipulating C data types.
 * 
 * */

#ifndef __INIT_H
#define __INIT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief boolean
 **/
enum e_bool {FALSE, TRUE};

/**
 * @brief a struct for slicing @ref AgxMatrix and @ref AgxVector data
 * @details it is used as a typedef for @ref AgxSlice
 * @warning it is still not implementing yet.
 **/
typedef struct s_slice {
    /// the begin of value
    int start;
    /// the interval value
    int step;
    /// the end of value
    int stop;
} AgxSlice;

/**
 * @defgroup printvalue a quick print of value
 * @brief a quick function of printing a value instead of using printf()
 * @{
 **/
/**
 * @brief print an integer value
 * @param val
 * @details example:
 * @code
 * agx_print_integer(5);
 * @endcode
 * output:
 * @code {.sh}
 * 5
 * @endcode
 **/
void *agx_print_integer(int val);

/**
 * @brief print a double value
 * @param val
 * @details example:
 * @code
 * agx_print_double(5.);
 * @endcode
 * output:
 * @code {.sh}
 * 5.0000
 * @endcode
 **/
void *agx_print_double(double val);

/**
 * @brief print a string (an array of character)
 * @param val
 * @details example:
 * @code
 * agx_print_string("hello world");
 * @endcode
 * output:
 * @code {.sh}
 * hello world
 * @endcode
 **/
void *agx_print_string(char *val);
/**@}**/

/**
 * @defgroup stringlength counting the length of a C data types string
 * @{
 **/
/**
 * @brief count the string length of an integer value
 * @param val
 * @details usage:
 * @code
 * int len;
 * len = agx_string_length_integer(5);
 * @endcode
 **/
int agx_string_length_integer(int val);

/**
 * @brief count the string length of a string
 * @param str
 * @details usage:
 * @code
 * int len;
 * len = agx_string_length_string("hello world");
 * @endcode
 **/
int agx_string_length_string(char *str);

/**
 * @brief count the string length of a double value
 * @param val
 * @details usage:
 * @code
 * int len;
 * len = agx_string_length_double(8.5);
 * @endcode
 **/
int agx_string_length_double(double val);
/**@}**/

/**
 * @brief create a string from double using special format
 * @param fmt format style of double
 * @param val double value
 * @details usage:
 * @code
 * char *str;
 * str = agx_string_from_double_set("%.2f",7.897);
 * @endcode
 **/
char *agx_string_from_double_set(char *fmt, double val);

/**
 * @brief create a string from integer
 * @param val
 * @details usage:
 * @code
 * char *str;
 * str = agx_string_from_integer(3);
 * @endcode
 **/
char *agx_string_from_integer(int val);

/**
 * @brief appending the existing string with an integer value
 * @param[out] target the string target
 * @param[in] val the input value
 * @param[in] isInitial boolean value, TRUE if using copy, not concatenate
 **/
void *agx_string_append_integer(char *target, int val, int isInitial);

/**
 * @brief create a string from double
 * @param val double value
 * @details usage:
 * @code
 * char *str;
 * str = agx_string_from_double(7.897);
 * @endcode
 **/
char *agx_string_from_double(double val);

/**
 * @brief appending the existing string with an double value
 * @param[out] target the string target
 * @param[in] val the input value
 * @param[in] isInitial boolean value, TRUE if using copy, not concatenate
 **/
void *agx_string_append_double(char *target, double val, int isInitial);

/**
 * @brief print some values in variant formats
 * @param inbetween define string between values, such as newline "\n" or space " "
 * @param end define string after the end value, such as newline "\n"
 * @param fmt format style for all, for the example "fddcss" -> double "f", string "s", char "c", and integer "d"
 * @param args(...) all values as order, such as: 5, "hello", 2.7
 **/
void *agx_print_values(char *inbetween, char *end, char *fmt, ...);

/**
 * @brief the quick function of @ref agx_print_values using inbetween = " ", and end = "\n"
 **/
void *agx_print_values_space(char *fmt, ...);

/**
 * @brief the quick function of @ref agx_print_values using inbetween = "\n", and end = " "
 **/
void *agx_print_values_new_line(char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif