%{
#include<stdio.h>

int l=0,w=0,c=0;
%}

%%
\n          { l++; c++; }
[ \t]+      { c += yyleng; }
[^ \t\n]+   { w++; c += yyleng; }
%%

int main()
{
    extern FILE *yyin;

    yyin=fopen("input.txt","r");

    if(yyin==NULL){
        printf("File not found");
        return 1;
    }

    yylex();

    printf("No. of lines: %d\n",l);
    printf("No. of words: %d\n",w);
    printf("No. of characters: %d\n",c);

    fclose(yyin);
    return 0;
}

int yywrap()
{
    return 1;
}