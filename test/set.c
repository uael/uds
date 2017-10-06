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

#include "uds/set.h"

CUTEST_DATA {
  i8set_t i8set;
  u8set_t u8set;
  i16set_t i16set;
  u16set_t u16set;
  i32set_t i32set;
  u32set_t u32set;
  i64set_t i64set;
  u64set_t u64set;
  strset_t strset;
};

CUTEST_SETUP {
  i8set_ctor(&self->i8set);
  u8set_ctor(&self->u8set);
  i16set_ctor(&self->i16set);
  u16set_ctor(&self->u16set);
  i32set_ctor(&self->i32set);
  u32set_ctor(&self->u32set);
  i64set_ctor(&self->i64set);
  u64set_ctor(&self->u64set);
  strset_ctor(&self->strset);
}

CUTEST_TEARDOWN {
  i8set_ctor(&self->i8set);
  u8set_ctor(&self->u8set);
  i16set_dtor(&self->i16set);
  u16set_dtor(&self->u16set);
  i32set_dtor(&self->i32set);
  u32set_dtor(&self->u32set);
  i64set_dtor(&self->i64set);
  u64set_dtor(&self->u64set);
  strset_dtor(&self->strset);
}

CUTEST(set, i8) {
  u32_t out;
  i8_t i;

  for (i = 0; i < I8_MAX; ++i) {
    switch (i8set_put(&self->i8set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (i8set_put(&self->i8set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i8set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i8set.cap);
  for (i = 0; i < I8_MAX; ++i) {
    ASSERT(i8set_get(&self->i8set, i, &out));
    ASSERT(i8set_del(&self->i8set, out));
  }
  ASSERT_EQ(0, self->i8set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i8set.cap);
  i8set_clear(&self->i8set);
  return CUTE_SUCCESS;
}

CUTEST(set, u8) {
  u32_t out;
  u8_t i;

  for (i = 0; i < U8_MAX; ++i) {
    switch (u8set_put(&self->u8set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (u8set_put(&self->u8set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u8set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u8set.cap);
  for (i = 0; i < U8_MAX; ++i) {
    ASSERT(u8set_get(&self->u8set, i, &out));
    ASSERT(u8set_del(&self->u8set, out));
  }
  ASSERT_EQ(0, self->u8set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u8set.cap);
  u8set_clear(&self->u8set);
  return CUTE_SUCCESS;
}

CUTEST(set, i16) {
  u32_t out;
  i16_t i;

  for (i = 0; i < I16_MAX; ++i) {
    switch (i16set_put(&self->i16set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (i16set_put(&self->i16set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i16set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i16set.cap);
  for (i = 0; i < I16_MAX; ++i) {
    ASSERT(i16set_get(&self->i16set, i, &out));
    ASSERT(i16set_del(&self->i16set, out));
  }
  ASSERT_EQ(0, self->i16set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i16set.cap);
  i16set_clear(&self->i16set);
  return CUTE_SUCCESS;
}

CUTEST(set, u16) {
  u32_t out;
  u16_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (u16set_put(&self->u16set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (u16set_put(&self->u16set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u16set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u16set.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(u16set_get(&self->u16set, i, &out));
    ASSERT(u16set_del(&self->u16set, out));
  }
  ASSERT_EQ(0, self->u16set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u16set.cap);
  u16set_clear(&self->u16set);
  return CUTE_SUCCESS;
}

CUTEST(set, i32) {
  u32_t out;
  u32_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (i32set_put(&self->i32set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (i32set_put(&self->i32set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i32set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i32set.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(i32set_get(&self->i32set, i, &out));
    ASSERT(i32set_del(&self->i32set, out));
  }
  ASSERT_EQ(0, self->i32set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->i32set.cap);
  i32set_clear(&self->i32set);
  return CUTE_SUCCESS;
}

CUTEST(set, u32) {
  u32_t out;
  u32_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (u32set_put(&self->u32set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (u32set_put(&self->u32set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u32set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u32set.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(u32set_get(&self->u32set, i, &out));
    ASSERT(u32set_del(&self->u32set, out));
  }
  ASSERT_EQ(0, self->u32set.len);
  ASSERT_EQ(pow2_next32(i + 2), self->u32set.cap);
  u32set_clear(&self->u32set);
  return CUTE_SUCCESS;
}

CUTEST(set, i64) {
  u32_t out;
  i64_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (i64set_put(&self->i64set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (i64set_put(&self->i64set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->i64set.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->i64set.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(i64set_get(&self->i64set, i, &out));
    ASSERT(i64set_del(&self->i64set, out));
  }
  ASSERT_EQ(0, self->i64set.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->i64set.cap);
  i64set_clear(&self->i64set);
  return CUTE_SUCCESS;
}

CUTEST(set, u64) {
  u32_t out;
  u64_t i;

  for (i = 0; i < U16_MAX; ++i) {
    switch (u64set_put(&self->u64set, i, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (u64set_put(&self->u64set, i, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
  }
  ASSERT_EQ(i, self->u64set.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->u64set.cap);
  for (i = 0; i < U16_MAX; ++i) {
    ASSERT(u64set_get(&self->u64set, i, &out));
    ASSERT(u64set_del(&self->u64set, out));
  }
  ASSERT_EQ(0, self->u64set.len);
  ASSERT_EQ(pow2_next32((u32_t) i + 2), self->u64set.cap);
  u64set_clear(&self->u64set);
  return CUTE_SUCCESS;
}

CUTEST(set, str) {
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
    switch (strset_put(&self->strset, *str, &out)) {
      case RET_SUCCESS:
        break;
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        FAIL("populated");
    }
    switch (strset_put(&self->strset, *str, &out)) {
      case RET_SUCCESS:
        FAIL("must be populated");
      case RET_ERRNO:
        FAIL("allocation failure");
      case RET_FAILURE:
        break;
    }
    ++str;
  }
  ASSERT_EQ(50, self->strset.len);
  str = strs;
  while (*str) {
    ASSERT(strset_get(&self->strset, *str, &out));
    ASSERT(strset_del(&self->strset, out));
    ++str;
  }
  ASSERT_EQ(0, self->u64set.len);
  strset_clear(&self->strset);
  return CUTE_SUCCESS;
}

i32_t main(void) {
  CUTEST_DATA test;

  CUTEST_PASS(set, i8);
  CUTEST_PASS(set, u8);
  CUTEST_PASS(set, i16);
  CUTEST_PASS(set, u16);
  CUTEST_PASS(set, i32);
  CUTEST_PASS(set, u32);
  CUTEST_PASS(set, i64);
  CUTEST_PASS(set, u64);
  CUTEST_PASS(set, str);
  return EXIT_SUCCESS;
}
