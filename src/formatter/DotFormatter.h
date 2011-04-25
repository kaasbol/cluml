#ifndef DOTFORMATTER_H
#define DOTFORMATTER_H

#include <iostream>
#include <list>
#include <string>
#include "Formatter.h"

class DotFormatter : public Formatter {
  public:
    DotFormatter();
    ~DotFormatter();
    virtual void process();
  protected:
  private:
    static std::string start;
    static std::string stop;
    static std::string header;
    static std::string emptyArrow;
    static std::string veeArrow;

    std::list<std::string> inheritance;
    std::list<std::string> relations;

    char protectionToSign(std::string, char);
    std::string nameFormatter(reflection::Type);
    std::string cleanUp(std::string);
    void findAndReplace(std::string&, std::string, std::string);
};

#endif // DOTFORMATTER_H
