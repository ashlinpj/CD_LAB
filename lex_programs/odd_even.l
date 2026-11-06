%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+  {
            int n = atoi(yytext);
            if (n % 2 == 0)
                printf("Even number\n");
            else
                printf("Odd number\n");
        }

%%

int main()
{
    printf("Enter a number: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
