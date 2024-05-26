#pragma once

#include "Block.h"

class DirectionalSpreaderBlock : public Block
{
public:
    using Block::Block;
    ~DirectionalSpreaderBlock();

    void update();
    void react(Block* otherBlock);
protected:
    

};

