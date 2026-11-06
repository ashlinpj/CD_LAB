#include <stdio.h>
#include <string.h>

struct statement
{
    char op[2];
    char a1[4];
    char a2[4];
    char res[4];
    int  flag;
};

struct statement st[32];
int cnt = 0;

void replace(char *targ, char *repl, int i)
{
    st[i].flag = 1;

    for (int j = i + 1; j < cnt; j++)
    {
        if (strcmp(targ, st[j].a1) == 0)
            strcpy(st[j].a1, repl);

        if (strcmp(targ, st[j].a2) == 0)
            strcpy(st[j].a2, repl);
    }
}

int main()
{
    FILE *fp, *out;

    fp = fopen("in.txt", "r");

    if (fp == NULL)
    {
        printf("Input file cannot be opened\n");
        return 1;
    }

    out = fopen("output.txt", "w");

    if (out == NULL)
    {
        printf("Output file cannot be opened\n");
        fclose(fp);
        return 1;
    }

    while (fscanf(fp, "%s %s %s %s",
                  st[cnt].op,
                  st[cnt].a1,
                  st[cnt].a2,
                  st[cnt].res) == 4)
    {
        st[cnt].flag = 0;
        cnt++;
    }

    fclose(fp);

    for (int i = 0; i < cnt; i++)
    {
        if (st[i].op[0] == '=')
            replace(st[i].res, st[i].a1, i);
    }

    fprintf(out, "Constant propagated code:\n");
    fprintf(out, "OPR\tA1\tA2\tRES\n");

    for (int i = 0; i < cnt; i++)
    {
        if (st[i].flag == 1)
            continue;

        fprintf(out, "%s\t%s\t%s\t%s\n",
                st[i].op,
                st[i].a1,
                st[i].a2,
                st[i].res);
    }

    fclose(out);

    return 0;
}


/* INPUT FILE: in.txt

= 3 - a
= 5 - b
+ a b c
* c 2 d

*/


/* OUTPUT FILE: output.txt

Constant propagated code:
OPR     A1      A2      RES
+       3       5       c
*       c       2       d

*/