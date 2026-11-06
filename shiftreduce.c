
// Target Grammar
// E -> E+E | E*E | (E) | id

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stk[100], inp[100];
int scnt = 0;

int reduce(char ch, int index, char *trans)
{
    scnt = index;
    stk[scnt] = ch;
    stk[scnt + 1] = '\0';

    printf("%s\t|\t%s\n", stk, trans);
    return 1;
}

int check()
{
    if (scnt >= 3 &&
        stk[scnt] == 'E' &&
        stk[scnt - 1] == '+' &&
        stk[scnt - 2] == 'E')
        return reduce('E', scnt - 2, "E -> E+E");

    if (scnt >= 3 &&
        stk[scnt] == 'E' &&
        stk[scnt - 1] == '*' &&
        stk[scnt - 2] == 'E')
        return reduce('E', scnt - 2, "E -> E*E");

    if (scnt >= 3 &&
        stk[scnt] == ')' &&
        stk[scnt - 1] == 'E' &&
        stk[scnt - 2] == '(')
        return reduce('E', scnt - 2, "E -> (E)");

    if (scnt >= 1 &&
        isalpha((unsigned char)stk[scnt]) &&
        stk[scnt] != 'E')
        return reduce('E', scnt, "E -> id");

    return 0;
}

int main()
{
    int i;

    printf("Enter Expression to Validate: ");
    scanf("%99s", inp);

    stk[0] = '$';
    stk[1] = '\0';
    scnt = 0;

    printf("\nSTACK\t|\tREDUCTION\n");
    printf("-------------------------------\n");

    for (i = 0; inp[i] != '\0'; i++)
    {
        // Treat id as one symbol
        if (inp[i] == 'i' && inp[i + 1] == 'd')
        {
            stk[++scnt] = 'x';
            i++;
        }
        else
        {
            stk[++scnt] = inp[i];
        }

        stk[scnt + 1] = '\0';
        printf("%s\t|\tSHIFT\n", stk);

        while (check());
    }

    if (strcmp(stk, "$E") == 0)
        printf("\nValid Expression.\n");
    else
        printf("\nInvalid Expression.\n");

    return 0;
}
