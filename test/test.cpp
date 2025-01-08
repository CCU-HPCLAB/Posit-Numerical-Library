#include <cstdlib>
#include <ctime>
#include <iostream>
#include <positWrapperC.h>

template <size_t nbits, size_t es, typename uType>
void testBinaryCFunction(int lowerBound, int upperBound, int step,
                         uType (*positFunc)(uType, uType),
                         double (*doubleFunc)(double, double)) {
  if (lowerBound < 0 or upperBound < 0 or step < 0) {
    std::cerr << "Invalid input" << std::endl;
    return;
  }

  unsigned passed = 0, failed = 0;

  for(int i = lowerBound; i <= upperBound; i += step) {
    for(int j = lowerBound; j <= upperBound; j += step) {
      uType positResultRaw = positFunc(i, j);

      auto doubleValue1 = getDouble<nbits, es>(i);
      auto doubleValue2 = getDouble<nbits, es>(j);
      double doubleResult = doubleFunc(doubleValue1, doubleValue2);
      uType doubleResultRaw = get_uType<nbits, es, uType>(doubleResult);

      if (positResultRaw != doubleResultRaw) {
        failed++;
        std::cerr
            << "FAIL: i = " << i << " j = " << j
            << " positResultRaw = " << positResultRaw
            << " doubleResultRaw = " << doubleResultRaw
            << " doubleValue1 = " << doubleValue1
            << " doubleValue2 = " << doubleValue2
            << " doubleResult = " << doubleResult << std::endl;
      } else {
        passed++;
      }
    }
  }

  std::cout << "Passed: " << passed << " Failed: " << failed << std::endl;
}

double add(double a, double b) {
  return a + b;
}
double subtract(double a, double b) {
  return a - b;
}
double multiply(double a, double b) {
  return a * b;
}
double divide(double a, double b) {
  return a / b;
}

int main() {
  std::cout << "Testing posit8es0" << std::endl;
  testBinaryCFunction<8, 0, uint8_t>(0, 255, 1, posit8es0_add, add);
  testBinaryCFunction<8, 0, uint8_t>(0, 255, 1, posit8es0_sub, subtract);
  testBinaryCFunction<8, 0, uint8_t>(0, 255, 1, posit8es0_mul, multiply);
  testBinaryCFunction<8, 0, uint8_t>(0, 255, 1, posit8es0_div, divide);

  int passed = 0, failed = 0;
  int sample = 256;
  for (int i = 0; i < sample; i++) {
    // a is a random integer
    int8_t a = rand() % 256;
    uint8_t b = posit8es0_sitofp(a);

    double da = static_cast<double>(a);
    sw::universal::posit<8, 0> pb(da);
    uint8_t b_ref = get_uType<8, 0, uint8_t>(pb);

    if (b != b_ref) {
      failed++;
      std::cerr << "FAIL: a = " << int(a) << " b = " << int(b)
                << " b_ref = " << int(b_ref) << std::endl;
    } else {
      passed++;
    }
  }
  std::cout << "Passed " << passed << " tests\n";
  std::cout << "Failed " << failed << " tests\n";
}