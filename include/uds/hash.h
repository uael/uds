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

/*!@file uds/err.h
 * @author uael
 */
#ifndef __UDS_HASH_H
# define __UDS_HASH_H

#include <uty.h>

#define i8hash(key) ((u32_t)(key))
#define u8hash(key) ((u32_t)(key))
#define i16hash(key) ((u32_t)(key))
#define u16hash(key) ((u32_t)(key))
#define i32hash(key) ((u32_t)(key))
#define u32hash(key) ((u32_t)(key))
#define i64hash(key) ((u32_t)(((key)>>33^(key)^(key)<<11)))
#define u64hash(key) ((u32_t)(((key)>>33^(key)^(key)<<11)))

static inline PURE CONST u32_t
strhash(__const char_t *s) {
  u32_t h = (u32_t) *s;
  if (h) for (++s; *s; ++s) h = (h << 5) - h + (u32_t) *s;
  return h;
}

#endif /* !__UDS_HASH_H */
