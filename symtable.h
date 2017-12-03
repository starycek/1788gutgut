/*

Projekt z předmětů IFJ a IAL
Překladač jazyka IFJ17

symtable.h

Autoři:

Daniel Poisl (xpoisl00)
Daniel Švub (xsvubd00)

*/

#define max_size 100

typedef char* tklic;
typedef char* tid;
typedef int ttype;
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

int hashCode (tklic klic);
void initTable (thtable* ptrht);
void tInsert (thtable* ptrht, tklic klic, tdata data, tid id, ttype type);
thitem *tSearch (thtable* ptrht, tklic klic);
void tDelete(thtable* ptrht, tklic klic);
void tClearall (thtable* ptrht);
