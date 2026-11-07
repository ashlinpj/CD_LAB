
%{
#include <stdio.h>
#include <string.h>

int comment = 0;
%}

%%

"//".*                  { comment++; }

"/*"([^*]|\*+[^*/])*\*+"/"  { comment++; }

[0-9]+                  { printf("%s\tNumber\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  {
                            if (strcmp(yytext, "int") == 0 ||
                                strcmp(yytext, "float") == 0 ||
                                strcmp(yytext, "void") == 0 ||
                                strcmp(yytext, "if") == 0 ||
                                strcmp(yytext, "else") == 0 ||
                                strcmp(yytext, "main") == 0)
                                printf("%s\tKeyword\n", yytext);
                            else
                                printf("%s\tIdentifier\n", yytext);
                        }

(==|<=|>=|!=|<|>)       { printf("%s\tRelational Operator\n", yytext); }

[=+\-*/%]               { printf("%s\tArithmetic Operator\n", yytext); }

[(){};,]                { printf("%s\tSpecial Symbol\n", yytext); }

[ \t\n]+                { /* Ignore whitespace */ }

.                       { /* Ignore other characters */ }

%%

int main()
{
    yyin = fopen("input.txt", "r");

    if (yyin == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    yylex();

    printf("\n%d Comments Ignored\n", comment);

    fclose(yyin);

    return 0;
}

int yywrap()
{
    return 1;
}
