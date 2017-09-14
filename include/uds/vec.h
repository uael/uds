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

/*!@file uds/vec.h
 * @author uael
 */
#ifndef __UDS_VEC_H
# define __UDS_VEC_H

#include <uty.h>
#include <stdlib.h>

#include "err.h"
#include "math.h"

#ifndef VEC_MIN_CAP
# define VEC_MIN_CAP 32
#endif

#define vecof(TItem, TSizeBits) struct { \
    u##TSizeBits##_t cap, len; \
    TItem *buf; \
  }

#define VEC_DEFINE_ALLOC(ID, TItem, TSizeBits, CMP_FN, MALLOC_FN, REALLOC_FN, \
  FREE_FN) \
  typedef vecof(TItem, TSizeBits) ID##_t; \
  static inline void \
  ID##_ctor(ID##_t *restrict self) { \
    *self = (ID##_t) {.cap = 0, .len = 0, .buf = nil}; \
  } \
  static inline void \
  ID##_dtor(ID##_t *restrict self) { \
    self->cap = 0; \
    self->len = 0; \
    if (self->buf) { \
      FREE_FN(self->buf); \
      self->buf = nil; \
    } \
  } \
  static inline err_t \
  ID##_growth(ID##_t *restrict self, const u##TSizeBits##_t nmin) { \
    if (nmin > 0) { \
      if (self->cap) { \
        if (self->cap < nmin) { \
          if (nmin == U##TSizeBits##_MAX || ISPOW2(nmin)) { \
            self->cap = nmin; \
          } else { \
            do self->cap *= 2; while (self->cap < nmin); \
          } \
          if ((self->buf = (TItem *) \
            REALLOC_FN(self->buf, sizeof(TItem) * (size_t) self->cap)) \
            == nil) { \
            self->cap = 0; \
            return (err_t) errno; \
          } \
        } \
      } else { \
        if (nmin == VEC_MIN_CAP || (nmin > VEC_MIN_CAP && \
          (nmin == U##TSizeBits##_MAX || ISPOW2(nmin)))) { \
          self->cap = nmin; \
        } else { \
          self->cap = VEC_MIN_CAP; \
          while (self->cap < nmin) self->cap *= 2; \
        } \
        if ((self->buf = \
          (TItem *) MALLOC_FN(sizeof(TItem) * (size_t) self->cap)) == nil) { \
          self->cap = 0; \
          return (err_t) errno; \
        } \
      } \
    } \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_decay(ID##_t *restrict self, const u##TSizeBits##_t nmax) { \
    u##TSizeBits##_t nearest_pow2; \
    nearest_pow2 = pow2_next##TSizeBits(nmax); \
    if (self->cap > nearest_pow2) { \
      self->cap = nearest_pow2; \
      if ((self->buf = (TItem *) \
        REALLOC_FN(self->buf, sizeof(TItem) * (size_t) self->cap)) == nil) { \
        self->cap = 0; \
        return (err_t) errno; \
      } \
    } \
    if (self->len > nmax) { \
      memset((i8_t *) self->buf + nmax * sizeof(TItem), 0, \
        ((size_t) (self->len - nmax)) * sizeof(TItem) \
      ); \
      self->len = nmax; \
    } \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_grow(ID##_t *restrict self, const u##TSizeBits##_t nmem) { \
    u##TSizeBits##_t u; \
    u = self->len + nmem; \
    return ID##_growth(self, (const u##TSizeBits##_t) \
      (u < self->len ? U##TSizeBits##_MAX : u)); \
  } \
  static inline err_t \
  ID##_shrink(ID##_t *restrict self, const u##TSizeBits##_t nmem) { \
    return ID##_decay( \
      self, \
      (const u##TSizeBits##_t) (nmem >= self->len ? 0 : self->len - nmem) \
    ); \
  } \
  static inline err_t \
  ID##_trim(ID##_t *restrict self) { \
    u##TSizeBits##_t nearest_pow2; \
    nearest_pow2 = pow2_next##TSizeBits(self->len); \
    if (self->cap > nearest_pow2) { \
      self->cap = nearest_pow2; \
      if ((self->buf = (TItem *) \
        REALLOC_FN(self->buf, sizeof(TItem) * (size_t) self->cap)) == nil) { \
        return (err_t) errno; \
      } \
    } \
    return SUCCESS; \
  } \
  static inline bool_t \
  ID##_remove(ID##_t *restrict self, const u##TSizeBits##_t idx) { \
    if (idx >= self->len) { \
      return false; \
    } \
    if (idx + 1 == self->len) { \
      --self->len; \
    } else { \
      memmove( \
        self->buf + idx, \
        self->buf + idx + 1, \
        (size_t) (--self->len - idx) * sizeof(TItem) \
      ); \
    } \
    return true; \
  } \
  static inline bool_t \
  ID##_removen(ID##_t *restrict self, const u##TSizeBits##_t idx, \
    const u##TSizeBits##_t n) { \
    if (idx >= self->len) { \
      return false; \
    } \
    if (idx + n > self->len) { \
      self->len = idx; \
    } else { \
      memmove( \
        self->buf + idx, \
        self->buf + idx + n, \
        (size_t) ((self->len -= n) - idx) * sizeof(TItem) \
      ); \
    } \
    return true; \
  } \
  static inline u##TSizeBits##_t \
  ID##_erase(ID##_t *restrict self, TItem item) { \
    u##TSizeBits##_t len, i, j, n; \
    if (self->len == 0) { \
      return 0; \
    } \
    len = self->len; \
    for (i = 0; i < self->len; ++i) { \
      if (CMP_FN(item, self->buf[i]) == 0) { \
        j = i; \
        n = 1; \
        while (i + 1 < self->len && CMP_FN(item, self->buf[i + 1]) == 0) { \
          ++i; \
          ++n; \
        } \
        memmove( \
          self->buf + j, \
          self->buf + j + n, \
          (size_t) ((self->len -= n) - j) * sizeof(TItem) \
        ); \
      } \
    } \
    return len - self->len; \
  } \
  static inline u##TSizeBits##_t \
  ID##_erasen(ID##_t *restrict self, TItem item, \
    u##TSizeBits##_t n) { \
    u##TSizeBits##_t len, i, j, c; \
    if (n == 0 || self->len == 0) { \
      return 0; \
    } \
    len = self->len; \
    for (i = 0; i < self->len && n > 0; ++i) { \
      if (CMP_FN(item, self->buf[i]) == 0) { \
        --n; \
        j = i; \
        c = 1; \
        while (n > 0 && i + 1 < self->len && \
          CMP_FN(item, self->buf[i + 1]) == 0) { \
          --n; \
          ++i; \
          ++c; \
        } \
        memmove( \
          self->buf + j, \
          self->buf + j + c, \
          (size_t) ((self->len -= c) - j) * sizeof(TItem) \
        ); \
      } \
    } \
    return len - self->len; \
  } \
  static inline bool_t \
  ID##_eraseonce(ID##_t *restrict self, TItem item) { \
    u##TSizeBits##_t i; \
    for (i = 0; i < self->len; ++i) { \
      if (CMP_FN(item, self->buf[i]) == 0) { \
        memmove( \
          self->buf + i, \
          self->buf + i + 1, \
          (size_t) (--self->len - i) * sizeof(TItem) \
        ); \
        return true; \
      } \
    } \
    return false; \
  } \
  static inline err_t \
  ID##_insert(ID##_t *restrict self, const u##TSizeBits##_t idx, \
    TItem item) { \
    err_t err; \
    if (idx > self->len) { \
      return FAILURE; \
    } \
    if ((err = ID##_grow(self, 1)) > 0) { \
      return err; \
    } \
    if (idx == self->len) { \
      ++self->len; \
    } else { \
      memmove( \
        self->buf + idx + 1, \
        self->buf + idx, \
        (size_t) (self->len++ - idx) * sizeof(TItem) \
      ); \
    } \
    self->buf[idx] = item; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_emplace(ID##_t *restrict self, const u##TSizeBits##_t idx, \
    TItem *items, const u##TSizeBits##_t n) { \
    err_t err; \
    if (idx > self->len) { \
      return FAILURE; \
    } \
    if ((err = ID##_grow(self, n)) > 0) { \
      return err; \
    } \
    if (idx != self->len) { \
      memmove( \
        self->buf + idx + n, \
        self->buf + idx, \
        (size_t) (self->len - idx) * sizeof(TItem) \
      ); \
    } \
    memcpy(self->buf + idx, items, (size_t) n * sizeof(TItem)); \
    self->len += n; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_push(ID##_t *restrict self, TItem item) { \
    err_t err; \
    if ((err = ID##_grow(self, 1)) > 0) { \
      return err; \
    } \
    self->buf[self->len++] = item; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_pop(ID##_t *restrict self, TItem *restrict out) { \
    if (self->len == 0) { \
      return FAILURE; \
    } \
    --self->len; \
    if (out != nil) { \
      *out = self->buf[self->len]; \
    } \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_append(ID##_t *restrict self, TItem *items, const u##TSizeBits##_t n) { \
    err_t err; \
    if (n == 0) { \
      return SUCCESS; \
    } \
    if ((err = ID##_grow(self, n)) > 0) { \
      return err; \
    } \
    memcpy(self->buf + self->len, items, (size_t) n * sizeof(TItem)); \
    self->len += n; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_unshift(ID##_t *restrict self, TItem item) { \
    err_t err; \
    if ((err = ID##_grow(self, 1)) > 0) { \
      return err; \
    } \
    memmove( \
      self->buf + 1, \
      self->buf, \
      (size_t) self->len++ * sizeof(TItem) \
    ); \
    self->buf[0] = item; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_shift(ID##_t *restrict self, TItem *restrict out) { \
    if (self->len == 0) { \
      return FAILURE; \
    } \
    if (out != nil) { \
      *out = self->buf[0]; \
    } \
    if (self->len == 1) { \
      --self->len; \
    } else { \
      memmove( \
        self->buf, \
        self->buf + 1, \
        (size_t) --self->len * sizeof(TItem) \
      ); \
    } \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_prepend(ID##_t *restrict self, TItem *items, \
    const u##TSizeBits##_t n) { \
    err_t err; \
    if (n == 0) { \
      return SUCCESS; \
    } \
    if ((err = ID##_grow(self, n)) > 0) { \
      return err; \
    } \
    memmove( \
      self->buf + n, \
      self->buf, \
      (size_t) self->len * sizeof(TItem) \
    ); \
    memcpy(self->buf, items, (size_t) n * sizeof(TItem)); \
    self->len += n; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_resize(ID##_t *restrict self, const u##TSizeBits##_t n) { \
    err_t err; \
    if ((err = ID##_growth(self, n)) > 0) { \
      return err; \
    } \
    self->len = n; \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_cpy(ID##_t *restrict self, ID##_t *restrict src) { \
    err_t err; \
    if ((err = ID##_growth(self, src->len)) > 0) { \
      return err; \
    } \
    memcpy(self->buf, src->buf, (size_t) (self->len = src->len)); \
    return SUCCESS; \
  } \
  static inline err_t \
  ID##_ncpy(ID##_t *restrict self, ID##_t *restrict src, \
    const u##TSizeBits##_t n) { \
    err_t err; \
    if ((err = ID##_growth(self, n)) > 0) { \
      return err; \
    } \
    memcpy(self->buf, src->buf, (size_t) (self->len = n)); \
    return SUCCESS; \
  }

#define VEC_DEFINE(ID, TItem, TSizeBits, CMP_FN) \
  VEC_DEFINE_ALLOC(ID, TItem, TSizeBits, CMP_FN, malloc, realloc, free)

#define VEC8_DEFINE(ID, TItem, CMP_FN) \
  VEC_DEFINE(ID, TItem, 8, CMP_FN)

#define VEC16_DEFINE(ID, TItem, CMP_FN) \
  VEC_DEFINE(ID, TItem, 16, CMP_FN)

#define VEC32_DEFINE(ID, TItem, CMP_FN) \
  VEC_DEFINE(ID, TItem, 32, CMP_FN)

#define VEC64_DEFINE(ID, TItem, CMP_FN) \
  VEC_DEFINE(ID, TItem, 64, CMP_FN)

VEC32_DEFINE(i8vec, i8_t, i8cmp);
VEC32_DEFINE(u8vec, u8_t, u8cmp);
VEC32_DEFINE(i16vec, i16_t, i16cmp);
VEC32_DEFINE(u16vec, u16_t, u16cmp);
VEC32_DEFINE(i32vec, i32_t, i32cmp);
VEC32_DEFINE(u32vec, u32_t, u32cmp);
VEC32_DEFINE(i64vec, i64_t, i64cmp);
VEC32_DEFINE(u64vec, u64_t, u64cmp);
VEC32_DEFINE(strvec, i8_t *, strcmp);
VEC32_DEFINE(dstr, i8_t, i8cmp);

#endif /* !__UDS_VEC_H */
