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

#define NOMEM_REALLOC(x, y) ((errno = ENOMEM), nil)
VEC_DEFINE_DFT(i8vec_nomem, i8_t, 8, NOMEM_REALLOC, free, i8cmp)

typedef struct {
  f64_t x, y;
} point_t;

i8_t point_cmp(__const point_t a, __const point_t b) {
  return f64cmp(a.x, b.x) + f64cmp(a.y, b.y);
}

VEC64_DEFINE(line, point_t, point_cmp)

CUTEST_DATA {
  i8vec_t i8vec;
  i8vec_nomem_t i8vec_nomem;
  line_t line;
};

CUTEST_SETUP {
  i8vec_ctor(&self->i8vec);
  i8vec_nomem_ctor(&self->i8vec_nomem);
  line_ctor(&self->line);
}

CUTEST_TEARDOWN {
  i8vec_dtor(&self->i8vec);
  i8vec_nomem_dtor(&self->i8vec_nomem);
  line_dtor(&self->line);
}

CUTEST(vec, ensure) {
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 0));
  ASSERT_EQ(0, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next8(SEQ_MIN_CAP + 1), i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, U32_MAX));
  ASSERT_EQ(U32_MAX, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, U32_MAX));
  ASSERT_EQ(U32_MAX, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);

  ASSERT_EQ(RET_ERRNO, i8vec_nomem_ensure(&self->i8vec_nomem, 1));
  ASSERT_EQ(0, i8vec_nomem_cap(&self->i8vec_nomem));
  ASSERT_EQ(0, i8vec_nomem_size(&self->i8vec_nomem));
  ASSERT_EQ(nil, self->i8vec_nomem.buf);
  
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 0));
  ASSERT_EQ(0, line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_EQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 1));
  ASSERT_EQ(SEQ_MIN_CAP, line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 1));
  ASSERT_EQ(SEQ_MIN_CAP, line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, 2));
  ASSERT_EQ(SEQ_MIN_CAP, line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next64(SEQ_MIN_CAP + 1), line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(RET_SUCCESS, line_ensure(&self->line, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  line_dtor(&self->line);
  ASSERT_EQ(RET_SUCCESS,
    line_ensure(&self->line, pow2_next64(SEQ_MIN_CAP + 1))
  );
  ASSERT_EQ(pow2_next64(SEQ_MIN_CAP + 1), line_cap(&self->line));
  ASSERT_EQ(0, line_size(&self->line));
  ASSERT_NEQ(nil, self->line.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, grow) {
  ASSERT_EQ(RET_SUCCESS, i8vec_grow(&self->i8vec, 0));
  ASSERT_EQ(0, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_grow(&self->i8vec, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_grow(&self->i8vec, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_grow(&self->i8vec, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_grow(&self->i8vec, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, shrink) {
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_shrink(&self->i8vec, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_shrink(&self->i8vec, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_shrink(&self->i8vec, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_shrink(&self->i8vec, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, trim) {
  ASSERT_EQ(RET_SUCCESS, i8vec_ensure(&self->i8vec, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  self->i8vec.len = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, i8vec_trim(&self->i8vec));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_cap(&self->i8vec));
  ASSERT_EQ(SEQ_MIN_CAP, i8vec_size(&self->i8vec));
  ASSERT_NEQ(nil, self->i8vec.buf);
  while (self->i8vec.len) {
    --self->i8vec.len;
    ASSERT_EQ(RET_SUCCESS, i8vec_trim(&self->i8vec));
    ASSERT_EQ(self->i8vec.len, i8vec_cap(&self->i8vec));
    if (self->i8vec.len) {
      ASSERT_NEQ(nil, self->i8vec.buf);
    }
  }
  ASSERT_EQ(0, i8vec_cap(&self->i8vec));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, insert) {
  ASSERT_EQ(RET_SUCCESS, i8vec_insert(&self->i8vec, 0, 2));
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS, i8vec_insert(&self->i8vec, 1, 4));
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(RET_SUCCESS, i8vec_insert(&self->i8vec, 0, 1));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(RET_SUCCESS, i8vec_insert(&self->i8vec, 2, 3));
  ASSERT_EQ(4, i8vec_size(&self->i8vec));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(RET_FAILURE, i8vec_insert(&self->i8vec, 5, 5));
  ASSERT_EQ(RET_ERRNO, i8vec_nomem_insert(&self->i8vec_nomem, 0, 1));
  return CUTE_SUCCESS;
}

CUTEST(vec, emplace) {
  ASSERT_EQ(RET_SUCCESS,
    i8vec_emplace(&self->i8vec, 0, vec(i8_t, 4, 3, 2, 1), 0)
  );
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS,
    i8vec_emplace(&self->i8vec, 0, vec(i8_t, 4, 3, 2, 1), 1)
  );
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_emplace(&self->i8vec, 1, vec(i8_t, 4, 3, 2, 1), 2)
  );
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_emplace(&self->i8vec, 0, vec(i8_t, 4, 3, 2, 1), 3)
  );
  ASSERT_EQ(6, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_emplace(&self->i8vec, 3, vec(i8_t, 4, 3, 2, 1), 4)
  );
  ASSERT_EQ(10, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 6));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 7));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 8));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 9));
  ASSERT_EQ(RET_ERRNO,
    i8vec_nomem_emplace(&self->i8vec_nomem, 0, vec(i8_t, 4, 3, 2, 1), 1)
  );
  return CUTE_SUCCESS;
}

CUTEST(vec, push) {
  u8_t i, j;

  for (i = 0; i < 10; ++i) {
    ASSERT_EQ(RET_SUCCESS, i8vec_push(&self->i8vec, i));
    ASSERT_EQ(i + 1, i8vec_size(&self->i8vec));
    for (j = 0; j < i8vec_size(&self->i8vec); ++j) {
      ASSERT_EQ(j, i8vec_at(&self->i8vec, (u8_t) j));
    }
  }
  ASSERT_EQ(RET_ERRNO, i8vec_nomem_push(&self->i8vec_nomem, 0));
  return CUTE_SUCCESS;
}

CUTEST(vec, append) {
  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 0));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 1));
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 2));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 3));
  ASSERT_EQ(6, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 4));
  ASSERT_EQ(10, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 6));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 7));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 8));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 9));
  ASSERT_EQ(RET_ERRNO,
    i8vec_nomem_append(&self->i8vec_nomem, vec(i8_t, 4, 3, 2, 1), 4)
  );
  return CUTE_SUCCESS;
}

CUTEST(vec, pop) {
  i8_t i;

  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 4));
  ASSERT_EQ(4, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(true, i8vec_pop(&self->i8vec, nil));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(true, i8vec_pop(&self->i8vec, &i));
  ASSERT_EQ(2, i);
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_pop(&self->i8vec, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(true, i8vec_pop(&self->i8vec, &i));
  ASSERT_EQ(4, i);
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(false, i8vec_pop(&self->i8vec, &i));
  return CUTE_SUCCESS;
}

CUTEST(vec, unshift) {
  u8_t i, j;
  i8_t k;

  for (i = 0; i < 10; ++i) {
    ASSERT_EQ(RET_SUCCESS, i8vec_unshift(&self->i8vec, i));
    ASSERT_EQ(i + 1, i8vec_size(&self->i8vec));
    for (j = 0, k = i; j < i8vec_size(&self->i8vec); ++j) {
      ASSERT_EQ(k--, i8vec_at(&self->i8vec, (u8_t) j));
    }
  }
  ASSERT_EQ(RET_ERRNO, i8vec_nomem_unshift(&self->i8vec_nomem, 0));
  return CUTE_SUCCESS;
}

CUTEST(vec, prepend) {
  ASSERT_EQ(RET_SUCCESS, i8vec_prepend(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 0));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(nil, self->i8vec.buf);
  ASSERT_EQ(RET_SUCCESS, i8vec_prepend(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 1));
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS, i8vec_prepend(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 2));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(RET_SUCCESS, i8vec_prepend(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 3));
  ASSERT_EQ(6, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(RET_SUCCESS, i8vec_prepend(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 4));
  ASSERT_EQ(10, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 5));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 6));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 7));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 8));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 9));
  ASSERT_EQ(RET_ERRNO,
    i8vec_nomem_prepend(&self->i8vec_nomem, vec(i8_t, 4, 3, 2, 1), 4)
  );
  return CUTE_SUCCESS;
}

CUTEST(vec, shift) {
  i8_t i;

  ASSERT_EQ(RET_SUCCESS, i8vec_append(&self->i8vec, vec(i8_t, 4, 3, 2, 1), 4));
  ASSERT_EQ(4, i8vec_size(&self->i8vec));
  ASSERT_EQ(4, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(true, i8vec_shift(&self->i8vec, nil));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(true, i8vec_shift(&self->i8vec, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_shift(&self->i8vec, &i));
  ASSERT_EQ(2, i);
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(true, i8vec_shift(&self->i8vec, &i));
  ASSERT_EQ(1, i);
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(false, i8vec_shift(&self->i8vec, &i));
  return CUTE_SUCCESS;
}

CUTEST(vec, remove) {
  i8_t i;

  ASSERT_EQ(false, i8vec_remove(&self->i8vec, 0, nil));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&self->i8vec, vec(i8_t, 0, 1, 2, 3), 4)
  );
  ASSERT_EQ(false, i8vec_remove(&self->i8vec, 4, nil));
  ASSERT_EQ(true, i8vec_remove(&self->i8vec, 2, nil));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(true, i8vec_remove(&self->i8vec, 1, &i));
  ASSERT_EQ(1, i);
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_remove(&self->i8vec, 1, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(true, i8vec_remove(&self->i8vec, 0, &i));
  ASSERT_EQ(0, i);
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(false, i8vec_remove(&self->i8vec, 0, &i));
  return CUTE_SUCCESS;
}

CUTEST(vec, removen) {
  i8_t buf[2], *ptr;

  ptr = buf;
  ASSERT_EQ(false, i8vec_removen(&self->i8vec, 0, 0, nil));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&self->i8vec, vec(i8_t, 0, 1, 2, 3, 5, 6), 6)
  );
  ASSERT_EQ(false, i8vec_removen(&self->i8vec, 6, 0, nil));
  ASSERT_EQ(true, i8vec_removen(&self->i8vec, 2, 2, nil));
  ASSERT_EQ(4, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(1, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(5, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(6, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(true, i8vec_removen(&self->i8vec, 1, 2, &ptr));
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(1, buf[0]);
  ASSERT_EQ(5, buf[1]);
  ASSERT_EQ(6, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_removen(&self->i8vec, 0, 1, &ptr));
  ASSERT_EQ(1, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, buf[0]);
  ASSERT_EQ(6, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(true, i8vec_removen(&self->i8vec, 0, 1, &ptr));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(6, buf[0]);
  ASSERT_EQ(false, i8vec_removen(&self->i8vec, 0, 1, &ptr));
  return CUTE_SUCCESS;
}

CUTEST(vec, erase) {
  ASSERT_EQ(0, i8vec_erase(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&self->i8vec, vec(i8_t, 1, 2, 1, 2, 3, 3, 2), 7)
  );
  ASSERT_EQ(2, i8vec_erase(&self->i8vec, 1));
  ASSERT_EQ(5, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(3, i8vec_erase(&self->i8vec, 2));
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_erase(&self->i8vec, 3));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_erase(&self->i8vec, 3));
  return CUTE_SUCCESS;
}

CUTEST(vec, erasen) {
  ASSERT_EQ(0, i8vec_erasen(&self->i8vec, 0, 1));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&self->i8vec, vec(i8_t, 1, 2, 1, 2, 3, 3, 2), 7)
  );
  ASSERT_EQ(0, i8vec_erasen(&self->i8vec, 1, 0));
  ASSERT_EQ(2, i8vec_erasen(&self->i8vec, 1, 3));
  ASSERT_EQ(5, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(2, i8vec_erasen(&self->i8vec, 2, 2));
  ASSERT_EQ(3, i8vec_size(&self->i8vec));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(1, i8vec_erasen(&self->i8vec, 2, 2));
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(2, i8vec_erasen(&self->i8vec, 3, 2));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(0, i8vec_erasen(&self->i8vec, 3, 1));
  return CUTE_SUCCESS;
}

CUTEST(vec, eraseonce) {
  ASSERT_EQ(false, i8vec_eraseonce(&self->i8vec, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&self->i8vec, vec(i8_t, 1, 2, 1, 2, 3, 3, 2), 7)
  );
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 1));
  ASSERT_EQ(false, i8vec_eraseonce(&self->i8vec, 1));
  ASSERT_EQ(5, i8vec_size(&self->i8vec));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 2));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 3));
  ASSERT_EQ(2, i8vec_at(&self->i8vec, 4));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 2));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 2));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 2));
  ASSERT_EQ(false, i8vec_eraseonce(&self->i8vec, 2));
  ASSERT_EQ(2, i8vec_size(&self->i8vec));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 0));
  ASSERT_EQ(3, i8vec_at(&self->i8vec, 1));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 3));
  ASSERT_EQ(true, i8vec_eraseonce(&self->i8vec, 3));
  ASSERT_EQ(false, i8vec_eraseonce(&self->i8vec, 3));
  ASSERT_EQ(0, i8vec_size(&self->i8vec));
  ASSERT_EQ(false, i8vec_eraseonce(&self->i8vec, 3));
  return CUTE_SUCCESS;
}

CUTEST(vec, cpy) {
  i8vec_t src;

  i8vec_ctor(&src);
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&src, vec(i8_t, 1, 2, 1, 2, 3, 3, 2), 7)
  );
  ASSERT_EQ(RET_SUCCESS, i8vec_cpy(&self->i8vec, &src));
  ASSERT_EQ(7, self->i8vec.len);
  ASSERT_EQ(src.len, self->i8vec.len);
  ASSERT_EQ(src.cap, self->i8vec.cap);
  ASSERT_NEQ(src.buf, self->i8vec.buf);
  return CUTE_SUCCESS;
}

CUTEST(vec, ncpy) {
  i8vec_t src;

  i8vec_ctor(&src);
  ASSERT_EQ(RET_SUCCESS,
    i8vec_append(&src, vec(i8_t, 0, 1, 2, 3, 4, 5, 6), 7)
  );
  ASSERT_EQ(RET_SUCCESS, i8vec_ncpy(&self->i8vec, &src, 5));
  ASSERT_EQ(5, self->i8vec.len);
  ASSERT_NEQ(src.len, self->i8vec.len);
  ASSERT_EQ(src.cap, self->i8vec.cap);
  ASSERT_NEQ(src.buf, self->i8vec.buf);
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
  CUTEST_PASS(vec, pop);
  CUTEST_PASS(vec, unshift);
  CUTEST_PASS(vec, prepend);
  CUTEST_PASS(vec, shift);
  CUTEST_PASS(vec, remove);
  CUTEST_PASS(vec, removen);
  CUTEST_PASS(vec, erase);
  CUTEST_PASS(vec, erasen);
  CUTEST_PASS(vec, eraseonce);
  CUTEST_PASS(vec, cpy);
  CUTEST_PASS(vec, ncpy);
  return EXIT_SUCCESS;
}
