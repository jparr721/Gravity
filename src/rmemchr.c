#include <sys/types.h>

/**
 * Reverse memchr()
 */
void* rmemchr(const void* s, int c, size_t n) {
  if (n != 0) {
    const unsigned char* cp;
    cp = (unsigned char*)s + n;
    do {
      if (*(--cp) == (unsigned char)c)
        return ((void*)cp);
    } while (--n != 0);
  }
  return ((void*) 0);
}
