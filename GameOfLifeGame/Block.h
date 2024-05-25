#pragma once
#include <string>

#include "BlockType.h" 

class Block
{

public:
	Block(BlockType* type, glm::vec2 position);
	~Block();

	BlockType* getType() {
		return m_type;
	}

	glm::vec2* getPosition() {
		return &m_position;
	}


protected:
	BlockType* m_type;
	glm::vec2 m_position;
};
