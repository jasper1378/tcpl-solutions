#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#define NULL_ 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
  int cnt;
  char *ptr;
  char *base;
  struct {
    unsigned int read : 1;
    unsigned int write : 1;
    unsigned int unbuf : 1;
    unsigned int eof : 1;
    unsigned int err : 1;
  } flag;
  int fd;
} FILE;

enum _flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

extern FILE _iob[OPEN_MAX];

FILE _iob[OPEN_MAX] = {{0, (char *)0, (char *)0, {1, 0, 0, 0, 0}, 0},
                       {0, (char *)0, (char *)0, {0, 1, 0, 0, 0}, 1},
                       {0, (char *)0, (char *)0, {0, 1, 1, 0, 0}, 2}};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(const char *, const char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);

#define feof(p) ((p)->flag.eof == 1)
#define ferror(p) ((p)->flag.err == 1)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS 0666

FILE *fopen(const char *name, const char *mode) {
  int fd;
  FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL_;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (fp->flag.read == 0 && fp->flag.write == 0)
      break;
  if (fp >= _iob + OPEN_MAX)
    return NULL_;
  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1)
    return NULL_;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL_;
  memset(&fp->flag, 0, sizeof(fp->flag));
  if (*mode == 'r') {
    fp->flag.read = 1;
  } else {
    fp->flag.write = 1;
  }
  return fp;
}

int _fillbuf(FILE *fp) {
  int bufsize;

  if (!(fp->flag.read == 1 && fp->flag.eof == 0 && fp->flag.err == 0))
    return EOF;
  if (fp->flag.unbuf == 1) {
    bufsize = 1;
  } else {
    bufsize = BUFSIZ;
  }
  if (fp->base == NULL_)
    if ((fp->base = (char *)malloc(bufsize)) == NULL_)
      return EOF;
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag.eof = 1;
    else
      fp->flag.err = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int main() { return 0; }
