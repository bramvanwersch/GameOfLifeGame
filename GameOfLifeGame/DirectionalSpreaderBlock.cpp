#include "DirectionalSpreaderBlock.h"


DirectionalSpreaderBlock::DirectionalSpreaderBlock(BlockType* type, glm::vec2 position, unsigned int stayPriority, Direction direction) : Block(type, position, stayPriority, direction){
	switch (direction)
	{
	case Direction::UP:
		m_color = BWengine::ColorRGBA8(255, 0, 0);
		break;
	case Direction::RIGHT:
		m_color = BWengine::ColorRGBA8(255, 255, 0);
		break;
	case Direction::DOWN:
		m_color = BWengine::ColorRGBA8(0, 255, 255);
		break;
	case Direction::LEFT:
		m_color = BWengine::ColorRGBA8(0, 0, 255);
		break;
	}
}

DirectionalSpreaderBlock::~DirectionalSpreaderBlock()
{
}

void DirectionalSpreaderBlock::update(std::vector<std::shared_ptr<Block>>* newBlockBuffer)
{
	switch (m_direction)
	{
	case Direction::NONE:
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x, m_position.y + BLOCK_HEIGTH}, 0, Direction::UP)));
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x + BLOCK_WIDTH, m_position.y}, 0, Direction::RIGHT)));
		newBlockBuffer->push_back(std::make_shared<DirectionalSpreaderBlock>(DirectionalSpreaderBlock(m_type, {m_position.x, m_position.y - BLOCK_HEIGTH}, 0, Direction::DOWN)));
		m_direction = Direction::LEFT;
		m_color = BWengine::ColorRGBA8(0, 0, 255);
		m_position.x -= BLOCK_WIDTH;
		break;
	case Direction::UP:
		m_position.y += 2;
		break;
	case Direction::RIGHT:
		m_position.x += 2;
		break;
	case Direction::DOWN:
		m_position.y -= 2;
		break;
	case Direction::LEFT:
		m_position.x -= 2;
		break;
	default:
		return;
	}
}

BWengine::ColorRGBA8& DirectionalSpreaderBlock::getColor() 
{
	return m_color;
}
