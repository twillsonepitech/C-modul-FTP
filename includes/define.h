/**
 * @file define.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Define, constant that are used for return value or check function return.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS    (0)
#endif // EXIT_SUCCESS
#if !defined(EXIT_FAILURE)
#define EXIT_FAILURE    (1)
#endif // EXIT_FAILURE

#define EXIT_FAILURE_EPI    (84)
#define FUNCTION_RETURN_ERROR   (-1)

#define NUMBER_OF_ARGUMENTS_HELP    (2)
#define NUMBER_OF_ARGUMENTS (3)
#define HELP_INDEX  (1)
#define PORT_INDEX  (1)
#define PATH_INDEX  (2)
#define INIT_INTEGER    (0)
#define INIT_POINTER    (NULL)

#define sizeof_array(array) (sizeof(array) / sizeof(array[0]))

static const enum return_code_e {
    SUCCESS,
    FAILURE,
} return_code_e;
