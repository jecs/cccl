//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// template<class T>
//   inline constexpr bool enable_borrowed_range<owning_view<T>> = enable_borrowed_range<T>;

#include <ranges>

#include "test_range.h"

static_assert( std::ranges::borrowed_range<std::ranges::owning_view<BorrowedView>>);
#if _LIBCUDACXX_HAS_RANGES
static_assert(!std::ranges::borrowed_range<std::ranges::owning_view<NonBorrowedView>>);
#endif // _LIBCUDACXX_HAS_RANGES

int main(int, char**)
{
  return 0;
}