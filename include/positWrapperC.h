#pragma once

#include <linux/stat.h>
#include <stdint.h>
#ifdef __cplusplus
// export a C interface if used by C++ source code
extern "C" {
#endif

#define DEFINE_POSIT(bits, es_val, op_name)                                    \
  uint##bits##_t posit##bits##es##es_val##_##op_name(uint##bits##_t a,         \
                                                     uint##bits##_t b);

#define DEFINE_POSIT_BOOL(bits, es_val, op_name)                               \
  bool posit##bits##es##es_val##_##op_name(uint##bits##_t a, uint##bits##_t b);

#define DEFINE_POSIT_SELECT(bits, es_val)                                      \
  uint##bits##_t posit##bits##es##es_val##_select(                             \
      bool condition, uint##bits##_t true_, uint##bits##_t false_);

#define DEFINE_POSIT_UNARY_MATH(bits, es_val, op_name)                         \
  uint##bits##_t posit##bits##es##es_val##_##op_name(uint##bits##_t a);

// signed integer temperary just i32
#define DEFINE_POSIT_SITOFP(bits, es_val)                                      \
  uint##bits##_t posit##bits##es##es_val##_sitofp(int a);

#define DEFINE_NBITS_ESVAL(bits, es_val)                                       \
  DEFINE_POSIT(bits, es_val, add)                                              \
  DEFINE_POSIT(bits, es_val, sub)                                              \
  DEFINE_POSIT(bits, es_val, mul)                                              \
  DEFINE_POSIT(bits, es_val, div)                                              \
  DEFINE_POSIT_BOOL(bits, es_val, oeq)                                         \
  DEFINE_POSIT_BOOL(bits, es_val, ogt)                                         \
  DEFINE_POSIT_BOOL(bits, es_val, oge)                                         \
  DEFINE_POSIT_BOOL(bits, es_val, olt)                                         \
  DEFINE_POSIT_BOOL(bits, es_val, ole)                                         \
  DEFINE_POSIT_BOOL(bits, es_val, one)                                         \
  DEFINE_POSIT_SELECT(bits, es_val)                                            \
  DEFINE_POSIT_UNARY_MATH(bits, es_val, sqrt)                                  \
  DEFINE_POSIT_UNARY_MATH(bits, es_val, exp)                                   \
  DEFINE_POSIT_UNARY_MATH(bits, es_val, tanh)                                  \
  DEFINE_POSIT_UNARY_MATH(bits, es_val, erf)                                   \
  DEFINE_POSIT_SITOFP(bits, es_val)

DEFINE_NBITS_ESVAL(8, 0)
DEFINE_NBITS_ESVAL(8, 1)
DEFINE_NBITS_ESVAL(8, 2)
DEFINE_NBITS_ESVAL(8, 3)
DEFINE_NBITS_ESVAL(16, 0)
DEFINE_NBITS_ESVAL(16, 1)
DEFINE_NBITS_ESVAL(16, 2)
DEFINE_NBITS_ESVAL(16, 3)
DEFINE_NBITS_ESVAL(32, 0)
DEFINE_NBITS_ESVAL(32, 1)
DEFINE_NBITS_ESVAL(32, 2)
DEFINE_NBITS_ESVAL(32, 3)

#ifdef __cplusplus
}
#endif

// C++ function prototypes

#include <cstddef>
#include <universal/number/posit/posit.hpp>

template <size_t nbits, typename uType>
void wrap(uType a, sw::universal::bitblock<nbits> &raw) {
  // NaR handling
  // if (((uType) 1 << (nbits - 1)) == a) {
  //   raw.reset();
  //   raw.set(nbits - 1, true);
  //   return;
  // }

  for (size_t i = 0; i < nbits; i++) {
    raw[i] = a & 1;
    a >>= 1;
  }
  // if negative, two's complement except the sign bit
  if (raw[nbits - 1]) {
    sw::universal::bitblock<nbits - 1> remain;
    for (size_t i = 0; i < nbits - 1; i++) {
      remain[i] = raw[i];
    }
    remain = sw::universal::internal::twos_complement(remain);
    for (size_t i = 0; i < nbits - 1; i++) {
      raw[i] = remain[i];
    }
  }
}

template <size_t nbits, typename uType>
void unwrap(sw::universal::bitblock<nbits> &raw, uType &a) {
  // NaR handling
  // if (raw[nbits - 1]) {
  //   a = ((uType) 1 << (nbits - 1));
  //   return;
  // }

  if (raw[nbits - 1]) {
    sw::universal::bitblock<nbits - 1> remain;
    for (size_t i = 0; i < nbits - 1; i++) {
      remain[i] = raw[i];
    }
    remain = sw::universal::internal::twos_complement(remain);
    for (size_t i = 0; i < nbits - 1; i++) {
      raw[i] = remain[i];
    }
  }

  a = 0;
  for (int i = (int)nbits - 1; i >= 0; i--) {
    a <<= 1;
    a |= raw[i];
  }
}

// get posit from uType
template <size_t nbits, size_t es, typename uType>
sw::universal::posit<nbits, es> get_posit(uType a) {
  sw::universal::bitblock<nbits> b_a;
  wrap<nbits>(a, b_a);

  sw::universal::posit<nbits, es> pa;
  pa.setBitblock(b_a);
  return pa;
}

// get uType from posit
template <size_t nbits, size_t es, typename uType>
uType get_uType(sw::universal::posit<nbits, es> pa) {
  sw::universal::bitblock<nbits> b_res;
  uType res = 0;
  b_res = pa.get();
  unwrap<nbits>(b_res, res);
  return res;
}

template <size_t n_bits, size_t es, typename uType>
double getDouble(uType rawBit) {
  sw::universal::posit<n_bits, es> p = get_posit<n_bits, es>(rawBit);
  return static_cast<double>(p);
}

template <size_t n_bits, size_t es, typename uType> uType getRawBit(double d) {
  sw::universal::posit<n_bits, es> p(d);
  return get_uType<n_bits, es, uType>(p);
}