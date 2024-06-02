#pragma once
#include "Block.h"

class StopperBlock : public Block
{
public:
    using Block::Block;
    ~StopperBlock();

    void update(std::vector<std::shared_ptr<Block>>* newBlockBuffer);
    BWengine::ColorRGBA8& getColor();

protected:

};

