#ifndef CLUMLPARSER_H
#define CLUMLPARSER_H
#include "../scanner/Scanner.h"
#include "Parser.h"
#include "../reflection/Type.h"
#include "../reflection/Argument.h"
#include "../reflection/Attribute.h"
#include "../reflection/Method.h"
#include <list>

class CLUMLParser : public Parser{
	public:
		CLUMLParser(Scanner * s);
		~CLUMLParser();
		virtual void process();
	protected:
	private:
		void accept();
		void acceptClass();
		void acceptClassList();
		void acceptParentList();

		void acceptInheritance();
		void acceptInheritanceFirst();
		void acceptInheritanceSecond();
		void acceptBlock();

		void acceptEOL();


		void acceptClassBlock();
		void acceptBlockOpen(); void acceptBlockClose(); // {}
		void acceptArgsOpen(); void acceptArgsClose(); // ()
		void acceptEquals(); // =
		void acceptComma(); // ,

		void acceptProperties();
		void acceptProperty();
		void acceptMethod();
		void acceptAttribute();
		void acceptArgumentList(); void acceptArgument();

		void acceptGenerics(); void acceptGeneric();

		void acceptAttribName(); void acceptAttribNames();
		void acceptAttribPTR(); void handleAttribPTR();
		void acceptAttribProtection(); void handleAttribProtection();
		void acceptAttribValue(); void handleAttribValue();
		void acceptDefaultAttribValue();
		void acceptAttribType(); void handleAttribType();
		void handleMethod(); void handleAttribute(); void handleArgument();

		void acceptArgType(); void handleArgType();
		void acceptArgPTR(); void handleArgPTR();
		void acceptArgName(); void handleArgName();
		void acceptArgValue(); void handleArgValue();

		
		void processClassList();

		void handleClassname();
		void handleParentname();
		void clearTArgument(); void clearTProperty();


		reflection::Type * ensureType(std::string);
		void reset();
		void next();
		Scanner * scanner;
		Token * token;

		reflection::Argument argument;
		reflection::Method method;
		reflection::Attribute attribute;

		reflection::Type * type;
		reflection::Type * parentType;
		std::string classType;
		std::string generic;
		std::string protection;
		std::string attribType;

		std::string defaultAttribValue;
		bool useDefaultAttribValue;

		std::list<std::string> parentList;
		std::list<std::string> classList;
};

#endif // CLUMLPARSERH
