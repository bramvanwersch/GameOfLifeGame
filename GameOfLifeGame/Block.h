#pragma once
#include <string>
#include <array>
#include <vector>

#include "BlockType.h" 


enum class ReactionResult {
	BOTH_DELETE,
	MOVE_DELETE,
	CURRENT_DELETE
};

enum class Direction {
	NONE,
	UP,
	RIGHT,
	DOWN,
	LEFT
};


class Block
{

public:
	Block(BlockType* type, glm::vec2 position, unsigned int stayPriority = 0, Direction direction = Direction::NONE): m_type(type), m_position(position), m_stayPriority(stayPriority), m_direction(direction){
		m_color = type->getColor();
	};
	virtual ~Block() = default;

	virtual void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer) = 0;

	ReactionResult react(Block* movingBlock){
		unsigned int stay1 = getStayPriority();
		unsigned int stay2 = movingBlock->getStayPriority();
		if (stay1 == stay2){
			return ReactionResult::BOTH_DELETE;
		}
		if (stay1 > stay2){
			return ReactionResult::MOVE_DELETE;
		}
		return ReactionResult::CURRENT_DELETE;
	}

	glm::vec4 getUVs() { return m_type->getUVs(); }
	GLuint getTextureID() { return m_type->getTextureID(); }
	BWengine::ColorRGBA8& getColor() { return m_color; }

	unsigned int getStayPriority(){
		return m_stayPriority;
	}

	glm::vec2* getPosition() {
		return &m_position;
	}

	std::array<int, 2> getCoord() {
		return { (int) round(m_position.x / BLOCK_WIDTH), (int) round(m_position.y / BLOCK_HEIGTH) };
	}

protected:
	BlockType* m_type;
	glm::vec2 m_position;
	unsigned int m_stayPriority;
	Direction m_direction;
	BWengine::ColorRGBA8 m_color;
};
