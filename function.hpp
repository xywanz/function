#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_

#include <cstdlib>
#include <memory>


// function_base is for the virtual base class for storage of functor
template<class R, class ...Args>
class function_base
{
public:
	virtual R operator()(Args ...args) = 0;
	virtual ~function_base() {}
};

// function_handler is the storage of function, function pointer or functor.
template<class FuncType, class R, class ...Args>
class function_handler :public function_base<R, Args...>
{
public:
	function_handler(const FuncType& func) :f(func)
	{
	}

	R operator()(Args ...args)
	{
		return f(args...);
	}
private:
	FuncType f;
};

// function is the wrapper.
template<class FuncPrototype>
class function;

template<class R, class ...Args>
class function<R(Args...)>
{
public:
	template<class FuncType>
	function(const FuncType& func) :func_base(new function_handler<FuncType, R, Args...>(func))
	{
	}

	R operator()(Args ...args)
	{
		(*func_base)(args...);
	}
private:
	std::shared_ptr<function_base<R, Args...>> func_base;
};


#endif
