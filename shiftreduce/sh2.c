/*
Grammar:
    E -> E + T
    E -> E - T
    E -> T
    T -> T * F
    T -> T / F
    T -> F
    F -> id
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stk[64], inp[64];
int scnt = 0;

void reduce(char ch, int index, char *trans)
{
    scnt = index;
    stk[scnt] = ch;
    stk[scnt + 1] = '\0';

    printf("%s\t|\t%s\n", stk, trans);
}

int check(char next)
{
    // T->T * F
    if(scnt >= 3 &&
       stk[scnt - 2] == 'T' &&
       stk[scnt - 1] == '*' &&
       stk[scnt] == 'F')
    {
        reduce('T', scnt - 2, "T -> T * F");
        return 1;
    }

    //T->T / F
    if(scnt >= 3 &&
       stk[scnt - 2] == 'T' &&
       stk[scnt - 1] == '/' &&
       stk[scnt] == 'F')
    {
        reduce('T', scnt - 2, "T -> T / F");
        return 1;
    }

    //F->id
    if(scnt >= 1 &&
       isalnum((unsigned char)stk[scnt]) &&
       stk[scnt] != 'E' &&
       stk[scnt] != 'T' &&
       stk[scnt] != 'F')
    {
        reduce('F', scnt, "F -> id");
        return 1;
    }

    // F -> T
    if(scnt >= 1 && stk[scnt] == 'F')
    {
        reduce('T', scnt, "T -> F");
        return 1;
    }

    //  E ->E + T
    if(scnt >= 3 &&
       stk[scnt - 2] == 'E' &&
       stk[scnt - 1] == '+' &&
       stk[scnt] == 'T' &&
       next != '*' && next != '/')
    {
        reduce('E', scnt - 2, "E -> E + T");
        return 1;
    }

    //  E ->E - T
    if(scnt >= 3 &&
       stk[scnt - 2] == 'E' &&
       stk[scnt - 1] == '-' &&
       stk[scnt] == 'T' &&
       next != '*' && next != '/')
    {
        reduce('E', scnt - 2, "E -> E - T");
        return 1;
    }

    // E->T
    if(scnt >= 1 && stk[scnt] == 'T' &&
       next != '*' && next != '/')
    {
        reduce('E', scnt, "E -> T");
        return 1;
    }

    return 0;
}

int main()
{
    int i;

    printf("Enter Expression: ");
    scanf("%s", inp);

    stk[0] = '$';
    stk[1] = '\0';

    printf("\nSTACK\t|\tREDUCTION\n");
    printf("-------------------------\n");

    for(i = 0; inp[i] != '\0'; i++)
    {
        stk[++scnt] = inp[i];
        stk[scnt + 1] = '\0';

        printf("%s\t|\n", stk);

        while(check(inp[i + 1]));
    }

    if(strcmp(stk, "$E") == 0)
        printf("\nValid Expression.\n");
    else
        printf("\nInvalid Expression.\n");

    return 0;
}
