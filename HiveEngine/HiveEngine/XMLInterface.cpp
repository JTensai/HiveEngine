#include "XMLInterface.h"

using namespace Hive;

XMLInterface::XMLInterface()
{
}

XMLInterface::XMLInterface(const char* filename)
{
	tinyxml2::XMLError err = doc.LoadFile(filename);
	if (err != tinyxml2::XML_NO_ERROR)
	{
		switch (err)
		{
		case tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND:
			throw DataErrorException("File not found.");
		case tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			throw DataErrorException("Unable to open file.");
		case tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR:
			throw DataErrorException("Read error.");
		case tinyxml2::XMLError::XML_ERROR_EMPTY_DOCUMENT:
			throw DataErrorException("Empty document.");
		case tinyxml2::XMLError::XML_ERROR_MISMATCHED_ELEMENT:
			throw DataErrorException("Mismatched element.");
		default:
			throw DataErrorException(std::string("Unkown error: ") + std::to_string(static_cast<int>(err)));
		}
	}
}

XMLIterator XMLInterface::begin()
{
	return XMLIterator(doc.RootElement());
}

XMLIterator::XMLIterator()
{
	elem = nullptr;
}

bool XMLIterator::isValid()
{
	return elem != nullptr;
}

XMLIterator XMLIterator::next()
{
	if (elemName.empty())
	{
		return XMLIterator(elem->NextSiblingElement());
	}
	return XMLIterator(elem->NextSiblingElement(elemName.c_str()), elemName);
}

XMLIterator XMLIterator::getChildrenOfName(std::string name)
{
	return XMLIterator(elem->FirstChildElement(name.c_str()), name);
}

int XMLIterator::getNumChildrenOfName(std::string name)
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

std::string XMLIterator::getAttribute(std::string attr)
{
	const char* str = elem->Attribute(attr.c_str());
	if (str)
		return std::string(str);
	return "";
}

std::string XMLIterator::getValue()
{
	return getAttribute("value");
}

std::string XMLIterator::getID()
{
	return getAttribute("id");
}

std::string XMLIterator::getParentID()
{
	return getAttribute("parent");
}

void XMLIterator::forEachChildOfName(std::string name, std::function<void(XMLIterator)> func)
{
	XMLIterator xmliter = getChildrenOfName(name);
	while (xmliter.isValid())
	{
		func(xmliter);
		xmliter = xmliter.next();
	}
}

XMLInterface::~XMLInterface()
{
}
