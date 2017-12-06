/*

Projekt z předmětů IFJ a IAL
Překladač jazyka IFJ17

scanner.c

Autoři:

Daniel Poisl (xpoisl00)
Filip Weigel (xweige01)
Daniel Švub (xsvubd00)

*/

#include "scanner.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getNextToken(){
  char c;
  int state=0;
  int i=0;
  token[0] = '\0';
  if(transfer[0] != '\0'){
    strcpy(token, transfer);
    transfer[0] = '\0';
    return 0;
  }
  while(1){
    c=getc(stdin);
    if(feof(stdin)){
      token[0] = '\0';
      return 0;
    }
    if(token[0] == '\0' && c == '\n') state = 9;

      switch(state){
    case 0:
      if (isspace(c)){
        state=0;
      }
      else if(c=='\\'){
        token[i]=c;
        i++;
        return INTDIV;
      }
      else if(isalpha(c)||c=='_'){
        token[i]=tolower(c);
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
      else if (c=='/'){
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
        state=10;
      }
        else if (c=='='){
        token[i]=c;
        token[i+1]='\0';
        i++;
        return EQL;
      }
        else if(c=='>'){
        token[i]=c;
        i++;
        if((c=getc(stdin))=='='){
          token[i]=c;
          i++;
          return GREQ;
        } else{
        ungetc(c, stdin);
        return GREATR;
        }
        }
        else if(c=='<'){
          token[i]=c;
          i++;
          c=getc(stdin);
        if(c=='='){
          token[i]=c;
          i++;
          return LESEQ;
        } else if(c=='>'){
          token[i]=c;
          i++;
          return DIFFERENT;
        }else{
        ungetc(c, stdin);
        return LESSER;
        }
      }
      else if(c==','){
        token[i]=c;
        i++;
        token[i]='\0';
        return COMM;
      }
      else if(c==';'){
        token[i]=c;
        i++;
        token[i]='\0';
        return SEMICOL;
      }
      else if(c==')'){
        token[i]=c;
        i++;
        token[i]='\0';
        return RIGHTBRAC;
      }
      else if(c=='('){
        token[i]=c;
        i++;
        token[i]='\0';
        return LEFTBRAC;
        }
      else if(c=='"'){
        token[i]=c;
        i++;
        state=4;
      }
      else if(c=='\'') state = 5;
      else{
        return 1;
      }
    break;

    case 1:
      if(c=='\''){
        state=6;
      }else if(isdigit(c)){
      ungetc(c,stdin);
      return DOUBDIV;
      }else{
      return 1;
      }
      break;
    case 2:
      if(isalnum(c) || c=='_'){
        token[i]=tolower(c);
        i++;
        break;
      }else{
        if(c == '\n'){
          ungetc(c, stdin);
          state = 9;
        }
        ungetc(c, stdin);
        token[i]='\0';
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
        return DOUBLE;
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
        return STRING;
      }else if(strcmp(token,"substr")==0){
        return SUBSTRA;
      }else  if(strcmp(token,"then")==0){
        return THEN;
      }else if(strcmp(token,"while")==0){
        return WHIL;
      }else{
      return ID;
      }
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
      }else if (c=='+' ||c=='-' ||c=='*' ||c=='/' ||c=='\\' ||c==' ' || c=='\n' || c=='=' || c=='<' || c=='>' || c==';'){
      state=0;
      ungetc(c,stdin);
      token[i]='\0';
      return INTNUM;
      }else{
      return 1;
      }
      break;
    case 4:
      if(c=='"'){
        token[i]=c;
        i++;
        token[i]='\0';
        return INPUTSTR;
      }else{
        token[i]=c;
        i++;
        state= 4;
      }
      break;
    case 5:
      if(c=='\n'){
        return EOL;
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
      if(c=='/'){
        c=getc(stdin);
        while(c=='\n') c=getc(stdin);
        ungetc(c, stdin);
        i=0;
        state = 0;
        break;
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
      ungetc(c,stdin);
      return DOUBNUM;
      }else{
      return 1;
      }
      break;
    case 9:
      row=row;
      char t = getc(stdin);
      if(t == '\n'){
        ungetc(t, stdin);
        break;
      }
      if(feof(stdin)){
        token[0] = '\0';
        return EOL;
      }
      ungetc(t, stdin);
      token[0] = c;
      token[1] = '\0';
      return EOL;
    case 10:
      if(c=='"'){
        state=4;
        token[i]=c;
        i++;
      }
      else{
        return 1;
      }
      break;
    }
  }
}


