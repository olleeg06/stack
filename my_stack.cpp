#include <stdio.h> 
#include <stdlib.h> 

#include "stack_function.h"




int main(){
    stack_t stk = {};
    StackCtor (&stk, 1);
    
    StackPush (&stk, 345);
    StackPush (&stk, 2);
    StackPush (&stk, 3);
    StackPush (&stk, 4);
    StackPush (&stk, 5);
    StackPush (&stk, 6);
    StackPush (&stk, 7);
    StackPush (&stk, 8);
    StackPush (&stk, 9);
    StackPush (&stk, 10);
    StackPush (&stk, 11);

    stack_elem_t x = 0;

    StackPop (&stk, &x);

    StackPop (&stk, &x);
    StackPop (&stk, &x);
    StackPop (&stk, &x);
    StackPop (&stk, &x);
    stk.data[4] = 52;
    StackPop (&stk, &x);
    StackPop (&stk, &x);
    
    StackPop (&stk, &x);
    StackPop (&stk, &x);
    StackPop (&stk, &x);
    StackPop (&stk, &x);



    



}

