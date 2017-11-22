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
string *s = NULL;
char c;
int state=0;
int radek=1;
String_Init (s);
String_Clear(s);

printf("%s",s->str);
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
      return DOUBDIV;
    }
    else if(isalpha(c)||c=='_'){
      String_Add_Char_Lower(s,c);
      state=2;
    }
    else if(isdigit(c)){
      String_Add_Char_Lower(s,c);
      state=3;
    }
    else if (c=='-'){
      return SUB;
    }
    else if (c=='\\'){
      state=1;
    }
      else if (c=='*'){
      return MULT;
    }
      else if (c=='+'){
      return ADD;
    }
      else if (c=='!'){
          return STRINGSTART;
    }
      else if (c=='='){
          return EQL;
    }
      else if(c=='>'){
      if((c=getc(source))=='='){
        return GREQ;
      } else{
      return GREATR;
      }
      }
      else if(c=='<'){
      if((c=getc(source))=='='){
        return LESEQ;
      } else if((c=getc(source))=='>'){
      return DIFFERENT;
      }else{
      return LESSER;
      }
    }
    else if(c==','){
      return COMM;
    }
    else if(c==';'){
      return SEMICOL;
    }
    else if(c==')'){
      return RIGHTBRAC;
    }
    else if(c=='('){
      return LEFTBRAC;
      }
    else if(c=='"'){
      state=4;
    }
    else{
      return 1;
    }
  break;

  case 1:
    if(c=='\''){
      state=6;
    }else if(isdigit(c)){
    return INTDIV;
    }else{
    return 1;
    }
    break;
  case 2:
    if(isalnum(c) || c=='_'){
      String_Add_Char_Lower(s,c);
      break;
    }else{
      ungetc(c,source);
    if(strcmp(s->str,"as")==0){
      return AS;
    }else if(strcmp(s->str,"asc")==0){
      return ASC;
    }else if(strcmp(s->str,"declare")==0){
      return DECLARE;
    }else if(strcmp(s->str,"dim")==0){
      return DIM;
    }else  if(strcmp(s->str,"do")==0){
      return DOO;
    }else if(strcmp(s->str,"double")==0){
      return DOUBL;
    }else if(strcmp(s->str,"else")==0){
      return ESLE;
    }else if(strcmp(s->str,"end")==0){
      return EDN;
    }else  if(strcmp(s->str,"chr")==0){
      return CHR;
    }else if(strcmp(s->str,"function")==0){
      return FUNCTION;
    }else if(strcmp(s->str,"if")==0){
      return FI;
    }else if(strcmp(s->str,"input")==0){
      return INPUT;
    }else  if(strcmp(s->str,"integer")==0){
      return INTEGER;
    }else if(strcmp(s->str,"lenght")==0){
      return LENGHT;
    }else if(strcmp(s->str,"loop")==0){
      return LOOP;
    }else if(strcmp(s->str,"print")==0){
      return PRINT;
    }else  if(strcmp(s->str,"return")==0){
      return RETUNR;
    }else if(strcmp(s->str,"scope")==0){
      return SCOPE;
    }else if(strcmp(s->str,"string")==0){
      return STRENK;
    }else if(strcmp(s->str,"substr")==0){
      return SUBSTRA;
    }else  if(strcmp(s->str,"then")==0){
      return THEN;
    }else if(strcmp(s->str,"while")==0){
      return WHIL;
    }else{
    return ID;
    }
    break;
  case 3:
    if (isdigit(c)){
      String_Add_Char_Lower(s,c);
      state=3;
    }else if(c=='.'){
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
      return TEXT;
    }else{
    String_Add_Char(s,c);
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


