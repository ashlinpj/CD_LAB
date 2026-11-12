/*
Question:
Write a Lex program to search your name in an input file
and write FOUND or NOT FOUND in an output file.
The search should be case-insensitive and should ignore
spaces, tabs and newlines between the letters.
*/


%{
#include<stdio.h>
int found = 0;
%}

%%
[aA][ \t\r\n]*[sS][ \t\r\n]*[hH][ \t\r\n]*[lL][ \t\r\n]*[iI][ \t\r\n]*[nN]    { found = 1; }

.|\n    ;
%%

int main()
{
    yyin = fopen("input.txt","r");

    yylex();

    FILE *fp = fopen("output.txt","w");

    if(found == 1)
        fprintf(fp,"FOUND");
    else
        fprintf(fp,"NOT FOUND");

    fclose(fp);
    fclose(yyin);

    return 0;
}

int yywrap()
{
    return 1;
}

-------------------------------------------------------------
/*
[aA]          - Matches a or A
[ \t\r\n]*    - Allows zero or more spaces, tabs or newlines
[sS]          - Matches s or S
[hH]          - Matches h or H
[lL]          - Matches l or L
[iI]          - Matches i or I
[nN]          - Matches n or N
*/
---------------------------------------------------------------
