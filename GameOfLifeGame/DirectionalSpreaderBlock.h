#pragma once

#include "Block.h"

class DirectionalSpreaderBlock : public Block
{
public:
    DirectionalSpreaderBlock(BlockType* type, glm::vec2 position, unsigned int stayPriority = 0, Direction direction = Direction::NONE);
    ~DirectionalSpreaderBlock();

    void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer);
    BWengine::ColorRGBA8& getColor();

protected:
};

