#include "XMLInterface.h"



XMLInterface::XMLInterface()
{
}

XMLInterface::XMLInterface(const char* filename)
{
	doc.LoadFile(filename);
}

XMLInterface::XMLIterator XMLInterface::begin()
{
	return XMLInterface::XMLIterator(doc.RootElement());
}

XMLInterface::XMLIterator::XMLIterator()
{
}

bool XMLInterface::XMLIterator::isValid()
{
	return valid;
}

XMLInterface::XMLIterator XMLInterface::XMLIterator::next()
{
	if (elemName.empty())
	{
		return XMLIterator(elem->NextSiblingElement());
	}
	return XMLIterator(elem->NextSiblingElement(elemName.c_str()), elemName);
}

XMLInterface::XMLIterator XMLInterface::XMLIterator::getChildrenOfName(std::string name)
{
	return XMLIterator(elem->FirstChildElement(name.c_str()), name);
}

int XMLInterface::XMLIterator::getNumChildrenOfName(std::string name)
{
	XMLIterator iter = getChildrenOfName(name);
	int count = 0;
	while (iter.isValid())
	{
		count++;
		iter = iter.next();
	}
	return count;
}

std::string XMLInterface::XMLIterator::getAttribute(std::string attr)
{
	const char* str = elem->Attribute(attr.c_str());
	if (str)
		return std::string(str);
	return "";
}

std::string XMLInterface::XMLIterator::getValue()
{
	return getAttribute("value");
}

std::string XMLInterface::XMLIterator::getID()
{
	return getAttribute("id");
}

std::string XMLInterface::XMLIterator::getParentID()
{
	return getAttribute("parent");
}

void XMLInterface::XMLIterator::forEachChildOfName(std::string name, std::function<void(XMLIterator)> func)
{
	XMLInterface::XMLIterator xmliter = getChildrenOfName(name);
	while (xmliter.isValid())
	{
		func(xmliter);
		xmliter = xmliter.next();
	}
}

XMLInterface::~XMLInterface()
{
}
