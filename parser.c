#include "parser.h"

int des_sc_list(){
  int type = GetNextToken()
  if(type) return LEX_ERR;
  if(strcmp(token, "end")){ // 3
    return (des_KEYWORD("scope"));
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){
    return (des_stat() && des_KEYWORD("\n") && des_sc_list());
  }
  return FALSE;
}

// Zjistí typ následujícího tokenu
int des_TTYPE(){
  int type = GetNextToken();
  if(GetNextToken()) return LEX_ERR;
  return type;
}

// Porovná následující token z parametrem
int des_KEYWORD(char *input){
  if(GetNextToken()) return LEX_ERR;
  if(strcmp(token, input)) return TRUE;
  else return FALSE;
}

int des_prog(){
  if(GetNextToken()) return LEX_ERR;
  if(strcmp(token, "scope")){ // 1
    return (des_sc_list() && des_prog());
  } else if(strcmp(token, "declare")){ // 25
    return (des_KEYWORD("function") && (des_TTYPE() == ID) && des_KEYWORD("(") && des_par_list() && des_KEYWORD("as") && (des_TTYPE() == TYPE) && des_prog());
  } else if(strcmp(token, "function")){ // 30
    return ((des_TTYPE() == ID) && des_par_list() && des_KEYWORD("as") && (des_TTYPE() == TYPE) && des_KEYWORD("\n") && des_func_list() && des_prog());
  }
  return FALSE;
}

int descent(){
  int result = des_prog();
  if(result == LEX_ERR) return 1;
  else if(result == FALSE) return 2;
  else return 0;
}

int main(int argc, char *argv[]){
  if(argc == 2){
    if(!(source = fopen(argv[1], "r"))){
      fprintf(stderr, "Chyba otevření souboru!\n");
      return 99;
    }
  } else {
    fprintf(stderr, "Chybný počet parametrů!\n");
    return 99;
  }
  int result = descent();
  fclose(source);
  printf("Program returned %d\n", result);
  return result;
}
