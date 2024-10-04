#include <stdio.h> 
#include <stdlib.h> 

#include "stack_function.h"

stack_t stk = {};


int main(){

    StackCtor (&stk, 1);
    StackPush (&stk, 345);
    StackPush (&stk, 2);
  
    stack_elem_t x = 0;
    //stk.data = NULL;
    StackPop (&stk, &x);
    StackPop (&stk, &x);

}

