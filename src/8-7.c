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

void *malloc_(unsigned);
static Header *morecore(unsigned);
void free_(void *);

void *malloc_(unsigned nbytes) {
  Header *p;
  Header *prevp;
  unsigned nunits;

  if (nbytes <= 0) {
    return NULL;
  }
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
  if (bp->s.size <= 0) {
    return;
  }
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

int main() {
  void *p;

  printf("malloc(0) -> %p\n", malloc_(0));
  p = malloc_(1);
  ((Header *)p - 1)->s.size = 0;
  printf("free(...size=0...)\n");
  free_(p);
  return 0;
}
