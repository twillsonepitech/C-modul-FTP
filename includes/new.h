/**
 * @file new.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Main functions of C modular.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdarg.h>
#include "object.h"

Object *new(const Class *class, ...);
Object *va_new(const Class *class, va_list *va_list_args);
void delete(Object *ptr);
