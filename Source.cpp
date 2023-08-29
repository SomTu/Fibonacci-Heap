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
	
	return 0;
}
