#include "InputManager.h"


namespace BWengine {

	InputManager::InputManager() : m_mouseCoords(0), m_scrolled(0)
	{

	}

	InputManager::~InputManager() {

	}

	void InputManager::update() {

		for (auto& it : m_keyMap) {
			m_previousKeyMap[it.first] = it.second;
		}
		m_scrolled = { 0, 0 };
	}

	void InputManager::pressKey(unsigned int keyID) {
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}

	void InputManager::setScrolled(float x, float y)
	{
		m_scrolled.x = x;
		m_scrolled.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		return isKeyDown(keyID) == true && wasKeyDown(keyID) == false;
	}
}