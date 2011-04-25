#ifndef TYPE_H
#define TYPE_H
#include "Attribute.h"
#include "Method.h"
#include <list>
#include <string>

namespace reflection {
	class Type {
		public:
			Type(){};
			Type(std::string n){ name = n; };
			std::string name;
			std::list<Attribute> attributes;
			std::list<Method> methods;
			std::list<std::string> parents;
			bool isAbstract;
			std::string classType;

			void addParent(std::string t){
				bool found = false;
				for(std::list<std::string>::iterator iter = parents.begin();
						iter != parents.end(); ++iter)
					found = found || (*iter) == t;
				if(!found)
					parents.push_back(t);
			}
	};
};

#endif // TYPE_H
