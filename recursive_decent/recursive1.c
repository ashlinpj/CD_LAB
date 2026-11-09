//recursive decent parser for arithmetic expression

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

/* F -> (E) | id */
void F()
{
    if (str[i] == '(')
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

/* T1 -> *FT1 | epsilon */
void T1()
{
    if (str[i] == '*')
    {
        printf("\nT' -> *FT'");
        i++;

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

/* E1 -> +TE1 | epsilon */
void E1()
{
    if (str[i] == '+')
    {
        printf("\nE' -> +TE'");
        i++;

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
    printf("Enter the expression: ");
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


/*
Grammar Productions:

E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | id
*/
