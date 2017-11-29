#define max_size 100

typedef char* tklic;
typedef int tid;
typedef char* ttype;
typedef float tdata;
typedef struct thitem{
	tklic klic;
	tid id;
	ttype type;
	tdata data;
	struct thitem* ptnext;
} thitem;

typedef thitem* thtable[max_size];

extern int htsize;

int hashcode (tklic klic);
void inittable (thtable* ptrht);
void tinsert (thtable* ptrht, tklic klic, tdata data,tid id, ttype type);
void tsearch (thtable* ptrht, tklic klic);
void tdelete(thtable* ptrht, tklic klic);
void tclearall (thtable* ptrht);
