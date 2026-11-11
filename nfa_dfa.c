
#include <stdio.h>

int main()
{
    int n, m, start;
    int trans[10][10][10] = {0};
    int dfa[100][10] = {0};
    int temp[10], count = 1, flag;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter transition table (1 if transition exists, otherwise 0):\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("State %d, Symbol %d: ", i, j);

            for (int k = 0; k < n; k++)
                scanf("%d", &trans[i][j][k]);
        }
    }

    printf("Enter start state: ");
    scanf("%d", &start);

    dfa[0][start] = 1;

    for (int i = 0; i < count; i++)
    {
        for (int a = 0; a < m; a++)
        {
            for (int j = 0; j < n; j++)
                temp[j] = 0;

            for (int j = 0; j < n; j++)
            {
                if (dfa[i][j] == 1)
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (trans[j][a][k] == 1)
                            temp[k] = 1;
                    }
                }
            }

            flag = 0;

            for (int j = 0; j < count; j++)
            {
                int same = 1;

                for (int k = 0; k < n; k++)
                    if (dfa[j][k] != temp[k])
                        same = 0;

                if (same)
                    flag = 1;
            }

            if (flag == 0)
            {
                for (int j = 0; j < n; j++)
                    dfa[count][j] = temp[j];

                count++;
            }
        }
    }

    printf("\nDFA STATES:\n");

    for (int i = 0; i < count; i++)
    {
        printf("D%d = { ", i);

        for (int j = 0; j < n; j++)
            if (dfa[i][j] == 1)
                printf("%d ", j);

        printf("}\n");
    }

    return 0;
}
