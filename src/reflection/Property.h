#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

namespace reflection {
	class Property {
		public:
			std::string name;
			std::string type;
			std::string protection;
			std::string ptr;
			bool isFinal;
			bool isStatic;
			bool isConst;
	};
};

#endif // PROPERTY_H
