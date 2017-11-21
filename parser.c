#include "parser.h"

int des_exp(){
  return TRUE;
}

int des_in(){
  if(GetNextToken()) return LEX_ERR;
  if(strcmp(token, ")")){ // 23
    return TRUE;
  } else if(strcmp(token, ",")){ // 22
    int type = GetNextToken();
    if(type) return LEX_ERR;
    return (((type == ID) || (type == DOUBLE) || (type == INT)) && des_in());
  }
  return FALSE;
}

int des_in_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if((type == ID) || (type == DOUBLE) || (type == INT)){ // 21
    return (des_in());
  } else if(strcmp(token, ")")){ // 20
    return TRUE;
  }
  return FALSE;
}

int des_par(){
  if(GetNextToken()) return LEX_ERR;
  if(strcmp(token, ")")){ // 29
    return TRUE;
  } else if(strcmp(token, ",")){ // 28
    return (des_def() && des_par());
  }
  return FALSE;
}

int des_par_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(type == ID){ // 27
    return (des_def() && des_par());
  } else if(strcmp(token, ")")){ // 26
    return TRUE;
  }
  return FALSE;
}

int des_ass(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(type == ID){ // 19
    return (des_KEYWORD("(") && des_in_list());
  } else { // 18
    des_exp();
  }
  return FALSE;
}

int des_def(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(type == ID){ // 5
    return (des_KEYWORD("as") && (des_TTYPE() == TYPE));
  }
  return FALSE;
}

int des_stat(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "dim")){ // 4
    return (des_def());
  } else if(type == ID){ // 17
    return (des_KEYWORD("=") && des_ass());
  } else if(strcmp(token, "print")){ // 6
    return (des_exp());
  } else if(strcmp(token, "input")){ // 7
    return (des_TTYPE() == ID);
  } else if(strcmp(token, "if")){ // 8
    return (des_exp() && des_KEYWORD("then") && des_KEYWORD("\n") && des_if_list());
  } else if(strcmp(token, "do")){ // 14
    return (des_KEYWORD("while") && des_exp() && des_KEYWORD("\n") && des_loop_list());
  } else if(strcmp(token, "return")){ // 24
    type = GetNextToken();
    if(type) return LEX_ERR;
    return ((type == ID) || (type == DOUBLE) || (type == INT));
  }
  return FALSE;
}

int des_loop_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "loop")){ // 16
    return TRUE;
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){ // 12
    return (des_stat() && des_KEYWORD("\n") && des_loop_list());
  }
  return FALSE;
}

int des_else_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "end")){ // 13
    return (des_KEYWORD("if"));
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){ // 12
    return (des_stat() && des_KEYWORD("\n") && des_else_list());
  }
  return FALSE;
}

int des_if_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "end")){ // 10
    return (des_KEYWORD("if"));
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){ // 9
    return (des_stat() && des_KEYWORD("\n") && des_if_list());
  } else if(strcmp(token, "else")){ // 11
    return (des_KEYWORD("\n") && des_else_list());
  }
  return FALSE;
}

int des_func_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "end")){ // 32
    return (des_KEYWORD("function"));
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){ // 31
    return (des_stat() && des_KEYWORD("\n") && des_func_list());
  }
  return FALSE;
}

int des_sc_list(){
  int type = GetNextToken();
  if(type) return LEX_ERR;
  if(strcmp(token, "end")){ // 3
    return (des_KEYWORD("scope"));
  } else if(strcmp(token, "dim") || (type == ID) || strcmp(token, "print") || strcmp(token, "input") || strcmp(token, "if") || strcmp(token, "do") || strcmp(token, "return")){ // 2
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
