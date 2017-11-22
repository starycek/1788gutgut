#include "scanner.h"
#include "string.h"
#include "funkce.c"
//#include "parser.c"
//#include "parser.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


FILE *source;
int GetNextToken(){
char c;
int state=0;
int radek=1;
int i=0;
token[i]='\0';
while(1){
  c=getc(source);
  if(feof(source)){

    return 0;
  }
  if (c=='\n')
    radek++;

    switch(state){
  case 0:
    if (isspace(c)){
      state=0;
    }
    else if(c=='/'){
      token[i]=c;
      i++;
      return DOUBDIV;
    }
    else if(isalpha(c)||c=='_'){
      token[i]=c;
      i++;
      state=2;
    }
    else if(isdigit(c)){
      token[i]=c;
      i++;
      state=3;
    }
    else if (c=='-'){
      token[i]=c;
      i++;
      return SUB;
    }
    else if (c=='\\'){
      token[i]=c;
      i++;
      state=1;
    }
      else if (c=='*'){
      token[i]=c;
      i++;
      return MULT;
    }
      else if (c=='+'){
      token[i]=c;
      i++;
      return ADD;
    }
      else if (c=='!'){
      token[i]=c;
      i++;
      return STRINGSTART;
    }
      else if (c=='='){
      token[i]=c;
      i++;
      return EQL;
    }
      else if(c=='>'){
      token[i]=c;
      i++;
      if((c=getc(source))=='='){
        token[i]=c;
        i++;
        return GREQ;
      } else{
      return GREATR;
      }
      }
      else if(c=='<'){
        token[i]=c;
        i++;
      if((c=getc(source))=='='){
        token[i]=c;
        i++;
        return LESEQ;
      } else if((c=getc(source))=='>'){
        token[i]=c;
        i++;
        return DIFFERENT;
      }else{
      return LESSER;
      }
    }
    else if(c==','){
      token[i]=c;
      i++;
      return COMM;
    }
    else if(c==';'){
      token[i]=c;
      i++;
      return SEMICOL;
    }
    else if(c==')'){
      token[i]=c;
      i++;
      return RIGHTBRAC;
    }
    else if(c=='('){
      token[i]=c;
      i++;
      return LEFTBRAC;
      }
    else if(c=='"'){
      token[i]=c;
      i++;
      state=4;
    }
    else{
      return 1;
    }
  break;

  case 1:
    if(c=='\''){
      token[i]=c;
      i++;
      state=6;
    }else if(isdigit(c)){
    ungetc(c,source);
    return INTDIV;
    }else{
    return 1;
    }
    break;
  case 2:
    if(isalnum(c) || c=='_'){
      token[i]=c;
      i++;
      break;
    }else{
      token[i]=c;
      i++;
    if(strcmp(token,"as")==0){
      return AS;
    }else if(strcmp(token,"asc")==0){
      return ASC;
    }else if(strcmp(token,"declare")==0){
      return DECLARE;
    }else if(strcmp(token,"dim")==0){
      return DIM;
    }else  if(strcmp(token,"do")==0){
      return DOO;
    }else if(strcmp(token,"double")==0){
      return DOUBL;
    }else if(strcmp(token,"else")==0){
      return ESLE;
    }else if(strcmp(token,"end")==0){
      return EDN;
    }else  if(strcmp(token,"chr")==0){
      return CHR;
    }else if(strcmp(token,"function")==0){
      return FUNCTION;
    }else if(strcmp(token,"if")==0){
      return FI;
    }else if(strcmp(token,"input")==0){
      return INPUT;
    }else  if(strcmp(token,"integer")==0){
      return INTEGER;
    }else if(strcmp(token,"lenght")==0){
      return LENGHT;
    }else if(strcmp(token,"loop")==0){
      return LOOP;
    }else if(strcmp(token,"print")==0){
      return PRINT;
    }else  if(strcmp(token,"return")==0){
      return RETUNR;
    }else if(strcmp(token,"scope")==0){
      return SCOPE;
    }else if(strcmp(token,"string")==0){
      return STRENK;
    }else if(strcmp(token,"substr")==0){
      return SUBSTRA;
    }else  if(strcmp(token,"then")==0){
      return THEN;
    }else if(strcmp(token,"while")==0){
      return WHIL;
    }else{
    return ID;
    }
    break;
  case 3:
    if (isdigit(c)){
      token[i]=tolower(c);
      i++;;
      state=3;
    }else if(c=='.'){
      token[i]=c;
      i++;
    state=7;
    }else if (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='\\' ||c==' '){
    state=0;
    ungetc(c,source);
    return INTNUM;
    }else{
    return 1;
    }
    break;
  case 4:
    if(c=='"'){
      token[i]=c;
      i++;
      return TEXT;
    }else{
    token[i]=c;
    i++;
    state= 4;
    }
    break;
  case 5:
    if(c=='\n'){
      return COMMENT;
    }else{
    state= 5;
    }
    break;
  case 6:
    if(c=='\''){
      state= 8;
    }else{
     state= 6;
    }
    break;
  case 8:
    if(c=='\\'){
      return COMMENT;
    }else{
    state= 6;
    }
    break;
  case 7:
    if(isdigit(c)){
      token[i]=c;
      i++;
      state= 7;
    }else if(c=='+'|| c=='-' || c=='*' || c=='/' || c=='\\'){
    state=0;
    ungetc(c,source);
    return DOUBNUM;
    }else{
    return 1;
    }
break;
    }
}
}
}


