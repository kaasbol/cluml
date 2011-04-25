#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <ostream>

enum TokenType { CLASS, WORD, COMMA, BLOCK_OPEN, BLOCK_CLOSE, ARG_OPEN, ARG_CLOSE, EOL, INHERITANCE, TYPE_MODIFIER, PROTECTION, EQUALS, PTR, HASH, GEN_OPEN, GEN_CLOSE, TILDE };

class Token {
	public:
		std::string text;
		TokenType type;
		friend std::ostream & operator << (std::ostream & out, Token *t){
			out << "type: " << t->type << "\t text: " << t->text ;
			return out;
		}
};

#endif // TOKEN_H
