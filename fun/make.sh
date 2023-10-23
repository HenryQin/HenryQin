#!/bin/bash
program_name=${1}
program_file="./"$program_name".cpp"

g++ -o $program_name $program_file -std=c++11 -lpthread -fno-elide-constructors
