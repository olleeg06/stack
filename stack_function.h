#ifndef MOEW
#define MOEW
#include <stdio.h> 

typedef double stack_elem_t;

enum number_error { 
    ok               = -1, 
    error_ctor       =  0, 
    error_push       =  1, 
    error_pop        =  2, 
    error_assert     =  3, 
    error_empty      =  4, 
}; 

struct stack_t {
    long long ded_loh;
    stack_elem_t *data;
    size_t size;
    size_t capacity;
    long long ded_loh;
};


const double poison = 52.333; 


enum number_error StackCtor (struct stack_t* stk, size_t size_capacity); 
enum number_error StackPush (struct stack_t* stk, stack_elem_t value); 
enum number_error StackPop  (struct stack_t* stk, stack_elem_t* x); 
enum number_error StackAssert (struct stack_t* stk, enum number_error error, size_t line); 
enum number_error StackEmpty (struct stack_t* stk, size_t line); 
void StackDumb (struct stack_t* stk); 
void StackRealloc (struct stack_t* stk); 



#endif