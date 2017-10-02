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

#include "seq.h"

#define vecof(T, TSizeBits) \
  struct { \
    u##TSizeBits##_t cap, len; \
    T *buf; \
  }

#define VEC_DECL(SCOPE, ID, T, BITS) \
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
#define VEC8_DECL(SCOPE, ID, T) VEC_DECL(SCOPE, ID, T, 8)
#define VEC16_DECL(SCOPE, ID, T) VEC_DECL(SCOPE, ID, T, 16)
#define VEC32_DECL(SCOPE, ID, T) VEC_DECL(SCOPE, ID, T, 32)
#define VEC64_DECL(SCOPE, ID, T) VEC_DECL(SCOPE, ID, T, 64)

#define VEC_IMPL_DFT(SCOPE, ID, T, BITS, REALLOC, FREE, CMP) \
  SEQ_IMPL(SCOPE, ID, T, BITS, cap, len, buf, REALLOC, FREE, CMP, \
    SEQ_IMPL_ctor, \
    SEQ_IMPL_dtor, \
    SEQ_IMPL_cap, \
    SEQ_IMPL_size, \
    SEQ_IMPL_at, \
    SEQ_IMPL_offset, \
    SEQ_IMPL_realloc, \
    SEQ_IMPL_ensure, \
    SEQ_IMPL_grow, \
    SEQ_IMPL_shrink, \
    SEQ_IMPL_trim, \
    SEQ_IMPL_insert, \
    SEQ_IMPL_emplace, \
    SEQ_IMPL_push, \
    SEQ_IMPL_append, \
    SEQ_IMPL_pop, \
    SEQ_IMPL_unshift, \
    SEQ_IMPL_prepend, \
    SEQ_IMPL_shift, \
    SEQ_IMPL_remove, \
    SEQ_IMPL_removen, \
    SEQ_IMPL_erase, \
    SEQ_IMPL_erasen, \
    SEQ_IMPL_eraseonce, \
    SEQ_IMPL_cpy, \
    SEQ_IMPL_ncpy \
  )
#define VEC8_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  VEC_IMPL_DFT(SCOPE, ID, T, 8, REALLOC, FREE, CMP)
#define VEC16_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  VEC_IMPL_DFT(SCOPE, ID, T, 16, REALLOC, FREE, CMP)
#define VEC32_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  VEC_IMPL_DFT(SCOPE, ID, T, 32, REALLOC, FREE, CMP)
#define VEC64_IMPL_DFT(SCOPE, ID, T, REALLOC, FREE, CMP) \
  VEC_IMPL_DFT(SCOPE, ID, T, 64, REALLOC, FREE, CMP)

#define VEC_IMPL(SCOPE, ID, T, BITS, CMP) \
  VEC_IMPL_DFT(SCOPE, ID, T, BITS, realloc, free, CMP)
#define VEC8_IMPL(SCOPE, ID, T, CMP) \
  VEC_IMPL(SCOPE, ID, T, 8, CMP)
#define VEC16_IMPL(SCOPE, ID, T, CMP) \
  VEC_IMPL(SCOPE, ID, T, 16, CMP)
#define VEC32_IMPL(SCOPE, ID, T, CMP) \
  VEC_IMPL(SCOPE, ID, T, 32, CMP)
#define VEC64_IMPL(SCOPE, ID, T, CMP) \
  VEC_IMPL(SCOPE, ID, T, 64, CMP)

#define VEC_DEFINE_DFT(ID, T, BITS, REALLOC, FREE, CMP) \
  typedef vecof(T, BITS) ID##_t; \
  VEC_IMPL_DFT(static FORCEINLINE, ID, T, BITS, REALLOC, FREE, CMP)
#define VEC8_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  VEC_DEFINE_DFT(ID, T, 8, REALLOC, FREE, CMP)
#define VEC16_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  VEC_DEFINE_DFT(ID, T, 16, REALLOC, FREE, CMP)
#define VEC32_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  VEC_DEFINE_DFT(ID, T, 32, REALLOC, FREE, CMP)
#define VEC64_DEFINE_DFT(ID, T, REALLOC, FREE, CMP) \
  VEC_DEFINE_DFT(ID, T, 64, REALLOC, FREE, CMP)

#define VEC_DEFINE(ID, T, BITS, CMP) \
  VEC_DEFINE_DFT(ID, T, BITS, realloc, free, CMP)
#define VEC8_DEFINE(ID, T, CMP) VEC_DEFINE(ID, T, 8, CMP)
#define VEC16_DEFINE(ID, T, CMP) VEC_DEFINE(ID, T, 16, CMP)
#define VEC32_DEFINE(ID, T, CMP) VEC_DEFINE(ID, T, 32, CMP)
#define VEC64_DEFINE(ID, T, CMP) VEC_DEFINE(ID, T, 64, CMP)

VEC32_DEFINE(i8vec, i8_t, i8cmp)
VEC32_DEFINE(u8vec, u8_t, u8cmp)
VEC32_DEFINE(i16vec, i16_t, i16cmp)
VEC32_DEFINE(u16vec, u16_t, u16cmp)
VEC32_DEFINE(i32vec, i32_t, i32cmp)
VEC32_DEFINE(u32vec, u32_t, u32cmp)
VEC32_DEFINE(i64vec, i64_t, i64cmp)
VEC32_DEFINE(u64vec, u64_t, u64cmp)
VEC32_DEFINE(charvec, char_t, i8cmp)
VEC32_DEFINE(strvec, char_t *, strcmp)
VEC32_DEFINE(dstr, i8_t, i8cmp)

#endif /* !__UDS_VEC_H */
