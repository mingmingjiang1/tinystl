#ifndef PAIR
#define PAIR

namespace tinystl
{
	template <class T1, class T2>
	struct Pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		// 默认构造函数
		Pair()
			: first(T1()), second(T2()) {} // T1()用0初始化 T2()用0初始化

		// 构造函数
		Pair(const T1 &a, const T2 &b)
			: first(a), second(b) {}

		// 拷贝构造函数
		template <class U, class V>
		Pair(const Pair<U, V> &p)
			: first(p.first), second(p.second) { } //{用来测试那些对象创建调用了copy构造函数}
	};

	// 比较
	template <class T1, class T2>
	bool operator==(const Pair<T1, T2> &s1, const Pair<T1, T2> &s2)
	{
		return s1.first == s2.first && s1.second == s2.second;
	}

	template <class T1, class T2>
	bool operator>(const Pair<T1, T2> &s1, const Pair<T1, T2> &s2)
	{
		return (s1.first > s2.first) || (!(s1.first < s2.first) && s1.second > s2.second);
	}

	template <class T1, class T2>
	bool operator<(const Pair<T1, T2> &s1, const Pair<T1, T2> &s2)
	{
		return (s1.first < s2.first) || (!(s1.first > s2.first) && s1.second < s2.second);
	}
}

#endif