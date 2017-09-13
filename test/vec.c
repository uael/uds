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

#include "cute.h"

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

VEC_DEFINE_ALLOC(v8_nomem, i8_t, 8, i8cmp, malloc, NOMEM_REALLOC, free);
VEC_DEFINE_ALLOC(v16_nomem, i8_t, 16, i8cmp, malloc, NOMEM_REALLOC, free);
VEC_DEFINE_ALLOC(v32_nomem, i8_t, 32, i8cmp, malloc, NOMEM_REALLOC, free);
VEC_DEFINE_ALLOC(v64_nomem, i8_t, 64, i8cmp, malloc, NOMEM_REALLOC, free);

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

CUTEST(v8, growth) {
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, 0));
  ASSERT_EQ(0, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, 2));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, VEC_MIN_CAP + 1));
  ASSERT_EQ(pow2_next8(VEC_MIN_CAP + 1), self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, U8_MAX));
  ASSERT_EQ(U8_MAX, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, U8_MAX));
  ASSERT_EQ(U8_MAX, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  vi8_dtor(&self->vi8);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  vi8_dtor(&self->vi8);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, U8_MAX));
  ASSERT_EQ(U8_MAX, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  vi8_dtor(&self->vi8);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, pow2_next8(VEC_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next8(VEC_MIN_CAP + 1), self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v8_nomem_growth(&self->v8_nomem, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->v8_nomem.cap);
  ASSERT_EQ(0, self->v8_nomem.len);
  ASSERT_NEQ(nil, self->v8_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v8_nomem_growth(&self->v8_nomem, VEC_MIN_CAP + 1));
  ASSERT_EQ(0, self->v8_nomem.cap);
  ASSERT_EQ(0, self->v8_nomem.len);
  ASSERT_EQ(nil, self->v8_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v16, growth) {
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, 0));
  ASSERT_EQ(0, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_EQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, 2));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, VEC_MIN_CAP + 1));
  ASSERT_EQ(pow2_next16(VEC_MIN_CAP + 1), self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, U16_MAX));
  ASSERT_EQ(U16_MAX, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, U16_MAX));
  ASSERT_EQ(U16_MAX, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  vi16_dtor(&self->vi16);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  vi16_dtor(&self->vi16);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, U16_MAX));
  ASSERT_EQ(U16_MAX, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  vi16_dtor(&self->vi16);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, pow2_next16(VEC_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next16(VEC_MIN_CAP + 1), self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v16_nomem_growth(&self->v16_nomem, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->v16_nomem.cap);
  ASSERT_EQ(0, self->v16_nomem.len);
  ASSERT_NEQ(nil, self->v16_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v16_nomem_growth(&self->v16_nomem, VEC_MIN_CAP + 1));
  ASSERT_EQ(0, self->v16_nomem.cap);
  ASSERT_EQ(0, self->v16_nomem.len);
  ASSERT_EQ(nil, self->v16_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v32, growth) {
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, 0));
  ASSERT_EQ(0, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_EQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, 2));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, VEC_MIN_CAP + 1));
  ASSERT_EQ(pow2_next32(VEC_MIN_CAP + 1), self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  vi32_dtor(&self->vi32);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  vi32_dtor(&self->vi32);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, pow2_next32(VEC_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next32(VEC_MIN_CAP + 1), self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v32_nomem_growth(&self->v32_nomem, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->v32_nomem.cap);
  ASSERT_EQ(0, self->v32_nomem.len);
  ASSERT_NEQ(nil, self->v32_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v32_nomem_growth(&self->v32_nomem, VEC_MIN_CAP + 1));
  ASSERT_EQ(0, self->v32_nomem.cap);
  ASSERT_EQ(0, self->v32_nomem.len);
  ASSERT_EQ(nil, self->v32_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v64, growth) {
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, 0));
  ASSERT_EQ(0, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_EQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, 2));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, VEC_MIN_CAP + 1));
  ASSERT_EQ(pow2_next64(VEC_MIN_CAP + 1), self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  vi64_dtor(&self->vi64);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  vi64_dtor(&self->vi64);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, pow2_next64(VEC_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next64(VEC_MIN_CAP + 1), self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v64_nomem_growth(&self->v64_nomem, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->v64_nomem.cap);
  ASSERT_EQ(0, self->v64_nomem.len);
  ASSERT_NEQ(nil, self->v64_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v64_nomem_growth(&self->v64_nomem, VEC_MIN_CAP + 1));
  ASSERT_EQ(0, self->v64_nomem.cap);
  ASSERT_EQ(0, self->v64_nomem.len);
  ASSERT_EQ(nil, self->v64_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(line, growth) {
  ASSERT_EQ(SUCCESS, line_growth(&self->line, 0));
  ASSERT_EQ(0, self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_EQ(nil, self->line.buf);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, 1));
  ASSERT_EQ(VEC_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, 2));
  ASSERT_EQ(VEC_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, VEC_MIN_CAP + 1));
  ASSERT_EQ(pow2_next64(VEC_MIN_CAP + 1), self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(SUCCESS, line_growth(&self->line, pow2_next64(VEC_MIN_CAP + 1)));
  ASSERT_EQ(pow2_next64(VEC_MIN_CAP + 1), self->line.cap);
  ASSERT_EQ(0, self->line.len);
  ASSERT_NEQ(nil, self->line.buf);
  return CUTE_SUCCESS;
}

CUTEST(v8, decay) {
  ASSERT_EQ(SUCCESS, vi8_decay(&self->vi8, 0));
  ASSERT_EQ(0, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_EQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_growth(&self->vi8, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_decay(&self->vi8, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_decay(&self->vi8, 4));
  ASSERT_EQ(4, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_decay(&self->vi8, 2));
  ASSERT_EQ(2, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);
  ASSERT_EQ(SUCCESS, vi8_decay(&self->vi8, 4));
  ASSERT_EQ(2, self->vi8.cap);
  ASSERT_EQ(0, self->vi8.len);
  ASSERT_NEQ(nil, self->vi8.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v8_nomem_growth(&self->v8_nomem, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->v8_nomem.cap);
  ASSERT_EQ(0, self->v8_nomem.len);
  ASSERT_NEQ(nil, self->v8_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v8_nomem_decay(&self->v8_nomem, 4));
  ASSERT_EQ(0, self->v8_nomem.cap);
  ASSERT_EQ(0, self->v8_nomem.len);
  ASSERT_EQ(nil, self->v8_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v16, decay) {
  ASSERT_EQ(SUCCESS, vi16_decay(&self->vi16, 0));
  ASSERT_EQ(0, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_EQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_growth(&self->vi16, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_decay(&self->vi16, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_decay(&self->vi16, 4));
  ASSERT_EQ(4, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_decay(&self->vi16, 2));
  ASSERT_EQ(2, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);
  ASSERT_EQ(SUCCESS, vi16_decay(&self->vi16, 4));
  ASSERT_EQ(2, self->vi16.cap);
  ASSERT_EQ(0, self->vi16.len);
  ASSERT_NEQ(nil, self->vi16.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v16_nomem_growth(&self->v16_nomem, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->v16_nomem.cap);
  ASSERT_EQ(0, self->v16_nomem.len);
  ASSERT_NEQ(nil, self->v16_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v16_nomem_decay(&self->v16_nomem, 4));
  ASSERT_EQ(0, self->v16_nomem.cap);
  ASSERT_EQ(0, self->v16_nomem.len);
  ASSERT_EQ(nil, self->v16_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v32, decay) {
  ASSERT_EQ(SUCCESS, vi32_decay(&self->vi32, 0));
  ASSERT_EQ(0, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_EQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_growth(&self->vi32, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_decay(&self->vi32, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_decay(&self->vi32, 4));
  ASSERT_EQ(4, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_decay(&self->vi32, 2));
  ASSERT_EQ(2, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);
  ASSERT_EQ(SUCCESS, vi32_decay(&self->vi32, 4));
  ASSERT_EQ(2, self->vi32.cap);
  ASSERT_EQ(0, self->vi32.len);
  ASSERT_NEQ(nil, self->vi32.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v32_nomem_growth(&self->v32_nomem, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->v32_nomem.cap);
  ASSERT_EQ(0, self->v32_nomem.len);
  ASSERT_NEQ(nil, self->v32_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v32_nomem_decay(&self->v32_nomem, 4));
  ASSERT_EQ(0, self->v32_nomem.cap);
  ASSERT_EQ(0, self->v32_nomem.len);
  ASSERT_EQ(nil, self->v32_nomem.buf);
  return CUTE_SUCCESS;
}

CUTEST(v64, decay) {
  ASSERT_EQ(SUCCESS, vi64_decay(&self->vi64, 0));
  ASSERT_EQ(0, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_EQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_growth(&self->vi64, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_decay(&self->vi64, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_decay(&self->vi64, 4));
  ASSERT_EQ(4, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_decay(&self->vi64, 2));
  ASSERT_EQ(2, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);
  ASSERT_EQ(SUCCESS, vi64_decay(&self->vi64, 4));
  ASSERT_EQ(2, self->vi64.cap);
  ASSERT_EQ(0, self->vi64.len);
  ASSERT_NEQ(nil, self->vi64.buf);

  /* No memory left tests */
  ASSERT_EQ(SUCCESS, v64_nomem_growth(&self->v64_nomem, VEC_MIN_CAP));
  ASSERT_EQ(VEC_MIN_CAP, self->v64_nomem.cap);
  ASSERT_EQ(0, self->v64_nomem.len);
  ASSERT_NEQ(nil, self->v64_nomem.buf);
  ASSERT_EQ(ERR_NOMEM, v64_nomem_decay(&self->v64_nomem, 4));
  ASSERT_EQ(0, self->v64_nomem.cap);
  ASSERT_EQ(0, self->v64_nomem.len);
  ASSERT_EQ(nil, self->v64_nomem.buf);
  return CUTE_SUCCESS;
}

i32_t main(void) {
  CUTEST_DATA test;

  CUTEST_PASS(v8, growth);
  CUTEST_PASS(v16, growth);
  CUTEST_PASS(v32, growth);
  CUTEST_PASS(v64, growth);
  CUTEST_PASS(line, growth);
  CUTEST_PASS(v8, decay);
  CUTEST_PASS(v16, decay);
  CUTEST_PASS(v32, decay);
  CUTEST_PASS(v64, decay);
  return EXIT_SUCCESS;
}
