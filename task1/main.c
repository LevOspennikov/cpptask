#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv) {
    int n;
    int x, y;

    scanf("%d", &n);
    int ** table = malloc((n + 1) * (sizeof(int * )));
    for (int i = 0; i <= n; i++) {
        table[i] = malloc((n + 1) * (sizeof (int)));
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            table[i][j] = i * j;
        }
    }

    int x1, x2, y1, y2;
    x1 = 1;
    while (x1 != 0) {
        scanf("%d", &x1);
        if (x1 == 0) {
            break;
        }
        scanf("%d %d %d", &y1, &x2, &y2);
        for (int i = x1; i < x2 + 1; i++) {
            for (int j = y1; j < y2 + 1; j++) {
                printf("%d ", table[i][j]);
            }
            printf("\n");
        }
    }
    for (int i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);
    return 0;
}