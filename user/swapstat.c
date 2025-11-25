#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int nr_read, nr_write;
  // sys_swapstat() 같은 시스템 콜을 하나 만들어서
  // 내부에서 kernel의 swapstat()을 호출하게 할 수 있음.
  swapstat(&nr_read, &nr_write);

  printf("swapstat: read=%d write=%d\n", nr_read, nr_write);
  exit(0);
}

