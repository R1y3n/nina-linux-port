#pragma once
#ifndef debug_new
#define debug_new(x) new x
#endif
#pragma once
template<class T> inline T& AsLvalue(const T& t){ return const_cast<T&>(t); }
