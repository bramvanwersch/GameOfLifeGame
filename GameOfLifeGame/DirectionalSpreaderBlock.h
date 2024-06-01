#pragma once

#include "Block.h"

class DirectionalSpreaderBlock : public Block
{
public:
    DirectionalSpreaderBlock(BlockType* type, glm::vec2 position, unsigned int direction = 0): Block(type, position), m_direction(direction){}
    ~DirectionalSpreaderBlock();

    void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer);
    void react(Block* otherBlock);
protected:
    // if direction is 0 spreads all 4 otherwise 1 to indicates NESW (that order)
    unsigned int m_direction = 0;

};

