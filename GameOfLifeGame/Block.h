#pragma once
#include <string>

#include "BlockType.h" 

class Block
{

public:
	Block(BlockType* type, glm::vec2 position): m_type(type), m_position(position){};
	virtual ~Block() = default;

	virtual void update() = 0;
	virtual void react(Block* otherBlock) = 0;

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
