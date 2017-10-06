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

#include "uds/map.h"

I8_MAP_DEFINE(test_i8map, u8_t, u8cmp)
U8_MAP_DEFINE(test_u8map, u8_t, u8cmp)
I16_MAP_DEFINE(test_i16map, u8_t, u8cmp)
U16_MAP_DEFINE(test_u16map, u8_t, u8cmp)
I32_MAP_DEFINE(test_i32map, u8_t, u8cmp)
U32_MAP_DEFINE(test_u32map, u8_t, u8cmp)
I64_MAP_DEFINE(test_i64map, u8_t, u8cmp)
U64_MAP_DEFINE(test_u64map, u8_t, u8cmp)
STR_MAP_DEFINE(test_strmap, u8_t, u8cmp)

CUTEST_DATA {
  test_i8map_t i8map;
  test_u8map_t u8map;
  test_i16map_t i16map;
  test_u16map_t u16map;
  test_i32map_t i32map;
  test_u32map_t u32map;
  test_i64map_t i64map;
  test_u64map_t u64map;
  test_strmap_t strmap;
};

CUTEST_SETUP {
  test_i8map_ctor(&self->i8map);
  test_u8map_ctor(&self->u8map);
  test_i16map_ctor(&self->i16map);
  test_u16map_ctor(&self->u16map);
  test_i32map_ctor(&self->i32map);
  test_u32map_ctor(&self->u32map);
  test_i64map_ctor(&self->i64map);
  test_u64map_ctor(&self->u64map);
  test_strmap_ctor(&self->strmap);
}

CUTEST_TEARDOWN {
  test_i8map_ctor(&self->i8map);
  test_u8map_ctor(&self->u8map);
  test_i16map_dtor(&self->i16map);
  test_u16map_dtor(&self->u16map);
  test_i32map_dtor(&self->i32map);
  test_u32map_dtor(&self->u32map);
  test_i64map_dtor(&self->i64map);
  test_u64map_dtor(&self->u64map);
  test_strmap_dtor(&self->strmap);
}

CUTEST(map, i8) {
  u32_t out;
  i8_t i;

  for (i = 0; i < I8_MAX; ++i) {
    switch (test_i8map_put(&self->i8map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_i8map_put(&self->i8map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i8map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i8map.cap);
  for (i = 0; i < I8_MAX; ++i) {
    ASSERT(test_i8map_get(&self->i8map, i, &out));
    ASSERT(test_i8map_del(&self->i8map, out));
  }
  ASSERT_EQ(0, self->i8map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i8map.cap);
  test_i8map_clear(&self->i8map);
  return CUTE_SUCCESS;
}

CUTEST(map, u8) {
  u32_t out;
  u8_t i;

  for (i = 0; i < U8_MAX; ++i) {
    switch (test_u8map_put(&self->u8map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_u8map_put(&self->u8map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u8map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u8map.cap);
  for (i = 0; i < U8_MAX; ++i) {
    ASSERT(test_u8map_get(&self->u8map, i, &out));
    ASSERT(test_u8map_del(&self->u8map, out));
  }
  ASSERT_EQ(0, self->u8map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u8map.cap);
  test_u8map_clear(&self->u8map);
  return CUTE_SUCCESS;
}

CUTEST(map, i16) {
  u32_t out;
  i16_t i;

  for (i = 0; i < I16_MAX; ++i) {
    switch (test_i16map_put(&self->i16map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_i16map_put(&self->i16map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i16map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i16map.cap);
  for (i = 0; i < I16_MAX; ++i) {
    ASSERT(test_i16map_get(&self->i16map, i, &out));
    ASSERT(test_i16map_del(&self->i16map, out));
  }
  ASSERT_EQ(0, self->i16map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i16map.cap);
  test_i16map_clear(&self->i16map);
  return CUTE_SUCCESS;
}

CUTEST(map, u16) {
  u32_t out;
  u16_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (test_u16map_put(&self->u16map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_u16map_put(&self->u16map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u16map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u16map.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(test_u16map_get(&self->u16map, i, &out));
    ASSERT(test_u16map_del(&self->u16map, out));
  }
  ASSERT_EQ(0, self->u16map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u16map.cap);
  test_u16map_clear(&self->u16map);
  return CUTE_SUCCESS;
}

CUTEST(map, i32) {
  u32_t out, i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (test_i32map_put(&self->i32map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_i32map_put(&self->i32map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i32map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i32map.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(test_i32map_get(&self->i32map, i, &out));
    ASSERT(test_i32map_del(&self->i32map, out));
  }
  ASSERT_EQ(0, self->i32map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i32map.cap);
  test_i32map_clear(&self->i32map);
  return CUTE_SUCCESS;
}

CUTEST(map, u32) {
  u32_t out;
  u32_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (test_u32map_put(&self->u32map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_u32map_put(&self->u32map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u32map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u32map.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(test_u32map_get(&self->u32map, i, &out));
    ASSERT(test_u32map_del(&self->u32map, out));
  }
  ASSERT_EQ(0, self->u32map.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u32map.cap);
  test_u32map_clear(&self->u32map);
  return CUTE_SUCCESS;
}

CUTEST(map, i64) {
  u32_t out;
  i64_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (test_i64map_put(&self->i64map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_i64map_put(&self->i64map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i64map.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->i64map.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(test_i64map_get(&self->i64map, i, &out));
    ASSERT(test_i64map_del(&self->i64map, out));
  }
  ASSERT_EQ(0, self->i64map.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->i64map.cap);
  test_i64map_clear(&self->i64map);
  return CUTE_SUCCESS;
}

CUTEST(map, u64) {
  u32_t out;
  u64_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (test_u64map_put(&self->u64map, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_u64map_put(&self->u64map, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u64map.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->u64map.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(test_u64map_get(&self->u64map, i, &out));
    ASSERT(test_u64map_del(&self->u64map, out));
  }
  ASSERT_EQ(0, self->u64map.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->u64map.cap);
  test_u64map_clear(&self->u64map);
  return CUTE_SUCCESS;
}

CUTEST(map, str) {
  u32_t out;
  __const char_t **str;
  __const char_t *strs[51] = {
    "2lsDCacn6PYP7XbIWBDj",
    "rUPoh4tmafEbIxevHCSk",
    "VKaP4ZFpkOsedOYzvbQr",
    "KD30gGmnSwTNCOCUsHPG",
    "iLgdLRLMjAWUebIGUIRB",
    "bzQRVJaW7Pbdaa0uXN7F",
    "bDGPXbKV1eORSnrUcKpY",
    "nnvxJ5caqTswn67TUR2n",
    "L8rrOQ176El3CdJPy5Xq",
    "OtKDpfKFuN2oRG239KvK",
    "chvuzpvz9tyV8wwPPu9X",
    "Uy3cvIHR16KJWqPL2uNr",
    "Lbj4KPMwMJJgIsfyCJAt",
    "UcOc2zpGTZKthmoxAr1z",
    "ADTQo6o3axlrGRlK08aX",
    "iBVeBysuO0g65PSa2Z9v",
    "IIi7c7TL5NMZYJqXAYc3",
    "dtjIH6Us5snbvkotQRVE",
    "Ch2SevYxj7MMtfD0C7cY",
    "CIwtnvrKqbwGWrjeIJI0",
    "aykAPp72oqjOb5Qu6e6E",
    "7s85g9xBseiKRAm5xfUe",
    "HligRMrPQBCsv12ejGsJ",
    "uEFkV2Mz6FtscTaQpYEl",
    "HjcpWpxj6nMPnN6ut9Me",
    "1j9QI5omSEXcTlj7XCot",
    "C4TAFjU1ZySISDOtOmlG",
    "R7yaBBOOO8eeiLLGykJz",
    "6ycVA2aTYzDIPo7KYAkG",
    "mHD0ZGm9iSYF4jbeyWKy",
    "4CgUKokOaW87x6tymFjv",
    "Zpjyu8izAmpfCnM2bQar",
    "5GtFnjgSr7jcVcp5GTbt",
    "qPfra6DHtSldxer95dax",
    "YLBqp8nhM5WlIf5jzjzL",
    "2YHlBUCemE0lCCdroaDL",
    "ZsK7NTxtmewsJn7gRdov",
    "LqPefw767IQGWVriw1zt",
    "zfPP10z2ldi2WaM66A94",
    "d6J9xts1Rh16UCnTLiKC",
    "cTRi56evRxZDQOXmPefY",
    "lRCyN67Fmr0FShxeFdL5",
    "V6gmc0S2IK8KYVgwXR8t",
    "w70GkoKHjSF67ETpRoWR",
    "GjL81xpZVwo0s4RtuVGU",
    "tO8aGuNGVhxUnRjNc17I",
    "QUqdpKDmR7pawzqWBd3i",
    "DQC6ynjuqO97RIKVIEVc",
    "ikJah1IgglY7Fz2F9t8A",
    "NCUZIpgWsWU4w9u80KUq",
    nil
  };

  str = strs;
  while (*str) {
    switch (test_strmap_put(&self->strmap, *str, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (test_strmap_put(&self->strmap, *str, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
    ++str;
  }
  ASSERT_EQ(50, self->strmap.len);
  str = strs;
  while (*str) {
    ASSERT(test_strmap_get(&self->strmap, *str, &out));
    ASSERT(test_strmap_del(&self->strmap, out));
    ++str;
  }
  ASSERT_EQ(0, self->u64map.len);
  test_strmap_clear(&self->strmap);
  return CUTE_SUCCESS;
}

i32_t main(void) {
  CUTEST_DATA test;

  CUTEST_PASS(map, i8);
  CUTEST_PASS(map, u8);
  CUTEST_PASS(map, i16);
  CUTEST_PASS(map, u16);
  CUTEST_PASS(map, i32);
  CUTEST_PASS(map, u32);
  CUTEST_PASS(map, i64);
  CUTEST_PASS(map, u64);
  CUTEST_PASS(map, str);
  return EXIT_SUCCESS;
}
