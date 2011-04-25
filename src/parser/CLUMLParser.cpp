#include "CLUMLParser.h"
#include <iostream>

using namespace std;
using namespace reflection;

CLUMLParser::CLUMLParser(Scanner *s) {
	scanner = s;
}
CLUMLParser::~CLUMLParser() {
}

void CLUMLParser::process(){
	next(); // get first token
	while(scanner->hasNext()){
		accept();
	}
}

void CLUMLParser::accept(){
	reset();
	acceptClass();
}
void CLUMLParser::reset(){
	useDefaultAttribValue = false;

	type = NULL;
	protection = "";
	parentList.clear();
	classList.clear();
}
// class

void CLUMLParser::acceptClass(){
	if(token->type == CLASS || token->type == WORD || token->type == INHERITANCE){
		if(token->type == CLASS){
			classType = token->text;
			next();
		}else
			classType = "class";
		if(token->type == INHERITANCE) // double check
			acceptInheritanceFirst();
		else if(token->type == WORD) // double check
			acceptInheritanceSecond();
		processClassList();
		acceptClassBlock();
		acceptEOL();
	}
}
void CLUMLParser::acceptInheritanceFirst(){
	if(token->type == INHERITANCE){
			acceptInheritance();
			acceptClassList();
	}
}
void CLUMLParser::acceptInheritanceSecond(){
	if(token->type == WORD){
		acceptClassList();
		acceptInheritance();
	}
}
void CLUMLParser::acceptClassBlock(){
	if(token->type == BLOCK_OPEN){
		acceptBlockOpen();
		acceptProperties();
		acceptBlockClose();
	}	
}
void CLUMLParser::acceptProperties(){
	while(token->type == WORD || token->type == PROTECTION){
		clearTProperty();
		acceptProperty();
	}
}
void CLUMLParser::acceptProperty(){
	if(token->type == WORD || token->type == PROTECTION){
		acceptAttribProtection();
		acceptAttribType();
		acceptAttribPTR();
		acceptAttribNames();
		useDefaultAttribValue = false;
		acceptEOL();
	}
}
void CLUMLParser::acceptAttribNames(){
	while(token->type == WORD){
		acceptAttribName();
		if(token->type == ARG_OPEN){
			acceptMethod();

		}
		else
			acceptAttribute();
		acceptComma();
	}
}

void CLUMLParser::acceptMethod(){
	if(token->type == ARG_OPEN){
		acceptArgsOpen();
		acceptArgumentList();
		acceptArgsClose();
		handleMethod();
	}
}
void CLUMLParser::acceptArgumentList(){
	while(token->type == WORD){
		clearTArgument();
		acceptArgument();
		acceptComma();
	}	
}
void CLUMLParser::acceptArgument(){
	if(token->type == WORD){
		acceptArgType();
		acceptArgPTR();
		acceptArgName();
		acceptEquals();
		acceptArgValue();
		
		handleArgument();
	}
}
void CLUMLParser::acceptComma(){
	if(token->type == COMMA)
		next();
}
void CLUMLParser::acceptArgName(){
	if(token->type == WORD){
		handleArgName();
		next();
	}
}
void CLUMLParser::acceptArgPTR(){
	if(token->type == PTR){
		handleArgPTR();
		next();
	}
}
void CLUMLParser::acceptArgType(){
	if(token->type == WORD){
		handleArgType();
		next();
		if(token->type == GEN_OPEN){
			//next();
			generic = "";
			acceptGenerics();
			argument.type+=generic;
		}
	}
}
void CLUMLParser::acceptAttribute(){
	if(token->type == EQUALS || token->type == TILDE){
		if(token->type == TILDE){ // acceptDildo
			acceptDefaultAttribValue();
			useDefaultAttribValue = true;
		}else{
			acceptAttribValue();
			useDefaultAttribValue = false;
		}
		handleAttribute();
	}else if(token->type == EOL || token->type == COMMA){
		handleAttribute();
	}
}

void CLUMLParser::acceptAttribProtection(){
	if(token->type == PROTECTION){
		protection = token->text;
		next();
	}
	handleAttribProtection();
}
void CLUMLParser::acceptAttribType(){
	if(token->type == WORD){
		attribType = token->text;
		next();
		generic = "";
		acceptGenerics();
		attribType+=generic;
	}
}
void CLUMLParser::acceptAttribPTR(){
	if(token->type == PTR){
		handleAttribPTR();
		next();	
	}
}
void CLUMLParser::acceptAttribName(){
	if(token->type == WORD){
		attribute.name = token->text;
		next();
	}
}
// class aap, noot, mies;
void CLUMLParser::acceptClassList(){
	if(token->type == WORD){
		handleClassname();
		classList.push_back(type->name); // handleClass
		next();
		if(token->type == COMMA){
			acceptComma();
			if(token->type == WORD)
				acceptClassList();
		}
	}
}

void CLUMLParser::acceptParentList(){
	if(token->type == WORD){
		handleParentname();
		parentList.push_back(parentType->name);
		next();
		if(token->type == COMMA){
			acceptComma();
			if(token->type == WORD){
				acceptParentList();
			}
		}
	}
}
void CLUMLParser::acceptInheritance(){
	if(token->type == INHERITANCE) {
		next();
		acceptParentList();
        }
}
void CLUMLParser::acceptBlockOpen(){
	if(token->type == BLOCK_OPEN){
		next();

	}
}
void CLUMLParser::acceptBlockClose(){
	if(token->type == BLOCK_CLOSE && scanner->hasNext()){
		next();
	}
}
void CLUMLParser::acceptEOL(){
	if(token->type == EOL && scanner->hasNext())
		next();
}
void CLUMLParser::acceptArgsClose(){
	if(token->type == ARG_CLOSE)
		next();
}
void CLUMLParser::acceptArgsOpen(){
	if(token->type == ARG_OPEN)
		next();
}
void CLUMLParser::acceptEquals(){
	if(token->type == EQUALS){
		next();

	}
}
void CLUMLParser::acceptArgValue(){
	if(token->type == WORD){
		handleArgValue();
		next();
	}
}

void CLUMLParser::acceptAttribValue(){
	if(token->type == EQUALS){
		next();
		if(token->type == WORD){
			attribute.value = token->text;
			next();
		}
	}
}
void CLUMLParser::acceptGenerics(){
	if(token->type == GEN_OPEN){
		next();// accept genOpen
		acceptGeneric();
		next();// accept genClose
	}
}
void CLUMLParser::acceptGeneric(){
	if(token->type == WORD){
		generic+='<';
		generic+=token->text;
		next();
		acceptGenerics();
		if(token->type == PTR){
			generic+=token->text;
			next();
		}
		if(token->type == COMMA){
			generic+=token->text;
			next();
			generic+=token->text;
			next();
			if(token->type == GEN_OPEN){
				next();// acceptGEN_OPEN
				acceptGeneric();
				next();
			}
			if(token->type == PTR){
				generic+= token->text;
				next();// acceptPTR
			}

		}
		generic+='>';
	}
}
// handle functions
void CLUMLParser::acceptDefaultAttribValue(){
	if(token->type == TILDE){
		next();
                if(token->type == WORD){
                  defaultAttribValue = token->text;
                  next();
                }
	}
}
void CLUMLParser::handleAttribPTR(){
	attribute.ptr = token->text;
}
void CLUMLParser::handleAttribProtection(){
	attribute.protection = protection;
}
void CLUMLParser::handleArgType(){
	argument.type = token->text;
}
void CLUMLParser::handleArgName(){
	argument.name = token->text;
}
void CLUMLParser::handleArgValue(){
	argument.value = token->text;
}
void CLUMLParser::handleArgPTR(){
	argument.ptr = token->text;
}

void CLUMLParser::handleClassname(){
	if(token->type == WORD)
		type = ensureType(token->text);
}

void CLUMLParser::handleParentname(){
	if(token->type == WORD)
		parentType = ensureType(token->text);
}
void CLUMLParser::handleArgument(){
	method.arguments.push_back(argument);
}
void CLUMLParser::handleMethod(){
	method.name = attribute.name; //TODO fix dit mooi!
	method.type = attribType;
	attribute.value = "";
	method.protection = attribute.protection;
	method.ptr = attribute.ptr;
	method.isFinal = attribute.isFinal;
	method.isStatic = attribute.isStatic;
	method.isConst = attribute.isConst;

	type->methods.push_back(method);
}
void CLUMLParser::handleAttribute(){

	attribute.type = attribType;

	if(useDefaultAttribValue && attribute.value == "")
		attribute.value = defaultAttribValue;
	type->attributes.push_back(attribute);

	attribute.value = "";

}
void CLUMLParser::clearTProperty(){
	method = Method();
	attribute = Attribute();
}
void CLUMLParser::clearTArgument(){
	argument = Argument();
}
void CLUMLParser::processClassList(){
	for(list<string>::iterator iter = classList.begin(); 
			iter != classList.end(); ++iter){
		for(list<string>::iterator piter = parentList.begin(); 
				piter != parentList.end(); ++piter)
			ensureType(*iter)->addParent(*piter);
		ensureType(*iter)->classType = classType;
	}
}
Type * CLUMLParser::ensureType(string name){
	if(types->find(name) == types->end())
		(*types)[name] = Type(name);
	return &((*types)[name]);
}
void CLUMLParser::next(){
	delete token;
	if(scanner->hasNext()){
		token = scanner->next();
		//	cerr << "current token text: " << token->text << endl;
	}else{
		cerr << " ERROR: there should be a next token" << endl;
		//		exit(1);
	}
}
