
%{
#include <stdio.h>
#include <string.h>

int comment = 0;
%}

%%

"//".*                  { comment++; }

"/*"([^*]|\*+[^*/])*\*+"/"  { comment++; }

[0-9]+                  { fprintf(yyout, "%s\tNumber\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*  {
                            if (strcmp(yytext, "int") == 0 ||
                                strcmp(yytext, "float") == 0 ||
                                strcmp(yytext, "void") == 0 ||
                                strcmp(yytext, "if") == 0 ||
                                strcmp(yytext, "else") == 0 ||
                                strcmp(yytext, "main") == 0)
                                fprintf(yyout, "%s\tKeyword\n", yytext);
                            else
                                fprintf(yyout, "%s\tIdentifier\n", yytext);
                        }

(==|<=|>=|!=|<|>)       { fprintf(yyout, "%s\tRelational Operator\n", yytext); }

[=+\-*/%]               { fprintf(yyout, "%s\tArithmetic Operator\n", yytext); }

[(){};,]                { fprintf(yyout, "%s\tSpecial Symbol\n", yytext); }

[ \t\n]+                { /* Ignore whitespace */ }

.                       { /* Ignore other characters */ }

%%

int main()
{
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");

    if (yyin == NULL || yyout == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }

    yylex();

    fprintf(yyout, "\n%d Comments Ignored\n", comment);

    fclose(yyin);
    fclose(yyout);

    printf("Output saved successfully in output.txt\n");

    return 0;
}

int yywrap()
{
    return 1;
}
