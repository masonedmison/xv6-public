#include "types.h"
#include "user.h"

void
errexit(char *msg)
{
  printf(2, "error with '%s'.\n", msg);
  exit();
}

int
main(int argc, char *argv[])
{
  int forkrc;
  int *p = 1; /* point to first page in virtual address space */

  if ((forkrc = fork()) < 0)
    errexit("fork");
  else if(forkrc > 0) { /* child */
    if (mprotect((char *)0, 1) < 0)
      errexit("mprotect");
    // immediately unprotect and try to write to this page.
    int x = 1;
    if (munprotect((char *)0, x) < 0)
      errexit("munprotect");
    printf(1, "Attempting to write in child\n");
    *p = 1;
    printf(1, "Finished writing in child.\n");
  }
  else { /* parent */
    wait(); /* wait for children processes */
    if (mprotect((char *)0, 1) < 0)
      errexit("mprotect");
    printf(1, "Attempting to write to read only page in parent.\n");
    *p = 1; /* should result in trap */
    printf(1, "This shouldn't print.\n");
  }

  exit();
}
