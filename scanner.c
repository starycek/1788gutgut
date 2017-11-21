#include "scanner.h"
#include "main.c"
#include "string.h"
#include "funkce.c"


int getNextToken(string *s){
char c;
int state=0;
int radek=1;
str

while(1){
  c=getc(source);
  if (c=='\n')
    radek++;

    switch(state){
  case 0:
    if (isspace(c)){
      state=0;
    }
    else if(c=='/'){
      return doubdiv;
    }
    else if(isalpha(c)||c=='_'){
      str
      state=2;
    }
    else if(isdigit(c)){
      str
      state=3;
    }
    else if (c=='-'){
      return sub;
    }
    else if (c=='\\'){
      state=1;
    }
      else if (c=='*'){
      return mult;
    }
      else if (c=='+'){
      return add;
    }
      else if (c=='!'){
          return stringstart;
    }
      else if (c=='='){
          return eql;
    }
      else if(c=='>'){
      if((c=getc(source))=='='){
        return greq;
      } else{
      return greatr;
      }
      }
      else if(c=='<'){
      if((c=getc(source))=='='){
        return leseq;
      } else if((c=getc(source))=='>'){
      return different;
      }else{
      return lesser;
      }
    }
    else if(c==','){
      return comm;
    }
    else if(c==';'){
      return semicol;
    }
    else if(c==')'){
      return rightbrac;
    }
    else if(c=='('){
      return leftbrac;
      }
       else if(c=='\''){
      return comment;
      }
    else if(c=='"'){
      state=4;
    }
    else{
      return 1
    }
  break;
  }
  case 1:
    if(c=='\'')}
      state=6;
    }else if(isdigit(c)){
    return intdiv;
    }else{
    return 1;
    }
    break;
  case 2:
    if(isalnum(c) || c=='_'){
      str
      break;
    }else{
      ungetc(c,source);
    if(strcmp(s->str,"as")==0){
      return as;
    }else if(strcmp(s->str,"asc")==0){
      return asc;
    }else if(strcmp(s->str,"declare")==0){
      return as;
    }else if(strcmp(s->str,"dim")==0){
      return dim;
    }else  if(strcmp(s->str,"do")==0){
      return do;
    }else if(strcmp(s->str,"double")==0){
      return double;
    }else if(strcmp(s->str,"else")==0){
      return esle;
    }else if(strcmp(s->str,"end")==0){
      return edn;
    }else  if(strcmp(s->str,"chr")==0){
      return chr;
    }else if(strcmp(s->str,"function")==0){
      return function;
    }else if(strcmp(s->str,"if")==0){
      return fi;
    }else if(strcmp(s->str,"input")==0){
      return input;
    }else  if(strcmp(s->str,"integer")==0){
      return integer;
    }else if(strcmp(s->str,"lenght")==0){
      return lenght;
    }else if(strcmp(s->str,"loop")==0){
      return loop;
    }else if(strcmp(s->str,"print")==0){
      return print;
    }else  if(strcmp(s->str,"return")==0){
      return retunr;
    }else if(strcmp(s->str,"scope")==0){
      return scope;
    }else if(strcmp(s->str,"string")==0){
      return string;
    }else if(strcmp(s->str,"substr")==0){
      return substr;
    }else  if(strcmp(s->str,"then")==0){
      return then;
    }else if(strcmp(s->str,"while")==0){
      return whil;
    }else{
    return id;
    }
    break;
  case 3:
    if (isdigit(c)){
      str
      state=3;
    }else if(c=='.'){
    state=7;
    }else if (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='\\' ||c==' '){
    state=0;
    unget(c,source);
    return num;
    }else{
    return 1;
    }
    break;
  case 4:
    if(c=='"'){
      return TEXT;
    }else{
    case 4;
    }
    break;
  case 5:
    if(c=='\n'){
      return COMMENT;
    }else{
    case 5;
    }
    break;
  case 6:
    if(c=='\''){
      case 8;
    }else{
     case 6;
    }
    break;
  case 8:
    if(c=='\\'){
      return COMMENT;
    }else{
    case 6;
    }
    break
  case 7:
    if(isdigit(c)){
      case 7;
    }else if(c=='+'|| c=='-' || c=='*' || c=='/' || c=='\\'){
    state=0;
    ungetc(c,source);
    return NUM
    }else{
    return 1;
    }
break;
    }
}


