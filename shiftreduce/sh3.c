/*
GRAMMAR:
S -> AB
A -> aA
A -> a
B -> bB
B -> b
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
    // A -> a
    if(scnt >= 1 && stk[scnt] == 'a')
    {
        reduce('A', scnt, "A -> a");
        return 1;
    }

    // A -> aA
    if(scnt >= 2 &&
       stk[scnt - 1] == 'a' &&
       stk[scnt] == 'A')
    {
        reduce('A', scnt - 1, "A -> aA");
        return 1;
    }

    // B -> b
    if(scnt >= 1 && stk[scnt] == 'b')
    {
        reduce('B', scnt, "B -> b");
        return 1;
    }

    // B -> bB
    if(scnt >= 2 &&
       stk[scnt - 1] == 'b' &&
       stk[scnt] == 'B')
    {
        reduce('B', scnt - 1, "B -> bB");
        return 1;
    }

    // S -> AB
    if(scnt >= 2 &&
       stk[scnt - 1] == 'A' &&
       stk[scnt] == 'B')
    {
        reduce('S', scnt - 1, "S -> AB");
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

    if(strcmp(stk, "$S") == 0)
        printf("\nValid Expression.\n");
    else
        printf("\nInvalid Expression.\n");

    return 0;
}

