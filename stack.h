#define MAX_STACK 20

int STACK_SIZE;
int err_flag;

#define MAX_SERR    3
#define SERR_INIT   1
#define SERR_PUSH   2
#define SERR_TOP    3

typedef struct {
  int arr[MAX_STACK];
  int top;
} tStack;

void stackError (int error_code);
void stackInit (tStack* s);
int stackEmpty (const tStack* s);
int stackFull (const tStack* s);
int stackTop (const tStack* s);
int stackTopTerm (tStack* s, int handle);
void stackPop (tStack* s);
void stackPush (tStack* s, int c);
int stackReduce (tStack* s);
