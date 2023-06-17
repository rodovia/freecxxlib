#pragma once 

#include <stddef.h>

#define __FCL_UNUSED(x) (void)(x)

#ifdef _FCL_ANOTHER_NAMESPACE
#define _FCL_NAMESPACE_BEGIN namespace fcl {
#else
#define _FCL_NAMESPACE_BEGIN namespace std {
#endif

#define _FCL_NAMESPACE_END }

_FCL_NAMESPACE_BEGIN

using nullptr_t = decltype(nullptr);
using size_t = ::size_t;

_FCL_NAMESPACE_END
