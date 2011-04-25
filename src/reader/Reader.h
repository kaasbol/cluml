#ifndef READER_H
#define READER_H
#include <string>

class Reader {
  public:
	  virtual bool good() = 0;
	  virtual char readChar() = 0;
	  virtual void readLine(std::string&) = 0;
};

#endif // READER_H
