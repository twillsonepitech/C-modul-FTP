/**
 * @file new.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Main functions of C modular.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "object.h"
#include "raise.h"

Object *va_new(const Class *class, va_list *va_list_args)
{
    Class *obj = (Class *)malloc(class->__size__);

    if (NULL == class)
        raise("The class has not be passed.");
    if (NULL == obj)
        raise("Cannot allocate memory for class.");
    if (NULL == memcpy(obj, class, class->__size__))
        raise("Out of memory.");
    if (((Class *)obj)->__ctor__)
        ((Class *)obj)->__ctor__(obj, va_list_args);
    return obj;
}

Object *new(const Class *class, ...)
{
    Object *obj;
    va_list list;

    if (NULL == class)
        raise("The class has not be passed.");
    va_start(list, class);
    obj = va_new(class, &list);
    va_end(list);
    return obj;
}

void delete(Object *ptr)
{
    if (NULL == ptr)
        raise("No object passed.");
    if (((Class *)ptr)->__dtor__)
        ((Class *)ptr)->__dtor__(ptr);
    free(ptr);
}
