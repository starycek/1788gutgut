#include "stdio.h"
#include "funkce.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DEF_SIZE 8



int String_Init(string *s){

	s->str = (char*)  malloc(DEF_SIZE);
	if(s->str == NULL) return EXIT_FAILURE;
	s->str[0]='\0';
	s->lenght=0;
	s->size = DEF_SIZE;
	return EXIT_SUCCESS;
}
int String_Add_Char(string *string, char c){
	if(string->lenght +1 >= string->size){
//		string->str = (char *)  realloc(string->str, string->lenght + DEF_SIZE);
		if(string->str == NULL) return EXIT_FAILURE;
		string->size =string->lenght + DEF_SIZE;
	}
	string->str[string->lenght] = c;
	string->lenght++;
	string->str[string->lenght] = '\0';
	return EXIT_SUCCESS;
}
int String_Add_Char_Lower(string *string, char c){
	if(string->lenght +1 >= string->size){
//		string->str = (char *)  realloc(string->str, string->lenght + DEF_SIZE);
		if(string->str == NULL) return EXIT_FAILURE;
		string->size =string->lenght + DEF_SIZE;
	}
	string->str[string->lenght] = tolower(c);
	string->lenght++;
	string->str[string->lenght] = '\0';
	return EXIT_SUCCESS;
}
int String_Copy(string *string1,string *string2){
	int lenght2 = string2->lenght;
	if(lenght2 >= string1->size){
//		string1->str = (char *)  realloc(string1->str,lenght2 + 1);
		if(string1->str == NULL) return EXIT_FAILURE;
	}
	strcpy(string1->str,string2->str);
	string1->lenght=lenght2;
	return EXIT_SUCCESS;
}
void String_Delete_Char(string *string){
	string->lenght--;
	string->str[string->lenght] = '\0';
}
void String_Clear (string *s){
	s->str[0] = '\0';
	s->lenght = 0;
}
void String_Delete (string *s){
	String_Clear(s);
	free (s->str);
}
