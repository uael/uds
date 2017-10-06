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

#include "uds/deq.h"

#define NOMEM_REALLOC(x, y) ((errno = ENOMEM), nil)
DEQ_DEFINE_DFT(i8deq_nomem, i8_t, 8, NOMEM_REALLOC, free, i8cmp)

typedef struct {
  f64_t x, y;
} point_t;

i8_t point_cmp(__const point_t a, __const point_t b) {
  return f64cmp(a.x, b.x) + f64cmp(a.y, b.y);
}

DEQ64_DEFINE(line, point_t, point_cmp)

CUTEST_DATA {
  i8deq_t i8deq;
  i8deq_nomem_t i8deq_nomem;
  line_t line;
};

CUTEST_SETUP {
  i8deq_ctor(&self->i8deq);
  i8deq_nomem_ctor(&self->i8deq_nomem);
  line_ctor(&self->line);
}

CUTEST_TEARDOWN {
  i8deq_dtor(&self->i8deq);
  i8deq_nomem_dtor(&self->i8deq_nomem);
  line_dtor(&self->line);
}

CUTEST(deq, ensure) {
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 0));
  ASSERT_EQ(0, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, SEQ_MIN_CAP + 1));
  ASSERT_EQ(pow2_next8(SEQ_MIN_CAP + 1), i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, U32_MAX));
  ASSERT_EQ(U32_MAX, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, U32_MAX));
  ASSERT_EQ(U32_MAX, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);

  ASSERT_EQ(RET_ERRNO, i8deq_nomem_ensure(&self->i8deq_nomem, 1));
  ASSERT_EQ(0, i8deq_nomem_cap(&self->i8deq_nomem));
  ASSERT_EQ(0, i8deq_nomem_size(&self->i8deq_nomem));
  ASSERT_EQ(nil, self->i8deq_nomem.buf);
  
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

CUTEST(deq, grow) {
  ASSERT_EQ(RET_SUCCESS, i8deq_grow(&self->i8deq, 0));
  ASSERT_EQ(0, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_grow(&self->i8deq, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_grow(&self->i8deq, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_grow(&self->i8deq, SEQ_MIN_CAP));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_grow(&self->i8deq, SEQ_MIN_CAP + 1));
  ASSERT_EQ(SEQ_MIN_CAP * 2, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  return CUTE_SUCCESS;
}

CUTEST(deq, shrink) {
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_shrink(&self->i8deq, 2));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_shrink(&self->i8deq, SEQ_MIN_CAP / 2));
  ASSERT_EQ(SEQ_MIN_CAP / 2, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_shrink(&self->i8deq, SEQ_MIN_CAP / 4));
  ASSERT_EQ(SEQ_MIN_CAP / 4, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_shrink(&self->i8deq, SEQ_MIN_CAP / 8));
  ASSERT_EQ(SEQ_MIN_CAP / 8, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  return CUTE_SUCCESS;
}

CUTEST(deq, trim) {
  ASSERT_EQ(RET_SUCCESS, i8deq_ensure(&self->i8deq, 1));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  self->i8deq.tail = SEQ_MIN_CAP;
  ASSERT_EQ(RET_SUCCESS, i8deq_trim(&self->i8deq));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_cap(&self->i8deq));
  ASSERT_EQ(SEQ_MIN_CAP, i8deq_size(&self->i8deq));
  ASSERT_NEQ(nil, self->i8deq.buf);
  while (self->i8deq.tail) {
    --self->i8deq.tail;
    ASSERT_EQ(RET_SUCCESS, i8deq_trim(&self->i8deq));
    ASSERT_EQ(self->i8deq.tail, i8deq_cap(&self->i8deq));
    if (self->i8deq.tail) {
      ASSERT_NEQ(nil, self->i8deq.buf);
    }
  }
  ASSERT_EQ(0, i8deq_cap(&self->i8deq));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  return CUTE_SUCCESS;
}

CUTEST(deq, insert) {
  ASSERT_EQ(RET_SUCCESS, i8deq_insert(&self->i8deq, 0, 2));
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS, i8deq_insert(&self->i8deq, 1, 4));
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(RET_SUCCESS, i8deq_insert(&self->i8deq, 0, 1));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(RET_SUCCESS, i8deq_insert(&self->i8deq, 2, 3));
  ASSERT_EQ(4, i8deq_size(&self->i8deq));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(RET_FAILURE, i8deq_insert(&self->i8deq, 5, 5));
  ASSERT_EQ(RET_ERRNO, i8deq_nomem_insert(&self->i8deq_nomem, 0, 1));
  return CUTE_SUCCESS;
}

CUTEST(deq, emplace) {
  ASSERT_EQ(RET_SUCCESS,
    i8deq_emplace(&self->i8deq, 0, (i8_t[4]){4, 3, 2, 1}, 0)
  );
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS,
    i8deq_emplace(&self->i8deq, 0, (i8_t[4]){4, 3, 2, 1}, 1)
  );
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_emplace(&self->i8deq, 1, (i8_t[4]){4, 3, 2, 1}, 2)
  );
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_emplace(&self->i8deq, 0, (i8_t[4]){4, 3, 2, 1}, 3)
  );
  ASSERT_EQ(6, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_emplace(&self->i8deq, 3, (i8_t[4]){4, 3, 2, 1}, 4)
  );
  ASSERT_EQ(10, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 6));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 7));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 8));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 9));
  ASSERT_EQ(RET_ERRNO,
    i8deq_nomem_emplace(&self->i8deq_nomem, 0, (i8_t[4]){4, 3, 2, 1}, 1)
  );
  return CUTE_SUCCESS;
}

CUTEST(deq, push) {
  u8_t i, j;

  for (i = 0; i < 10; ++i) {
    ASSERT_EQ(RET_SUCCESS, i8deq_push(&self->i8deq, i));
    ASSERT_EQ(i + 1, i8deq_size(&self->i8deq));
    for (j = 0; j < i8deq_size(&self->i8deq); ++j) {
      ASSERT_EQ(j, i8deq_at(&self->i8deq, (u8_t) j));
    }
  }
  ASSERT_EQ(RET_ERRNO, i8deq_nomem_push(&self->i8deq_nomem, 0));
  return CUTE_SUCCESS;
}

CUTEST(deq, append) {
  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 0));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 1));
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 2));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 3));
  ASSERT_EQ(6, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(10, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 6));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 7));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 8));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 9));
  ASSERT_EQ(RET_ERRNO,
    i8deq_nomem_append(&self->i8deq_nomem, (i8_t[4]){4, 3, 2, 1}, 4)
  );
  return CUTE_SUCCESS;
}

CUTEST(deq, pop) {
  i8_t i;

  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(4, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(true, i8deq_pop(&self->i8deq, nil));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(true, i8deq_pop(&self->i8deq, &i));
  ASSERT_EQ(2, i);
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_pop(&self->i8deq, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(true, i8deq_pop(&self->i8deq, &i));
  ASSERT_EQ(4, i);
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(false, i8deq_pop(&self->i8deq, &i));
  return CUTE_SUCCESS;
}

CUTEST(deq, unshift) {
  u8_t i, j;
  i8_t k;

  for (i = 0; i < 10; ++i) {
    ASSERT_EQ(RET_SUCCESS, i8deq_unshift(&self->i8deq, i));
    ASSERT_EQ(i + 1, i8deq_size(&self->i8deq));
    for (j = 0, k = i; j < i8deq_size(&self->i8deq); ++j) {
      ASSERT_EQ(k--, i8deq_at(&self->i8deq, (u8_t) j));
    }
  }
  ASSERT_EQ(RET_ERRNO, i8deq_nomem_unshift(&self->i8deq_nomem, 0));
  return CUTE_SUCCESS;
}

CUTEST(deq, prepend) {
  ASSERT_EQ(RET_SUCCESS, i8deq_prepend(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 0));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(nil, self->i8deq.buf);
  ASSERT_EQ(RET_SUCCESS, i8deq_prepend(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 1));
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS, i8deq_prepend(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 2));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(RET_SUCCESS, i8deq_prepend(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 3));
  ASSERT_EQ(6, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(RET_SUCCESS, i8deq_prepend(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(10, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 5));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 6));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 7));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 8));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 9));
  ASSERT_EQ(RET_ERRNO,
    i8deq_nomem_prepend(&self->i8deq_nomem, (i8_t[4]){4, 3, 2, 1}, 4)
  );
  return CUTE_SUCCESS;
}

CUTEST(deq, shift) {
  i8_t i;

  ASSERT_EQ(RET_SUCCESS, i8deq_append(&self->i8deq, (i8_t[4]){4, 3, 2, 1}, 4));
  ASSERT_EQ(4, i8deq_size(&self->i8deq));
  ASSERT_EQ(4, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(true, i8deq_shift(&self->i8deq, nil));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(true, i8deq_shift(&self->i8deq, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_shift(&self->i8deq, &i));
  ASSERT_EQ(2, i);
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(true, i8deq_shift(&self->i8deq, &i));
  ASSERT_EQ(1, i);
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(false, i8deq_shift(&self->i8deq, &i));
  return CUTE_SUCCESS;
}

CUTEST(deq, remove) {
  i8_t i;

  ASSERT_EQ(false, i8deq_remove(&self->i8deq, 0, nil));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&self->i8deq, (i8_t[4]){0, 1, 2, 3}, 4)
  );
  ASSERT_EQ(false, i8deq_remove(&self->i8deq, 4, nil));
  ASSERT_EQ(true, i8deq_remove(&self->i8deq, 2, nil));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(true, i8deq_remove(&self->i8deq, 1, &i));
  ASSERT_EQ(1, i);
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_remove(&self->i8deq, 1, &i));
  ASSERT_EQ(3, i);
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(true, i8deq_remove(&self->i8deq, 0, &i));
  ASSERT_EQ(0, i);
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(false, i8deq_remove(&self->i8deq, 0, &i));
  return CUTE_SUCCESS;
}

CUTEST(deq, removen) {
  i8_t buf[2], *ptr;

  ptr = buf;
  ASSERT_EQ(false, i8deq_removen(&self->i8deq, 0, 0, nil));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&self->i8deq, (i8_t[6]){0, 1, 2, 3, 5, 6}, 6)
  );
  ASSERT_EQ(false, i8deq_removen(&self->i8deq, 6, 0, nil));
  ASSERT_EQ(true, i8deq_removen(&self->i8deq, 2, 2, nil));
  ASSERT_EQ(4, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(1, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(5, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(6, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(true, i8deq_removen(&self->i8deq, 1, 2, &ptr));
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(1, buf[0]);
  ASSERT_EQ(5, buf[1]);
  ASSERT_EQ(6, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_removen(&self->i8deq, 0, 1, &ptr));
  ASSERT_EQ(1, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, buf[0]);
  ASSERT_EQ(6, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(true, i8deq_removen(&self->i8deq, 0, 1, &ptr));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(6, buf[0]);
  ASSERT_EQ(false, i8deq_removen(&self->i8deq, 0, 1, &ptr));
  return CUTE_SUCCESS;
}

CUTEST(deq, erase) {
  ASSERT_EQ(0, i8deq_erase(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&self->i8deq, (i8_t[7]){1, 2, 1, 2, 3, 3, 2}, 7)
  );
  ASSERT_EQ(2, i8deq_erase(&self->i8deq, 1));
  ASSERT_EQ(5, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(3, i8deq_erase(&self->i8deq, 2));
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_erase(&self->i8deq, 3));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_erase(&self->i8deq, 3));
  return CUTE_SUCCESS;
}

CUTEST(deq, erasen) {
  ASSERT_EQ(0, i8deq_erasen(&self->i8deq, 0, 1));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&self->i8deq, (i8_t[7]){1, 2, 1, 2, 3, 3, 2}, 7)
  );
  ASSERT_EQ(0, i8deq_erasen(&self->i8deq, 1, 0));
  ASSERT_EQ(2, i8deq_erasen(&self->i8deq, 1, 3));
  ASSERT_EQ(5, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(2, i8deq_erasen(&self->i8deq, 2, 2));
  ASSERT_EQ(3, i8deq_size(&self->i8deq));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(1, i8deq_erasen(&self->i8deq, 2, 2));
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(2, i8deq_erasen(&self->i8deq, 3, 2));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(0, i8deq_erasen(&self->i8deq, 3, 1));
  return CUTE_SUCCESS;
}

CUTEST(deq, eraseonce) {
  ASSERT_EQ(false, i8deq_eraseonce(&self->i8deq, 0));
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&self->i8deq, (i8_t[7]){1, 2, 1, 2, 3, 3, 2}, 7)
  );
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 1));
  ASSERT_EQ(false, i8deq_eraseonce(&self->i8deq, 1));
  ASSERT_EQ(5, i8deq_size(&self->i8deq));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 2));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 3));
  ASSERT_EQ(2, i8deq_at(&self->i8deq, 4));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 2));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 2));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 2));
  ASSERT_EQ(false, i8deq_eraseonce(&self->i8deq, 2));
  ASSERT_EQ(2, i8deq_size(&self->i8deq));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 0));
  ASSERT_EQ(3, i8deq_at(&self->i8deq, 1));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 3));
  ASSERT_EQ(true, i8deq_eraseonce(&self->i8deq, 3));
  ASSERT_EQ(false, i8deq_eraseonce(&self->i8deq, 3));
  ASSERT_EQ(0, i8deq_size(&self->i8deq));
  ASSERT_EQ(false, i8deq_eraseonce(&self->i8deq, 3));
  return CUTE_SUCCESS;
}

CUTEST(deq, cpy) {
  i8deq_t src;

  i8deq_ctor(&src);
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&src, (i8_t[7]){1, 2, 1, 2, 3, 3, 2}, 7)
  );
  ASSERT_EQ(RET_SUCCESS, i8deq_cpy(&self->i8deq, &src));
  ASSERT_EQ(7, i8deq_size(&self->i8deq));
  ASSERT_EQ(i8deq_size(&src), i8deq_size(&self->i8deq));
  ASSERT_EQ(src.cap, self->i8deq.cap);
  ASSERT_NEQ(src.buf, self->i8deq.buf);
  return CUTE_SUCCESS;
}

CUTEST(deq, ncpy) {
  i8deq_t src;

  i8deq_ctor(&src);
  ASSERT_EQ(RET_SUCCESS,
    i8deq_append(&src, (i8_t[7]){1, 2, 1, 2, 3, 3, 2}, 7)
  );
  ASSERT_EQ(RET_SUCCESS, i8deq_ncpy(&self->i8deq, &src, 5));
  ASSERT_EQ(5, i8deq_size(&self->i8deq));
  ASSERT_NEQ(i8deq_size(&src), i8deq_size(&self->i8deq));
  ASSERT_EQ(src.cap, self->i8deq.cap);
  ASSERT_NEQ(src.buf, self->i8deq.buf);
  return CUTE_SUCCESS;
}

i32_t main(void) {
  CUTEST_DATA test;

  CUTEST_PASS(deq, ensure);
  CUTEST_PASS(deq, grow);
  CUTEST_PASS(deq, shrink);
  CUTEST_PASS(deq, trim);
  CUTEST_PASS(deq, insert);
  CUTEST_PASS(deq, emplace);
  CUTEST_PASS(deq, push);
  CUTEST_PASS(deq, append);
  CUTEST_PASS(deq, pop);
  CUTEST_PASS(deq, unshift);
  CUTEST_PASS(deq, prepend);
  CUTEST_PASS(deq, shift);
  CUTEST_PASS(deq, remove);
  CUTEST_PASS(deq, removen);
  CUTEST_PASS(deq, erase);
  CUTEST_PASS(deq, erasen);
  CUTEST_PASS(deq, eraseonce);
  CUTEST_PASS(deq, cpy);
  CUTEST_PASS(deq, ncpy);
  return EXIT_SUCCESS;
}
