/* Parser for Tiny Programming Language (For more information
   on the specifics of Tiny, refer to 'Compiler Construction: 
   Principles and Practice' by 'Kenneth C Louden'
 
   Author: Sai Sudheer Goturu
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ENDFILE 0
#define FALSE 0
#define TRUE 1
#define BUFLEN 100
#define START 0
#define INCOMMENT 1
#define INNUM 2
#define INID 3
#define INASSIGN 4
#define DONE 5
char buf[BUFLEN];
int bufpos;
int state;
int curTokenIndex;
FILE *listing;
FILE *source;
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
//TokenType getToken(void);
//TokenType printToken(char* str,int option);
TokenType checkKeyword(char* str);
void printString(TokenType);
char getNextChar(void);
TokenType printToken(const char* tokenString, TokenType token);
int lineno; 

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

int Error;
char tokenString[BUFLEN+1];




