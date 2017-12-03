#include "symtable.h"

int htsize=max_size;

int hashCode(tklic klic){
int returnval=1;
int kliclen=strlen(klic);
for(int i=0;i<kliclen;i++)
{
  returnval+=klic[i];
}
return(returnval%htsize);
}

void initTable(thtable* ptrht){
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

void tInsert (thtable* ptrht, tklic klic, tdata data,tid id, ttype type){
  int pomocna=hashCode(klic);
  thitem *prvek=tSearch(ptrht,klic);
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
      (*ptrht)[pomocna]->type=type;
      (*ptrht)[pomocna]->ptnext=NULL;
    }
  }
  else
  {
    if(((prvek=tSearch(ptrht,klic))!=NULL))
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

thitem *tSearch (thtable* ptrht, tklic klic){
  int pomocna=hashCode(klic);
  thitem* prvek=(*ptrht)[pomocna];
  if((ptrht)==NULL || prvek==NULL)
  {
    return NULL;
  }else{
    while(prvek!=NULL)
    {
      if(!strcmp(prvek->klic, klic))
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

void tDelete(thtable* ptrht, tklic klic){
  if((*ptrht)==NULL)
  {
    return;
  }
  thitem *prvek,*predchozi;
  prvek=NULL;
  predchozi=NULL;
  if((*ptrht)[hashCode(klic)]!=NULL){
    prvek=(*ptrht)[hashCode(klic)];
    while (prvek!=NULL)
    {
      if(prvek->klic==klic)
      {
        if(predchozi!=NULL)
        {
          predchozi->ptnext=prvek->ptnext;
        }
        if(prvek==(*ptrht)[hashCode(klic)])
        {
          (*ptrht)[hashCode(klic)]=prvek->ptnext;
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

void tClearall(thtable* ptrht){
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
