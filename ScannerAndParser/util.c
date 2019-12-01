/* Utility Functions for the scanner for Tiny Programming Language.
   For more details on Tiny Programming language, refer to the book
   'Compiler Construction: Principles and Practice' by 'Kenneth C Louden'

   Author: Sai Sudheer Goturu
*/

#include "main.h"
TokenType checkKeyword(char* str);
TokenType printToken(char* str,int isID){
	//printf("str received is %s\n",str);
	if(isID==1){
		token=checkKeyword(str);
		if(token!=ID)
			fprintf(output,"\t%d: reserved word: %s\n",lineNum,str);
		else 
			fprintf(output,"\t%d: ID, name= %s\n",lineNum,str);
	}
	else if(isID==2){
		token=NUM;
		fprintf(output,"\t%d: NUM, val= %s\n",lineNum,str);
	}
	//state=START;
	return token;
}//end of printToken
char getNextChar(void);

TokenType getToken(void){
	//if(scanNextChar)
	currentToken[0]='\0';
	curTokenIndex=0;
	int error=0;
	int id=0;
	valid=1;
	//c=buf[bufpos++];
	while(state!=DONE){
		c=getNextChar();
		if(eof)
		{
			token=ENDFILE;
			return token;
		}
		switch(state){
			case START:
				if(c==' '||c=='\t'||c=='\n'){
					state=START;
				}
				else if(isdigit(c) && !error){
					id=2;
					state=INNUM;
					currentToken[curTokenIndex++]=c;
					token=NUM;
				}
				else if(isalpha(c)){
					id=1;
					state=INID;
					currentToken[curTokenIndex++]=c;
					token=ID;
				}
				else if(c==':')
					state=INASSIGN;
				else if(c=='{')
					state=INCOMMENT;
					else{
						state=DONE;
					switch(c){	
						case '+':
							token=PLUS;
							fprintf(output,"\t%d: %c\n",lineNum,'+');
							break; 
						case '-': 	
							token=MINUS;
							fprintf(output,"\t%d: %c\n",lineNum,'-');
							break;
						case '*': 
							token=TIMES;
							fprintf(output,"\t%d: %c\n",lineNum,'*');
							break;
						case '/': 
							token=OVER;
							fprintf(output,"\t%d: %c\n",lineNum,'/');
							break;
						case '<': 
							token=LT;
							fprintf(output,"\t%d: %c\n",lineNum,'<');
							break;
						case '=':
							token=EQ;
							fprintf(output,"\t%d: %c\n",lineNum,'=');
							break;	
						case ';':
							token=SEMI;
							fprintf(output,"\t%d: %c\n",lineNum,';');
							break;
						case '(':
							token=LPAREN;
							fprintf(output,"\t%d: %c\n",lineNum,'(');
							break;
						case ')':
							token=RPAREN;
							fprintf(output,"\t%d: %c\n",lineNum,')');
							break;
						default:
							//fprintf(output,"\t%d: ERROR %c\n",lineNum,c);
							currentToken[curTokenIndex++]=c;
							error=1;
					}//end of switch(c)
				}//end else in START stae
				break;
			case INCOMMENT:
				if(c=='}')
					state=START;
				//else if(c=='\n')
					//	return;
				break;
			case INNUM:
				if(!isdigit(c))
				{
					state=DONE;
					bufpos--;
				}
				else currentToken[curTokenIndex++]=c;
				break;
			case INID:
				if(!isalpha(c))
				{
					state=DONE;
					bufpos--;
				}
				else currentToken[curTokenIndex++]=c;
				break;
			case INASSIGN:
				if(c=='='){
					error=0;
					token=ASSIGN;
					fprintf(output,"\t%d: :=\n",lineNum);
				}
				else{
					bufpos--;
					error=1;
				}
				state=DONE;
				break;
	}//end of switch(state)
		if(bufpos>=BUFLEN)
			return;
		//c=buf[bufpos++];
	}//end of while	
	//state=DONE
	if(state==DONE){
	currentToken[curTokenIndex]='\0';
	if(strlen(currentToken)!=0){
		token=printToken(currentToken,id);
	}
	if(error){
		token=ERROR;
		printError(currentToken,lineNum);
	}
	state=START;
	}//end state=DONE
	return token;
}//end of getToken

char getNextChar(void){
	c=buf[bufpos++];
	if(bufpos>strlen(buf))
	{
		bufpos=0;
		if(fgets(buf,BUFLEN,fp)!=NULL)
		{
			lineNum++;
			fprintf(output,"%2d: %s",lineNum,buf);
			c= buf[bufpos++];
		}
		else{
			eof=1;
			c=0;
		}
	}
	return c;
}//end of getNextChar
/*option is set to true only if this function 
* is called from INID or INNUM, wherein a check
* is required to find out whether it is a keyword
* and then printed accordingly.*/

void printString(TokenType tok){
	tok++;
	switch(tok){
		case 1:	printf("ENDFILE\n");	break;
		case 2:	printf("ERROR\n");	break;
		case 3:	printf("IF\n"); break;
		case 4:	printf("THEN\n"); break;
		case 5:	printf("ELSE\n"); break;
		case 6:	printf("END\n"); break;
		case 7:	printf("REPEAT\n"); break;
		case 8:	printf("UNTIL\n"); break;
		case 9:	printf("READ\n"); break;
		case 10:printf("WRITE\n"); break;
		case 11:printf("ID\n");	break;
		case 12:printf("NUM\n"); break;
		case 13:printf("ASSIGN\n"); break;
		case 14:printf("EQ\n");	break;
		case 15:printf("LT\n");	break;
		case 16:printf("PLUS\n");break;
		case 17:printf("MINUS\n");break;
		case 18:printf("TIMES\n");break;
		case 19:printf("OVER\n");break;
		case 20:printf("LPAREN\n");break;
		case 21:printf("RPAREN\n");	break;
		case 22:printf("SEMI\n");break;
	}//end of switch(tok)
}//end of printString

TokenType checkKeyword(char* str){
	if(strcmp(str,"if")==0)
		return IF;
	else if(strcmp(str,"then")==0)
		return THEN;
	else if(strcmp(str,"else")==0)
		return ELSE;
	else if(strcmp(str,"end")==0)
		return END;	
	else if(strcmp(str,"repeat")==0)
		return REPEAT;
	else if(strcmp(str,"until")==0)
		return UNTIL;
	else if(strcmp(str,"read")==0)
		return READ;
	else if(strcmp(str,"write")==0)
		return WRITE;
	else 
		return ID;
}//end of checkKeyword

void printError(char* str,int lineNum){
	fprintf(output,"\t%d: ERROR IN THE LINE: %s\n",lineNum,str);
}//end of printError
