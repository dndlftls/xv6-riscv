#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("fork test start\n");
    for (int i = 0; i < 200; i++) {
        int pid = fork();
        if (pid < 0) {
            printf("fork failed at %d\n", i);
            exit(1);
        }
        if (pid == 0) {
            // child alloc memory
            char *buf = malloc(4096 * 50); // 50 pages
            if (buf) {
                for (int j = 0; j < 4096 * 50; j += 4096)
                    buf[j] = 'A';
            }
            // sleep so memory stays allocated
            sleep(1000);
            exit(0);
        }
    }
    sleep(3000);
    return 0;
}

