/*

Projekt z předmětů IFJ a IAL
Překladač jazyka IFJ17

parser.h

Autoři:

Daniel Švub (xsvubd00)

*/

// Knihovny:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nástroje pro tabulku symbolů:

#include "symtable.c"

// Logické hodnoty:

#define TRUE 1
#define FALSE 0

// Návratové kódy:

#define LEX_ERR 1
#define SYN_ERR 2
#define DIM_ERR 3
#define TYP_ERR 4
#define SEM_ERR 6

// Globální proměnné:

char token[1000];
char transfer[1000];
int error;
int row;
thtable *vartable;
thtable *fntable;

// Rekurzivní sestup:

int descent();

int des_KEYWORD(char *input);
int des_TTYPE();

int des_prog();
int des_sc_list();
int des_func_list();
int des_if_list();
int des_else_list();
int des_loop_list();
int des_stat(int type);
int des_def();
int des_ass();
int des_par_list();
int des_par();
int des_in_list();
int des_in();
int des_exp();

int pre_next(int *input);

// Precedenční tabulka:

int PRE_TAB[8][8];

#define PRE_ADDSUB 0
#define PRE_MULDIV 1
#define PRE_INTDIV 2
#define PRE_RELOPS 3
#define PRE_LB 4
#define PRE_RB 5
#define PRE_ID 6
#define PRE_END 7
#define PRE_NON 8
#define PRE_LEFT 9

void create_table(){

PRE_TAB[0][0] = 2;
PRE_TAB[0][1] = 1;
PRE_TAB[0][2] = 1;
PRE_TAB[0][3] = 2;
PRE_TAB[0][4] = 1;
PRE_TAB[0][5] = 2;
PRE_TAB[0][6] = 1;
PRE_TAB[0][7] = 2;

PRE_TAB[1][0] = 2;
PRE_TAB[1][1] = 2;
PRE_TAB[1][2] = 2;
PRE_TAB[1][3] = 2;
PRE_TAB[1][4] = 1;
PRE_TAB[1][5] = 2;
PRE_TAB[1][6] = 1;
PRE_TAB[1][7] = 2;

PRE_TAB[2][0] = 2;
PRE_TAB[2][1] = 1;
PRE_TAB[2][2] = 2;
PRE_TAB[2][3] = 2;
PRE_TAB[2][4] = 1;
PRE_TAB[2][5] = 2;
PRE_TAB[2][6] = 1;
PRE_TAB[2][7] = 2;

PRE_TAB[3][0] = 1;
PRE_TAB[3][1] = 1;
PRE_TAB[3][2] = 1;
PRE_TAB[3][3] = 0;
PRE_TAB[3][4] = 1;
PRE_TAB[3][5] = 2;
PRE_TAB[3][6] = 1;
PRE_TAB[3][7] = 2;

PRE_TAB[4][0] = 1;
PRE_TAB[4][1] = 1;
PRE_TAB[4][2] = 1;
PRE_TAB[4][3] = 1;
PRE_TAB[4][4] = 1;
PRE_TAB[4][5] = 3;
PRE_TAB[4][6] = 1;
PRE_TAB[4][7] = 0;

PRE_TAB[5][0] = 2;
PRE_TAB[5][1] = 2;
PRE_TAB[5][2] = 2;
PRE_TAB[5][3] = 2;
PRE_TAB[5][4] = 0;
PRE_TAB[5][5] = 2;
PRE_TAB[5][6] = 0;
PRE_TAB[5][7] = 2;

PRE_TAB[6][0] = 2;
PRE_TAB[6][1] = 2;
PRE_TAB[6][2] = 2;
PRE_TAB[6][3] = 2;
PRE_TAB[6][4] = 0;
PRE_TAB[6][5] = 2;
PRE_TAB[6][6] = 0;
PRE_TAB[6][7] = 2;

PRE_TAB[7][0] = 1;
PRE_TAB[7][1] = 1;
PRE_TAB[7][2] = 1;
PRE_TAB[7][3] = 1;
PRE_TAB[7][4] = 1;
PRE_TAB[7][5] = 0;
PRE_TAB[7][6] = 1;
PRE_TAB[7][7] = 0;

}

// Další soubory:

#include "stack.c"
#include "scanner.c"
