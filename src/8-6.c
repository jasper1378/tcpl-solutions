#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>

#define NALLOC 1024

typedef long double Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *malloc_(unsigned);
static Header *morecore(unsigned);
void free_(void *ap);
void *calloc_(unsigned, unsigned);
void *memset_(void *, int, unsigned);

void *malloc_(unsigned nbytes) {
  Header *p;
  Header *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits) {
        prevp->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

static Header *morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC) {
    nu = NALLOC;
  }
  cp = (char *)sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) {
    return NULL;
  }
  up = (Header *)cp;
  up->s.size = nu;
  free_((void *)(up + 1));
  return freep;
}

void free_(void *ap) {
  Header *bp;
  Header *p;

  bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;
    }
  }
  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }
  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }
  freep = p;
}

void *calloc_(unsigned num, unsigned size) {
  void *p;
  if ((p = malloc_(num * size)) == NULL) {
    return NULL;
  } else {
    return memset_(p, 0, num * size);
  }
}

void *memset_(void *dest, int ch, unsigned count) {
  unsigned char *p;

  for (p = (unsigned char *)dest; count > 0; ++p, --count) {
    *p = (unsigned char)ch;
  }
  return dest;
}

int main() {
  int n;
  int *p;
  int i;

  n = 8;
  printf("calloc(%d, sizeof(int))\n", n);
  p = (int *)calloc_(n, sizeof(int));
  putchar('[');
  for (i = 0; i < n; ++i) {
    if (i != 0) {
      putchar(',');
    }
    printf("%d", p[i]);
  }
  puts("]");
  puts("free()");
  return 0;
}
