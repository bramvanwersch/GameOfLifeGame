#include "BlockTypeLibrary.h"

BlockTypeLibrary::BlockTypeLibrary()
{
	m_typeMap.insert(std::make_pair("test", BlockType(BWengine::ColorRGBA8(0, 255, 0))));
}

BlockType* BlockTypeLibrary::getBlockType(std::string *name)
{
	auto it = m_typeMap.find(*name);

	if (it == m_typeMap.end()) {
		char buffer[128];
		sprintf_s(buffer, "RuntimeError: Failed to find block type with name %s", (*name).c_str());
		BWengine::fatalError(buffer);
	}
	return &it->second;
}
