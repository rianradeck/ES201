#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(int *v, int n) {
    int a_sz;
    int b_sz;
    int *a;
    int *b;
    int i;
    int j;
    int k;

    if (n == 1) {
        return;
    }

    a_sz = n - (n / 2);
    b_sz = n / 2;

    a = malloc(a_sz * sizeof(int));
    b = malloc(b_sz * sizeof(int));

    if (a == NULL || b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(a, v, a_sz * sizeof(int));
    memcpy(b, v + a_sz, b_sz * sizeof(int));

    merge_sort(a, a_sz);
    merge_sort(b, b_sz);

    i = 0;
    j = 0;
    k = 0;

    while (i < a_sz || j < b_sz) {
        if (i == a_sz) {
            v[k] = b[j];
            k++;
            j++;
        } else if (j == b_sz) {
            v[k] = a[i];
            k++;
            i++;
        } else {
            if (b[j] < a[i]) {
                v[k] = b[j];
                j++;
            } else {
                v[k] = a[i];
                i++;
            }
            k++;
        }
    }

    free(a);
    free(b);
}

int main() {
    int v[] = {4, 3, 2, 1, 5};
    int n = 5;
    int i;

    printf("%d\n", n);
    merge_sort(v, n);

    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    puts("");

    return 0;
}
