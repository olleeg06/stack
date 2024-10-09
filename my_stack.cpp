#include <stdio.h> 
#include <stdlib.h> 

#include "stack_function.h"




int main(){
    stack_t stk = {};
    StackCtor (&stk, 1);
    
    StackPush (&stk, 345);
    StackPush (&stk, 2);
    StackPush (&stk, 3);

    stack_elem_t x = 0;

    StackPop (&stk, &x);

}

