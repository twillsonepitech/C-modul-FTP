/**
 * @file raise.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Define that handle error output
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define raise(msg)                                                  \
    do {                                                            \
        fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, msg);   \
        abort();                                                    \
    } while(0);

#define error(msg, return_code)                                     \
    do {                                                            \
        fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, msg);   \
        return (return_code);                                       \
    } while(0);
