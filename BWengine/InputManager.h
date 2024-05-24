#pragma once

#include <SDL/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace BWengine {

	enum Keys {
		w = SDLK_w,
		a = SDLK_a,
		s = SDLK_s,
		d = SDLK_d,
		e = SDLK_e,
		q = SDLK_q,
		m = SDLK_m,
		t = SDLK_t,
		i = SDLK_i,
		tab = SDLK_TAB,
		n1 = SDLK_1,
		n2 = SDLK_2,
		n3 = SDLK_3,
		n4 = SDLK_4,
		mouse_left = SDL_BUTTON_LEFT,
		mouse_right = SDL_BUTTON_RIGHT,
		ctrl_l = SDLK_LCTRL,
		space = SDLK_SPACE,
		shiftL = SDLK_LSHIFT,
		up = SDLK_UP,
		down = SDLK_DOWN,
		left = SDLK_LEFT,
		rigth = SDLK_RIGHT,
		equals = SDLK_EQUALS,
		plus_np = SDLK_KP_PLUS,
		minus = SDLK_MINUS,
		minus_np = SDLK_KP_MINUS
	};

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);
		void setScrolled(float x, float y);

		// return if a key is being held down
		bool isKeyDown(unsigned int keyID);


		//return if a key was presed this frame
		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }
		glm::vec2 getScrolled() const { return m_scrolled; }

	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;

		glm::vec2 m_mouseCoords;
		glm::vec2 m_scrolled;

	};

}
