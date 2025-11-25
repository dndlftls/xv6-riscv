#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static inline void touch(char *p) {
  // 읽기 + 쓰기 → page fault 확실히 유발
  char t = *p;
  *p = t + 1;
}

int
main(void)
{
  printf("swaprtest2: start\n");

  int pages = 0;
  char *base = sbrk(0);

  //
  // 1) 메모리를 가능한 한 많이 확보
  //
  while (1) {
    char *p = sbrk(4096);
    if (p == (void*)-1)
      break;
    p[0] = 1;  // 실제 페이지 할당
    pages++;
  }

  printf("swaprtest2: allocated %d pages\n", pages);

  //
  // 2) Hot set (상위 1/4 페이지만 반복 접근)
  //
  int hot_start = pages * 3 / 4;
  printf("swaprtest2: hot-set touching [%d ~ %d)\n",
         hot_start, pages);

  for (int round = 0; round < 50; round++) {
    for (int i = hot_start; i < pages; i++) {
      touch(base + i * 4096);
    }
  }

  //
  // 3) Cold set 전체 접근 → swap_in이 반드시 발생함
  //
  printf("swaprtest2: cold-set touching all pages\n");

  for (int i = 0; i < pages; i++) {
    touch(base + i * 4096);
  }

  printf("swaprtest2: done\n");
  exit(0);
}

