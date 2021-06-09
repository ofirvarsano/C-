#include <iostream>
#include <vector>
#include <list>

#define ARR_NUM_ELEM(X) (sizeof(X) / sizeof(X[0]))
/*
CONCEPT OF ptr: (iterator)
++
* (deref)
!=
template<typename T>
T Accumulate(T* a_arr, size_t a_size) {
	T sum = T();
	
	for(T* p = a_arr; p != a_arr + a_size; ++p) {
		sum += *p;
	}
	return sum;
}*/

template<class T, class ITR>
T Accumulate(ITR a_first, ITR a_last, T a_initialValue) {
	T sum = a_initialValue;

	for ( ; a_first != a_last ; ++a_first) {
		sum += *a_first;
	}

return sum;
}

/*
template<>
std::string Accumulate<std::string>(std::string* a_arr, size_t a_size) {
	std::string sum = 0;
	for(int i = 0; i < a_size; ++i) {
		sum = sum + a_arr[i];
	}
	return sum;
}
*/

template<class ElementT, class ContainerT>
ElementT Accumulate(ContainerT vec, size_t a_size) {
	ElementT sum = 0;
	for(int i = 0; i < a_size; ++i) {
		sum = sum + vec[i];
	}
	return sum;
}

// CONCEPT OF ContainerT:
// op[]
// typedef value_type
// CONCEPT OF value_type:
// copyCTOR
// defCTOR
// op +=
template<class ContainerT>
typename ContainerT::value_type Accumulate(const ContainerT& vec, size_t a_size) {
	typename ContainerT::value_type sum = typename ContainerT::value_type();
	for(int i = 0; i < a_size; ++i) {
		sum = sum + vec[i];
	}
	return sum;
}

/*
template<class ElementT, class ContainerT>
ElementT Accumulate(ContainerT vec, size_t a_size, ElementT initialVal) {
	ElementT sum = initialVal;
	for(int i = 0; i < a_size; ++i) {
		sum = sum + vec[i];
	}
	return sum;
}
*/

Iterator Begin();
Iterator End();
ConstIterator Begin() const;
ConstIterator End() const;
// Can convert an Iterator to a ConstIterator
// ADVANCED:
// - Add op--
// - Add op->

struct X {
	X(int a_i) : m_i(a_i) {}
	int m_i;
};

int main() {
	std::vector<double> arr2;
	arr2.push_back(6.2);
	arr2.push_back(4534.1);
	arr2.push_back(1.9);
	double sum2 = Accumulate<double, std::vector<double> >(arr2, ARR_NUM_ELEM(arr2));
	// or double sum2 = Accumulate<double>(arr2, ARR_NUM_ELEM(arr2));
	// or double sum2 = Accumulate(arr2, ARR_NUM_ELEM(arr2). 0.0);
	std::cout << sum2 << std::endl;
	
	std::vector<std::string> arr3;
	arr3.push_back("I");
	arr3.push_back(" c a ");
	arr3.push_back("Juk");
	std::string s = Accumulate(arr3.begin(), arr3.end(), std::string());
	// or double sum2 = Accumulate<double>(arr2, ARR_NUM_ELEM(arr2));
	// or double sum2 = Accumulate(arr2, ARR_NUM_ELEM(arr2). 0.0);
	std::cout << s << std::endl;
	
	/*
	int arr[] = { 6, 4534, 1, 17 };
	int sum = Accumulate(arr, ARR_NUM_ELEM(arr));
	std::cout << sum << std::endl;
	
	double arr2[] = { 6.2, 4534.1, 1.9, 17.3, 3.14 };
	double sum2 = Accumulate(arr2, ARR_NUM_ELEM(arr2));
	std::cout << sum2 << std::endl;
	
	std::string arr3[] = { "hello", "*", "world" };
	std::string sum3 = Accumulate(arr3, ARR_NUM_ELEM(arr3));
	std::cout << sum3 << std::endl;
	
	X arr4[] = { X(3), X(8), X(34) };
	X sum4 = Accumulate(arr4, ARR_NUM_ELEM(arr4));
	
	const char* arr5[] = { "hello", "*", "world" };
	const char* sum5 = Accumulate(arr5, ARR_NUM_ELEM(arr5));
	std::cout << sum5 << std::endl;
	*/
	
	return 0;
}


