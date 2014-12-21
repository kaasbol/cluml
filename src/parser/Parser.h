#ifndef PARSER_H
#define PARSER_H
#include <map>
#include <string>
#include "../reflection/Type.h"

class Parser {
	public:
		virtual ~Parser() {}
		virtual void process() = 0;
		void setMap(std::map<std::string, reflection::Type> * t ){
			types = t;
		};
	protected:
		std::map<std::string, reflection::Type>* types;
};

#endif // PARSER_H
