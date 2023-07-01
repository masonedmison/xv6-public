#include "types.h"
#include "user.h"

int
main(int arg, char *arv[])
{
  if (mprotect((char*)0, 1)) {
    printf(2, "oh noes\n");
    exit();
  }

  if (munprotect((char*)0, 1)) {
    printf(2, "munprotect failed.\n");
    exit();
  }

  printf(1, "Fin!\n");
  exit();
}
