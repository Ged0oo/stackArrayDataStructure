/*
 * stackArrayDataStructure.h
 *
 * Created: 21 OCT 2022
 * Author : Mohamed Nagy
 */


#ifndef _STACKARRAYDATASTRUCURE_H
#define _STACKARRAYDATASTRUCURE_H

#include "stdTypes.h"

 /************************************************************************/
 /*                   section: data type declaration                     */
 /************************************************************************/
typedef enum {
    STACK_NOK = 0,     /* Stack operation not performed successfully */
    STACK_OK,          /* Stack operation performed successfully  */
    STACK_FULL,        /* Stack is full */
    STACK_EMPTY,       /* Stack is empty */
    STACK_NULL_POINTER /* NULL pointer passed to the Stack operations */
}EN_stackStatus_t;

typedef struct {
    void** stackArray;    /* Points to the array that allocated in the heap */
    sint32 elementCount;  /* Has the actual number of elements in the stack */
    uint32 stackMaxSize;  /* Has the maximum number of elements in the stack */
    sint32 stackTop;      /* Has the index of the top element in the stack */
}ST_stack_t;



/************************************************************************/
/*                   section: functions prototype                       */
/************************************************************************/
ST_stack_t* CreateStack(uint32 maxSize, EN_stackStatus_t* retStatus);
ST_stack_t* DestroyStack(ST_stack_t* stackObj, EN_stackStatus_t* retStatus);

EN_stackStatus_t PushStack(ST_stack_t* stackObj, void* itemPtr);
EN_stackStatus_t StackCount(ST_stack_t* stackObj, uint32* stackCount);

void* PopStack(ST_stack_t* stackObj, EN_stackStatus_t* retStatus);
void* StackTop(ST_stack_t* stackObj, EN_stackStatus_t* retStatus);

#endif//_STACKARRAYDATASTRUCURE_H