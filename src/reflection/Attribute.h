#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include "Property.h"

namespace reflection {
	class Attribute : public Property{
		public:
			std::string value;
	};
};

#endif // ATTRIBUTE_H
