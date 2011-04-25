#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"

class Scanner {
	public:
		virtual bool hasNext() = 0;
		virtual Token * next() = 0;
};

#endif // SCANNER_H
