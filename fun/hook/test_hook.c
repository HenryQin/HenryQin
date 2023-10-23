#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "enable_hook.h"

int main()
{     
      enable_hook(); // 入侵代码
      int fd = open("./hook.c", O_RDONLY);
      return 0;
}
