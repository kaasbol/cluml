#ifndef CLUML_H
#define CLUML_H

#include <map>
#include <string>

#include "reflection/Type.h"
#include "parser/Parser.h"
#include "formatter/Formatter.h"

class CLUML {
	public:
		CLUML(Parser *, Formatter *);
		~CLUML();
		void process();
	protected:
	private:
		std::map<std::string, reflection::Type> types;
		Parser *parser;
		Formatter *formatter;
};

#endif // CLUML_H
