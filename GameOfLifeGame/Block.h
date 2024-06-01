#pragma once
#include <string>
#include <array>
#include <vector>

#include "BlockType.h" 

class Block
{

public:
	Block(BlockType* type, glm::vec2 position): m_type(type), m_position(position){};
	virtual ~Block() = default;

	virtual void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer) = 0;
	virtual void react(Block* otherBlock) = 0;

	BlockType* getType() {
		return m_type;
	}

	glm::vec2* getPosition() {
		return &m_position;
	}

	std::array<int, 2> getCoord() {
		return { (int)(m_position.x / BLOCK_WIDTH), (int)(m_position.y / BLOCK_HEIGTH) };
	}

protected:
	BlockType* m_type;
	glm::vec2 m_position;
};
