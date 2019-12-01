%{
#include "main.h"

FILE *source,*listing;
#define TRUE 1
#define FALSE 0

/* typedef enum {ENDOFFILE,PLUS,MINUS,MULTIPLY,DIVIDE,LT,EQUAL,LPAREN,RPAREN,SEMICOLON,ERROR,IF,THEN,END,ELSE,REPEAT,UNTIL,READ,WRITE,ID,NUM,ASSIGN} TOKENTYPE; */

%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+
%option 	noyywrap

%%

"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}
":="            {return ASSIGN;}
"="             {return EQUAL;}
"<"             {return LT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return MULTIPLY;}
"/"             {return DIVIDE;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMICOLON;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
                
.               {return ERROR;}

%%


void printToken(TOKENTYPE currentToken, char* tokenString)
 {

  switch(currentToken)
  {
   case PLUS:
   	fprintf(listing,"\t PLUS %s\n",tokenString); 
  	break;
   case MINUS:
      	fprintf(listing,"\t MINUS %s\n",tokenString); 
   	break;
   case MULTIPLY:
      	fprintf(listing,"\t MULTIPLY %s\n",tokenString); 
   	break;
   case DIVIDE:
      	fprintf(listing,"\t DIVIDE %s\n",tokenString); 
   	break;
   case LT:
      	fprintf(listing,"\t LT %s\n",tokenString); 
   	break;
   case EQUAL:
      	fprintf(listing,"\t EQUAL %s\n",tokenString); 
   	break;
   case LPAREN:
      	fprintf(listing,"\t LPAREN %s\n",tokenString); 
   	break;
   case RPAREN:
      	fprintf(listing,"\t RPAREN %s\n",tokenString); 
   	break;
   case SEMICOLON:
      	fprintf(listing,"\t SEMICOLON %s\n",tokenString); 
   	break;
   case ENDOFFILE:
      	fprintf(listing,"ENDOFFILE\n"); 
   	break;
   case ERROR:
      	fprintf(listing,"\t ERROR %s\n",tokenString); 
   	break;
   case IF:
      	fprintf(listing,"\t IF %s\n",tokenString); 
   	break;
   case THEN:
      	fprintf(listing,"\t THEN %s\n",tokenString); 
   	break;
   case END:
      	fprintf(listing,"\t END %s\n",tokenString); 
   	break;
   case ELSE:
      	fprintf(listing,"\t ELSE %s\n",tokenString); 
   	break;
   case REPEAT:
      	fprintf(listing,"\t REPEAT %s\n",tokenString); 
   	break;
   case UNTIL:
      	fprintf(listing,"\t UNTIL %s\n",tokenString); 
   	break;
   case READ:
      	fprintf(listing,"\t READ %s\n",tokenString); 
   	break;
   case WRITE:
      	fprintf(listing,"\t WRITE %s\n",tokenString); 
   	break;
   case ID:
   	fprintf(listing,"\t ID %s\n",tokenString);
   	break;
   case NUM:
   	fprintf(listing,"\t NUM %s\n",tokenString);
   	break;
   case ASSIGN:
   	fprintf(listing,"\t ASSIGN %s\n",tokenString);
   	break;
   default:
   	break;
  } //end of switch case statement
 } //end of printToken function
 
 
 
TOKENTYPE getToken(void)
{ static int firstTime = TRUE;
  TOKENTYPE currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);

  fprintf(listing,"\t%d: ",lineno);
  printToken(currentToken,tokenString);


  return currentToken;
}

void main(int argc, char* argv[])
{
 if(argc!=3)
 {
  printf("Invalid usage.\nUsage: ./a.out <input> <output>\n");
  exit(100);
 }  //end of if statement
 
 
 source=fopen(argv[1],"r"); 
 listing=fopen(argv[2],"w");
 TOKENTYPE token;
 
 do
 {
  token=getToken();
 }while(token!=ENDOFFILE);
 
}
