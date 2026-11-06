
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char numbers[100][128], keywords[100][128];
char identifiers[100][128], operators[100][128];
char symbols[100][128];

int n = 0, k = 0, id = 0, op = 0, sym = 0;

int isKeyword(char word[])
{
    return strcmp(word, "int") == 0 ||
           strcmp(word, "void") == 0 ||
           strcmp(word, "main") == 0;
}

int isOperator(int ch)
{
    return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '%' || ch == '=';
}

int isSymbol(int ch)
{
    return ch == '(' || ch == ')' ||
           ch == '{' || ch == '}' ||
           ch == ';' || ch == ',';
}

int main(void)
{
    FILE *fp = fopen("input_1.txt", "r");
    int ch, next;
    char word[128];
    int len;

    if (fp == NULL) {
        printf("Cannot open input file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        /* Ignore spaces, tabs and newlines */
        if (isspace((unsigned char)ch))
            continue;

        /* Read numbers */
        if (isdigit((unsigned char)ch)) {
            len = 0;
            do { 
                if (len < 127)
                    word[len++] = (char)ch;
                ch = fgetc(fp);
            } while (ch != EOF &&
                     isdigit((unsigned char)ch));

            word[len] = '\0';
            strcpy(numbers[n++], word);

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* Read keywords and identifiers */
        else if (isalpha((unsigned char)ch) || ch == '_') {
            len = 0;
            do {
                if (len < 127)
                    word[len++] = (char)ch;
                ch = fgetc(fp);
            } while (ch != EOF &&
                     (isalnum((unsigned char)ch) ||
                      ch == '_'));

            word[len] = '\0';

            if (isKeyword(word))
                strcpy(keywords[k++], word);
            else
                strcpy(identifiers[id++], word);

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* Read operators and ignore // comments */
        else if (isOperator(ch)) {
            if (ch == '/') {
                next = fgetc(fp);

                if (next == '/') {
                    while ((ch = fgetc(fp)) != EOF &&
                           ch != '\n')
                        ;
                    continue;
                }

                if (next != EOF)
                    ungetc(next, fp);
            }

            word[0] = (char)ch;
            word[1] = '\0';
            strcpy(operators[op++], word);
        }

        /* Read special symbols */
        else if (isSymbol(ch)) {
            word[0] = (char)ch;
            word[1] = '\0';
            strcpy(symbols[sym++], word);
        }
    }

    fclose(fp);

    int i;

    printf("\nNumber:        [");
    for (i = 0; i < n; i++)
        printf("'%s' ", numbers[i]);

    printf("]\nKeyWord:       [");
    for (i = 0; i < k; i++)
        printf("'%s' ", keywords[i]);

    printf("]\nIdentifier:    [");
    for (i = 0; i < id; i++)
        printf("'%s' ", identifiers[i]);

    printf("]\nOperators:     [");
    for (i = 0; i < op; i++)
        printf("'%s' ", operators[i]);

    printf("]\nSymbols:       [");
    for (i = 0; i < sym; i++)
        printf("'%s' ", symbols[i]);

    printf("]\n\n");

    return 0;
}
