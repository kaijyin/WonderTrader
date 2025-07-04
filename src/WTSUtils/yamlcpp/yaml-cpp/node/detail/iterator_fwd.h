#ifndef VALUE_DETAIL_ITERATOR_FWD_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define VALUE_DETAIL_ITERATOR_FWD_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                                       \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) ||            \
     (__GNUC__ >= 4)) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include "yaml-cpp/dll.h"
#include <list>
#include <utility>
#include <vector>

namespace YAML {

namespace detail {
struct iterator_value;
template <typename V> class iterator_base;
} // namespace detail

using iterator = detail::iterator_base<detail::iterator_value>;
using const_iterator = detail::iterator_base<const detail::iterator_value>;
} // namespace YAML

#endif // VALUE_DETAIL_ITERATOR_FWD_H_62B23520_7C8E_11DE_8A39_0800200C9A66
