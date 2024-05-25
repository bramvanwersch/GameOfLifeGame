#pragma once
#pragma warning(disable : 4996)

#include <memory>
#include <string>
#include <stdexcept>

class AverageCollection {
public:
	
	void add(float value) {
		m_pool[m_currentIndex] = value;
		m_currentIndex++;
		if (m_currentIndex == 10) {
			m_currentIndex = 0;
		}
	}

	float getAverage() {
		float total = 0;
		for (size_t index = 0; index < 10; index++) {
			total += m_pool[index];
		}
		return total / 10.0f;
	}

private:
	float m_pool[10];
	int m_currentIndex = 0;
};


template <typename T> class Cycler {
public:
	Cycler(T data[], int size) {
		m_container = new T[size];
		m_size = size;
		for (int index = 0; index < size; index++) {
			m_container[index] = data[index];
		}
	}

	~Cycler(){
		delete m_container;
	}

	T* next() {
		m_currentIndex = (m_currentIndex + 1) % m_size;
		return &m_container[m_currentIndex];
	}

	int getSize() { return m_size; }

private:

	T* m_container;
	int m_currentIndex = 0;
	int m_size;
};


// from https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { 
		throw std::runtime_error("Error during formatting."); 
	}
	auto size = static_cast<size_t>(size_s);
	auto buf = std::make_unique<char[]>(size);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}