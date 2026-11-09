//recursive decent parser for boolean expression


#include <stdio.h>
#include <ctype.h>

char str[100];
int i = 0;

void E();
void E1();
void T();
void T1();
void F();

int error = 0;

/* F -> !F | (E) | id */
void F()
{
    if (str[i] == '!')
    {
        printf("\nF -> !F");
        i++;

        F();
    }
    else if (str[i] == '(')
    {
        printf("\nF -> (E)");
        i++;

        E();

        if (str[i] == ')')
        {
            i++;
        }
        else
        {
            error = 1;
        }
    }
    else if (isalpha((unsigned char)str[i]) || str[i] == '_')
    {
        printf("\nF -> id");

        while (isalnum((unsigned char)str[i]) || str[i] == '_')
        {
            i++;
        }
    }
    else
    {
        error = 1;
    }
}

/* T1 -> &&FT1 | epsilon */
void T1()
{
    if (str[i] == '&' && str[i + 1] == '&')
    {
        printf("\nT' -> &&FT'");
        i += 2;

        F();
        T1();
    }
    else
    {
        printf("\nT' -> epsilon");
    }
}

/* T -> FT1 */
void T()
{
    printf("\nT -> FT'");
    F();
    T1();
}

/* E1 -> ||TE1 | epsilon */
void E1()
{
    if (str[i] == '|' && str[i + 1] == '|')
    {
        printf("\nE' -> ||TE'");
        i += 2;

        T();
        E1();
    }
    else
    {
        printf("\nE' -> epsilon");
    }
}

/* E -> TE1 */
void E()
{
    printf("\nE -> TE'");
    T();
    E1();
}

int main()
{
    printf("Enter the Boolean expression: ");
    scanf("%99s", str);

    i = 0;
    error = 0;

    E();

    if (error == 0 && str[i] == '\0')
        printf("\n\nAccepted!\n");
    else
        printf("\n\nInvalid Expression!\n");

    return 0;
}
