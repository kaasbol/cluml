#include "parser/Parser.h"
#include "parser/CLUMLParser.h"
#include "scanner/Scanner.h"
#include "scanner/CLUMLScanner.h"
#include "formatter/Formatter.h"
#include "formatter/StructureFormatter.h"
#include "formatter/DotFormatter.h"
#include "reader/Reader.h"
#include "reader/StreamReader.h"
#include "CLUML.h"
#include "getopt_pp.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace GetOpt;
using namespace std;

int main(int argc, char** argv) {

  GetOpt_pp ops(argc, argv);

  if (ops >> OptionPresent('h', "help")) {
    cout << "Usage: cluml [OPTION]..." << endl;
    // TODO: description
    cout << "  -i, --input FILE     Input from FILE" << endl;
    cout << "  -o, --output FILE    Output to FILE" << endl;
    cout << "  -f, --format FORMAT  Specify output format: dot, debug" << endl;
    return 0;
  }

  Scanner * scanner = NULL;
  Parser * parser = NULL; 
  Formatter * formatter = NULL;
  Reader * reader = NULL;

  // determine reader from args
  string inputFile = "";
  ops >> Option('i', "input", inputFile);

  if (inputFile == "") {
    reader = new StreamReader(&cin);
  } else {
    ifstream * ifs = new ifstream(inputFile.c_str());
    reader = new StreamReader(ifs);
  }

  // determine scanner and input from args
  scanner = new CLUMLScanner(reader);

  // determine parser from args
  parser = new CLUMLParser(scanner); 

  // determine formatter from args
  string format;
  ops >> Option('f', "format", format, "dot");

  if (format == "dot") {
    formatter = new DotFormatter();
  } else if (format == "debug") {
    formatter = new StructureFormatter();
  }
  string outputFile = "";
  ops >> Option('o', "output", outputFile);

  if (outputFile == "") {
    formatter->setOut(&cout);
  } else {
    ofstream * ofs = new ofstream(outputFile.c_str());
    formatter->setOut(ofs);
  }

  CLUML cluml(parser, formatter);
  cluml.process();

  // cleanup when done
  delete reader;
  delete scanner;
  delete parser;
  delete formatter;

  return 0;
}
