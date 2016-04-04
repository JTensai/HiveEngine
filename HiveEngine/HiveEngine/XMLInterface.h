#pragma once

#include <string>
#include <functional>

#include <tinyxml2\tinyxml2.h>

#include "Exceptions.h"

namespace Hive
{
	class XMLIterator;

	class XMLInterface
	{
	private:
		tinyxml2::XMLDocument doc;
	public:
		XMLInterface();
		XMLInterface(const char* filename);

		XMLIterator begin();
		~XMLInterface();
	};

	class XMLIterator
	{
	private:
		std::string elemName;
		tinyxml2::XMLElement* elem;

		XMLIterator(tinyxml2::XMLElement* Element, std::string Name) : elem(Element), elemName(Name) {};

		std::string getAttribute(std::string attr);
	public:
		XMLIterator();
		XMLIterator(tinyxml2::XMLElement* Element) : elem(Element) {};

		bool isValid();
		XMLIterator next();
		XMLIterator getChildrenOfName(std::string name);
		int getNumChildrenOfName(std::string name);
		std::string getValue();
		std::string getID();
		std::string getParentID();

		void forEachChildOfName(std::string name, std::function<void(XMLIterator)> func);
	};

}
