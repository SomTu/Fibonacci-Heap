#include "Header.h"
#include <string>
#include <chrono>
#include <vector>


int main() {
	const int val = 10000;
	fib::Fib_Heap<char> halda('0');
	
	for (int i = 0; i < val; i++) {
		halda.insert('A' + i % (32+27), i);
	}
	while (!halda.empty()) {
		std::cout << halda.extract_min() << "\n";
	}


	//std::vector<std::unique_ptr<fib::Node<char>>> vec;
	//for (int i = 0; i < 7; i++) {
	//	vec.push_back(nullptr);
	//	std::unique_ptr<fib::Node<char>> ptr = std::make_unique<fib::Node<char>>('a' + i, i);
	//	fib::merge_in_vector<char>(vec, std::move(ptr));
	//	// 0 -> 1 dissapears
	//}




	return 0;
}