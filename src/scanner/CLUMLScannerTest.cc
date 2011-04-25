#include "CLUMLScanner.h"
#include <iostream>

int main(){
	CLUMLScanner scanner;
	while(scanner.hasNext()) // memleak
		std::cout << " producing token: " << (scanner.next()) << std::endl;
}
