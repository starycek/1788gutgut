typedef struct{
	char *str;
	int lenght;
	int size;
} string;

int String_Init(string *s);
int String_Add_Char(string *string, char c);
int String_Add_Char_Lower(string *string, char c);
void String_Delete_Char(string *string);
void String_Clear (string *s);
void String_Delete (string *s);
