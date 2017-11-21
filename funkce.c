#define DEF_SIZE 8



int String_Init(string *s){
	
	s->str = (char *) malloc(DEF_SIZE);
	if(s->str == NULL) return EXIT_FAILURE;
	s->str[0]='\0';
	s->lenght=0;
	s->size = DEF_SIZE;
	return EXIT_SUCCESS;
}
int String_Add_Char(string *string, char c){
	if(string->lenght +1 >= string->size){
		string->str = (char *) realloc(string->str, string->lenght + DEF_SIZE)
		if(string->str == NULL) return EXIT_FAILURE;
		string->size + DEF_SIZE;
	}
	string->str[string->lenght] = c;
	string->lenght++;
	string->str[string->lenght] = '\0';
	return EXIT_SUCCESS;
}
int String_Add_Char_Lower(string *string, char c){
	if(string->lenght +1 >= string->size){
		string->str = (char *) realloc(string->str, string->lenght + DEF_SIZE)
		if(string->str == NULL) return EXIT_FAILURE;
		string->size + DEF_SIZE;
	}
	string->str[string->lenght] = tolower(c);
	string->lenght++;
	string->str[string->lenght] = '\0';
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
