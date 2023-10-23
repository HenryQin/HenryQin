#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "enable_hook.h"

int main()
{     
      enable_hook();
      int fd = open("/home/lighthouse/codespace/cpp/fun/hook.c", O_RDONLY);
      return 0;
}
