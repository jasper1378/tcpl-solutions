#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void dirwalk(const char *dir, void (*fcn)(const char *));
void fsize(const char *name);
char *permstr(mode_t mode);

void dirwalk(const char *dir, void (*fcn)(const char *)) {
  char name[NAME_MAX + 2];
  DIR *dirp;
  struct dirent *dp;

  if ((dirp = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dirp)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
    } else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dirp);
}

void fsize(const char *name) {
  struct stat stbuf;
  char tbuf[20];

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    dirwalk(name, fsize);
  }
  strftime(tbuf, 20, "%Y-%m-%d %H:%M:%S", localtime(&(stbuf.st_mtime)));
  printf("%s %4d %4d %8ld %s %s\n", permstr(stbuf.st_mode), stbuf.st_uid,
         stbuf.st_gid, stbuf.st_size, tbuf, name);
}

#define PERMSTR_SETCHAR(f, y, n) (s[i++] = ((mode & (f)) != 0) ? (y) : (n))

char *permstr(mode_t mode) {
  static char s[11];
  int i;

  i = 0;
  s[10] = '\0';

  switch (mode & S_IFMT) {
  case S_IFSOCK: {
    s[i++] = 's';
  } break;
  case S_IFLNK: {
    s[i++] = 'l';
  } break;
  case S_IFREG: {
    s[i++] = '-';
  } break;
  case S_IFBLK: {
    s[i++] = 'b';
  } break;
  case S_IFDIR: {
    s[i++] = 'd';
  } break;
  case S_IFCHR: {
    s[i++] = 'c';
  } break;
  case S_IFIFO: {
    s[i++] = 'p';
  } break;
  default: {
    s[i++] = '?';
  } break;
  }

  PERMSTR_SETCHAR(S_IRUSR, 'r', '-');
  PERMSTR_SETCHAR(S_IWUSR, 'w', '-');
  if ((mode & S_ISUID) != 0) {
    PERMSTR_SETCHAR(S_IXUSR, 's', 'S');
  } else {
    PERMSTR_SETCHAR(S_IXUSR, 'x', '-');
  }
  PERMSTR_SETCHAR(S_IRGRP, 'r', '-');
  PERMSTR_SETCHAR(S_IWGRP, 'w', '-');
  if ((mode & S_ISGID) != 0) {
    PERMSTR_SETCHAR(S_IXGRP, 's', 'S');
  } else {
    PERMSTR_SETCHAR(S_IXGRP, 'x', '-');
  }
  PERMSTR_SETCHAR(S_IROTH, 'r', '-');
  PERMSTR_SETCHAR(S_IWOTH, 'w', '-');
  if ((mode & S_ISVTX) != 0) {
    PERMSTR_SETCHAR(S_IXOTH, 't', 'T');
  } else {
    PERMSTR_SETCHAR(S_IXOTH, 'x', '-');
  }

  return s;
}

int main(int argc, char *argv[]) {
  printf("format: perms uid gid size mtime name\n");
  if (argc == 1) {
    fsize(".");
  } else {
    while (--argc > 0) {
      fsize(*++argv);
    }
  }
  return 0;
}
