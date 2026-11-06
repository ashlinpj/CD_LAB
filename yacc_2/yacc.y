
%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUM other
%left '+' '-'
%left '*' '/'

%%
start : T '\n' { printf("Result: %d\n", $1); }
      ;

T : T '+' T   { $$ = $1 + $3; }
  | T '-' T   { $$ = $1 - $3; }
  | T '*' T   { $$ = $1 * $3; }
  | T '/' T   { $$ = $1 / $3; }
  | '(' T ')' { $$ = $2; }
  | NUM       { $$ = $1; }
  ;
%%

void yyerror(const char *s)
{
    printf("Error: Invalid expression\n");
}

int main(void)
{
    printf("Enter arithmetic expression: ");
    yyparse();
    return 0;
}
