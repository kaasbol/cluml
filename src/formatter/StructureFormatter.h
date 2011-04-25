#ifndef STRUCTUREFORMATTER_H
#define STRUCTUREFORMATTER_H

#include <iostream>
#include "Formatter.h"

class StructureFormatter : public Formatter {
  public:
    StructureFormatter();
    ~StructureFormatter();
    virtual void process();
  protected:
  private:
};

#endif // STRUCTUREFORMATTER_H
