#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <assert.h> 

#include "stack_function.h"




enum number_error StackCtor (struct stack_t* stk, size_t size_capacity){

    stk->capacity = size_capacity; 
    stk->data = (stack_elem_t*) calloc (stk->capacity, sizeof(stack_elem_t)); 
    stk->size = 0; 
    for (int i = 0; i < stk->capacity; i++){ 
        stk->data[i] = poison; 
    } 
     
    StackAssert (stk, error_ctor, __LINE__);  
    return ok; 
}

enum number_error StackPush (struct stack_t *stk, stack_elem_t value){

    StackAssert (stk, error_push, __LINE__);
    if (stk->size == stk->capacity) 
    { 
        stk->capacity = 2 * (stk->capacity); 
        stk->data = (stack_elem_t*) realloc (stk->data, (stk->capacity) * sizeof(stack_elem_t));
        for (int i = stk->size; i < stk->capacity; i++){ 
            stk->data[i] = poison; 
        } 
    } 
    stk->data[stk->size] = value; 
    stk->size++;
    StackEmpty(stk, __LINE__);
    StackAssert (stk, error_push, __LINE__);
    return ok;
}

enum number_error StackPop (struct stack_t *stk, stack_elem_t *value){

    StackAssert (stk, error_push, __LINE__);  
    StackEmpty (stk, __LINE__); 

    stk->size--; 
    *value = stk->data[stk->size]; 

    printf ("Elem = %0.2f\n", *value); 
    stk->data[stk->size] = poison; 
    if (stk->size < (stk->capacity)/4){ 
        stk->capacity = (stk->capacity) / 4;
    }  
 
    StackAssert (stk, error_pop, __LINE__); 
    return ok; 
}


void StackDumb (struct stack_t* stk){
    printf ("Dump\n"); 
    printf ("Capacity = %lu\n", stk->capacity); 
    printf ("Size = %lld\n", stk->size); 
 
    for (size_t i = 0; i < stk->capacity; i++){ 
        printf ("{%lu} Value = %f\n", i, stk->data[i]); 
    } 
 
    printf("\n\n"); 
    return; 
} 

enum number_error StackAssert (struct stack_t* stk, enum number_error error, size_t line){ 
    int err = 0; 
    if (!err && stk == NULL)       { err = 1;   }
    if (!err && stk->data == NULL) { err = 2;   }
    if (!err && stk->size < 0)     { err = 3;   }
    if (err == 0)                  { return ok; }

    printf ("Code error is {%d}, in StackAssert error is {%d}, in line = %ld\n", error, err, line); 
    StackDumb (stk); 
    return error; 
} 

enum number_error StackEmpty (struct stack_t* stk, size_t line){ 
    if (stk->data[0] == poison){ 
        printf ("Code error is {4} in line = %ld\n", line); 
        StackDumb (stk); 
        assert (0); 
    } 
    return ok; 
}