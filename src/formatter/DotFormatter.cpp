#include "DotFormatter.h"

using namespace std;
using namespace reflection;

string DotFormatter::start = "digraph G {";
string DotFormatter::stop = "}";
string DotFormatter::header =
"  fontname = \"Bitstream Vera Sans\"\n"
"  fontsize = 8\n"
"\n"
"  node [\n"
"    fontname = \"Bitstream Vera Sans\"\n"
"    fontsize = 8\n"
"    shape = \"record\"\n"
"  ]\n"
"\n"
"  edge [\n"
"    fontname = \"Bitstream Vera Sans\"\n"
"    fontsize = 8\n"
"  ]\n";
string DotFormatter::emptyArrow =
"  edge [\n"
"    arrowhead = \"empty\"\n"
"  ]\n";
string DotFormatter::veeArrow = 
"  edge [\n"
"    arrowhead = \"vee\"\n"
"  ]\n";

DotFormatter::DotFormatter() {
  out = &cout;
}
DotFormatter::~DotFormatter() {
}

void DotFormatter::process() {

  *out << start << endl << endl;
  *out << "// header" << endl << endl << header << endl << endl;
  *out << "// objects" << endl << endl;

  map<string, Type>::iterator iter;
  for (iter = types->begin(); iter != types->end(); ++iter) {
    string name = iter->first;
    Type type = iter->second;

    // classname
    *out << "  " << name << " [" << endl;
    *out << "    label = \"{" << nameFormatter(type) << "|";

    // attributes
    list<Attribute>::iterator attr_iter;
    for (attr_iter = type.attributes.begin(); attr_iter != type.attributes.end(); ++attr_iter) {
      *out << protectionToSign(attr_iter->protection, '-') << cleanUp(attr_iter->type);
      if (attr_iter->ptr != "") *out << " " << attr_iter->ptr;
      *out << " " << attr_iter->name;
      if (attr_iter->value != "") *out << " = " << attr_iter->value;
      *out << "\\l";

      // relations
      if (types->find(attr_iter->type) != types->end())
        relations.push_back(name + " -> " + attr_iter->type);
    }
    *out << "|";

    // methods
    list<Method>::iterator meth_iter;
    for (meth_iter = type.methods.begin(); meth_iter != type.methods.end(); ++meth_iter) {
      *out << protectionToSign(meth_iter->protection, '+') << meth_iter->type << " " << meth_iter->name << "(";
      
      // arguments of method
      int count = 0;
      list<Argument>::iterator arg_iter;
      for(arg_iter = meth_iter->arguments.begin(); arg_iter != meth_iter->arguments.end(); ++arg_iter) {
        if (count++ != 0) *out << ", ";
        *out << cleanUp(arg_iter->type);
        if (arg_iter->ptr != "") *out << " " << arg_iter->ptr;
        *out << " " << arg_iter->name;
        if (arg_iter->value != "") *out << " = " << arg_iter->value;
      }
      *out << ")\\l";
    }
    *out << "}\"" << endl << "  ]" << endl;

    // inheritance
    list<string>::iterator par_iter;
    for (par_iter = type.parents.begin(); par_iter != type.parents.end(); ++par_iter) {
      inheritance.push_back(name + " -> " + (*par_iter));
    }
  }

  *out << endl << "// edges" << endl << endl;

  *out << emptyArrow << endl << endl;
  list<string>::iterator str_iter;
  for (str_iter = inheritance.begin(); str_iter != inheritance.end(); ++str_iter)
    *out << "  " << (*str_iter) << endl;

  *out << endl << veeArrow << endl << endl;
  for (str_iter = relations.begin(); str_iter != relations.end(); ++str_iter)
    *out << "  " << (*str_iter) << endl;

  *out << endl << stop << endl;
}

char DotFormatter::protectionToSign(string prot, char def) {
  char result = def;
  if (prot == "public") {
    result = '+';
  } else if (prot == "private") {
    result = '-';
  } else if (prot == "protected") {
    result = '#';
  } else if (prot == "package") {
    result = '~';
  }
  return result;
}

string DotFormatter::nameFormatter(Type t) {
  string result;
  if (t.classType == "interface")
    result = "<<" + t.name + ">>";
  else 
    result = t.name;
  return cleanUp(result);
}

string DotFormatter::cleanUp(string s) {
  string result = s;
  findAndReplace(result, "<", "&lt;");
  findAndReplace(result, ">", "&gt;");
  return result;
}

void DotFormatter::findAndReplace(string &source, const string find, string replace) {
  size_t j;
  for ( ; (j = source.find( find )) != string::npos ; ) {
    source.replace( j, find.length(), replace );
  }
}
