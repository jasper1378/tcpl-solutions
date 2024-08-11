#!/usr/bin/env bash

gcc \
  -ansi \
  -pedantic \
  -O0 \
  -g3 \
  -Wall \
  -Wextra \
  -Wpedantic \
  -fsanitize=address \
  -fsanitize=undefined \
  $@
