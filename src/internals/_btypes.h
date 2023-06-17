#pragma once 

#include <stddef.h>

#define __FCL_UNUSED(x) (void)(x)

namespace std {

using nullptr_t = decltype(nullptr);
using size_t = ::size_t;

}
