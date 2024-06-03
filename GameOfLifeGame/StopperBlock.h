#pragma once
#include "Block.h"

class StopperBlock : public Block
{
public:
	StopperBlock(BlockType* type, glm::vec2 position, unsigned int stayPriority = 1000, Direction direction = Direction::NONE): Block(type, position, stayPriority, direction){};
    ~StopperBlock();

    void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer);
    BWengine::ColorRGBA8& getColor();

protected:

};

