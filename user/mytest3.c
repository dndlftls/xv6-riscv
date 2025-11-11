#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"

int main(int argc, char **argv){

  int size = 4096;
  //int fd = open("README", O_RDONLY);
  char* text = (char*)mmap(0, size, PROT_READ, MAP_POPULATE, -1, 0);
  printf("mmap return is: %d\n", text);


  exit(0);
}
