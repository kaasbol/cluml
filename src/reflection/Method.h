#ifndef METHOD_H
#define METHOD_H
#include "Argument.h"
#include "Property.h"
#include <list>

namespace reflection {
	class Method : public Property{
		public:
			std::list<Argument> arguments;
	};
};

#endif // METHOD_H
