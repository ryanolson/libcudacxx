//===----------------------------------------------------------------------===//
//
// Part of libcu++, the C++ Standard Library for your entire system,
// under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <cassert>
#include <cuda/memory_resource>
#include <cuda/std/type_traits>
#include <cuda/stream_view>
#include <cuda/std/cstddef>

template <cuda::memory_kind Kind> 
constexpr bool test_memory_kind() {
  using mr = cuda::memory_resource<Kind>;
  return mr::kind == Kind;
}

template <cuda::memory_kind Kind, std::size_t Alignment>
constexpr bool test_alignment() {
  using mr = cuda::memory_resource<Kind>;
  return mr::default_alignment == Alignment;
}

struct custom_context {};

int main(int argc, char **argv) {

#ifndef __CUDA_ARCH__
  using cuda::memory_kind;
  static_assert(test_memory_kind<memory_kind::host>(), "");
  static_assert(test_memory_kind<memory_kind::device>(), "");
  static_assert(test_memory_kind<memory_kind::unified>(), "");
  static_assert(test_memory_kind<memory_kind::pinned>(), "");

  static_assert(test_alignment<memory_kind::host, alignof(cuda::std::max_align_t)>(), "");
  static_assert(test_alignment<memory_kind::device, alignof(cuda::std::max_align_t)>(), "");
  static_assert(test_alignment<memory_kind::unified, alignof(cuda::std::max_align_t)>(), "");
  static_assert(test_alignment<memory_kind::pinned, alignof(cuda::std::max_align_t)>(), "");

  using default_context_mr = cuda::memory_resource<memory_kind::host>;
  static_assert( cuda::std::is_same<default_context_mr::context, cuda::any_context>::value, "");
  static_assert(default_context_mr::default_alignment == alignof(cuda::std::max_align_t), "");

  using custom_context_mr = cuda::memory_resource<cuda::memory_kind::host, custom_context>;
  static_assert(cuda::std::is_same<custom_context_mr::context, custom_context>::value, "");

#endif

  return 0;
}
