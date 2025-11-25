#include "kernel/types.h"
#include "user/user.h"

int main() {
    int n = 2000;
    char *arr[n];

    printf("malloc test start\n");
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(4096);
        if (!arr[i]) {
            printf("alloc failed at %d\n", i);
            break;
        }
        arr[i][0] = 'X';
    }

    sleep(5000);
    return 0;
}

