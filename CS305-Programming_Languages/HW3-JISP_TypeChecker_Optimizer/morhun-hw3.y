%{
#include <stdio.h>
#include <stdlib.h>
#include "morhunNodesHW3.h"
#include <string.h>

void yyerror (const char *s) 
{}
int yylex();
%}

%union {
	TreeNode attributenode;
	int intval;
	char * strval;
	float realval;
	int oploc;
}

%token <intval> tNUM
%token <strval> tSTRING 
%token <realval> tREAL
%token <oploc> tADD tSUB tMUL tDIV

%token    tPRINT tGET tSET tFUNCTION tRETURN tIDENT tEQUALITY tIF tGT tLT tGEQ tLEQ tINC tDEC

%type <attributenode> EXPR
%type <attributenode> STMT
%type <attributenode> OPERATION
%type <attributenode> RETURNSTMT
%type <attributenode> SETSTMT
%type <attributenode> PRINT
%type <attributenode> IF
%type <attributenode> UNARYOPERATION

%start PROG

%%

PROG:		'[' STMTLST ']'
;

STMTLST:    STMTLST STMT {
            if($2.validType == 1 && $2.type == INT_TYPE)
            {
                printf("Result of expression on %d is (%d)\n", $2.lineNum, $2.integerValue);
            }
            
            else if($2.validType == 1 && $2.type == REAL_TYPE)
            {
                printf("Result of expression on %d is (%.1f)\n", $2.lineNum, $2.realValue);
            }

            else if($2.validType == 1 && $2.type == STRING_TYPE)
            {
                printf("Result of expression on %d is (%s)\n", $2.lineNum, $2.stringValue);
            }              
    } |
;

STMT:   SETSTMT | IF | PRINT | UNARYOPERATION 
	|   EXPR {$$ = $1;}
	|   RETURNSTMT {$$ = $1;}
;

SETSTMT:	'[' tSET ',' tIDENT ',' EXPR ']' {
            if( $6.validType == 1 && $6.type == INT_TYPE)
            {
                printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
            }
            
            else if( $6.validType == 1 && $6.type == REAL_TYPE)
            {
                printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
            }

            else if($6.validType == 1 && $6.type == STRING_TYPE)
            {
                printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
            }
		}
;

RETURNSTMT:	'[' tRETURN ',' EXPR ']' {$$ = $4;}
		| '[' tRETURN ']' {
			TreeNode node;
			node.validType = 0;
			node.type = COMPLETED_TYPE;
			node.printFlag = 0;

			$$ = node;
		}
;

EXPR:		tNUM {
				TreeNode node;
                node.type = INT_TYPE;
				node.validType = 0;
				node.printFlag = 0;
				
				node.integerValue = $1;
				$$ = node;
				}

			| tREAL {

				TreeNode node;
                node.type = REAL_TYPE;
				node.validType = 0;
				node.realValue = $1;
				node.printFlag = 0;

				$$ = node;
			}
			
			| tSTRING {

				TreeNode node;
                node.type = STRING_TYPE;
				node.validType = 0;
				node.stringValue = $1;
				node.printFlag = 0;
					
				$$ = node;
			}

			| OPERATION {
				$$ = $1;
			}
			
			| GETEXPR {
				TreeNode node;
                node.type = COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;
					
				$$ = node;
			}
			| FUNCTION {
				TreeNode node;
                node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;
				
				$$ = node;
			}

			| CONDITION {
				TreeNode node;
                node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;
				
				$$ = node;
			}
;

GETEXPR:	'[' tGET ',' tIDENT ',' '[' EXPRLIST ']' ']'
		| '[' tGET ',' tIDENT ',' '[' ']' ']'
		| '[' tGET ',' tIDENT ']'
;

EXPRLIST:	EXPRLIST ',' EXPR | EXPR
;

FUNCTION:	 '[' tFUNCTION ',' '[' PARAMETERLIST ']' ',' '[' STMTLST ']' ']'
		| '[' tFUNCTION ',' '[' ']' ',' '[' STMTLST ']' ']'
;

PARAMETERLIST: PARAMETERLIST ',' tIDENT | tIDENT
;

PRINT:		'[' tPRINT ',' EXPR ']' {
            if($4.validType == 1 && $4.type == INT_TYPE)
            {
                printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
            }
            else if($4.validType == 1 && $4.type == REAL_TYPE)
            {
                printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
            }

            else if($4.validType == 1 && $4.type == STRING_TYPE)
            {
                printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
            }

		}
;

OPERATION:	'[' tADD ',' EXPR ',' EXPR ']'{
			if($4.type == COMPLETED_TYPE || $6.type == COMPLETED_TYPE)
            {
				TreeNode node;
				node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;

				$$ = node;
				if($4.validType == 1 && $4.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
					
				}

				else if($4.validType == 1 && $4.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
				}

				else if($4.validType == 1 && $4.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
				}

				if($6.validType == 1 && $6.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
				}

				else if($6.validType == 1 && $6.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
				}

				else if($6.validType == 1 && $6.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
				}
			}

			else{

				if($4.type == INT_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
					node.type = INT_TYPE;
					node.validType = 1;

					node.integerValue = $4.integerValue + $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
					node.type = REAL_TYPE;
					node.validType = 1;

					node.realValue = $4.realValue + $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == INT_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.integerValue + $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue + $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == STRING_TYPE && $6.type == STRING_TYPE)
                {
					TreeNode node;
                    node.type = STRING_TYPE;
					node.validType = 1;

					node.lineNum = $2;

                    int strLen = strlen($4.stringValue) +  strlen($6.stringValue);
					node.stringValue = (char *) malloc(strLen * sizeof(char));
					strcpy(node.stringValue, $4.stringValue);
					strcat(node.stringValue, $6.stringValue);

					$$ = node;

				}

				else{
					TreeNode node;
					node.type = COMPLETED_TYPE;
					node.validType = 0;
					node.printFlag = 1;
					
					node.lineNum = globalLineNum;
					$$ = node;

					printf("Type mismatch on %d\n",globalLineNum);
					
					if($4.validType == 1 && $4.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
						
					}

					else if($4.validType == 1 && $4.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
					}

					else if($4.validType == 1 && $4.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
					}

					if($6.validType == 1 && $6.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
					}

					else if($6.validType == 1 && $6.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
					}

					else if($6.validType == 1 && $6.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
					}
				}
			}
		}
			
		| '[' tSUB ',' EXPR ',' EXPR ']' {
			if($4.type == COMPLETED_TYPE || $6.type == COMPLETED_TYPE)
            {
				TreeNode node;
				node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;

				$$ = node;
				if($4.validType == 1 && $4.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
					
				}

				else if($4.validType == 1 && $4.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
				}

				else if($4.validType == 1 && $4.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
				}

				if($6.validType == 1 && $6.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
				}

				else if($6.validType == 1 && $6.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
				}

				else if($6.validType == 1 && $6.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
				}
			}

			else{

				if($4.type == INT_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = INT_TYPE;
					node.validType = 1;
					
					node.integerValue = $4.integerValue - $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}
				else if($4.type == REAL_TYPE && $6.type == REAL_TYPE
                ){
					TreeNode node;
					node.type = REAL_TYPE;
					node.validType = 1;

					node.realValue = $4.realValue - $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}
				
				
				else if($4.type == INT_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
					node.type = REAL_TYPE;
					node.validType = 1;

					node.realValue = $4.integerValue - $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue - $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}
				else{
					
					TreeNode node;
                    node.type = COMPLETED_TYPE;
					node.validType = 0;
					node.printFlag = 1;
					
					node.lineNum = globalLineNum;
					$$ = node;

					printf("Type mismatch on %d\n",globalLineNum);
					
					if($4.validType == 1 && $4.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
						
					}

					else if($4.validType == 1 && $4.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
					}

					else if($4.validType == 1 && $4.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
					}

					if($6.validType == 1 && $6.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
					}

					else if($6.validType == 1 && $6.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
					}

					else if($6.validType == 1 && $6.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
					}
				}
			}

		}
			
		| '[' tMUL ',' EXPR ',' EXPR ']' {

			if($4.type == COMPLETED_TYPE || $6.type == COMPLETED_TYPE)
            {
				TreeNode node;
				node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;

				$$ = node;
				if($4.validType == 1 && $4.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
					
				}

				else if($4.validType == 1 && $4.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
				}

				else if($4.validType == 1 && $4.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
				}

				if($6.validType == 1 && $6.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
				}

				else if($6.validType == 1 && $6.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
				}

				else if($6.validType == 1 && $6.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
				}
			}

			else{
				if($4.type == INT_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = INT_TYPE;
					node.validType = 1;
					
					node.integerValue = $4.integerValue * $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue * $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == INT_TYPE && $4.integerValue >= 0 && $6.type == STRING_TYPE)
                {
					TreeNode node;
                    node.type = STRING_TYPE;
					node.validType = 1;
					
					int strSize = $4.integerValue * strlen($6.stringValue);

                    if(strSize == 0)
                    {
						node.stringValue = "";
                    }

					else{
					    node.stringValue = (char *) malloc(strSize * sizeof(char));
						strcpy(node.stringValue, $6.stringValue);

                        int i;
						for(i = 0; i < $4.integerValue -1; i++)
                        {
							strcat(node.stringValue, $6.stringValue);
						}
					}
					
					node.lineNum = $2;
					$$ = node;
				}

				else if($4.type == INT_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.integerValue * $6.realValue;
					node.lineNum = $2;
					$$ = node;
				}

				else if($4.type == REAL_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue * $6.integerValue;
					node.lineNum = $2;
					$$ = node;
				}

				else{
					TreeNode node;
                    node.type = COMPLETED_TYPE;
					node.validType = 0;
					node.printFlag = 1;
					
					node.lineNum = globalLineNum;
					$$ = node;

					printf("Type mismatch on %d\n",globalLineNum);

					if($4.validType == 1 && $4.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
						
					}

					else if($4.validType == 1 && $4.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
					}

					else if($4.validType == 1 && $4.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
					}

					if($6.validType == 1 && $6.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
					}

					else if($6.validType == 1 && $6.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
					}

					else if($6.validType == 1 && $6.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
					}
				}
			}

		}
			
		| '[' tDIV ',' EXPR ',' EXPR ']' {
			if($4.type == COMPLETED_TYPE || $6.type == COMPLETED_TYPE)
            {
				TreeNode node;
				node.type =  COMPLETED_TYPE;
				node.validType = 0;
				node.printFlag = 0;

				$$ = node;

				if($4.validType == 1 && $4.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
					
				}

				else if($4.validType == 1 && $4.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
				}

				else if($4.validType == 1 && $4.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
				}

				if($6.validType == 1 && $6.type == INT_TYPE)
				{
					printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
				}

				else if($6.validType == 1 && $6.type == REAL_TYPE)
				{
					printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
				}

				else if($6.validType == 1 && $6.type == STRING_TYPE)
				{
					printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
				}
			}

			else{
				if($4.type == INT_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = INT_TYPE;
					node.validType = 1;
					
					node.integerValue = $4.integerValue / $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue / $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}
				
				else if($4.type == INT_TYPE && $6.type == REAL_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.integerValue / $6.realValue;
					node.lineNum = $2;
					$$ = node;

				}

				else if($4.type == REAL_TYPE && $6.type == INT_TYPE)
                {
					TreeNode node;
                    node.type = REAL_TYPE;
					node.validType = 1;
					
					node.realValue = $4.realValue / $6.integerValue;
					node.lineNum = $2;
					$$ = node;

				}

				else{
					TreeNode node;
                    node.type = COMPLETED_TYPE;
					node.validType = 0;
					node.printFlag = 1;
					
					node.lineNum = globalLineNum;
					$$ = node;

					printf("Type mismatch on %d\n",globalLineNum);
				
					if($4.validType == 1 && $4.type == INT_TYPE)
					{
						
						printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
						
					}

					else if($4.validType == 1 && $4.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
					}

					else if($4.validType == 1 && $4.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
					}
					
					if($6.validType == 1 && $6.type == INT_TYPE)
					{
						printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
					}

					else if($6.validType == 1 && $6.type == REAL_TYPE)
					{
						printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
					}

					else if($6.validType == 1 && $6.type == STRING_TYPE)
					{
						printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
					}
				}
			}

		}			
;	

UNARYOPERATION: '[' tINC ',' tIDENT ']' {TreeNode node; node.validType = 0; $$ = node;}
		| '[' tDEC ',' tIDENT ']' {TreeNode node; node.validType = 0; $$ = node;}
;

IF:		'[' tIF ',' CONDITION ',' '[' STMTLST ']' ']' {TreeNode node; node.validType = 0; $$ = node;}
		| '[' tIF ',' CONDITION ',' '[' STMTLST ']' '[' STMTLST ']' ']' {TreeNode node; node.validType = 0; $$ = node;}
;

CONDITION:	'[' tEQUALITY ',' EXPR ',' EXPR ']'
		| '[' tGT ',' EXPR ',' EXPR ']'{

			if($4.validType == 1 && $4.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
				
			}

            else if($4.validType == 1 && $4.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
            }

			else if($4.validType == 1 && $4.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
            }
			
            if($6.validType == 1 && $6.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
			}

            else if($6.validType == 1 && $6.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
            }

			else if($6.validType == 1 && $6.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
            }
		}

		| '[' tLT ',' EXPR ',' EXPR ']'
		{

			if($4.validType == 1 && $4.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
				
			}

            else if($4.validType == 1 && $4.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
            }

			else if($4.validType == 1 && $4.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
            }
			
            if($6.validType == 1 && $6.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
			}

            else if($6.validType == 1 && $6.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
            }

			else if($6.validType == 1 && $6.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
            }
			
		}

		| '[' tGEQ ',' EXPR ',' EXPR ']'
		{

			if($4.validType == 1 && $4.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
				
			}

            else if($4.validType == 1 && $4.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
            }

			else if($4.validType == 1 && $4.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
            }
			
            if($6.validType == 1 && $6.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
			}

            else if($6.validType == 1 && $6.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
            }

			else if($6.validType == 1 && $6.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
            }
		}

		| '[' tLEQ ',' EXPR ',' EXPR ']'
		{

			if($4.validType == 1 && $4.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $4.lineNum, $4.integerValue);
				
			}

            else if($4.validType == 1 && $4.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $4.lineNum, $4.realValue);
            }

			else if($4.validType == 1 && $4.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $4.lineNum, $4.stringValue);
            }
			
            if($6.validType == 1 && $6.type == INT_TYPE)
            {
				printf("Result of expression on %d is (%d)\n", $6.lineNum, $6.integerValue);
			}

            else if($6.validType == 1 && $6.type == REAL_TYPE)
            {
				printf("Result of expression on %d is (%.1f)\n", $6.lineNum, $6.realValue);
            }

			else if($6.validType == 1 && $6.type == STRING_TYPE)
            {
				printf("Result of expression on %d is (%s)\n", $6.lineNum, $6.stringValue);
            }
		}
;
%%

int main ()
{
	if (yyparse()) {
		// parse error
		printf("ERROR\n");
		return 1;
	}
	else {
		// successful parsing
		return 0;
	}
}