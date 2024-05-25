#pragma once

#include <BWengine/BWengineErrors.h>
#include "BlockType.h"
#include <unordered_map>



class BlockTypeLibrary {
public:
	BlockTypeLibrary();

	BlockType* getBlockType(std::string* name);

protected:
	std::unordered_map<std::string, BlockType> m_typeMap;
};

