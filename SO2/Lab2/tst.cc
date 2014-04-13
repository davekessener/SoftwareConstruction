#include <iostream>

template<int N1, int N2>
struct Bigger
{
	enum { value = N1 > N2 };
};

template<typename T1, typename T2, bool s>
struct Switch;

template<typename T1, typename T2>
struct Switch<T1, T2, false>
{
	typedef T2 type;
};

template<typename T1, typename T2>
struct Switch<T1, T2, true>
{
	typedef T1 type;
};


template<typename T>
struct ToInt;

template<>
struct ToInt<char>
{
	enum { value = 0 };
	typedef char type;
};

template<>
struct ToInt<short>
{
	enum { value = 1 };
	typedef short type;
};

template<>
struct ToInt<int>
{
	enum { value = 2 };
	typedef int type;
};

template<>
struct ToInt<long>
{
	enum { value = 3 };
	typedef long type;
};

template<>
struct ToInt<float>
{
	enum { value = 4 };
	typedef float type;
};

template<>
struct ToInt<double>
{
	enum { value = 5 };
	typedef double type;
};

template<typename T>
struct ToInt<T *>
{
	enum { value = 10 + ToInt<T>::value };
	typedef T *type;
};

template<typename T1, typename T2>
struct Add
{
	typedef typename Switch<T1, T2, Bigger<ToInt<T1>::value, ToInt<T2>::value>::value>::type type;
};

template<typename T>
class Complex
{
	public:
		Complex(T const& r, T const& i) : real(r), img(i) { }
		template<typename TT> operator Complex<TT>( ) { return Complex<TT>(static_cast<TT>(real), static_cast<TT>(img)); }
		template<typename TT> 
			Complex<typename Add<T, TT>::type> operator+(Complex<TT> const& c)
		{
			return Complex<typename Add<T, TT>::type>(real + c.real, img + c.img);
		}

		T const real, img;
};

template<typename T>
Complex<T> operator+(double d, Complex<T> c) { return Complex<T>(c.real + d, c.img); }

int main(int argc, char *argv[])
{
	Complex<int> c(7, 5);
	Complex<double> dc(4.5, -3.1);
	auto e = c + dc;

	std::cout << "Real: " << e.real << std::endl;
	std::cout << "Imaginary: " << e.img << std::endl;

	return 0;
}

