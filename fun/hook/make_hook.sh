#!/bin/bash
#无需环境变量预设，入侵业务代码
gcc -o libhook.so  -fPIC -shared -D_GNU_SOURCE hook.c -ldl
export LD_LIBRARY_PATH=`pwd`
gcc -o test_hook test_hook.c -L./ -lhook
 
