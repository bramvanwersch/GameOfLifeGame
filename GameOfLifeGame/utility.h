#pragma once

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
