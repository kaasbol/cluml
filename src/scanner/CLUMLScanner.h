#ifndef CLUMLSCANNER_H
#define CLUMLSCANNER_H
#include <iostream>
#include <istream>
#include "Scanner.h"
#include "../reader/Reader.h"

class CLUMLScanner : public Scanner {
	public:
		CLUMLScanner(Reader * r);
		virtual ~CLUMLScanner();

		virtual bool hasNext();
		virtual Token * next();
	private:
		char lookAhead;
		std::string tokenText;

		bool nextChar();
		void stripWhitespace();

		Token * createToken();
		void handleOperator();
		void handleText();

		bool isWhite();
		bool isOperator();

		Token * token;

		bool _hasNext;

		Reader * reader;
		std::string operators; 
		std::string whitespace;

//		std::istream & is;
};

#endif // CLUMLSCANNER_H
