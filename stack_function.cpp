#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <assert.h> 

#include "stack_function.h"




enum number_error StackCtor (struct stack_t* stk, size_t size_capacity){

    stk->capacity = size_capacity; 
    stk->data = (stack_elem_t*) calloc (stk->capacity * sizeof(stack_elem_t) + 2 * sizeof(canary2), 1);
    
    stk->data[0] = canary2;   
    stk->data = stk->data + 1;
    stk->capacity = stk->capacity + 1;

    stk->size = 0; 
    stk->ded_loh_stk1 = canary1;
    stk->ded_loh_stk2 = canary1;
    stk->hash = hash_func(stk->data);
    for (int i = 0; i < stk->capacity; i++){ 
        stk->data[i] = poison; 
    } 
    stk->data[stk->capacity - 1] = canary2;
    stk->hash = hash_func(stk->data);
   
    StackAssert (stk, error_ctor, __LINE__, __FILE__);
    return ok;
}



enum number_error StackPush (struct stack_t *stk, stack_elem_t value){

    StackAssert (stk, error_push, __LINE__, __FILE__);
    if (stk->size == stk->capacity - 1){   
        stk->capacity = 2 * (stk->capacity); 
        
        stk->data = (stack_elem_t*) realloc (stk->data - 1, stk->capacity * sizeof(stack_elem_t) +  sizeof(canary2));
        
        stk->data[0] = canary2;   
        stk->data = stk->data + 1;

        for (int i = stk->size; i < stk->capacity - 1; i++){ 
            stk->data[i] = poison; 
        } 
        stk->data[stk->capacity - 1] = canary2;
    } 
    
    stk->data[stk->size] = value; 
    stk->size++;
    stk->hash = hash_func(stk->data);
    StackEmpty(stk, __LINE__, __FILE__);
    StackAssert (stk, error_push, __LINE__, __FILE__);
    
    return ok;
}

enum number_error StackPop (struct stack_t *stk, stack_elem_t *value){

    StackAssert (stk, error_push, __LINE__, __FILE__);  
    StackEmpty (stk, __LINE__, __FILE__); 
    //StackDumb(stk);
    stk->size--; 
    *value = stk->data[stk->size]; 

    printf ("Elem = %0.2f\n", *value); 
    stk->data[stk->size] = poison; 
    if (stk->size < (stk->capacity) / 4){ 
        stk->capacity = (stk->capacity) / 4;   
        stk->data = (stack_elem_t*) realloc (stk->data - 1, stk->capacity * sizeof(stack_elem_t) +  sizeof(canary2));
        
        stk->data[0] = canary2;   
        stk->data = stk->data + 1;
        stk->data[stk->capacity - 1] = canary2; 
    }  
    stk->hash = hash_func(stk->data);
 
    return ok; 
}


void StackDumb (struct stack_t* stk){
    printf ("Dump\n"); 
    printf ("stk:%p\n", stk);
    printf ("canary_stk_l = %lld, &canary_stk_l = %p\n", stk->ded_loh_stk1, &stk->ded_loh_stk1);
    printf ("size = %ld, &size = %p\n", stk->size, &stk->size); 
    printf ("capacity = %lu, &capacity = %p\n", stk->capacity, &stk->capacity); 
    printf ("canary_stk_r = %lld, &canary_stk_r = %p\n", stk->ded_loh_stk2, &stk->ded_loh_stk2);
    printf ("hash_func = %lu, hash = %lu, &hash = %p\n", hash_func(stk->data), stk->hash, &stk->hash);
    printf ("canary_data_l = %lf, &canary_data_l = %p\n", *(stk->data - 1), stk->data - 1);
    
    for (size_t i = 0; i < stk->capacity; i++){ 
        printf ("{%lu} value = %lf, &value = %p\n", i, stk->data[i], &stk->data[i]); 
    }
 
    printf("\n\n"); 
    return; 
} 

enum number_error StackAssert (struct stack_t* stk, enum number_error error, size_t line, const char * file_name){ 
    int err = 0; 
    if (!err && stk == NULL)                                { err = 1;   }
    if (!err && stk->data == NULL)                          { err = 2;   }
    if (!err && stk->capacity < 1)                          { err = 3;   }
    if (!err && stk->ded_loh_stk1 != canary1)               { err = 4;   }
    if (!err && stk->ded_loh_stk2 != canary1)               { err = 5;   }
    if (!err && (stk->data[-1]) != canary2)                 { err = 6;   }
    if (!err && stk->data[stk->capacity - 1] != canary2)    { err = 7;   }
    if (!err && stk->hash != hash_func(stk->data))          { err = 8;   }
    if (err == 0)                                           { return ok; }

    printf ("Code error is {%d}, in StackAssert err is {%d}, in file = %s, in line = %ld\n", error, err, file_name, line); 
    StackDumb (stk); 
    exit(1);
    return error; 
} 

enum number_error StackEmpty (struct stack_t* stk, size_t line, const char * file_name){ 
    if (stk->data[0] == poison){ 
        printf ("Code error is {4} in file \"%s\" in line = %ld\n", file_name, line); 
        StackDumb (stk); 
        exit(1);
    } 
    return ok; 
}

// Djb2 hash function
unsigned long hash_func(stack_elem_t *str) 
{
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % NUM_BUCKETS;
}