/*
Grammar:
    E -> E + E
    E -> E * E
    E -> ( E )
    E -> id
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

char stk[60],inp[60];
int scnt=0,icnt=0;
//scnt---->stack counter
//icnt---->input counter
int reduce(char ch,int index,char *trans)
{
    scnt=index;
    stk[scnt]=ch;
    stk[scnt+1]='\0';

    printf("%s\t|\t%s\n",stk,trans);
    return 1;
}

int check()
{
    // E -> id
    if(scnt>=1 &&
       isalnum((unsigned char)stk[scnt]) &&
       stk[scnt]!='E')
        return reduce('E',scnt,"E -> id");

    // E -> ( E )
    if(scnt>=3 &&
       stk[scnt]==')' &&
       stk[scnt-1]=='E' &&
       stk[scnt-2]=='(')
        return reduce('E',scnt-2,"E -> ( E )");

    // E -> E * E
    if(scnt>=3 &&
       stk[scnt]=='E' &&
       stk[scnt-1]=='*' &&
       stk[scnt-2]=='E')
        return reduce('E',scnt-2,"E -> E * E");

    // E -> E + E
    if(scnt>=3 &&
       stk[scnt]=='E' &&
       stk[scnt-1]=='+' &&
       stk[scnt-2]=='E' &&
       inp[icnt]!='*')
        return reduce('E',scnt-2,"E -> E + E");

    return 0;
}

int main()
{
    int i;

    printf("Enter the expression:   ");
    scanf("%59s",inp);

    stk[0]='$';
    stk[1]='\0';

    printf("\nSTACK\t|\tREDUCTION\n");
    printf("--------------------------\n");

    for(i=0;inp[i]!='\0';i++)
    {
        stk[++scnt]=inp[icnt++];
        stk[scnt+1]='\0';

        printf("%s\t|\n",stk);

        while(check());
    }

    if(strcmp(stk,"$E")==0)
        printf("\nValid Expression.\n");
    else
        printf("\nInvalid Expression.\n");

    return 0;
}