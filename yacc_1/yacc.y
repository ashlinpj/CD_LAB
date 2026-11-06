
%{
#include <stdio.h>
int yylex(void);
void yyerror(char *s);
%}

%token NUM ID other
%left '+' '-'
%left '*' '/'

%%
start : T '\n' { printf("Valid Expression\n"); };

T : T '+' T
  | T '-' T
  | T '*' T
  | T '/' T
  | '(' T ')'
  | NUM
  | ID
  ;
%%

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

int main(void)
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}
