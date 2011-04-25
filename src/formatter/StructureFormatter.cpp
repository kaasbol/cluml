#include "StructureFormatter.h"

using namespace std;
using namespace reflection;

StructureFormatter::StructureFormatter() {
}
StructureFormatter::~StructureFormatter() {
}

void StructureFormatter::process() {

  // classes
  map<string, Type>::iterator iter;
  for (iter = types->begin(); iter != types->end(); ++iter) {
    Type type = iter->second;
    *out << "class " << iter->first;
    
    // inheritance
    int count = 0;
    list<string>::iterator par_iter;
    for (par_iter = type.parents.begin(); par_iter != type.parents.end(); ++par_iter) {
      if (count++ == 0)
        *out << " extends ";
      else
        *out << ", ";
      *out << (*par_iter);
    }
    *out << " {" << endl;

    // attributes
    list<Attribute>::iterator attr_iter;
    for (attr_iter = type.attributes.begin(); attr_iter != type.attributes.end(); ++attr_iter) {
      *out << "\t" << attr_iter->protection << " " << attr_iter->type;
      if (attr_iter->ptr != "") *out << " " << attr_iter->ptr;
      *out << " " << attr_iter->name;
      if (attr_iter->value != "") *out << " = " << attr_iter->value;
      *out << ";" << endl;
    }

    list<Method>::iterator meth_iter;
    for (meth_iter = type.methods.begin(); meth_iter != type.methods.end(); ++meth_iter) {
      *out << "\t" << meth_iter->protection << " " << meth_iter->type << " " << meth_iter->name << "("; 
      // arguments of method
      count = 0;
      list<Argument>::iterator arg_iter;
      for(arg_iter = meth_iter->arguments.begin(); arg_iter != meth_iter->arguments.end(); ++arg_iter) {
        if (count++ != 0) *out << ", ";
        *out << arg_iter->type;
        if (arg_iter->ptr != "") *out << " " << arg_iter->ptr;
        *out << " " << arg_iter->name;
        if (arg_iter->value != "") *out << " = " << arg_iter->value;
      }
      *out << ");" << endl;
    }
    *out << "}" << endl;
  }
}
