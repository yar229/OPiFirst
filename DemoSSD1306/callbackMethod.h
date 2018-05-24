#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	#include <type_traits>
	#include <utility>
#ifdef __cplusplus
}
#endif


using namespace std;

//template< class T >
//using decay_t = typename decay<T>::type;

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> 
{
	template <typename... Args>
	static Ret callback(Args... args) 
	{
		func(args...);
	}
	static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;




template<typename Callable>
union storage
{
	storage() {}
	decay_t<Callable> callable;
};

template<int, typename Callable, typename Ret, typename... Args>
auto fnptr_(Callable&& c, Ret(*)(Args...))
{
	static bool used = false;
	static storage<Callable> s;
	using type = decltype(s.callable);

	if (used)
		s.callable.~type();
	new (&s.callable) type(std::forward<Callable>(c));
	used = true;

	return [](Args... args) -> Ret {
		return Ret(s.callable(args...));
	};
}

template<typename Fn, int N = 0, typename Callable>
Fn* fnptr(Callable&& c)
{
	return fnptr_<N>(std::forward<Callable>(c), (Fn*)nullptr);
}