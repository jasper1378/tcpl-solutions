#!/usr/bin/env bash

gcc -ansi -pedantic -O0 -g3 -fsanitize=address -Wall -Wextra $1
