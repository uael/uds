/*
 * MIT License
 *
 * Copyright (c) 2016-2017 Abel Lucas <www.github.com/uael>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!@file uds/deq.h
 * @author uael
 */
#ifndef __UDS_DEQ_H
# define __UDS_DEQ_H

#include "seq.h"

#define deqof(T, TSizeBits) \
  struct { \
    u##TSizeBits##_t cap, head, tail; \
    T *buf; \
  }

#define DEQ_IMPL_dtor(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_dtor(SCOPE, ID, T, BITS) { \
    self->CAP = 0; \
    self->LEN = 0; \
    self->head = 0; \
    if (self->BUF) { \
      FREE(self->BUF); \
      self->BUF = nil; \
    } \
  }

#define DEQ_IMPL_size(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_size(SCOPE, ID, T, BITS) { \
    return self->LEN - self->head; \
  }

#define DEQ_IMPL_at(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_at(SCOPE, ID, T, BITS) { \
    return self->BUF[self->head + idx]; \
  }

#define DEQ_IMPL_offset(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_offset(SCOPE, ID, T, BITS) { \
    return self->BUF + self->head + idx; \
  }

#define DEQ_IMPL_insert(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_insert(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if (idx > ID##_size(self)) { \
      return RET_FAILURE; \
    } \
    if ((ret = ID##_grow(self, 1)) > 0) { \
      return ret; \
    } \
    if (idx == 0 && self->head) { \
      --self->head; \
    } else if (idx == ID##_size(self)) { \
      ++self->LEN; \
    } else { \
      memmove( \
        self->BUF + self->head + idx + 1, \
        self->BUF + self->head + idx, \
        (usize_t) (self->LEN++ - idx) * sizeof(T) \
      ); \
    } \
    self->BUF[idx] = item; \
    return RET_SUCCESS; \
  }

#define DEQ_IMPL_emplace(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, \
  CMP) \
  SEQ_DECL_emplace(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if (idx > ID##_size(self)) { \
      return RET_FAILURE; \
    } \
    if ((ret = ID##_grow(self, n)) > 0) { \
      return ret; \
    } \
    if (idx == 0 && self->head >= n) { \
      self->head -= n; \
    } else if (idx == ID##_size(self)) { \
      self->LEN += n; \
    } else { \
      memmove( \
        self->BUF + self->head + idx + n, \
        self->BUF + self->head + idx, \
        (usize_t) (ID##_size(self) - idx) * sizeof(T) \
      ); \
      self->LEN += n; \
    } \
    memcpy(self->BUF + self->head + idx, items, (usize_t) n * sizeof(T)); \
    return RET_SUCCESS; \
  }

#define DEQ_IMPL_unshift(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, \
  CMP) \
  SEQ_DECL_unshift(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if ((ret = ID##_grow(self, 1)) > 0) { \
      return ret; \
    } \
    if (self->head == 0) { \
      memmove( \
        self->BUF + 1, \
        self->BUF, \
        (usize_t) self->LEN++ * sizeof(T) \
      ); \
    } else { \
      --self->head; \
    } \
    self->BUF[self->head] = item; \
    return RET_SUCCESS; \
  }

#define DEQ_IMPL_prepend(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, \
  CMP) \
  SEQ_DECL_prepend(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if (n == 0) { \
      return RET_SUCCESS; \
    } \
    if ((ret = ID##_grow(self, n)) > 0) { \
      return ret; \
    } \
    if (self->head == 0) { \
      memmove( \
        self->BUF + n, \
        self->BUF, \
        (usize_t) self->LEN * sizeof(T) \
      ); \
      self->LEN += n; \
    } else if (self->head < n) { \
      memmove( \
        self->BUF + n, \
        self->BUF + self->head, \
        (usize_t) (self->LEN - self->head) * sizeof(T) \
      ); \
      self->LEN += n - self->head; \
      self->head = 0; \
    } else { \
      self->head -= n; \
    } \
    memcpy(self->BUF, items, (usize_t) n * sizeof(T)); \
    return RET_SUCCESS; \
  }

#define DEQ_IMPL_shift(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_shift(SCOPE, ID, T, BITS) { \
    if (ID##_size(self) == 0) { \
      return false; \
    } \
    if (out != nil) { \
      *out = self->BUF[self->head]; \
    } \
    ++self->head; \
    return true; \
  }

#define DEQ_IMPL_remove(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_remove(SCOPE, ID, T, BITS) { \
    if (idx >= ID##_size(self)) { \
      return false; \
    } \
    if (out != nil) { \
      *out = ID##_at(self, idx); \
    } \
    if (idx == 0) { \
      ++self->head; \
    } else if (idx + self->head + 1 == self->LEN) { \
      --self->LEN; \
    } else  { \
      memmove( \
        self->BUF + idx + self->head, \
        self->BUF + idx + self->head + 1, \
        (usize_t) (--self->LEN - idx) * sizeof(T) \
      ); \
    } \
    return true; \
  }

#define DEQ_IMPL_removen(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, \
  CMP) \
  SEQ_DECL_removen(SCOPE, ID, T, BITS) { \
    if (idx >= ID##_size(self)) { \
      return false; \
    } \
    if (out != nil) { \
      memcpy(*out, ID##_offset(self, idx), n); \
    } \
    if (idx == 0) { \
      self->head += n; \
    } else if (idx + self->head + n == self->LEN) { \
      self->LEN -= n; \
    } else { \
      memmove( \
        self->BUF + self->head + idx, \
        self->BUF + self->head + idx + n, \
        (usize_t) ((self->LEN -= n) - idx) * sizeof(T) \
      ); \
    } \
    return true; \
  }

#define DEQ_IMPL_erase(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_erase(SCOPE, ID, T, BITS) { \
    u##BITS##_t len, i, j, n; \
    if ((len = ID##_size(self)) == 0) { \
      return 0; \
    } \
    for (i = self->head; i < self->LEN; ++i) { \
      if (CMP(item, self->BUF[i]) == 0) { \
        j = i; \
        n = 1; \
        while (i + 1 < self->LEN && CMP(item, self->BUF[i + 1]) == 0) { \
          ++i; \
          ++n; \
        } \
        memmove( \
          self->BUF + j, \
          self->BUF + j + n, \
          (usize_t) ((self->LEN -= n) - j) * sizeof(T) \
        ); \
      } \
    } \
    return len - ID##_size(self); \
  }

#define DEQ_IMPL_erasen(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_erasen(SCOPE, ID, T, BITS) { \
    u##BITS##_t len, i, j, c; \
    if (n == 0 || (len = ID##_size(self)) == 0) { \
      return 0; \
    } \
    for (i = self->head; i < self->LEN && n > 0; ++i) { \
      if (CMP(item, self->BUF[i]) == 0) { \
        --n; \
        j = i; \
        c = 1; \
        while (n > 0 && i + 1 < self->LEN && \
          CMP(item, self->BUF[i + 1]) == 0) { \
          --n; \
          ++i; \
          ++c; \
        } \
        memmove( \
          self->BUF + j, \
          self->BUF + j + c, \
          (usize_t) ((self->LEN -= c) - j) * sizeof(T) \
        ); \
      } \
    } \
    return len - ID##_size(self); \
  }

#define DEQ_IMPL_eraseonce(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, \
  CMP) \
  SEQ_DECL_eraseonce(SCOPE, ID, T, BITS) { \
    u##BITS##_t i; \
    for (i = self->head; i < self->LEN; ++i) { \
      if (CMP(item, self->BUF[i]) == 0) { \
        memmove( \
          self->BUF + i, \
          self->BUF + i + 1, \
          (usize_t) (--self->LEN - i) * sizeof(T) \
        ); \
        return true; \
      } \
    } \
    return false; \
  }

#define DEQ_IMPL_cpy(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_cpy(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if ((ret = ID##_ensure(self, src->LEN)) > 0) { \
      return ret; \
    } \
    memcpy(self->BUF, src->BUF, (usize_t) (self->LEN = src->LEN)); \
    self->head = src->head; \
    return RET_SUCCESS; \
  }

#define DEQ_IMPL_ncpy(SCOPE, ID, T, BITS, CAP, LEN, BUF, REALLOC, FREE, CMP) \
  SEQ_DECL_ncpy(SCOPE, ID, T, BITS) { \
    ret_t ret; \
    if ((ret = ID##_ensure(self, src->LEN)) > 0) { \
      return ret; \
    } \
    self->head = src->head; \
    memcpy(self->BUF + src->head, src->BUF + src->head, (usize_t) (n)); \
    self->LEN = self->head + n; \
    return RET_SUCCESS; \
  }

#define DEQ_DECL(SCOPE, ID, T, BITS) \
  SEQ_DECL(SCOPE, ID, T, BITS, \
    SEQ_DECL_ctor, \
    SEQ_DECL_dtor, \
    SEQ_DECL_cap, \
    SEQ_DECL_size, \
    SEQ_DECL_at, \
    SEQ_DECL_offset, \
    SEQ_DECL_realloc, \
    SEQ_DECL_ensure, \
    SEQ_DECL_grow, \
    SEQ_DECL_shrink, \
    SEQ_DECL_trim, \
    SEQ_DECL_insert, \
    SEQ_DECL_emplace, \
    SEQ_DECL_push, \
    SEQ_DECL_append, \
    SEQ_DECL_pop, \
    SEQ_DECL_unshift, \
    SEQ_DECL_prepend, \
    SEQ_DECL_shift, \
    SEQ_DECL_remove, \
    SEQ_DECL_removen, \
    SEQ_DECL_erase, \
    SEQ_DECL_erasen, \
    SEQ_DECL_eraseonce, \
    SEQ_DECL_cpy, \
    SEQ_DECL_ncpy \
  )
#define DEQ8_DECL(SCOPE, ID, T) DEQ_DECL(SCOPE, ID, T, 8)
#define DEQ16_DECL(SCOPE, ID, T) DEQ_DECL(SCOPE, ID, T, 16)
#define DEQ32_DECL(SCOPE, ID, T) DEQ_DECL(SCOPE, ID, T, 32)
#define DEQ64_DECL(SCOPE, ID, T) DEQ_DECL(SCOPE, ID, T, 64)

#define DEQ_IMPL_DFT(SCOPE, ID, T, BITS, REALLOC, FREE, CMP) \
  SEQ_IMPL(SCOPE, ID, T, BITS, cap, tail, buf, REALLOC, FREE, CMP, \
    SEQ_IMPL_ctor, \
    DEQ_IMPL_dtor, \
    SEQ_IMPL_cap, \
    DEQ_IMPL_size, \
    DEQ_IMPL_at, \
    DEQ_IMPL_offset, \
    SEQ_IMPL_realloc, \
    SEQ_IMPL_ensure, \
    SEQ_IMPL_grow, \
    SEQ_IMPL_shrink, \
    SEQ_IMPL_trim, \
    DEQ_IMPL_insert, \
    DEQ_IMPL_emplace, \
    SEQ_IMPL_push, \
    SEQ_IMPL_append, \
    SEQ_IMPL_pop, \
    DEQ_IMPL_unshift, \
    DEQ_IMPL_prepend, \
    DEQ_IMPL_shift, \
    DEQ_IMPL_remove, \
    DEQ_IMPL_removen, \
    DEQ_IMPL_erase, \
    DEQ_IMPL_erasen, \
    DEQ_IMPL_eraseonce, \
    DEQ_IMPL_cpy, \
    DEQ_IMPL_ncpy \
  )
#define DEQ8_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  DEQ_IMPL_DFT(SCOPE, ID, T, 8, REALLOC, FREE, CMP)
#define DEQ16_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  DEQ_IMPL_DFT(SCOPE, ID, T, 16, REALLOC, FREE, CMP)
#define DEQ32_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  DEQ_IMPL_DFT(SCOPE, ID, T, 32, REALLOC, FREE, CMP)
#define DEQ64_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  DEQ_IMPL_DFT(SCOPE, ID, T, 64, REALLOC, FREE, CMP)

#define DEQ_IMPL(SCOPE, ID, T, BITS, CMP) \
  DEQ_IMPL_DFT(SCOPE, ID, T, BITS, realloc, free, CMP)
#define DEQ8_IMPL(SCOPE, ID, T, CMP) \
  DEQ_IMPL(SCOPE, ID, T, 8, CMP)
#define DEQ16_IMPL(SCOPE, ID, T, CMP) \
  DEQ_IMPL(SCOPE, ID, T, 16, CMP)
#define DEQ32_IMPL(SCOPE, ID, T, CMP) \
  DEQ_IMPL(SCOPE, ID, T, 32, CMP)
#define DEQ64_IMPL(SCOPE, ID, T, CMP) \
  DEQ_IMPL(SCOPE, ID, T, 64, CMP)

#define DEQ_DEFINE_DFT(ID, T, BITS, REALLOC, FREE, CMP) \
  typedef deqof(T, BITS) ID##_t; \
  DEQ_IMPL_DFT(static FORCEINLINE, ID, T, BITS, REALLOC, FREE, CMP)
#define DEQ8_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  DEQ_DEFINE_DFT(ID, T, 8, REALLOC, FREE, CMP)
#define DEQ16_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  DEQ_DEFINE_DFT(ID, T, 16, REALLOC, FREE, CMP)
#define DEQ32_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  DEQ_DEFINE_DFT(ID, T, 32, REALLOC, FREE, CMP)
#define DEQ64_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  DEQ_DEFINE_DFT(ID, T, 64, REALLOC, FREE, CMP)

#define DEQ_DEFINE(ID, T, BITS, CMP) \
  DEQ_DEFINE_DFT(ID, T, BITS, realloc, free, CMP)
#define DEQ8_DEFINE(ID, T, CMP) DEQ_DEFINE(ID, T, 8, CMP)
#define DEQ16_DEFINE(ID, T, CMP) DEQ_DEFINE(ID, T, 16, CMP)
#define DEQ32_DEFINE(ID, T, CMP) DEQ_DEFINE(ID, T, 32, CMP)
#define DEQ64_DEFINE(ID, T, CMP) DEQ_DEFINE(ID, T, 64, CMP)

DEQ32_DEFINE(i8deq, i8_t, i8cmp)
DEQ32_DEFINE(u8deq, u8_t, u8cmp)
DEQ32_DEFINE(i16deq, i16_t, i16cmp)
DEQ32_DEFINE(u16deq, u16_t, u16cmp)
DEQ32_DEFINE(i32deq, i32_t, i32cmp)
DEQ32_DEFINE(u32deq, u32_t, u32cmp)
DEQ32_DEFINE(i64deq, i64_t, i64cmp)
DEQ32_DEFINE(u64deq, u64_t, u64cmp)
DEQ32_DEFINE(chardeq, char_t, i8cmp)
DEQ32_DEFINE(strdeq, char_t *, strcmp)

#endif /* !__UDS_DEQ_H */
