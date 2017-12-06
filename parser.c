/*

Projekt z předmětů IFJ a IAL
Překladač jazyka IFJ17

parser.c

Autoři:

Daniel Švub (xsvubd00)
Jan Zwierz (xzwier00)

*/

#include "parser.h"

int pre_next(int *input){
  int type = getNextToken();
  if(type == 1) return TRUE;
  else if((type == 11) || (type == 13)) *input = PRE_ADDSUB;
  else if((type == 10) || (type == 12)) *input = PRE_MULDIV;
  else if(type == 14) *input = PRE_INTDIV;
  else if((type >= 15) && (type <= 20)) *input = PRE_RELOPS;
  else if(type == 24) *input = PRE_LB;
  else if(type == 23) *input = PRE_RB;
  else if(type == 30){ // Proměnná, ověření existence
    tklic variable = (tklic) malloc(strlen(token)+1);
    strcpy(variable, token);
    if(tSearch(vartable, variable) == NULL){ // Vyhledání v tabulce
      if(tSearch(fntable, variable) == NULL){
        if(!error) error = DIM_ERR;
        fprintf(stderr, "Neexistující proměnná '%s'\n", token);
      }
      free(variable);
      *input = PRE_END;
      return type;
    } else {
      free(variable);
      *input = PRE_ID;
      return type;
    }
  }
  else if((type == DOUBNUM) || (type == INTNUM) || (type == INPUTSTR)) *input = PRE_ID;
  else *input = PRE_END;
  return type;
}

int des_exp(int ass){
  tStack *stack = malloc(sizeof(tStack));
  stackInit(stack);
  stackPush(stack, PRE_END);
  int top = 0;
  int input = ass;
  top = stackTopTerm(stack, 0); // Nalezení nejvyššího terminálu v zásobníku
  if(ass == 10){
    if(pre_next(&input) == 1){ // Další token
      if(!error) error = LEX_ERR;
      free(stack);
      return FALSE;
    }
  }
  do{
    if(PRE_TAB[top][input] == 0){ // Chyba
      free(stack);
      return FALSE;
    } else if(PRE_TAB[top][input] == 1){ // <
      top = stackTopTerm(stack, 1); // Vložení '<' za top
      stackPush(stack, input); // Vložení vstupu na zásobník
      if(pre_next(&input) == 1){ // Další token
        if(!error) error = LEX_ERR;
        free(stack);
        return FALSE;
      }
      if((ass != 10) && (input == PRE_RELOPS)){
        free(stack);
        return FALSE; // V přiřazení nesmí být relační operátor
      }
    } else if(PRE_TAB[top][input] == 2){ // >
      if(!stackReduce(stack)){ // Redukce, v případě neúspěchu chyba
        free(stack);
        return FALSE;
      }
    } else if(PRE_TAB[top][input] == 3){ // =
      if(pre_next(&input) == 1){ // Další token
        if(!error) error = LEX_ERR;
        free(stack);
        return FALSE;
      }
      if((ass != 10) && (input == PRE_RELOPS)){
        free(stack);
        return FALSE; // V přiřazení nesmí být relační operátor
      }
      stackPush(stack, input); // Vložení vstupu na zásobník
    } else {
      free(stack);
      return FALSE;
    }
    top = stackTopTerm(stack, 0); // Nalezení nejvyššího terminálu v zásobníku
  } while (!((input == PRE_END) && (top == PRE_END)));
  strcpy(transfer, token);
  free(stack);
  return TRUE; // Úspěch PSA
}

int des_out(){
  int input = 10;
  int type = pre_next(&input);
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "\n")){
    strcpy(transfer, token);
    return TRUE;
  } else {
    return des_exp(input) && des_KEYWORD(";") && des_out();
  }
}

int des_in(){
  if(getNextToken() == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, ")")){ // 23
    return TRUE;
  } else if(!strcmp(token, ",")){ // 22
    int type = getNextToken();
    if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
    return (((type == ID) || (type == DOUBNUM) || (type == INTNUM)) && des_in());
  }
  return FALSE;
}

int des_in_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if((type == ID) || (type == DOUBNUM) || (type == INTNUM)){ // 21
    return (des_in());
  } else if(!strcmp(token, ")")){ // 20
    return TRUE;
  }
  return FALSE;
}

int des_par(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, ")")){ // 29
    return TRUE;
  } else if(!strcmp(token, ",")){ // 28
    return (des_def(0) && des_par());
  }
  return FALSE;
}

int des_par_list(int declare){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(type == ID){ // 27
    if(declare) type = -type;
    return (des_def(type) && des_par());
  } else if(!strcmp(token, ")")){ // 26
    return TRUE;
  }
  return FALSE;
}

int des_ass(){
  int input = 10;
  int type = pre_next(&input);
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(type == ID){ // 19
    tklic label = (tklic) malloc(strlen(token)+1);
    strcpy(label, token);
    if(tSearch(vartable, label) != NULL){
      free(label);
      return des_exp(input);
    } else if(tSearch(fntable, label) != NULL){ // V přiřazení je funkce
      return (des_KEYWORD("(") && des_in_list());
    } else {
      fprintf(stderr, "Neplatný identifikátor '%s'\n", label);
      free(label);
      if(!error) error = DIM_ERR;
      return FALSE;
    }
  } else { // 18
    return des_exp(input); // Výraz
  }
  return FALSE;
}

int des_def(int type){
  int declare = FALSE;
  if(type == 0){ // Funkce je volána bez dim
    declare = TRUE;
    type = getNextToken();
    if(type == 1){
      if(!error) error = LEX_ERR;
      return FALSE;
    }
  }
  if(type == ID || type == -30){ // 5
    if(declare || type < 0){
      if(type < 0) type = -type;
      tklic variable = (tklic) malloc(strlen(token)+1);
      strcpy(variable, token);
      if(!des_KEYWORD("as")){
        free(variable);
        return FALSE;
      }
      int tok_type = des_TTYPE();
      // Získání typu proměnné
      int var_type;
      if(tok_type == INTEGER) var_type = 1;
      else if(tok_type == DOUBLE) var_type = 2;
      else if(tok_type == STRING) var_type = 3;
      else {
        free(variable);
        return FALSE;
      }
      if(tSearch(vartable, variable) != NULL){ // Ověření existence proměnné
        if(!error) error = DIM_ERR;
        fprintf(stderr, "Vícenásobná deklarace proměnné '%s'\n", variable);
        free(variable);
        return FALSE;
      }
      tInsert(vartable, variable, 0.0, "id", var_type); // Pokud neexistuje, vložení
      free(variable);
      return TRUE;
    } else {
      if(!des_KEYWORD("as")) return FALSE;
      int tok_type = des_TTYPE();
      if(tok_type == INTEGER || tok_type == DOUBLE || tok_type == STRING) return TRUE;
    }
  }
  return FALSE;
}

int des_stat(int type){
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "dim")){ // 4
    return (des_def(0));
  } else if(type == ID){ // 17
    tklic label = (tklic) malloc(strlen(token)+1);
    strcpy(label, token);
    if(tSearch(vartable, label) != NULL){
      free(label);
      return (des_KEYWORD("=") && des_ass());
    } else {
      fprintf(stderr, "Neplatný identifikátor '%s'\n", label);
      free(label);
      if(!error) error = DIM_ERR;
      return FALSE;
    }
  } else if(!strcmp(token, "print")){ // 6
    return (des_exp(10) && des_KEYWORD(";") && des_out());
  } else if(!strcmp(token, "input")){ // 7
    int tok_type = des_TTYPE();
    if(tok_type == ID){
      tklic variable = (tklic) malloc(strlen(token)+1);
      strcpy(variable, token);
      if(tSearch(vartable, variable) == NULL){
        if(!error) error = DIM_ERR;
        fprintf(stderr, "Neexistující proměnná '%s'\n", token);
        free(variable);
        return FALSE;
      } else {
        free(variable);
        return TRUE;
      }
    } else return FALSE;
  } else if(!strcmp(token, "if")){ // 8
    return (des_exp(10) && des_KEYWORD("then") && des_KEYWORD("\n") && des_if_list());
  } else if(!strcmp(token, "do")){ // 14
    return (des_KEYWORD("while") && des_exp(10) && des_KEYWORD("\n") && des_loop_list());
  } else if(!strcmp(token, "return")){ // 24
    int tok_type = des_TTYPE();
    if(tok_type == ID){ // Ověření existence proměnné
      tklic variable = (tklic) malloc(strlen(token)+1);
      strcpy(variable, token);
      if(tSearch(vartable, variable) == NULL){ // Vyhledání v tabulce
        if(!error) error = DIM_ERR;
        fprintf(stderr, "Neexistující proměnná '%s'\n", token);
        free(variable);
        return FALSE;
      } else {
        free(variable);
        return TRUE;
      }
    } else if (tok_type == (DOUBNUM || INTNUM)) return TRUE;
    else return FALSE;
  }
  return FALSE;
}

int des_loop_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "loop")){ // 16
    return TRUE;
  } else if(!strcmp(token, "dim") || (type == ID) || !strcmp(token, "print") || !strcmp(token, "input") || !strcmp(token, "if") || !strcmp(token, "do") || !strcmp(token, "return")){ // 12
    return (des_stat(type) && des_KEYWORD("\n") && des_loop_list());
  }
  return FALSE;
}

int des_else_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "end")){ // 13
    return (des_KEYWORD("if"));
  } else if(!strcmp(token, "dim") || (type == ID) || !strcmp(token, "print") || !strcmp(token, "input") || !strcmp(token, "if") || !strcmp(token, "do") || !strcmp(token, "return")){ // 12
    return (des_stat(type) && des_KEYWORD("\n") && des_else_list());
  }
  return FALSE;
}

int des_if_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "end")){ // 10
    return (des_KEYWORD("if"));
  } else if(!strcmp(token, "dim") || (type == ID) || !strcmp(token, "print") || !strcmp(token, "input") || !strcmp(token, "if") || !strcmp(token, "do") || !strcmp(token, "return")){ // 9
    return (des_stat(type) && des_KEYWORD("\n") && des_if_list());
  } else if(!strcmp(token, "else")){ // 11
    return (des_KEYWORD("\n") && des_else_list());
  }
  return FALSE;
}

int des_func_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "end")){ // 32
    tClearall(vartable);
    return (des_KEYWORD("function")) && des_KEYWORD("\n");
  } else if(!strcmp(token, "dim") || (type == ID) || !strcmp(token, "print") || !strcmp(token, "input") || !strcmp(token, "if") || !strcmp(token, "do") || !strcmp(token, "return")){ // 31
    return (des_stat(type) && des_KEYWORD("\n") && des_func_list());
  }
  return FALSE;
}

int des_sc_list(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "end")){ // 3
    tClearall(vartable);
    return (des_KEYWORD("scope")) && des_KEYWORD("\0");
  } else if(!strcmp(token, "dim") || (type == ID) || !strcmp(token, "print") || !strcmp(token, "input") || !strcmp(token, "if") || !strcmp(token, "do") || !strcmp(token, "return")){ // 2
    return (des_stat(type) && des_KEYWORD("\n") && des_sc_list());
  }
  return FALSE;
}

// Zjistí typ následujícího tokenu
int des_TTYPE(){
  int type = getNextToken();
  if(type == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  return type;
}

// Porovná následující token z parametrem
int des_KEYWORD(char *input){
  if(getNextToken() == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "\n") && !strcmp(input, "\n")) row++;
  if(!(!strcmp(token, input))) fprintf(stderr, "Neočekávaný token '%s', očekáváno: '%s'\n", token, input);
  if(!strcmp(token, input)) return TRUE;
  else return FALSE;
}

int des_prog(){
  if(getNextToken() == 1){
    if(!error) error = LEX_ERR;
    return FALSE;
  }
  if(!strcmp(token, "scope")){ // 1
    initTable(vartable); // Vytvoření tabulky pro scope
    return (des_KEYWORD("\n") && des_sc_list() && des_prog());
  } else if(!strcmp(token, "declare")){ // 25
    if(!des_KEYWORD("function")) return FALSE;
    if(des_TTYPE() == ID){
      tklic label = (tklic) malloc(strlen(token)+1);
      strcpy(label, token);
      if(!des_KEYWORD("(") || !des_par_list(FALSE) || !des_KEYWORD("as")){
        free(label);
        return FALSE;
      }
      int tok_type = des_TTYPE();
      int fn_type; // Zjištění typu funkce
      if(tok_type == INTEGER) fn_type = 1;
      else if(tok_type == DOUBLE) fn_type = 2;
      else if(tok_type == STRING) fn_type = 3;
      else {
        free(label);
        return FALSE;
      }
      if(tSearch(fntable, label) != NULL){ // Vyhledávání v tabulce
        if(!error) error = DIM_ERR;
        fprintf(stderr, "Vícenásobná deklarace funkce '%s'\n", label);
        free(label);
        return FALSE;
      } // Pokud neexistuje, vložení do tabulky
      tInsert(fntable, label, 1, "id", fn_type);
      free(label);
      return (des_KEYWORD("\n") && des_prog());
    } else return FALSE;
  } else if(!strcmp(token, "function")){ // 30
    initTable(vartable); // Tabulka pro funkci
    if(des_TTYPE() == ID){
      tklic label = (tklic) malloc(strlen(token)+1);
      strcpy(label, token);
      if(!des_KEYWORD("(") || !des_par_list(TRUE) || !des_KEYWORD("as")){ // Uloží parametry jako proměnné
        free(label);
        return FALSE;
      }
      int tok_type = des_TTYPE();
      int fn_type;
      if(tok_type == INTEGER) fn_type = 1;
      else if(tok_type == DOUBLE) fn_type = 2;
      else if(tok_type == STRING) fn_type = 3;
      else {
        free(label);
        return FALSE;
      }
      thitem *func = tSearch(fntable, label);
      if(func != NULL){
        if(func -> data > 1){
          if(!error) error = DIM_ERR;
          fprintf(stderr, "Vícenásobná definice funkce '%s'\n", label);
          free(label);
          return FALSE;
        } else {
          tInsert(fntable, label, func -> data + 2, "id", fn_type);
        }
      } else tInsert(fntable, label, 2, "id", fn_type);
      free(label);
      return (des_KEYWORD("\n") && des_func_list() && des_prog());
    } else return FALSE;
  } else if(!strcmp(token, "\0")){ // 33
    return TRUE;
  } else if(!strcmp(token, "\n")){
    return (des_prog());
  }
  return FALSE;
}

// Rekurzivní sestup
int descent(){
  int result = des_prog();
  if(!result) return 2;
  else return 0;
}

int main(int argc, char *argv[]){
  create_table(); // Vytvoření precedenční tabulky
  row = 1; // 1. řádek
  // Inicializace tabulek
  vartable = malloc(max_size*sizeof(thitem*));
  fntable = malloc(max_size*sizeof(thitem*));
  initTable(fntable);
  // Vložení vestavěných funkcí
  tInsert(fntable, "substr", 3, "id", 3);
  tInsert(fntable, "length", 3, "id", 1);
  tInsert(fntable, "asc", 3, "id", 1);
  tInsert(fntable, "chr", 3, "id", 3);
  // Ověření příkazové řádky
  if(argc != 1){
    fprintf(stderr, "99: Chybný počet parametrů!\n");
    return 99;
  }
  int result = descent(); // Spuštění analýzy
  if(!error) error = result;
  // Uvolnění paměti
  tClearall(vartable);
  tClearall(fntable);
  free(vartable);
  free(fntable);
  if(error == 1) fprintf(stderr, "01: Lexikální chyba na řádku %d!\n", row);
  if(error == 2) fprintf(stderr, "02: Syntaktická chyba na řádku %d!\n", row);
  if(error == 3) fprintf(stderr, "03: Sémantická chyba na řádku %d!\n", row);
  return error;
}
