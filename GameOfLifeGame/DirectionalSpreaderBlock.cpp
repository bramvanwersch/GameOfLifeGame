#include "DirectionalSpreaderBlock.h"

DirectionalSpreaderBlock::~DirectionalSpreaderBlock()
{
}

void DirectionalSpreaderBlock::update(std::vector<std::shared_ptr<Block>>* newBlockBuffer)
{
	switch (m_direction)
	{
	case 0:
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x, m_position.y + BLOCK_HEIGTH}, 1)));
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x + BLOCK_WIDTH, m_position.y}, 2)));
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x, m_position.y - BLOCK_HEIGTH}, 3)));
		m_direction = 4;
		m_position.x -= BLOCK_WIDTH;
		break;
	case 1:
		m_position.y += BLOCK_HEIGTH;
		break;
	case 2:
		m_position.x += BLOCK_WIDTH;
		break;
	case 3:
		m_position.y -= BLOCK_HEIGTH;
		break;
	case 4:
		m_position.x -= BLOCK_WIDTH;
		break;
	default:
		return;
	}
}

void DirectionalSpreaderBlock::react(Block *otherBlock)
{
}