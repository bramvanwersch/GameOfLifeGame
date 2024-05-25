#pragma once
#include <string>

#include "BlockType.h" 

class Block
{

public:
	Block(BlockType* type);
	~Block();

	BlockType* getType() {
		return m_type;
	}


protected:
	BlockType* m_type;
};
