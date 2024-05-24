#include "IOManager.h"

#include <fstream>

namespace BWengine {

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek end
		file.seekg(0, std::ios::end);

		//get file size
		int fileSize = (int) file.tellg();
		file.seekg(0, std::ios::beg);

		//remove the header bytes
		fileSize -= (int) file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek end
		file.seekg(0, std::ios::end);

		//get file size
		int fileSize = (int) file.tellg();
		file.seekg(0, std::ios::beg);

		//remove the header bytes
		fileSize -= (int) file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}