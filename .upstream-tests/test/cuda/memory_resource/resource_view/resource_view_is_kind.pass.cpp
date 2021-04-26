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
#include <cuda/std/cstddef>
#include <cuda/std/type_traits>
#include <cuda/stream_view>
#include <memory>
#include <tuple>
#include <vector>

int main(int argc, char **argv) {
#ifndef __CUDA_ARCH__
  cuda::resource_view<cuda::memory_access::host,
                      cuda::oversubscribable,
                      cuda::memory_location::host> props_only;

  cuda::resource_view<cuda::is_kind<cuda::memory_kind::host>> kind_only;

  cuda::resource_view<cuda::is_kind<cuda::memory_kind::host>,
                      cuda::memory_access::host,
                      cuda::oversubscribable,
                      cuda::memory_location::host> props_and_kind;

  props_only = kind_only;  // the source properties should be propagated form is_kind
  props_and_kind = kind_only;  // the additional properties should be propagated form is_kind
#endif
  return 0;
}
