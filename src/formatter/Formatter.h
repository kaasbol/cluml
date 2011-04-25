#ifndef FORMATTER_H
#define FORMATTER_H

#include <ostream>
#include <map>
#include <string>
#include "../reflection/Type.h"

class Formatter {
  public:
    virtual void process() = 0;
    void setMap(std::map<std::string, reflection::Type> * t ){
      types = t;
    };
    void setOut(std::ostream * os) {
      out = os;
    };

  protected:
    std::map<std::string, reflection::Type>* types;
    std::ostream * out;
};

#endif // FORMATTER_H
