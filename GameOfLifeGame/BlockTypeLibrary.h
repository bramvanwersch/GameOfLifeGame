#pragma once

#include <BWengine/BWengineErrors.h>
#include "BlockType.h"
#include <unordered_map>



class BlockTypeLibrary {
public:
	BlockTypeLibrary();

	BlockType* getBlockType(std::string* name);
	std::string getNameByKey(char key);
	std::unordered_map<char, std::string>* getMaterialKeyMap();

protected:
	std::unordered_map<std::string, BlockType> m_typeMap;
	std::unordered_map<char, std::string> m_materialKeyMap;
};

