#ifndef STREAMREADER_H
#define STREAMREADER_H
#include "Reader.h"
#include <string>
#include <iostream>

class StreamReader : public Reader{
  public:
	  StreamReader(std::istream * i){
	  	is = i;
	  }
	  bool good(){
	  	return is->good();
	  }
	  char readChar(){
	  	return is->get();
	  }
	  void readLine(std::string& buf){
		  getline(*is, buf);
	  }
  private:
	  std::istream * is;
};

#endif // STREAMREADER_H
