#include "CLUMLScanner.h"

using namespace std;

CLUMLScanner::CLUMLScanner(Reader * r) {
	reader = r;
	operators = ",{}();=*&<>~";
	whitespace = " \t\n\r";

	nextChar();
	stripWhitespace();
}
CLUMLScanner::~CLUMLScanner() {
}

bool CLUMLScanner::nextChar(){
	if(reader->good()){
		lookAhead = reader->readChar();
		if(lookAhead == '#'){
			string devNull;
			reader->readLine(devNull);
			nextChar();
		}
	
		_hasNext = reader->good();
		return true;
	} else { // should never happen
		_hasNext = false;
		return false;
	}
}
void CLUMLScanner::stripWhitespace(){
	while(isWhite() && nextChar());
}
Token * CLUMLScanner::next(){
	return createToken();
}
bool CLUMLScanner::hasNext(){
	return _hasNext;
}

Token * CLUMLScanner::createToken(){
	token = new Token();

	token->text += lookAhead;

	if(isOperator())
		handleOperator();
	else
		handleText();

	stripWhitespace();

	return token;	
}
void CLUMLScanner::handleText(){
	bool status = nextChar();
	while(status && !isWhite() && !isOperator() ){
		if(lookAhead == '\\')
			status = nextChar();
		token->text+=lookAhead;
			status = nextChar();
	}
//	while(nextChar() && !isWhite() && !isOperator() )
//		token->text+=lookAhead;

	if(token->text == "class" || token->text == "interface" ||
			token->text == "bean")
		token->type = CLASS;
	else if(token->text == "extends" || token->text == "implements")
		token->type = INHERITANCE;
	else if(token->text == "const" || token->text == "static" ||
			token->text == "final" || token->text == "abstract") // java abstract
		token->type = TYPE_MODIFIER;
	else if(token->text == "public" || token->text == "protected" ||
			token->text == "private" || token->text == "package")
		token->type = PROTECTION;
	else
		token->type = WORD;
}
void CLUMLScanner::handleOperator(){

	if(lookAhead == ',')
		token->type = COMMA;
	else if(lookAhead == '{')
		token->type = BLOCK_OPEN;
	else if(lookAhead == '}')
		token->type = BLOCK_CLOSE;
	else if(lookAhead == '(')
		token->type = ARG_OPEN;
	else if(lookAhead == ')')
		token->type = ARG_CLOSE;
	else if(lookAhead == ';')
		token->type = EOL;
	else if(lookAhead == '=')
		token->type = EQUALS;
	else if(lookAhead == '*' || lookAhead == '&')
		token->type = PTR;
	else if(lookAhead == '<')
		token->type = GEN_OPEN;
	else if(lookAhead == '>')
		token->type = GEN_CLOSE;
	else if(lookAhead == '~')
		token->type = TILDE;

	nextChar();
}
bool CLUMLScanner::isOperator(){
	return (operators.find_first_of(lookAhead,0) != string::npos);
}
bool CLUMLScanner::isWhite(){
	return (whitespace.find_first_of(lookAhead,0) != string::npos);
}
