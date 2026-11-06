
#include <stdio.h>

char grammar[50][50];
char first[26][100], follow[26][100];

int n;

// Check non-terminal
int isNT(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

// Add character without duplicates
int add(char set[], char ch) {
    int i = 0;

    while (set[i] != '\0') {
        if (set[i] == ch)
            return 0;
        i++;
    }

    set[i] = ch;
    set[i + 1] = '\0';

    return 1;
}

// Calculate FIRST
void findFirst() {
    int i, j, k, changed;

    do {
        changed = 0;

        for (i = 0; i < n; i++) {

            char left = grammar[i][0];

            // Epsilon production
            if (grammar[i][2] == '#') {
                if (add(first[left - 'A'], '#'))
                    changed = 1;

                continue;
            }

            int allEpsilon = 1;

            for (j = 2; grammar[i][j] != '\0'; j++) {

                char ch = grammar[i][j];

                // Terminal
                if (!isNT(ch)) {
                    if (add(first[left - 'A'], ch))
                        changed = 1;

                    allEpsilon = 0;
                    break;
                }

                // Non-terminal
                int hasEpsilon = 0;

                for (k = 0; first[ch - 'A'][k] != '\0'; k++) {

                    if (first[ch - 'A'][k] == '#')
                        hasEpsilon = 1;

                    else {
                        if (add(first[left - 'A'],
                                first[ch - 'A'][k]))
                            changed = 1;
                    }
                }

                if (!hasEpsilon) {
                    allEpsilon = 0;
                    break;
                }
            }

            // All symbols can produce epsilon
            if (allEpsilon) {
                if (add(first[left - 'A'], '#'))
                    changed = 1;
            }
        }

    } while (changed);
}

// Calculate FOLLOW
void findFollow() {
    int i, j, k, m, changed;

    // Add $ to start symbol
    add(follow[grammar[0][0] - 'A'], '$');

    do {
        changed = 0;

        for (i = 0; i < n; i++) {

            char left = grammar[i][0];

            for (j = 2; grammar[i][j] != '\0'; j++) {

                char ch = grammar[i][j];

                if (!isNT(ch))
                    continue;

                int allEpsilon = 1;

                // Check symbols after current non-terminal
                for (k = j + 1; grammar[i][k] != '\0'; k++) {

                    char next = grammar[i][k];

                    // Terminal
                    if (!isNT(next)) {
                        if (add(follow[ch - 'A'], next))
                            changed = 1;

                        allEpsilon = 0;
                        break;
                    }

                    // Add FIRST of next non-terminal
                    int hasEpsilon = 0;

                    for (m = 0; first[next - 'A'][m] != '\0'; m++) {

                        if (first[next - 'A'][m] == '#')
                            hasEpsilon = 1;

                        else {
                            if (add(follow[ch - 'A'],
                                    first[next - 'A'][m]))
                                changed = 1;
                        }
                    }

                    if (!hasEpsilon) {
                        allEpsilon = 0;
                        break;
                    }
                }

                // Add FOLLOW of left side
                if (allEpsilon) {

                    for (m = 0; follow[left - 'A'][m] != '\0'; m++) {

                        if (add(follow[ch - 'A'],
                                follow[left - 'A'][m]))
                            changed = 1;
                    }
                }
            }
        }

    } while (changed);
}

// Display FIRST and FOLLOW
void display() {
    int i,j;
    
    printf("\nFIRST SETS\n");

    for(i=0;i<26;i++){
        if(first[i][0]!='\0'){
            printf("FIRST(%c)={",'A'+i);

            for(j=0;first[i][j]!='\0';j++){
                printf("%c ",first[i][j]);
            }
            printf("}\n");
        }
    }

    printf("\nFOLLOW SETS\n");
    for(i=0;i<26;i++){
        if(follow[i][0]!='\0'){
            printf("FOLLOW(%c)={",'A'+i);

            for(j=0;follow[i][j]!='\0';j++){
                printf("%c ",follow[i][j]);
            }
            printf("}\n");
        }
    }
}

// Main function
int main() {
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for (i = 0; i < n; i++)
        scanf("%49s", grammar[i]);

    findFirst();
    findFollow();
    display();

    return 0;
}
