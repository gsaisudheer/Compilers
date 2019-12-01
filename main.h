#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define BUFLEN 100
#define START 0
#define INCOMMENT 1
#define INNUM 2
#define INID 3
#define INASSIGN 4
#define DONE 5
#define TRUE 1
#define FALSE 0
char buf[BUFLEN];
int bufpos;
int state;
int curTokenIndex;
FILE *output;
FILE *fp;
int lineNum;
int scanNextChar;
char c;
int valid;
int eof;
char currentToken[BUFLEN];

void printError(char* str,int lineNum);
typedef enum{
	ENDFILE,ERROR,IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,ID,NUM,
	ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
}TokenType;

TokenType token;
/*typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;
typedef enum {Void,Integer,Boolean} ExpType;
*/
#define MAXCHILDREN 3

char * copyString(char * s);
int Error;
char tokenString[BUFLEN+1];

