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

#include <cute.h>

#include "uds/vec.h"

VEC8_DEFINE(vi8, i8_t, i8cmp);
VEC8_DEFINE(vu8, u8_t, u8cmp);
VEC16_DEFINE(vi16, i16_t, i16cmp);
VEC16_DEFINE(vu16, u16_t, u16cmp);
VEC32_DEFINE(vi32, i32_t, i32cmp);
VEC32_DEFINE(vu32, u32_t, u32cmp);
VEC64_DEFINE(vi64, i64_t, i64cmp);
VEC64_DEFINE(vu64, u64_t, u64cmp);
VEC8_DEFINE(strv8, i8_t *, strcmp);
VEC16_DEFINE(strv16, i8_t *, strcmp);
VEC32_DEFINE(strv32, i8_t *, strcmp);
VEC64_DEFINE(strv64, i8_t *, strcmp);

#define NOMEM_REALLOC(x, y) ((errno = ENOMEM), nil)

VEC_DEFINE_DFT(v8_nomem, i8_t, 8, NOMEM_REALLOC, free, i8cmp);
VEC_DEFINE_DFT(v16_nomem, i8_t, 16, NOMEM_REALLOC, free, i8cmp);
VEC_DEFINE_DFT(v32_nomem, i8_t, 32, NOMEM_REALLOC, free, i8cmp);
VEC_DEFINE_DFT(v64_nomem, i8_t, 64, NOMEM_REALLOC, free, i8cmp);

typedef struct {
  f64_t x, y;
} vec2_t;

i8_t vec2cmp(const vec2_t a, const vec2_t b) {
  return f64cmp(a.x, b.x) + f64cmp(a.y, b.y);
}

VEC64_DEFINE(line, vec2_t, vec2cmp);

CUTEST_DATA {
  vi8_t vi8;
  vu8_t vu8;
  v8_nomem_t v8_nomem;
  vi16_t vi16;
  vu16_t vu16;
  v16_nomem_t v16_nomem;
  vi32_t vi32;
  vu32_t vu32;
  v32_nomem_t v32_nomem;
  vi64_t vi64;
  vu64_t vu64;
  v64_nomem_t v64_nomem;
  line_t line;
};

CUTEST_SETUP {
  vi8_ctor(&self->vi8);
  vu8_ctor(&self->vu8);
  v8_nomem_ctor(&self->v8_nomem);
  vi16_ctor(&self->vi16);
  vu16_ctor(&self->vu16);
  v16_nomem_ctor(&self->v16_nomem);
  vi32_ctor(&self->vi32);
  vu32_ctor(&self->vu32);
  v32_nomem_ctor(&self->v32_nomem);
  vi64_ctor(&self->vi64);
  vu64_ctor(&self->vu64);
  v64_nomem_ctor(&self->v64_nomem);
  line_ctor(&self->line);
}

CUTEST_TEARDOWN {
  vi8_dtor(&self->vi8);
  vu8_dtor(&self->vu8);
  v8_nomem_dtor(&self->v8_nomem);
  vi16_dtor(&self->vi16);
  vu16_dtor(&self->vu16);
  v16_nomem_dtor(&self->v16_nomem);
  vi32_dtor(&self->vi32);
  vu32_dtor(&self->vu32);
  v32_nomem_dtor(&self->v32_nomem);
  vi64_dtor(&self->vi64);
  vu64_dtor(&self->vu64);
  v64_nomem_dtor(&self->v64_nomem);
  line_dtor(&self->line);
}

CUTEST(vec, ensure) {
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 0));
  ASSERT_EQ(0, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next8(SEQ_MIN_CAP + 1), self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, U8_MAX));
  ASSERT_EQ(U8_MAX, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, U8_MAX));
  ASSERT_EQ(U8_MAX, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);

  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 0));
  ASSERT_EQ(0, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_EQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next16(SEQ_MIN_CAP + 1), self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, U16_MAX));
  ASSERT_EQ(U16_MAX, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, U16_MAX));
  ASSERT_EQ(U16_MAX, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);

  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 0));
  ASSERT_EQ(0, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_EQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next32(SEQ_MIN_CAP + 1), self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, U32_MAX));
  ASSERT_EQ(U32_MAX, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, U32_MAX));
  ASSERT_EQ(U32_MAX, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);

  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 0));
  ASSERT_EQ(0, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_EQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next64(SEQ_MIN_CAP + 1), self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, U64_MAX));
  ASSERT_EQ(U64_MAX, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, U64_MAX));
  ASSERT_EQ(U64_MAX, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 0));
  ASSERT_EQ(0, self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_EQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next64(SEQ_MIN_CAP + 1), self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, pow2_next64(SEQ_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next64(SEQ_MIN_CAP + 1), self->line.cap);
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);

  ASSERT_EQ(RET_ERRNO, v8_nomem_ensure(&self->v8_nomem, 1));
  ASSERT_EQ(0, self->v8_nomem.cap);
  ASSERT_EQ(0, v8_nomem_size(&self->v8_nomem));
  ASSERT_EQ(nil, self->v8_nomem.buf);

  ASSERT_EQ(RET_ERRNO, v16_nomem_ensure(&self->v16_nomem, 1));
  ASSERT_EQ(0, self->v16_nomem.cap);
  ASSERT_EQ(0, v16_nomem_size(&self->v16_nomem));
  ASSERT_EQ(nil, self->v16_nomem.buf);

  ASSERT_EQ(RET_ERRNO, v32_nomem_ensure(&self->v32_nomem, 1));
  ASSERT_EQ(0, self->v32_nomem.cap);
  ASSERT_EQ(0, v32_nomem_size(&self->v32_nomem));
  ASSERT_EQ(nil, self->v32_nomem.buf);

  ASSERT_EQ(RET_ERRNO, v64_nomem_ensure(&self->v64_nomem, 1));
  ASSERT_EQ(0, self->v64_nomem.cap);
  ASSERT_EQ(0, v64_nomem_size(&self->v64_nomem));
  ASSERT_EQ(nil, self->v64_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, grow) {
  ASSERT_EQ(RET_SUCCESS, vi8_grow(&self->vi8, 0));
  ASSERT_EQ(0, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_grow(&self->vi8, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_grow(&self->vi8, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_grow(&self->vi8, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_grow(&self->vi8, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  
  ASSERT_EQ(RET_SUCCESS, vi16_grow(&self->vi16, 0));
  ASSERT_EQ(0, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_EQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_grow(&self->vi16, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_grow(&self->vi16, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_grow(&self->vi16, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_grow(&self->vi16, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  
  ASSERT_EQ(RET_SUCCESS, vi32_grow(&self->vi32, 0));
  ASSERT_EQ(0, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_EQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_grow(&self->vi32, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_grow(&self->vi32, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_grow(&self->vi32, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_grow(&self->vi32, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);

  ASSERT_EQ(RET_SUCCESS, vi64_grow(&self->vi64, 0));
  ASSERT_EQ(0, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_EQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_grow(&self->vi64, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_grow(&self->vi64, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_grow(&self->vi64, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_grow(&self->vi64, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, shrink) {
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_shrink(&self->vi8, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_shrink(&self->vi8, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_shrink(&self->vi8, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_shrink(&self->vi8, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);

  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_shrink(&self->vi16, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_shrink(&self->vi16, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_shrink(&self->vi16, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(RET_SUCCESS, vi16_shrink(&self->vi16, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);

  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_shrink(&self->vi32, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_shrink(&self->vi32, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_shrink(&self->vi32, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(RET_SUCCESS, vi32_shrink(&self->vi32, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);

  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_shrink(&self->vi64, 2));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_shrink(&self->vi64, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_shrink(&self->vi64, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(RET_SUCCESS, vi64_shrink(&self->vi64, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, trim) {
  ASSERT_EQ(RET_SUCCESS, vi8_ensure(&self->vi8, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  self->vi8.len = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, vi8_trim(&self->vi8));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(SEQ_MIN_CAP, vi8_size(&self->vi8));
  ASSERT_NEQ(nil, self->vi8.buf);
  while (self->vi8.len) {
    --self->vi8.len;
    ASSERT_EQ(RET_SUCCESS, vi8_trim(&self->vi8));
    ASSERT_EQ(self->vi8.len, self->vi8.cap);
    if (self->vi8.len) {
      ASSERT_NEQ(nil, self->vi8.buf);
    }
  }
  ASSERT_EQ(0, self->vi8.cap);
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_EQ(nil, self->vi8.buf);

  ASSERT_EQ(RET_SUCCESS, vi16_ensure(&self->vi16, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  self->vi16.len = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, vi16_trim(&self->vi16));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(SEQ_MIN_CAP, vi16_size(&self->vi16));
  ASSERT_NEQ(nil, self->vi16.buf);
  while (self->vi16.len) {
    --self->vi16.len;
    ASSERT_EQ(RET_SUCCESS, vi16_trim(&self->vi16));
    ASSERT_EQ(self->vi16.len, self->vi16.cap);
    if (self->vi16.len) {
      ASSERT_NEQ(nil, self->vi16.buf);
    }
  }
  ASSERT_EQ(0, self->vi16.cap);
  ASSERT_EQ(0, vi16_size(&self->vi16));
  ASSERT_EQ(nil, self->vi16.buf);

  ASSERT_EQ(RET_SUCCESS, vi32_ensure(&self->vi32, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  self->vi32.len = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, vi32_trim(&self->vi32));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(SEQ_MIN_CAP, vi32_size(&self->vi32));
  ASSERT_NEQ(nil, self->vi32.buf);
  while (self->vi32.len) {
    --self->vi32.len;
    ASSERT_EQ(RET_SUCCESS, vi32_trim(&self->vi32));
    ASSERT_EQ(self->vi32.len, self->vi32.cap);
    if (self->vi32.len) {
      ASSERT_NEQ(nil, self->vi32.buf);
    }
  }
  ASSERT_EQ(0, self->vi32.cap);
  ASSERT_EQ(0, vi32_size(&self->vi32));
  ASSERT_EQ(nil, self->vi32.buf);

  ASSERT_EQ(RET_SUCCESS, vi64_ensure(&self->vi64, 1));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  self->vi64.len = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, vi64_trim(&self->vi64));
  ASSERT_EQ(SEQ_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(SEQ_MIN_CAP, vi64_size(&self->vi64));
  ASSERT_NEQ(nil, self->vi64.buf);
  while (self->vi64.len) {
    --self->vi64.len;
    ASSERT_EQ(RET_SUCCESS, vi64_trim(&self->vi64));
    ASSERT_EQ(self->vi64.len, self->vi64.cap);
    if (self->vi64.len) {
      ASSERT_NEQ(nil, self->vi64.buf);
    }
  }
  ASSERT_EQ(0, self->vi64.cap);
  ASSERT_EQ(0, vi64_size(&self->vi64));
  ASSERT_EQ(nil, self->vi64.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, insert) {
  ASSERT_EQ(RET_SUCCESS, vi8_insert(&self->vi8, 0, 2));
  ASSERT_EQ(1, vi8_size(&self->vi8));
  ASSERT_EQ(2, vi8_at(&self->vi8, 0));
  ASSERT_EQ(RET_SUCCESS, vi8_insert(&self->vi8, 1, 4));
  ASSERT_EQ(2, vi8_size(&self->vi8));
  ASSERT_EQ(2, vi8_at(&self->vi8, 0));
  ASSERT_EQ(4, vi8_at(&self->vi8, 1));
  ASSERT_EQ(RET_SUCCESS, vi8_insert(&self->vi8, 0, 1));
  ASSERT_EQ(3, vi8_size(&self->vi8));
  ASSERT_EQ(1, vi8_at(&self->vi8, 0));
  ASSERT_EQ(2, vi8_at(&self->vi8, 1));
  ASSERT_EQ(4, vi8_at(&self->vi8, 2));
  ASSERT_EQ(RET_SUCCESS, vi8_insert(&self->vi8, 2, 3));
  ASSERT_EQ(4, vi8_size(&self->vi8));
  ASSERT_EQ(1, vi8_at(&self->vi8, 0));
  ASSERT_EQ(2, vi8_at(&self->vi8, 1));
  ASSERT_EQ(3, vi8_at(&self->vi8, 2));
  ASSERT_EQ(4, vi8_at(&self->vi8, 3));
  ASSERT_EQ(RET_FAILURE, vi8_insert(&self->vi8, 5, 5));
  ASSERT_EQ(RET_ERRNO, v8_nomem_insert(&self->v8_nomem, 0, 1));

  ASSERT_EQ(RET_SUCCESS, vi16_insert(&self->vi16, 0, 2));
  ASSERT_EQ(1, vi16_size(&self->vi16));
  ASSERT_EQ(2, vi16_at(&self->vi16, 0));
  ASSERT_EQ(RET_SUCCESS, vi16_insert(&self->vi16, 1, 4));
  ASSERT_EQ(2, vi16_size(&self->vi16));
  ASSERT_EQ(2, vi16_at(&self->vi16, 0));
  ASSERT_EQ(4, vi16_at(&self->vi16, 1));
  ASSERT_EQ(RET_SUCCESS, vi16_insert(&self->vi16, 0, 1));
  ASSERT_EQ(3, vi16_size(&self->vi16));
  ASSERT_EQ(1, vi16_at(&self->vi16, 0));
  ASSERT_EQ(2, vi16_at(&self->vi16, 1));
  ASSERT_EQ(4, vi16_at(&self->vi16, 2));
  ASSERT_EQ(RET_SUCCESS, vi16_insert(&self->vi16, 2, 3));
  ASSERT_EQ(4, vi16_size(&self->vi16));
  ASSERT_EQ(1, vi16_at(&self->vi16, 0));
  ASSERT_EQ(2, vi16_at(&self->vi16, 1));
  ASSERT_EQ(3, vi16_at(&self->vi16, 2));
  ASSERT_EQ(4, vi16_at(&self->vi16, 3));
  ASSERT_EQ(RET_FAILURE, vi16_insert(&self->vi16, 5, 5));
  ASSERT_EQ(RET_ERRNO, v16_nomem_insert(&self->v16_nomem, 0, 1));

  ASSERT_EQ(RET_SUCCESS, vi32_insert(&self->vi32, 0, 2));
  ASSERT_EQ(1, vi32_size(&self->vi32));
  ASSERT_EQ(2, vi32_at(&self->vi32, 0));
  ASSERT_EQ(RET_SUCCESS, vi32_insert(&self->vi32, 1, 4));
  ASSERT_EQ(2, vi32_size(&self->vi32));
  ASSERT_EQ(2, vi32_at(&self->vi32, 0));
  ASSERT_EQ(4, vi32_at(&self->vi32, 1));
  ASSERT_EQ(RET_SUCCESS, vi32_insert(&self->vi32, 0, 1));
  ASSERT_EQ(3, vi32_size(&self->vi32));
  ASSERT_EQ(1, vi32_at(&self->vi32, 0));
  ASSERT_EQ(2, vi32_at(&self->vi32, 1));
  ASSERT_EQ(4, vi32_at(&self->vi32, 2));
  ASSERT_EQ(RET_SUCCESS, vi32_insert(&self->vi32, 2, 3));
  ASSERT_EQ(4, vi32_size(&self->vi32));
  ASSERT_EQ(1, vi32_at(&self->vi32, 0));
  ASSERT_EQ(2, vi32_at(&self->vi32, 1));
  ASSERT_EQ(3, vi32_at(&self->vi32, 2));
  ASSERT_EQ(4, vi32_at(&self->vi32, 3));
  ASSERT_EQ(RET_FAILURE, vi32_insert(&self->vi32, 5, 5));
  ASSERT_EQ(RET_ERRNO, v32_nomem_insert(&self->v32_nomem, 0, 1));
  return CUTE_SUCCESS;
}

CUTEST(vec, emplace) {
  ASSERT_EQ(RET_SUCCESS, vi8_emplace(&self->vi8, 0, (i8_t[4]){4, 3, 2, 1}, 0));
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_emplace(&self->vi8, 0, (i8_t[4]){4, 3, 2, 1}, 1));
  ASSERT_EQ(1, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(RET_SUCCESS, vi8_emplace(&self->vi8, 1, (i8_t[4]){4, 3, 2, 1}, 2));
  ASSERT_EQ(3, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(4, vi8_at(&self->vi8, 1));
  ASSERT_EQ(3, vi8_at(&self->vi8, 2));
  ASSERT_EQ(RET_SUCCESS, vi8_emplace(&self->vi8, 0, (i8_t[4]){4, 3, 2, 1}, 3));
  ASSERT_EQ(6, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(3, vi8_at(&self->vi8, 1));
  ASSERT_EQ(2, vi8_at(&self->vi8, 2));
  ASSERT_EQ(4, vi8_at(&self->vi8, 3));
  ASSERT_EQ(4, vi8_at(&self->vi8, 4));
  ASSERT_EQ(3, vi8_at(&self->vi8, 5));
  ASSERT_EQ(RET_SUCCESS, vi8_emplace(&self->vi8, 3, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(10, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(3, vi8_at(&self->vi8, 1));
  ASSERT_EQ(2, vi8_at(&self->vi8, 2));
  ASSERT_EQ(4, vi8_at(&self->vi8, 3));
  ASSERT_EQ(3, vi8_at(&self->vi8, 4));
  ASSERT_EQ(2, vi8_at(&self->vi8, 5));
  ASSERT_EQ(1, vi8_at(&self->vi8, 6));
  ASSERT_EQ(4, vi8_at(&self->vi8, 7));
  ASSERT_EQ(4, vi8_at(&self->vi8, 8));
  ASSERT_EQ(3, vi8_at(&self->vi8, 9));
  ASSERT_EQ(
    RET_ERRNO, v8_nomem_emplace(&self->v8_nomem, 0, (i8_t[4]){4, 3, 2, 1}, 1)
  );
  return CUTE_SUCCESS;
}

CUTEST(vec, push) {
  i8_t i, j;

  for (i = 0; i < 10; ++i) {
    ASSERT_EQ(RET_SUCCESS, vi8_push(&self->vi8, i));
    ASSERT_EQ(i + 1, vi8_size(&self->vi8));
    for (j = 0; j < self->vi8.len; ++j) {
      ASSERT_EQ(j, vi8_at(&self->vi8, j));
    }
  }
  ASSERT_EQ(RET_ERRNO, v8_nomem_push(&self->v8_nomem, 0));
  return CUTE_SUCCESS;
}

CUTEST(vec, append) {
  ASSERT_EQ(RET_SUCCESS, vi8_append(&self->vi8, (i8_t[4]){4, 3, 2, 1}, 0));
  ASSERT_EQ(0, vi8_size(&self->vi8));
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(RET_SUCCESS, vi8_append(&self->vi8, (i8_t[4]){4, 3, 2, 1}, 1));
  ASSERT_EQ(1, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(RET_SUCCESS, vi8_append(&self->vi8, (i8_t[4]){4, 3, 2, 1}, 2));
  ASSERT_EQ(3, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(4, vi8_at(&self->vi8, 1));
  ASSERT_EQ(3, vi8_at(&self->vi8, 2));
  ASSERT_EQ(RET_SUCCESS, vi8_append(&self->vi8, (i8_t[4]){4, 3, 2, 1}, 3));
  ASSERT_EQ(6, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(4, vi8_at(&self->vi8, 1));
  ASSERT_EQ(3, vi8_at(&self->vi8, 2));
  ASSERT_EQ(4, vi8_at(&self->vi8, 3));
  ASSERT_EQ(3, vi8_at(&self->vi8, 4));
  ASSERT_EQ(2, vi8_at(&self->vi8, 5));
  ASSERT_EQ(RET_SUCCESS, vi8_append(&self->vi8, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(10, vi8_size(&self->vi8));
  ASSERT_EQ(4, vi8_at(&self->vi8, 0));
  ASSERT_EQ(4, vi8_at(&self->vi8, 1));
  ASSERT_EQ(3, vi8_at(&self->vi8, 2));
  ASSERT_EQ(4, vi8_at(&self->vi8, 3));
  ASSERT_EQ(3, vi8_at(&self->vi8, 4));
  ASSERT_EQ(2, vi8_at(&self->vi8, 5));
  ASSERT_EQ(4, vi8_at(&self->vi8, 6));
  ASSERT_EQ(3, vi8_at(&self->vi8, 7));
  ASSERT_EQ(2, vi8_at(&self->vi8, 8));
  ASSERT_EQ(1, vi8_at(&self->vi8, 9));
  ASSERT_EQ(
    RET_ERRNO, v8_nomem_append(&self->v8_nomem, (i8_t[4]){4, 3, 2, 1}, 4)
  );
  return CUTE_SUCCESS;
}

i32_t main(void) {
  CUTEST_DATA test;

  CUTEST_PASS(vec, ensure);
  CUTEST_PASS(vec, grow);
  CUTEST_PASS(vec, shrink);
  CUTEST_PASS(vec, trim);
  CUTEST_PASS(vec, insert);
  CUTEST_PASS(vec, emplace);
  CUTEST_PASS(vec, push);
  CUTEST_PASS(vec, append);
  return EXIT_SUCCESS;
}
