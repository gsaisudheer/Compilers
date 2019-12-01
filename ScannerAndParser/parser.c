/* Parser for Tiny Language (For more information,
   see 'Compiler Construction: Principles and Practice' 
   by Kenneth C Louden
 
   Author: Sai Sudheer Goturu
*/

#include "main.h"
#define MAXCHILDREN 3

typedef enum {Stmt,Exp}NodeKind;
typedef enum {If,Repeat,Assign,Read,Write}StmtKind;
typedef enum {Op,Const,Id}ExpKind;
typedef struct treeNode{
	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;
	int lineNo;
	NodeKind nodekind;
	union {StmtKind stmt;ExpKind exp;}kind;
	union {TokenType op;int val;char* name;}attr;
}TreeNode;

TreeNode* newStmtNode(StmtKind stmtkind){
	TreeNode* t=(TreeNode*)malloc(sizeof(TreeNode));
	if(t==NULL)
	{	
		printf("out of memory at line: %d\n",lineNum);
		exit(0);
	}
	int i;
	for(i=0;i<MAXCHILDREN;i++)
		t->child[i]=NULL;
	t->sibling=NULL;
	t->lineNo=lineNum;
	t->nodekind=Stmt;
	t->kind.stmt=stmtkind;
	return t;
}//end newStmtNode

TreeNode* newExpNode(ExpKind expkind){
	TreeNode* t=(TreeNode*)malloc(sizeof(TreeNode));
	if(t==NULL){
		printf("out of memory at line: %d\n",lineNum);
		exit(0);
	}
	int i;
	for(i=0;i<MAXCHILDREN;i++)
		t->child[i]=NULL;
	t->sibling=NULL;
	t->lineNo=lineNum;
	t->nodekind=Exp;
	t->kind.exp=expkind;
	return t;
}//end newExpNode

void match(TokenType tok){
	if(tok==token)
		token=getToken();
	else
		printf("unexpected token at %d: %s\n",lineNum+1,currentToken);
		
}//end match

TreeNode* parse(void);
TreeNode* stmt_seq(void);
TreeNode* stmt(void);
TreeNode* if_stmt(void);
TreeNode* expression(void);
TreeNode* repeat_stmt(void);
TreeNode* assign_stmt(void);
TreeNode* read(void);
TreeNode* write(void);
TreeNode* simple_exp(void);
TreeNode* term(void);
TreeNode* factor(void);
TreeNode* exp_stmt(void);

TokenType tok;
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Invalid input. Usage: ./a.out <filename>\n");
		exit(0);
	}
	char* str=argv[1];
	fp=fopen(str,"r");
	if(fp == NULL) {
      perror("Error opening input file\n");
      return(-1);
   	}
	output=fopen("parseOutput.tny","w");
	if(output==NULL){
		perror("Error opening output file\n");
		return(-1);
	}
	if(fgets (buf, BUFLEN, fp)!=NULL ) {
		bufpos=0;
		//c=buf[bufpos++];	
		token=getToken();
			//sleep(1);
   	}
	TreeNode *t=parse();
   	fclose(fp);
}//end of main

TreeNode* parse(void){
	TreeNode *t;
	t=stmt_seq();
	if(token!=ENDFILE)
		printf("syntax error at %d: %s\n",lineNum,currentToken);
	return t;
}//end of parse

TreeNode* stmt_seq(void){
	TreeNode *t,*s;
	t=stmt();
	s=t;
	while((token!=ENDFILE)&&(token!=ELSE)&&(token!=UNTIL)&&(token!=END))
	{
		TreeNode* p;
		match(SEMI);
		p=stmt();
		if(p!=NULL){
			if(t==NULL)
				t=s=p;
			else{
				s->sibling=p;
				s=p;
			}
		}
	}
	return t;
}//end of stmt_seq

TreeNode* stmt(void){
	TreeNode *t=NULL;
	switch(token){
		case IF:
			t=if_stmt();
			break;
		case REPEAT:
			t=repeat_stmt();
			break;
		case ID:
			t=assign_stmt();
			break;
		case READ:
			t=read();
			break;
		case WRITE:
			t=write();
			break;
		default:
			printf("Syntax Error at %d\t %s",lineNum+1,currentToken);
			printf("\n");
			token=getToken();
			break;
	}//end switch(token)
	return t;
}//end of stmt

TreeNode* if_stmt(void){
	TreeNode* t=newStmtNode(If);
	match(IF);
	if(t!=NULL){
		t->child[0]=exp_stmt();
		match(THEN);
		t->child[1]=stmt_seq();
		if(token==ELSE)
		{
			match(ELSE);
			t->child[2]=stmt_seq();
		}//end if(token==ELSE)
	}//end if(t!=NULL)
	match(END);
	return t;
}//end of if_stmt

TreeNode* repeat_stmt(void){
	TreeNode* t=newStmtNode(Repeat);	
	match(REPEAT);
	if(t!=NULL){
		t->child[0]=stmt_seq();
		match(UNTIL);
		t->child[1]=exp_stmt();
	}//end t!=NULL
	return t;
}//end of repeat_stmt

TreeNode* assign_stmt(void){
	TreeNode* t=newStmtNode(Assign);
	if(t!=NULL && token==ID)
	{
		int len=strlen(currentToken);
		t->attr.name=(char*)malloc(sizeof(char)*(len+1));
		strcpy(t->attr.name,currentToken);
		match(ID);
		match(ASSIGN);
		t->child[0]=exp_stmt();		
	}
	return t;
}//end of assign_stmt

TreeNode* read(void){
	TreeNode* t=newStmtNode(Read);
	match(READ);
	if(t!=NULL){
		if(token==ID)
		{
			int len=strlen(currentToken);		
			t->attr.name=(char*)malloc(sizeof(char)*(len+1));
			strcpy(t->attr.name,currentToken);
			match(ID);
		}
	}
	return t;	
}//end of read

TreeNode* write(void){
	TreeNode* t=newStmtNode(Write);
	match(WRITE);
	if(t!=NULL)
		t->child[0]=exp_stmt();
	return t;
}//end of write

TreeNode* exp_stmt(void){
	TreeNode* t;
	t=simple_exp();
	if(token==LT||token==EQ)
	{
		TreeNode* e=newExpNode(Op);
		if(e!=NULL){
			e->child[0]=t;
			e->attr.op=token;
			match(token);
			e->child[1]=simple_exp();
			return e;
		}//end e!=NULL
	}//end if token==LT||token==EQ
}//end of exp_stmt

TreeNode* simple_exp(void){
	TreeNode* t;
	t=term();
	while(token==PLUS||token==MINUS)
	{
		TreeNode *s=newExpNode(Op);
		if(s!=NULL)
		{
			s->child[0]=t;
			s->attr.op=token;
			match(token);
			s->child[1]=term();
			t=s;
		}//end if		
	}//end while
	return t;
}//end of simple_exp

TreeNode* term(void){
	TreeNode* t;
	t=factor();
	while(token==TIMES || token==OVER){
		TreeNode* s=newExpNode(Op);
		if(s!=NULL){
			s->child[0]=t;
			s->attr.op=token;
			match(token);
			s->child[1]=factor();
			t=s;
		}//endif
	}//end while
	return t;
}//end term


TreeNode* factor(void){
	TreeNode* t=NULL;
	switch(token){
		case LPAREN:
			match(LPAREN);
			t=exp_stmt();
			match(RPAREN);
			break;
		case NUM:
			t=newExpNode(Const);
			if(t!=NULL && token==NUM)
				t->attr.val=atoi(currentToken);
			match(NUM);
			break;
		case ID:
			t=newExpNode(Id);
			if(t!=NULL && token==ID){
				int len=strlen(currentToken);
				t->attr.name=(char*)malloc(sizeof(char)*len);
				strcpy(t->attr.name,currentToken);
			}
			match(ID);
			break;
		default:
			printf("syntax error at line:%d\n",lineNum+1);
			printToken(currentToken,0);
			token=getToken();
			break;
	}//end switch
	return t;
}//end factor


