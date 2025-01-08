#include <positWrapperC.h>
#include <universal/number/posit/posit.hpp>

// uint8_t posit8es0_add(uint8_t a, uint8_t b) {
//   auto pa = get_posit<8, 0>(a);
//   auto pb = get_posit<8, 0>(b);

//   auto pc = pa + pb;

//   uint8_t res = get_uType<8, 0, uint8_t>(pc);

//   return res;
// }

// uint8_t posit8es0_select(bool condition, uint8_t true_, uint8_t false_) {
//   return condition ? true_ : false_;
// }

// bool posit8es0_oeq(uint8_t a, uint8_t b) {
//   auto pa = get_posit<8, 0>(a);
//   auto pb = get_posit<8, 0>(b);

//   return pa == pb;
// }

#define SOURCE_POSIT_BASIC(bits, es_val, op_name, op_symbol)                   \
  uint##bits##_t posit##bits##es##es_val##_##op_name(uint##bits##_t a,         \
                                                     uint##bits##_t b) {       \
    auto pa = get_posit<bits, es_val>(a);                                      \
    auto pb = get_posit<bits, es_val>(b);                                      \
    auto pc = pa op_symbol pb;                                                 \
    uint##bits##_t res = get_uType<bits, es_val, uint##bits##_t>(pc);          \
    return res;                                                                \
  }

#define SOURCE_POSIT_CMP(bits, es_val, op_name, op_symbol)                     \
  bool posit##bits##es##es_val##_##op_name(uint##bits##_t a,                   \
                                           uint##bits##_t b) {                 \
    auto pa = get_posit<bits, es_val>(a);                                      \
    auto pb = get_posit<bits, es_val>(b);                                      \
    return pa op_symbol pb;                                                    \
  }

#define SOURCE_POSIT_SELECT(bits, es_val)                                      \
  uint##bits##_t posit##bits##es##es_val##_select(                             \
      bool condition, uint##bits##_t true_, uint##bits##_t false_) {           \
    return condition ? true_ : false_;                                         \
  }

#define SOURCE_POSIT_UNARY_MATH(bits, es_val, op_name, op_symbol)              \
  uint##bits##_t posit##bits##es##es_val##_##op_name(uint##bits##_t a) {       \
    auto pa = get_posit<bits, es_val>(a);                                      \
    auto pc = op_symbol<bits, es_val>(pa);                                     \
    uint##bits##_t res = get_uType<bits, es_val, uint##bits##_t>(pc);          \
    return res;                                                                \
  }

#define SOURCE_POSIT_SITOFP(bits, es_val)                                      \
  uint##bits##_t posit##bits##es##es_val##_sitofp(int a) {                     \
    double da = static_cast<double>(a);                                        \
    auto pa = sw::universal::posit<bits, es_val>(da);                          \
    uint##bits##_t res = get_uType<bits, es_val, uint##bits##_t>(pa);          \
    return res;                                                                \
}

#define SOURCE_NBITS_ESVAL(bits, es_val)                                       \
  SOURCE_POSIT_BASIC(bits, es_val, add, +)                                     \
  SOURCE_POSIT_BASIC(bits, es_val, sub, -)                                     \
  SOURCE_POSIT_BASIC(bits, es_val, mul, *)                                     \
  SOURCE_POSIT_BASIC(bits, es_val, div, /)                                     \
  SOURCE_POSIT_CMP(bits, es_val, oeq, ==)                                      \
  SOURCE_POSIT_CMP(bits, es_val, ogt, >)                                       \
  SOURCE_POSIT_CMP(bits, es_val, oge, >=)                                      \
  SOURCE_POSIT_CMP(bits, es_val, olt, <)                                       \
  SOURCE_POSIT_CMP(bits, es_val, ole, <=)                                      \
  SOURCE_POSIT_CMP(bits, es_val, one, !=)                                      \
  SOURCE_POSIT_SELECT(bits, es_val)                                            \
  SOURCE_POSIT_UNARY_MATH(bits, es_val, sqrt, sqrt)                            \
  SOURCE_POSIT_UNARY_MATH(bits, es_val, exp, exp)                              \
  SOURCE_POSIT_UNARY_MATH(bits, es_val, tanh, tanh)                            \
  SOURCE_POSIT_UNARY_MATH(bits, es_val, erf, erf)                              \
  SOURCE_POSIT_SITOFP(bits, es_val)

SOURCE_NBITS_ESVAL(8, 0)
SOURCE_NBITS_ESVAL(8, 1)
SOURCE_NBITS_ESVAL(8, 2)
SOURCE_NBITS_ESVAL(8, 3)
SOURCE_NBITS_ESVAL(16, 0)
SOURCE_NBITS_ESVAL(16, 1)
SOURCE_NBITS_ESVAL(16, 2)
SOURCE_NBITS_ESVAL(16, 3)
SOURCE_NBITS_ESVAL(32, 0)
SOURCE_NBITS_ESVAL(32, 1)
SOURCE_NBITS_ESVAL(32, 2)
SOURCE_NBITS_ESVAL(32, 3)