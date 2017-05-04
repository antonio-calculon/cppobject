
#ifndef _PRIVATE_HPP_
#define _PRIVATE_HPP_

#include <stdio.h>

#define LOG(lvl, v...) do {                     \
    printf("spcol:%s:%d:" lvl " ",              \
           __FILE__, __LINE__);                 \
    printf(v);                                  \
    printf("\n");                               \
  } while (0)

#define DEBUG(v...) LOG("", v)

#define ERROR(v...) LOG("ERROR:", v)

#define ASSERT(expr) do {                       \
    if (!(expr)) {                              \
      ERROR("ASSERTION FAILED: " #expr);        \
      abort();                                  \
    }                                           \
  } while (0)


#endif
