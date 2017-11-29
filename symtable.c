#include <stdio.h>
#include <stdlib.h>
#include <symtable.h>

int htsize=max_size;

int hashcode(tklic klic){
int returnval=1;
int kliclen=strlen(klic);
for(int i=0;i<kliclen;i++);
{
  returnval+=klic[i];
}
return(returnval%htsize);
}

void inittable(thtable* ptrht);{
if ((*ptrht)!=NULL)
{
  for(int i=0;i<max_size;++i)
  {
    (*ptrht)[i]=NULL;
  }
  }else
  {
    return;
  }
}

void tinsert (thtable* ptrht, tklic klic, tdata data,tid id, ttype type){
int pomocna=hashcode(klic);
thitem *prvek=htsearch(ptrht,klic);
if(prvek==NULL)
{
  if ((*ptrht)[pomocna]!=NULL)
  {
    prvek=malloc(sizeof(thtable));
    prvek->klic=klic;
    prvek->data=data;
    prvek->id=id;
    prvek->type=type;
    prvek->ptnext=NULL;
    (*ptrht)[pomocna]=prvek;
  }
  else
  {
    (*ptrht)[pomocna]=malloc(sizeof(thtable));
    (*ptrht)[pomocna]->klic=klic;
    (*ptrht)[pomocna]->id=id;
    (*ptrht)[pomocna]->data=data;
    (*ptrht)[pomocna]->type=type
    (*ptrht)[pomocna]->ptrnext=NULL;
  }
}
else
{
  if((prvek=tsearch(ptrht,klic)!=NULL))
  {
    thitem *prvek2;
    prvek2=(*ptrht)[pomocna];
    while(prvek2!=NULL){
      if(prvek2->klic==klic)
      {
        prvek2->data=data;
        return;
      }
      prvek2=prvek2->ptnext;
    }
  }
}
}

void tsearch (thtable* ptrht, tklic klic){
int pomocna=hashcode(klic);
thitem* prvek=(*ptrht)[pomocna];
if((ptrht)==NULL || prvek==NULL)
{
  return NULL;
}else{
while(prvek!=NULL)
{
  if(prvek->klic==klic)
  {
    return prvek;
  }
  else{
    prvek=prvek->ptnext;
  }
}
return NULL;
}
return NULL;
}

void tdelete(thtable* ptrht, tklic klic){
if((*ptrht)==NULL)
{
  return;
}
thitem *prvek,*predchozi;
prvek=NULL;
predchozi=NULL;
if((*ptrht)[hashcode(key)]!=NULL){
  prvek=(*ptrht)[hashCode(key)];
  while (prvek!=NULL)
  {
    if(prvek->klic==klic)
    {
      if(predchozi!=NULL)
      {
        predchozi->ptnext=prvek->ptnext;
      }
      if(prvek==(*ptrht)[hashCode(key)])
      {
        (*ptrht)[hashCode(key)]=prvek->ptnext;
      }
      free(prvek);
      prvek=NULL;
      return;
    }
    else
    {
      predchozi=prvek;
      prvek=prvek->ptnext;
    }
  }
}
}

void tclearall(thtable* ptrht){
if((*ptrht)==NULL)
{
  return;
}
else
{
  thitem *prvek;
for(int i=0;i<max_size;i++)
{
  while((*ptrht)[i]!=NULL)
  {
    prvek=(*ptrht)[i];
    (*ptrht)[i]=(*ptrht)[i]->ptnext;
    free(prvek);
  }
  (*ptrht)[i]=NULL;
}
}
}
