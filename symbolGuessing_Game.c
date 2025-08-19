#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char questions[6][100] = {
        "Which symbol is used in function calls or grouping expressions?",
        "Which symbol is used to define blocks of code?",
        "Which symbol is used to terminate statements?",
        "Which symbol is used in labels, inheritance, ternary operator?",
        "Which symbol is used for arrays or indexing?",
        "Which symbol is used for preprocessor directives?"
    };

    char answers[6][5] = {
        "()",   // function calls / grouping
        "{}",   // blocks
        ";",    // statement terminator
        ":",    // labels, inheritance, ternary
        "[]",   // arrays / indexing
        "#"     // preprocessor
    };

    int n = 6;
    int asked[6] = {0};
    int score = 0;

    srand(time(0));

    for (int i = 0; i < n; i++) {
        int q;
        do {
            q = rand() % n;  // pick random index
        } while (asked[q]);  // ensure not repeated

        asked[q] = 1;

        printf("\nQ%d: %s\n", i + 1, questions[q]);
        printf("Your Answer (enter symbol): ");

        char userAns[10];
        scanf("%s", userAns);

        if (strcmp(userAns, answers[q]) == 0) {
            printf("✅ Correct!\n");
            score++;
        } else {
            printf("❌ Wrong! Correct answer: %s\n", answers[q]);
        }
    }

    printf("\n🎯 Final Score: %d / %d\n", score, n);
    return 0;
}