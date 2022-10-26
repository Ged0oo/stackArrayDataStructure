/*
 * stackArrayDataStructure.c
 *
 * Created: 21 OCT 2022
 * Author : Mohamed Nagy
 */


#include "stackArrayDataStructure.h"


static uint8 StackIsFull(ST_stack_t* stackObj);
static uint8 StackIsEmpty(ST_stack_t* stackObj);


/**
  * @brief  This algorithm creates an empty stack by allocating the head
            structure and the array from dynamic memory.
  * @param  (maxSize) Stack maximum number of elements
  * @param  (ret_status) Status returned while performing this operation
  * @retval Pointer to the allocated stack in the heap
  */
ST_stack_t* CreateStack(uint32 maxSize, EN_stackStatus_t* retStatus)
{
    ST_stack_t* my_stack = NULL;
    if (NULL == retStatus)
    {
        *retStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
        my_stack = NULL;
    }
    else
    {
        /* Allocate the stack in the heap */
        my_stack = (ST_stack_t*)malloc(sizeof(ST_stack_t));
        if (!my_stack)
        {
            *retStatus = STACK_NOK; /* Stack not created successfully */
            my_stack = NULL;
        }
        else
        {
            my_stack->stackTop = -1;          /* Initialize the stack pointer to -1 (empty stack) */
            my_stack->elementCount = 0;       /* Initialize the element counter to 0 (empty stack) */
            my_stack->stackMaxSize = maxSize; /* Initialize the maximum number of elements in the stack */
            my_stack->stackArray = (void**)calloc(my_stack->stackMaxSize, sizeof(void*));
            if (!my_stack->stackArray)
            {
                free(my_stack);  /* Free the stack object as the Array not created successfully */
                my_stack = NULL; /* Array not created successfully */
                *retStatus = STACK_NOK;
            }
            else
            {
                *retStatus = STACK_OK;
            }
        }
    }
    return my_stack;
}


/**
  * @brief  This function releases all memory to the heap.
  * @param  (stackObj) pointer to stack head structure
  * @param  (retStatus) Status returned while performing this operation
  * @retval NULL
  */
ST_stack_t* DestroyStack(ST_stack_t* stackObj, EN_stackStatus_t* retStatus)
{
    if ((NULL == retStatus) || (NULL == stackObj))
    {
        *retStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
    }
    else
    {
        free(stackObj->stackArray); /* Release the Array object */
        free(stackObj); /* Release the stack object */
        *retStatus = STACK_OK;
    }
    return NULL;
}



/**
  * @brief This function pushes an item onto the stack.
  * @param  (stackObj) pointer to stack head structure
  * @param  (itemPtr) pointer to be inserted
  * @retval Status returned while performing this operation
  */
EN_stackStatus_t PushStack(ST_stack_t* stackObj, void* itemPtr)
{
    EN_stackStatus_t StackStatus = STACK_NOK;
    if ((NULL == stackObj) || (NULL == itemPtr))
    {
        StackStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
    }
    else
    {
        if (StackIsFull(stackObj))
        {
            StackStatus = STACK_FULL; /* Stack is full, prevent stack overflow */
        }
        else
        {
            (stackObj->stackTop)++; /* Points to the next element in the stack */
            stackObj->stackArray[stackObj->stackTop] = itemPtr;
            (stackObj->elementCount)++; /* Increment the number of elements in the stack */
            StackStatus = STACK_OK;
        }
    }
    return StackStatus;
}



/**
  * @brief This function pops the item on the top of the stack.
  * @param  (stackObj) pointer to stack head structure
  * @param  (retStatus) Status returned while performing this operation
  * @retval Pointer to user data if successful, NULL if underflow
  */
void* PopStack(ST_stack_t* stackObj, EN_stackStatus_t* retStatus)
{
    void* dataPtrOut = NULL;
    if ((NULL == stackObj) || (NULL == retStatus))
    {
        *retStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
        dataPtrOut = NULL;
    }
    else
    {
        if (StackIsEmpty(stackObj))
        {
            *retStatus = STACK_EMPTY; /* Stack is empty, prevent stack underflow */
            dataPtrOut = NULL;
        }
        else 
        {
            dataPtrOut = stackObj->stackArray[stackObj->stackTop];
            (stackObj->stackTop)--; /* Points to the next element in the stack */
            (stackObj->elementCount)--; /* Decrement the number of elements in the stack */
            *retStatus = STACK_OK;
        }
    }
    return dataPtrOut;
}



/**
  * @brief  This function retrieves the data from the top of the
            stack without changing the stack.
  * @param  (stackObj) pointer to stack head structure
  * @param  (retStatus) Status returned while performing this operation
  * @retval Pointer to user data if successful, NULL if underflow
  */
void* StackTop(ST_stack_t* stackObj, EN_stackStatus_t* retStatus)
{
    void* dataPtrOut = NULL;
    if ((NULL == stackObj) || (NULL == retStatus))
    {
        *retStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
        dataPtrOut = NULL;
    }
    else
    {
        if (StackIsEmpty(stackObj))
        {
            *retStatus = STACK_EMPTY; /* Stack is empty, prevent stack underflow */
            dataPtrOut = NULL;
        }
        else 
        {
            /* Copy the top element to the user */
            dataPtrOut = stackObj->stackArray[stackObj->stackTop];
            *retStatus = STACK_OK;
        }
    }
    return dataPtrOut;
}



/**
  * @brief  Returns number of elements in stack.
  * @param  (stackObj) pointer to stack head structure
  * @param  (stackCount) number of elements in stack.
  * @retval Status returned while performing this operation
  */
EN_stackStatus_t StackCount(ST_stack_t* stackObj, uint32* stackCount)
{
    EN_stackStatus_t StackStatus = STACK_NOK;
    if ((NULL == stackObj) || (NULL == stackCount)) 
    {
        StackStatus = STACK_NULL_POINTER; /* NULL pointer passed to the function */
    }
    else 
    {
        *stackCount = stackObj->elementCount;
        StackStatus = STACK_OK;
    }
    return StackStatus;
}



/**
  * @brief  Returns the stack state empty or not.
  * @param  (stackObj) pointer to stack head structure.
  * @retval Status of the stack empty or not.
  */
static uint8 StackIsEmpty(ST_stack_t* stackObj)
{
    return (stackObj->elementCount == 0);
}



/**
  * @brief  Returns the stack state full or not.
  * @param  (stackObj) pointer to stack head structure.
  * @retval Status of the stack full or not.
  */
static uint8 StackIsFull(ST_stack_t* stackObj) 
{
    return (stackObj->elementCount == stackObj->stackMaxSize);
}

