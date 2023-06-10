%{
#include <stdio.h>
void yyerror (const char * s){
	
}

%}
%token tSTRING
%token tNUM
%token tPRINT
%token tGET
%token tSET
%token tFUNCTION
%token tRETURN
%token tIDENT
%token tIF
%token tEQUALITY
%token tGT
%token tLT
%token tGEQ
%token tLEQ
%token tADD
%token tSUB
%token tMUL
%token tDIV
%token tINC
%token tDEC

%%
PROGR:  '[' STMTLIST ']' 
	|	'[' ']'
;
STMTLIST:   STMT STMTLIST
        |   STMT
;

STMT:   SET
    |   IF
    |   PRINT
    |   RETURN
    |   INC
    |   DEC 
    |   EXPR
;

SET:    '[' tSET ',' tIDENT ',' EXPR ']'
;

IF: '[' tIF ',' CONDITION ',' THEN ']'
    |   '[' tIF ',' CONDITION ',' THEN ELSE ']'	
;

THEN:   '['  STMTLIST ']'
	|	'[' ']'
;

ELSE:   '['  STMTLIST ']'
	|	'[' ']'	
;

PRINT:  '[' tPRINT ',' EXPR ']'	
;

INC:  '[' tINC ',' tIDENT ']'
;

DEC:  '[' tDEC ',' tIDENT ']'
;

CONDITION: '[' tGT ',' EXPR ',' EXPR ']'
	|	'[' tEQUALITY ',' EXPR ',' EXPR ']'
	|	'[' tLT ',' EXPR ',' EXPR ']'
	|	'[' tLEQ ',' EXPR ',' EXPR ']'
	|	'[' tGEQ ',' EXPR ',' EXPR ']'
;

EXPR:   tNUM
	|   tSTRING
	|   GET
	|   FUNCTION
	|   OPERAND
	|   CONDITION
;
	
GET:    '[' tGET ',' tIDENT ']'
	|   '[' tGET ',' tIDENT ',' '[' ']' ']'
	|   '[' tGET ',' tIDENT ',' '[' EXPRLIST ']' ']'
;

EXPRLIST:   EXPR ',' EXPRLIST
	|   EXPR

;

FUNCTION:   '[' tFUNCTION ',' '[' PARAMLIST ']' ',' '[' STMTLIST ']'  ']'
	|   '[' tFUNCTION ',' '[' ']' ',' '[' ']'  ']'
	|   '[' tFUNCTION ',' '[' PARAMLIST ']' ',' '['  ']'  ']'
	|   '[' tFUNCTION ',' '[' ']' ',' '[' STMTLIST ']'  ']'
;

PARAMLIST:  tIDENT 
    |   tIDENT ',' PARAMLIST
;

OPERAND:    '[' tADD ',' EXPR ',' EXPR ']'
	|   '[' tSUB ',' EXPR ',' EXPR ']'
	|	'[' tMUL ',' EXPR ',' EXPR ']'
	|	'[' tDIV ',' EXPR ',' EXPR ']'
;

RETURN: '[' tRETURN ']'
    |   '[' tRETURN ',' EXPR ']'	
;

%%

int main(){

	if (yyparse())
	{
		printf("ERROR\n");
		return 1;
	}
	else
	{
		printf("OK\n");
		return 0;
	}
}
