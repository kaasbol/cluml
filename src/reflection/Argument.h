#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <string>

namespace reflection {
	class Argument {
		public:
			std::string name;
			std::string type;
			std::string ptr;
			std::string value;
	};
};

#endif // ARGUMENT_H
