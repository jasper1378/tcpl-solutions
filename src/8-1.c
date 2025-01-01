#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 100

void filecopy(int ifd, int ofd);

void filecopy(int ifd, int ofd) {
  char buf[BUFSIZE];
  ssize_t r;

  while ((r = read(ifd, buf, BUFSIZE)) > 0) {
    write(ofd, buf, r);
  }
}

int main(int argc, char *argv[]) {
  int fd;

  char *prog = argv[0];

  if (argc == 1)
    filecopy(STDIN_FILENO, STDOUT_FILENO);
  else
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY)) == -1) {
        fprintf(stderr, "%s: can't open %s\n", prog, *argv);
        exit(1);
      } else {
        filecopy(fd, STDOUT_FILENO);
        close(fd);
      }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(2);
  }
  exit(0);
}
