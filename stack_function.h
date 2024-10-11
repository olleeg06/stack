#ifndef MOEW
#define MOEW
#include <stdio.h> 

#define NUM_BUCKETS 10000
typedef double stack_elem_t;

enum number_error { 
    ok                = -1, 
    error_ctor        =  0, 
    error_push        =  1, 
    error_pop         =  2, 
    error_assert      =  3, 
    error_empty       =  4, 
    error_canary_stk  =  5,
    error_canary_data =  6
}; 

struct stack_t {
    long long int ded_loh_stk1;
    stack_elem_t *data;
    long int size;
    size_t capacity;
    unsigned long hash;
    long long int ded_loh_stk2;
};


const double poison = 52.333; 
const long long int canary1 = 5233352;
const long long int canary2 = 33352333;

enum number_error StackCtor (struct stack_t* stk, size_t size_capacity); 
enum number_error StackPush (struct stack_t* stk, stack_elem_t value); 
enum number_error StackPop  (struct stack_t* stk, stack_elem_t* x); 
enum number_error StackAssert (struct stack_t* stk, enum number_error error, size_t line, const char * file_name); 
enum number_error StackEmpty (struct stack_t* stk, size_t line, const char * file_name); 

unsigned long hash_func(stack_elem_t *str);

void StackDumb (struct stack_t* stk); 
void StackRealloc (struct stack_t* stk); 



#endif