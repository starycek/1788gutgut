/*

Projekt z předmětů IFJ a IAL
Překladač jazyka IFJ17

stack.c

Autoři:

Daniel Švub (xsvubd00)

*/

#include "stack.h"

int STACK_SIZE = MAX_STACK;

void stackError ( int error_code ){
  static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
  if ( error_code <= 0 || error_code > MAX_SERR ) error_code = 0;
  printf ( "%s\n", SERR_STRINGS[error_code] );
  err_flag = 1;
}

void stackInit ( tStack* s ) {
  if(s == NULL) stackError(SERR_INIT);
  else s -> top = 0;
}

int stackEmpty (const tStack* s) {
  return(s -> top == 0);
}

int stackFull (const tStack* s) {
  return(s -> top == (STACK_SIZE));
}

int stackTop (const tStack* s) {
  if(stackEmpty(s)) stackError(SERR_TOP);
  else return s -> arr[s -> top];
  return 99;
}

int stackTopTerm (tStack* s, int handle){
  tStack *temp = malloc(sizeof(tStack));
  stackInit(temp);
  int top = stackTop(s);
  while(top == PRE_NON){
    stackPush(temp, top);
    stackPop(s);
    top = stackTop(s);
  }
  if(handle) stackPush(s, PRE_LEFT);
  while(!stackEmpty(temp)){
    stackPush(s, stackTop(temp));
    stackPop(temp);
  }
  free(temp);
  return top;
}


void stackPop (tStack* s) {
  if(!stackEmpty(s)) s -> top--;
}


void stackPush (tStack* s, int c) {
  if(stackFull(s)) stackError(SERR_PUSH);
  else s -> arr[++s -> top] = c;
}


int stackReduce (tStack* s){
  tStack *temp = malloc(sizeof(tStack));
  stackInit(temp);
  int top = stackTop(s); // Hodnota na vrcholu
  int prev = 10; // Předchozí hodnota na vrcholu
  while((top != PRE_LEFT) && (top != PRE_END)){ // Redukce
    if(((top < 4) && (prev == 8)) || ((prev < 4) && (top == 8)) || ((prev == 5) && (top == 8)) || ((prev < 8) && (top == 4)) || (top == 6) || ((prev == 10) && (top == 8))){ // Ověření pravidel PSA
      stackPush(temp, top);
      stackPop(s);
      prev = top;
      top = stackTop(s);
    } else {
      free(temp);
      return FALSE;
    }
  }
  free(temp);
  if((top == PRE_LEFT) && (prev > 3)){ // Korektní začátek výrazu
    stackPop(s);
    stackPush(s, PRE_NON);
    return TRUE;
  } else return FALSE;
}
