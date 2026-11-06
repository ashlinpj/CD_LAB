%{
#include<stdio.h>
#include<stdlib.h>

int flag,i,n;
%}

%%
[0-9]+ {
    n=atoi(yytext);
    flag=1;

    if(n<=1){
        flag=0;
    }
    else{
        for(i=2;i<n;i++){
            if(n%i==0){
                flag=0;
                break;
            }
        }
    }

    if(flag){
        printf("Prime Number\n");
    }
    else{
        printf("Not Prime Number\n");
    }
}
%%

int main(){
    printf("Enter the number: ");
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}