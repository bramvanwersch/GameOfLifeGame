#include "BlockTypeLibrary.h"

BlockTypeLibrary::BlockTypeLibrary()
{
	m_typeMap.insert(std::make_pair("directional_spreader", BlockType(BWengine::ColorRGBA8(0, 255, 0), 'd')));
	m_materialKeyMap.insert(std::make_pair('d', "directional_spreader"));
	m_typeMap.insert(std::make_pair("stopper", BlockType(BWengine::ColorRGBA8(0, 0, 0), 's')));
	m_materialKeyMap.insert(std::make_pair('s', "stopper"));
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

std::string BlockTypeLibrary::getNameByKey(char key)
{
	auto it = m_materialKeyMap.find(key);

	if (it == m_materialKeyMap.end()) {
		char buffer[128];
		sprintf_s(buffer, "Failed to find material with key %c", key);
		BWengine::fatalError(buffer);
	}
	return it->second;
}

std::unordered_map<char, std::string>* BlockTypeLibrary::getMaterialKeyMap()
{
	return &m_materialKeyMap;
}
