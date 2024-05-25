#include "Block.h"

Block::Block(BlockType* type, glm::vec2 position)
{
	m_type = type;
	m_position = position;
}

Block::~Block()
{
}
