
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char numbers[100][20], keywords[100][20];
char identifiers[100][20], operators[100][20];
char symbols[100][20];

int n = 0, k = 0, id = 0, op = 0, sym = 0;

int isKeyword(char word[])
{
    return strcmp(word, "int") == 0 ||
           strcmp(word, "void") == 0 ||
           strcmp(word, "main") == 0;
}

int main()
{
    FILE *fp;
    char ch, word[20];
    int i = 0;

    fp = fopen("input_1.txt", "r");

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        // Numbers
        if (isdigit(ch))
        {
            i = 0;

            while (isdigit(ch))
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';
            strcpy(numbers[n++], word);
            ungetc(ch, fp);
        }

        // Keywords and identifiers
        else if (isalpha(ch) || ch == '_')
        {
            i = 0;

            while (isalnum(ch) || ch == '_')
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';

            if (isKeyword(word))
                strcpy(keywords[k++], word);
            else
                strcpy(identifiers[id++], word);

            ungetc(ch, fp);
        }

        // Operators
        else if (ch == '+' || ch == '-' || ch == '*' ||
                 ch == '/' || ch == '%' || ch == '=')
        {
            if (ch == '/')
            {
                char next = fgetc(fp);

                if (next == '/')
                {
                    while ((ch = fgetc(fp)) != EOF && ch != '\n');
                    continue;
                }

                if (next != EOF)
                    ungetc(next, fp);
            }

            word[0] = ch;
            word[1] = '\0';
            strcpy(operators[op++], word);
        }

        // Special symbols
        else if (ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == ';' || ch == ',')
        {
            word[0] = ch;
            word[1] = '\0';
            strcpy(symbols[sym++], word);
        }
    }

    fclose(fp);

    printf("\nNumbers: ");
    for (i = 0; i < n; i++)
        printf("%s ", numbers[i]);

    printf("\nKeywords: ");
    for (i = 0; i < k; i++)
        printf("%s ", keywords[i]);

    printf("\nIdentifiers: ");
    for (i = 0; i < id; i++)
        printf("%s ", identifiers[i]);

    printf("\nOperators: ");
    for (i = 0; i < op; i++)
        printf("%s ", operators[i]);

    printf("\nSymbols: ");
    for (i = 0; i < sym; i++)
        printf("%s ", symbols[i]);

    return 0;
}
