
%{
#include <stdio.h>
int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]      { vowels++; }
[a-zA-Z]          { consonants++; }
%%

int main()
{
    printf("Enter a string: ");
    yylex();

    printf("Total vowels = %d\n", vowels);
    printf("Total consonants = %d\n", consonants);

    return 0;
}

int yywrap()
{
    return 1;
}
