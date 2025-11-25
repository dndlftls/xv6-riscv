// user/memtst.c
#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("memtst: start\n");

  int pages = 0;

  // 한 번에 1 page(4096)씩 heap을 늘려가며 채우기
  while (1) {
    char *np = sbrk(4096);
    if (np == (char*)-1) {
      printf("memtst: sbrk failed at %d pages\n", pages);
      break;
    }
    pages++;
    // 페이지에 실제로 접근해야 page fault / swap이 발생함
    np[0] = 'A';
    if (pages % 50 == 0)
      printf("memtst: allocated %d pages\n", pages);
  }

  printf("memtst: done\n");
  sleep(1000); // 조금 버티면서 swap 상황 관찰
  exit(0);
}

