#define _DEFAULT_SOURCE

#include <stddef.h>
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

Header *maybe_init();
void *malloc_(unsigned);
static Header *morecore(unsigned);
void free_(void *);
int bfree(void *, unsigned);

Header *maybe_init() {
  Header *prevp;

  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  return prevp;
}

void *malloc_(unsigned nbytes) {
  Header *p;
  Header *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  prevp = maybe_init();
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

int bfree(void *p, unsigned n) {
  Header *bp;

  if (n < 2 * sizeof(Header)) {
    return -1;
  }
  bp = (Header *)p;
  bp->s.size = (n / sizeof(Header)) - 1;
  maybe_init();
  free_((void *)(bp + 1));
  return 0;
}

int main() {
  void *p;
  char b[8 * sizeof(Header)];

  printf("/* use strace to see that sbrk() is not called */\n");
  printf("char b[8 * sizeof(Header)];\n");
  printf("bfree(b,sizeof(b));\n");
  bfree(b, sizeof(b));
  printf("p = malloc(4*sizeof(Header));\n");
  p = malloc_(4 * sizeof(Header));
  printf("free(p);\n");
  free_(p);
  return 0;
}
