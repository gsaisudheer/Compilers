#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZE 256
#define MAXRESERVED 8
#define MAXLEXEMELEN 40
#define MAXTOKENLEN 40
#define YES 1
#define NO 0

#define MAXCHILDREN 3

typedef enum {START, INCOMMENT,INNUM,INID,INASSIGN,DONE} STATE;
typedef enum {ENDOFFILE,PLUS,MINUS,MULTIPLY,DIVIDE,LT,EQUAL,LPAREN,RPAREN,SEMICOLON,ERROR,IF,THEN,END,ELSE,REPEAT,UNTIL,READ,WRITE,ID,NUM,ASSIGN} TOKENTYPE;

static struct { 
                char* str;
                TOKENTYPE tok;
              } reservedWords[MAXRESERVED]
              = { {"if",IF}, {"then",THEN}, {"else",ELSE}, {"end",END},
                  {"repeat",REPEAT}, {"until",UNTIL}, {"read",READ},
                  {"write",WRITE} };
                  

char buffer[BUFSIZE];
static int linepos=0;  
static int lineno=0;  
FILE *fp1,*fp2, *FPAR;
int Write;

static char getNextChar(void);
void ungetNextChar(void);
void printToken(TOKENTYPE, char*);
TOKENTYPE reservedLookup(char *s);
TOKENTYPE token;
char tokenString[MAXTOKENLEN];

