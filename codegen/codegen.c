
#include <stdio.h>
#include <string.h>

char op[5], arg1[10], arg2[10], result[10];

int main()
{
    FILE *fp;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    while (fscanf(fp, "%s%s%s%s", op, arg1, arg2, result) == 4)
    {
        if (strcmp(op, "+") == 0)
        {
            printf("MOV R0,%s\n", arg1);
            printf("ADD R0,%s\n", arg2);
            printf("MOV %s,R0\n", result);
        }

        if (strcmp(op, "*") == 0)
        {
            printf("MOV R0,%s\n", arg1);
            printf("MUL R0,%s\n", arg2);
            printf("MOV %s,R0\n", result);
        }

        if (strcmp(op, "-") == 0)
        {
            printf("MOV R0,%s\n", arg1);
            printf("SUB R0,%s\n", arg2);
            printf("MOV %s,R0\n", result);
        }

        if (strcmp(op, "/") == 0)
        {
            printf("MOV R0,%s\n", arg1);
            printf("DIV R0,%s\n", arg2);
            printf("MOV %s,R0\n", result);
        }

        if (strcmp(op, "=") == 0)
        {
            printf("MOV R0,%s\n", arg1);
            printf("MOV %s,R0\n", result);
        }
    }

    fclose(fp);

    return 0;
}
