//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <cuda/std/array>

// implicitly generated array constructors / assignment operators

#include <cuda/std/array>
#include <cuda/std/type_traits>
#include <cuda/std/cassert>
#include "test_macros.h"

// cuda::std::array is explicitly allowed to be initialized with A a = { init-list };.
// Disable the missing braces warning for this reason.
#include "disable_missing_braces_warning.h"

struct NoDefault {
  __host__ __device__ NoDefault(int) {}
};

int main(int, char**) {
  {
    typedef double T;
    typedef cuda::std::array<T, 3> C;
    C c = {1.1, 2.2, 3.3};
    C c2 = c;
    c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(cuda::std::is_copy_assignable<C>::value, "");
  }
  {
    typedef double T;
    typedef cuda::std::array<const T, 3> C;
    C c = {1.1, 2.2, 3.3};
    C c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(!cuda::std::is_copy_assignable<C>::value, "");
  }
  {
    typedef double T;
    typedef cuda::std::array<T, 0> C;
    C c = {};
    C c2 = c;
    c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(cuda::std::is_copy_assignable<C>::value, "");
  }
  {
    // const arrays of size 0 should disable the implicit copy assignment operator.
    typedef double T;
    typedef cuda::std::array<const T, 0> C;
    C c = {{}};
    C c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(!cuda::std::is_copy_assignable<C>::value, "");
  }
  {
    typedef NoDefault T;
    typedef cuda::std::array<T, 0> C;
    C c = {};
    C c2 = c;
    c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(cuda::std::is_copy_assignable<C>::value, "");
  }
  {
    typedef NoDefault T;
    typedef cuda::std::array<const T, 0> C;
    C c = {{}};
    C c2 = c;
    unused(c2);
    static_assert(cuda::std::is_copy_constructible<C>::value, "");
    static_assert(!cuda::std::is_copy_assignable<C>::value, "");
  }


  return 0;
}
