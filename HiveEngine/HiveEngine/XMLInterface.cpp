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
			throw IDataManager::DataErrorException("File not found.");
		case tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			throw IDataManager::DataErrorException("Unable to open file.");
		case tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR:
			throw IDataManager::DataErrorException("Read error.");
		case tinyxml2::XMLError::XML_ERROR_EMPTY_DOCUMENT:
			throw IDataManager::DataErrorException("Empty document.");
		case tinyxml2::XMLError::XML_ERROR_MISMATCHED_ELEMENT:
			throw IDataManager::DataErrorException("Mismatched element.");
		default:
			throw IDataManager::DataErrorException(std::string("Unkown error: ") + std::to_string(static_cast<int>(err)));
		}
	}
}

XMLInterface::XMLIterator XMLInterface::begin()
{
	return XMLInterface::XMLIterator(doc.RootElement());
}

XMLInterface::XMLIterator::XMLIterator()
{
	elem = nullptr;
}

bool XMLInterface::XMLIterator::isValid()
{
	return elem != nullptr;
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
