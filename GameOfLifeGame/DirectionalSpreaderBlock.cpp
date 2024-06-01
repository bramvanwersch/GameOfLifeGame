#include "DirectionalSpreaderBlock.h"

DirectionalSpreaderBlock::~DirectionalSpreaderBlock()
{
}

void DirectionalSpreaderBlock::update()
{
	m_position.x += BLOCK_WIDTH;
}

void DirectionalSpreaderBlock::react(Block* otherBlock){

}