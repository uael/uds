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

/*!@file uds/math.h
 * @author uael
 */
#ifndef __UDS_MATH_H
# define __UDS_MATH_H

#include <uty.h>

#if __has_builtin(__builtin_popcount)
#define ISPOW2(n) (__builtin_popcount(n) == 1)
#else
#define ISPOW2(n) (((n) != 0) && (((n) & (~(n) + 1)) == (n)))
#endif

static inline PURE CONST u8_t
pow2_next8(u8_t n) {
  u32_t j;
  u32_t i;

  if (n == U8_MAX || ISPOW2(n)) {
    return n;
  }
  i = (u32_t) n;
  i = (u32_t) (
    (void) ((j = i & 0xFFFF0000) || (j = i)),
      (void) ((i = j & 0xFF00FF00) || (i = j)),
      (void) ((j = i & 0xF0F0F0F0) || (j = i)),
      (void) ((i = j & 0xCCCCCCCC) || (i = j)),
      (void) ((j = i & 0xAAAAAAAA) || (j = i)),
      j << 1
  );
  return (i > U8_MAX || i < (u32_t) n) ? (u8_t) U8_MAX : (u8_t) i;
}

static inline PURE CONST u16_t
pow2_next16(u16_t n) {
  u32_t j;
  u32_t i;

  if (n == U16_MAX || ISPOW2(n)) {
    return n;
  }
  i = (u32_t) n;
  i = (u32_t) (
    (void) ((j = i & 0xFFFF0000) || (j = i)),
      (void) ((i = j & 0xFF00FF00) || (i = j)),
      (void) ((j = i & 0xF0F0F0F0) || (j = i)),
      (void) ((i = j & 0xCCCCCCCC) || (i = j)),
      (void) ((j = i & 0xAAAAAAAA) || (j = i)),
      j << 1
  );
  return (i > U16_MAX || i < (u32_t) n) ? (u16_t) U16_MAX : (u16_t) i;
}

static inline PURE CONST u32_t
pow2_next32(u32_t n) {
  u32_t j;

  if (n == U32_MAX || ISPOW2(n)) {
    return n;
  }
  j = (u32_t) (
    (void) ((j = n & 0xFFFF0000) || (j = n)),
      (void) ((n = j & 0xFF00FF00) || (n = j)),
      (void) ((j = n & 0xF0F0F0F0) || (j = n)),
      (void) ((n = j & 0xCCCCCCCC) || (n = j)),
      (void) ((j = n & 0xAAAAAAAA) || (j = n)),
      j << 1
  );
  return (j < n) ? (u32_t) U32_MAX : j;
}

static inline PURE CONST u64_t
pow2_next64(u64_t n) {
  u64_t j;

  if (n == U64_MAX || ISPOW2(n)) {
    return n;
  }
  j = (u64_t) (
    (void) ((j = n & 0xFFFF0000LL) || (j = n)),
      (void) ((n = j & 0xFF00FF00LL) || (n = j)),
      (void) ((j = n & 0xF0F0F0F0LL) || (j = n)),
      (void) ((n = j & 0xCCCCCCCCLL) || (n = j)),
      (void) ((j = n & 0xAAAAAAAALL) || (j = n)),
      j << 1
  );
  return (j < n) ? (u64_t) U64_MAX : j;
}

#endif /* !__UDS_MATH_H */
