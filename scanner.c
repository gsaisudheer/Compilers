/* Scanner for Tiny Programming Language. For more specifics
   on Tiny language, refer to 'Compiler Construction: Principles and
   Practice' by 'Kenneth C Louden'

   Author: Sai Sudheer Goturu
*/

#include "main.h"

int main(int argc,char* argv[]){
	if (argc!=2)
	{ printf("input invalid. Usage: ./main <filename>\n");
	  exit(0);
	}

	curTokenIndex=0;
	lineNum=1;
	scanNextChar=1;
	eof=0;
	state=START;
	token=ID;

	char* str=argv[1];
	//printf("file name is %s\n",str);
	fp=fopen(str,"r");
	if(fp == NULL) {
      perror("Error opening input file");
      return(-1);
   	}
	output=fopen("output.tny","w");
	if(output==NULL){
		perror("Error opening output file\n");
		return(-1);
	}	
	TokenType tok;
   	if(fgets (buf, BUFLEN, fp)!=NULL ) {
		fprintf(output,"%2d: %s",lineNum,buf);
		bufpos=0;
		//c=buf[bufpos++];		
		while(bufpos<strlen(buf)&&(!eof)){
			tok=getToken();
			printString(tok);
			//sleep(1);
			}
   	}
   	fclose(fp);
    fclose(output);
	
}//end of main


