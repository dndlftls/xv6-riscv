#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("forkmem: start\n");
  for (int i = 0; i < 30; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed at %d\n", i);
      break;
    }
    if (pid == 0) {
      // child: 각자 100 page 정도 사용
      char *buf = sbrk(4096 * 100);
      for (int j = 0; j < 4096 * 100; j += 4096)
        buf[j] = 'C';
      sleep(1000); // 종료 늦춰서 swap 유지
      exit(0);
    }
  }

  sleep(2000);
  printf("forkmem: done\n");
  exit(0);
}

