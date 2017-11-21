#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define SYN_ERR 1
#define LEX_ERR 2

#define ID 0
#define TYPE 0
#define INT 0
#define DOUBLE 0

FILE *source = NULL;
char *token = NULL;

int descent();

int des_KEYWORD(char *input);
int des_TTYPE();

int des_prog();
int des_sc_list();
int des_func_list();
int des_if_list();
int des_else_list();
int des_loop_list();
int des_stat();
int des_def();
int des_ass();
int des_par_list();
int des_par();
int des_in_list();
int des_in();
int des_exp();
