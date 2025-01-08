#include "positWrapperC.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

namespace py = pybind11;

template <size_t n_bits, size_t es, typename uType>
void bind_posit_functions(py::module_ &m, const std::string &suffix) {
  // This return f32 in python interface
  m.def(("getDouble_" + suffix).c_str(),
        [](uType rawBit) { return getDouble<n_bits, es, uType>(rawBit); },
        py::arg("rawBit"));

  // This return i32 in python interface
  m.def(("getRawBit_" + suffix).c_str(),
        [](double d) { return getRawBit<n_bits, es, uType>(d); }, py::arg("d"));

  m.def(("getDoubleArray_" + suffix).c_str(),
        [](py::array_t<uType> rawBits) -> py::array {
          py::buffer_info buf_info = rawBits.request();
          auto *ptr = static_cast<uType *>(buf_info.ptr);

          std::vector<py::ssize_t> shape(buf_info.shape);
          py::ssize_t total_size = 1;
          for (auto dim : shape) {
            total_size *= dim;
          }

          py::array_t<double> result(buf_info.shape);
          auto *result_ptr = static_cast<double *>(result.request().ptr);

          for (py::ssize_t i = 0; i < total_size; ++i) {
            result_ptr[i] = getDouble<n_bits, es, uType>(ptr[i]);
          }

          return result;
        },
        py::arg("rawBits"));
        
  m.def(("getRawBitArray_" + suffix).c_str(),
        [](py::array_t<double> inputArray) -> py::array_t<uType> {
          py::buffer_info buf_info = inputArray.request();
          auto *ptr =
              static_cast<double *>(buf_info.ptr);

          std::vector<py::ssize_t> shape(buf_info.shape);
          py::ssize_t total_size = 1;
          for (auto dim : shape) {
            total_size *= dim;
          }

          py::array_t<uType> result(buf_info.shape);
          auto *result_ptr = static_cast<uType *>(result.request().ptr);

          for (py::ssize_t i = 0; i < total_size; ++i) {
            result_ptr[i] = getRawBit<n_bits, es, uType>(ptr[i]);
          }

          return result;
        },
        py::arg("inputArray"));
}

// libpositWrapperPy matches the name of the .so file
PYBIND11_MODULE(libpositWrapperPy, m) {
  bind_posit_functions<8, 0, uint8_t>(m, "8_0");
  bind_posit_functions<8, 1, uint8_t>(m, "8_1");
  bind_posit_functions<8, 2, uint8_t>(m, "8_2");
  bind_posit_functions<8, 3, uint8_t>(m, "8_3");

  bind_posit_functions<16, 0, uint16_t>(m, "16_0");
  bind_posit_functions<16, 1, uint16_t>(m, "16_1");
  bind_posit_functions<16, 2, uint16_t>(m, "16_2");
  bind_posit_functions<16, 3, uint16_t>(m, "16_3");

  bind_posit_functions<32, 0, uint32_t>(m, "32_0");
  bind_posit_functions<32, 1, uint32_t>(m, "32_1");
  bind_posit_functions<32, 2, uint32_t>(m, "32_2");
  bind_posit_functions<32, 3, uint32_t>(m, "32_3");

  bind_posit_functions<64, 0, uint64_t>(m, "64_0");
  bind_posit_functions<64, 1, uint64_t>(m, "64_1");
  bind_posit_functions<64, 2, uint64_t>(m, "64_2");
  bind_posit_functions<64, 3, uint64_t>(m, "64_3");
}
