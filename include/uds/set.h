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

/*!@file uds/set.h
 * @author uael
 */
#ifndef __UDS_SET_H
# define __UDS_SET_H

#include <uty.h>
#include <uerr.h>
#include <stdlib.h>

#include "hash.h"
#include "map.h"
#include "math.h"

#define setof(TItem) struct { \
    u32_t cap, len, occupieds, upper_bound; \
    u8_t *buckets; \
    TItem *items; \
  }

#define SET_DEFINE_ALLOC(ID, TItem, HASH_FN, HASHEQ_FN, \
  MALLOC_FN, REALLOC_FN, FREE_FN) \
  typedef setof(TItem) ID##_t; \
  static FORCEINLINE void \
  ID##_ctor(ID##_t *__restrict self) { \
    *self = (ID##_t) { \
      .cap = 0, \
      .len = 0, \
      .occupieds = 0, \
      .upper_bound = 0, \
      .buckets = nil, \
      .items = nil \
    }; \
  } \
  static FORCEINLINE void \
  ID##_dtor(ID##_t *__restrict self) { \
    if (self && self->buckets) { \
      FREE_FN((void *)self->items); \
      FREE_FN(self->buckets); \
    } \
  } \
  static FORCEINLINE void \
  ID##_clear(ID##_t *__restrict self) { \
    if (self && self->buckets) { \
      memset(self->buckets, BUCKET_EMPTY, self->cap); \
      self->len = self->occupieds = 0; \
    } \
  } \
  static FORCEINLINE bool_t \
  ID##_get(__const ID##_t *self, TItem item, u32_t *__restrict out) { \
    if (self->cap) { \
      u32_t k, i, last, mask, step; \
      step = 0; \
      mask = self->cap - 1; \
      k = HASH_FN(item); \
      i = k & mask; \
      last = i; \
      while (!bucket_isempty(self->buckets, i) && (bucket_isdel(self->buckets, i) || \
        !HASHEQ_FN(self->items[i], item))) { \
        i = (i + (++step)) & mask; \
        if (i == last) \
          return false; \
      } \
      if (bucket_iseither(self->buckets, i)) \
        return false; \
      *out = i; \
      return true; \
    } \
    return false; \
  } \
  static FORCEINLINE ret_t \
  ID##_resize(ID##_t *__restrict self, u32_t ensure) { \
    u8_t *new_buckets; \
    u32_t j; \
    new_buckets = nil; \
    j = 1; \
    { \
      ensure = pow2_next32(ensure); \
      if (ensure < 4) ensure = 32; \
      if (self->len >= (u32_t)(ensure * MAP_HASH_UPPER + 0.5)) j = 0;  /* requested size is too small */ \
      else { /* hash table size to be changed (shrink or expand); rehash */ \
        new_buckets = (u8_t*)MALLOC_FN(ensure); \
        if (!new_buckets) return RET_ERRNO; \
        memset(new_buckets, 2, ensure); \
        if (self->cap < ensure) {  /* expand */ \
          TItem *new_items = (TItem*)REALLOC_FN((void *)self->items, ensure * sizeof(TItem)); \
          if (!new_items) { FREE_FN(new_buckets); return RET_ERRNO; } \
          self->items = new_items; \
        } /* otherwise shrink */ \
      } \
    } \
    if (j) { /* rehashing is needed */ \
      for (j = 0; j != self->cap; ++j) { \
        if (bucket_iseither(self->buckets, j) == 0) { \
          TItem item = self->items[j]; \
          u32_t new_mask; \
          new_mask = ensure - 1; \
          bucket_set_isdel_true(self->buckets, j); \
          while (1) { /* kick-out process; sort of like in Cuckoo hashing */ \
            u32_t k, i, step = 0; \
            k = HASH_FN(item); \
            i = k & new_mask; \
            while (!bucket_isempty(new_buckets, i)) i = (i + (++step)) & new_mask; \
            bucket_set_isempty_false(new_buckets, i); \
            if (i < self->cap && bucket_iseither(self->buckets, i) == 0) { /* kick out the existing element */ \
              { TItem tmp = self->items[i]; self->items[i] = item; item = tmp; } \
              bucket_set_isdel_true(self->buckets, i); /* mark it as deleted in the old hash table */ \
            } else { /* write the element and jump out of the loop */ \
              self->items[i] = item; \
              break; \
            } \
          } \
        } \
      } \
      if (self->cap > ensure) { /* shrink the hash table */ \
        self->items = (TItem*)REALLOC_FN((void *)self->items, ensure * sizeof(TItem)); \
      } \
      FREE_FN(self->buckets); /* free the working space */ \
      self->buckets = new_buckets; \
      self->cap = ensure; \
      self->occupieds = self->len; \
      self->upper_bound = (u32_t)(self->cap * MAP_HASH_UPPER + 0.5); \
    } \
    return RET_SUCCESS; \
  } \
  static FORCEINLINE ret_t \
  ID##_put(ID##_t *__restrict self, TItem item, u32_t *__restrict out) { \
    u32_t x; \
    if (self->occupieds >= self->upper_bound) { /* update the hash table */ \
      if (self->cap > (self->len << 1)) { \
        if (ID##_resize(self, self->cap - 1) != 0) { /* clear "deleted" elements */ \
          return RET_ERRNO; \
        } \
      } else if (ID##_resize(self, self->cap + 1) != 0) { /* expand the hash table */ \
         return RET_ERRNO; \
      } \
    } /* TODO: to implement automatically shrinking; resize() already support shrinking */ \
    { \
      u32_t k, i, site, last, mask = self->cap - 1, step = 0;\
      x = site = self->cap; k = HASH_FN(item); i = k & mask;\
      last = i; \
      while (1) { \
        unsigned char flag = self->buckets[i]; \
        if (flag & BUCKET_EMPTY) break; \
        if ((flag & BUCKET_DELETED) || !HASHEQ_FN(self->items[i], item)) { \
          i = (i + (++step)) & mask; \
          if (i == last) { x = site; break; } \
        } else break; \
      } \
      if (x == self->cap) { \
        if (bucket_isempty(self->buckets, i) && site != self->cap) x = site; \
        else x = i; \
      } \
    } \
    *out = x; \
    if (bucket_isempty(self->buckets, x)) { /* not present at all */ \
      self->items[x] = item; \
      bucket_set_isboth_false(self->buckets, x); \
      ++self->len; \
      ++self->occupieds; \
      return RET_SUCCESS; \
    } else if (bucket_isdel(self->buckets, x)) { /* deleted */ \
      self->items[x] = item; \
      bucket_set_isboth_false(self->buckets, x); \
      ++self->len; \
      return RET_SUCCESS; \
    } \
    return RET_FAILURE; /* Don't touch self->items[x] if populated */ \
  } \
  static FORCEINLINE bool_t \
  ID##_del(ID##_t *__restrict self, u32_t x) { \
    if (x != self->cap && bucket_ispopulated(self->buckets, x)) { \
      bucket_set_isdel_true(self->buckets, x); \
      --self->len; \
      return true; \
    } \
    return false; \
  }

#define SET_DEFINE(ID, TItem, HASH_FN, HASHEQ_FN) \
  SET_DEFINE_ALLOC(ID, TItem, HASH_FN, HASHEQ_FN, malloc, realloc, free)

#define I8_SET_DEFINE(ID) \
  SET_DEFINE(ID, i8_t, i8hash, i8eq)

#define U8_SET_DEFINE(ID) \
  SET_DEFINE(ID, u8_t, u8hash, u8eq)

#define I16_SET_DEFINE(ID) \
  SET_DEFINE(ID, i16_t, i16hash, i16eq)

#define U16_SET_DEFINE(ID) \
  SET_DEFINE(ID, u16_t, u16hash, u16eq)

#define I32_SET_DEFINE(ID) \
  SET_DEFINE(ID, i32_t, i32hash, i32eq)

#define U32_SET_DEFINE(ID) \
  SET_DEFINE(ID, u32_t, u32hash, u32eq)

#define I64_SET_DEFINE(ID) \
  SET_DEFINE(ID, i64_t, i64hash, i64eq)

#define U64_SET_DEFINE(ID) \
  SET_DEFINE(ID, u64_t, u64hash, u64eq)

#define STR_SET_DEFINE(ID) \
  SET_DEFINE(ID, __const char_t *, strhash, streq)

I8_SET_DEFINE(i8set)
U8_SET_DEFINE(u8set)
I16_SET_DEFINE(i16set)
U16_SET_DEFINE(u16set)
I32_SET_DEFINE(i32set)
U32_SET_DEFINE(u32set)
I64_SET_DEFINE(i64set)
U64_SET_DEFINE(u64set)
SET_DEFINE(charset, char_t, i8hash, i8eq)
STR_SET_DEFINE(strset)

#endif /* !__UDS_SET_H */
