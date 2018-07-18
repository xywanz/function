#ifndef _BIND_HPP_
#define _BIND_HPP_


template<int N>
struct PlaceHolder
{
};

extern PlaceHolder<1> _1;
extern PlaceHolder<2> _2;
extern PlaceHolder<3> _3;
extern PlaceHolder<4> _4;
extern PlaceHolder<5> _5;
extern PlaceHolder<6> _6;
extern PlaceHolder<7> _7;
extern PlaceHolder<8> _8;
extern PlaceHolder<9> _9;


struct BindArg0
{
	template<class T>
	T operator[](T arg)
	{
		return arg;
	}
};

template<class Arg1>
struct BindArg1 :public BindArg0
{
	BindArg1(Arg1 _arg1) :arg1(_arg1) {}

	Arg1 operator[](PlaceHolder<1> p)
	{
		return this->arg1;
	}

	template<class T>
	T operator[](T arg)
	{
		return arg;
	}

	Arg1 arg1;
};

template<class Arg1,class Arg2>
struct BindArg2 :public BindArg1<Arg1>
{
	BindArg2(Arg1 _arg1, Arg2 _arg2) :BindArg1<Arg1>(_arg1), arg2(_arg2) {}

	Arg1 operator[](PlaceHolder<1> p)
	{
		return this->arg1;
	}

	Arg2 operator[](PlaceHolder<2> p)
	{
		return this->arg2;
	}

	template<class T>
	T operator[](T arg)
	{
		return arg;
	}

	Arg2 arg2;
};

template<class Arg1, class Arg2, class Arg3>
struct BindArg3 :public BindArg2<Arg1, Arg2>
{
	BindArg3(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3) :BindArg2<Arg1, Arg2>(_arg1, _arg2), arg3(_arg3) {}

	Arg1 operator[](PlaceHolder<1> p)
	{
		return this->arg1;
	}

	Arg2 operator[](PlaceHolder<2> p)
	{
		return this->arg2;
	}

	Arg3 operator[](PlaceHolder<3> p)
	{
		return this->arg3;
	}

	template<class T>
	T operator[](T arg)
	{
		return arg;
	}

	Arg3 arg3;
};


struct BindList0 :public BindArg0
{
	template<class Func,class Args>
	void operator()(Func f, Args args)
	{
		f();
	}
};

template<class Arg1>
struct BindList1 :public BindArg1<Arg1>
{
	BindList1(Arg1 _arg1) :BindArg1<Arg1>(_arg1) {}

	template<class Func, class Args>
	void operator()(Func f, Args args)
	{
		f(args[this->arg1]);
	}
};

template<class Arg1, class Arg2>
struct BindList2 :public BindArg2<Arg1,Arg2>
{
	BindList2(Arg1 _arg1, Arg2 _arg2) :BindArg2<Arg1, Arg2>(_arg1, _arg2) {}

	template<class Func, class Args>
	void operator()(Func f, Args args)
	{
		f(args[this->arg1], args[this->arg2]);
	}
};

template<class Arg1, class Arg2, class Arg3>
struct BindList3 :public BindArg3<Arg1, Arg2, Arg3>
{
	BindList3(Arg1 _arg1, Arg2 _arg2, Arg3 _arg3) :BindArg3<Arg1, Arg2, Arg3>(_arg1, _arg2, _arg3) {}

	template<class Func, class Args>
	void operator()(Func f, Args args)
	{
		f(args[this->arg1], args[this->arg2], args[this->arg3]);
	}
};


template<class Func, class BindList>
struct BindType
{
	BindType(Func _f, BindList _lst) :f(_f), lst(_lst) {}

	void operator()()
	{
		lst(f, BindArg0());
	}

	template<class Arg1>
	void operator()(Arg1 arg1)
	{
		lst(f, BindArg1<Arg1>(arg1));
	}

	template<class Arg1, class Arg2>
	void operator()(Arg1 arg1, Arg2 arg2)
	{
		lst(f, BindArg2<Arg1, Arg2>(arg1, arg2));
	}

	template<class Arg1, class Arg2, class Arg3>
	void operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3)
	{
		lst(f, BindArg3<Arg1, Arg2, Arg3>(arg1, arg2, arg3));
	}

	Func f;
	BindList lst;
};


template<class Func>
BindType<Func, BindList0> bind(Func f)
{
	return BindType<Func, BindList0>(f, BindList0());
}

template<class Func,class Arg1>
BindType<Func, BindList1<Arg1>> bind(Func f, Arg1 arg1)
{
	return BindType<Func, BindList1<Arg1>>(f, BindList1<Arg1>(arg1));
}

template<class Func, class Arg1, class Arg2>
BindType<Func, BindList2<Arg1, Arg2>> bind(Func f, Arg1 arg1, Arg2 arg2)
{
	return BindType<Func, BindList2<Arg1, Arg2>>(f, BindList2<Arg1, Arg2>(arg1, arg2));
}

template<class Func, class Arg1, class Arg2, class Arg3>
BindType<Func, BindList3<Arg1, Arg2, Arg3>> bind(Func f, Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
	return BindType<Func, BindList3<Arg1, Arg2, Arg3>>(f, BindList3<Arg1, Arg2, Arg3>(arg1, arg2, arg3));
}


#endif
