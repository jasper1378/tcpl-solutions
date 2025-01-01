#include <stdlib.h>

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
  int flag;
  int fd;
} FILE;

enum _flags { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

extern FILE _iob[OPEN_MAX];

FILE _iob[OPEN_MAX] = {{0, (char *)0, (char *)0, _READ, 0},
                       {0, (char *)0, (char *)0, _WRITE, 1},
                       {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(const char *, const char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int _flushbuf_impl(int, FILE *, int);
int fflush(FILE *);
int _fflush_all();
int fclose(FILE *);
void exit_flush();

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
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
    if ((fp->flag & (_READ | _WRITE)) == 0)
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
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

int _fillbuf(FILE *fp) {
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL_)
    if ((fp->base = (char *)malloc(bufsize)) == NULL_)
      return EOF;
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

int _flushbuf(int ch, FILE *fp) { return _flushbuf_impl(ch, fp, 1); }

int _flushbuf_impl(int ch, FILE *fp, int put_ch) {
  int bufsize;

  if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL_) {
    if ((fp->base = (char *)malloc(bufsize)) == NULL_) {
      return EOF;
    }
  } else {
    if (write(fp->fd, fp->base, fp->ptr - fp->base) != (fp->ptr - fp->base)) {
      fp->flag |= _ERR;
      return EOF;
    }
  }
  fp->ptr = fp->base;
  if (put_ch) {
    *fp->ptr++ = ch;
    fp->cnt = bufsize - 1;
  } else {
    fp->cnt = bufsize;
  }
  return ch;
}

int fflush(FILE *fp) {
  if (fp != NULL_) {
    if ((fp->flag & _WRITE) != 0) {
      if (_flushbuf_impl('\0', fp, 0) == EOF) {
        return EOF;
      }
    }
    return 0;
  } else {
    return _fflush_all();
  }
}

int _fflush_all() {
  FILE *fp;

  for (fp = _iob; fp < _iob + OPEN_MAX; ++fp) {
    if (fflush(fp) != 0) {
      return EOF;
    }
  }
  return 0;
}

int fclose(FILE *fp) {
  int r;

  r = 0;
  if (fp) {
    if (fflush(fp) == EOF) {
      r = EOF;
    }
    free(fp->base);
    fp->ptr = NULL_;
    fp->base = NULL_;
    fp->cnt = 0;
    if (close(fp->fd) == -1) {
      r = EOF;
    }
  }
  return r;
}

void exit_flush() { fflush(NULL_); }

void filecopy(FILE *, FILE *);

void filecopy(FILE *ifp, FILE *ofp) {
  int c;

  while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}

int main(int argc, char *argv[]) {
  FILE *fp;

  atexit(exit_flush);

  if (argc == 1)
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        exit(1);
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }
  if (ferror(stdout)) {
    exit(2);
  }
  exit(0);
}
