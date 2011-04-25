#include "CLUML.h"

CLUML::CLUML(Parser * p, Formatter *f) {
	parser = p;
	formatter = f;
	parser->setMap(&types);
	formatter->setMap(&types);
}
CLUML::~CLUML() {
}

void CLUML::process() {
	parser->process();
	formatter->process();
}
