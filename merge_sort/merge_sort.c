#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// v is the array, n is the size of the array
void merge_sort(int *v, int n){
    if (n == 1)
        return;

    int a_sz = n - (n / 2), b_sz = n / 2;

    int *a = malloc(a_sz * sizeof(int));
    int *b = malloc(b_sz * sizeof(int));
    memcpy(a, v, a_sz * sizeof(int));
    memcpy(b, v + a_sz, b_sz * sizeof(int));

    merge_sort(a, a_sz);
    merge_sort(b, b_sz);
    
    // puts("=======");
    // for(int i = 0;i < a_sz;i++){
    //     printf("%d ", a[i]);
    // }
    // puts("");
    // for(int i = 0;i < b_sz;i++){
    //     printf("%d ", b[i]);
    // }
    // puts("");

    int i = 0, j = 0, k = 0;
    // printf("a_sz = %d, b_sz = %d\n", a_sz, b_sz);
    while (i < a_sz || j < b_sz) {
        // printf("a[%d] = %d, b[%d] = %d, k = %d\n", i, a[i], j, b[j], k);
        if (i == a_sz){
            v[k++] = b[j++];
        } else if (j == b_sz) {
            v[k++] = a[i++];
        } else {
            v[k++] = (b[j] < a[i]) ? b[j++] : a[i++];
        }
    }

    // for(int i = 0;i < a_sz + b_sz;i++){
    //     printf("%d ", v[i]);
    // }
    // puts("\n=======");

    free(a);
    free(b);
}

int main(){
    int v [] = {4, 3, 2, 1, 5};
    int n = 5;
    
    printf("%d\n", n);
    merge_sort(v, n);

    for(int i = 0;i < n;i++)
        printf("%d ", v[i]);
    puts("");
}