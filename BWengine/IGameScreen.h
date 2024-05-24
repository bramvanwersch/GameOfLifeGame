#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

namespace BWengine{

	class IMainGame;

	enum class ScreenState {
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS,
	};


	class IGameScreen
	{
	public:
		friend class ScreenList;

		IGameScreen() {};
		virtual ~IGameScreen() {
			//empty
		}

		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;

		virtual void build() = 0;
		virtual void destroy() = 0;

		virtual void onEntry() = 0;
		virtual void onExit() = 0;

		virtual void update() = 0;
		virtual void draw() = 0;

		void setParentGame(IMainGame* game) { m_game = game; }

		int getIndex()const { return m_screenIndex; }

		void setRunning() { m_currentState = ScreenState::RUNNING; }

		void setScreenState(ScreenState state) { m_currentState = state; }

		ScreenState getState() { return m_currentState; }

		void setFps(float fps) { m_fps = fps; }

	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame* m_game = nullptr;

		float m_fps = 0;
		int m_screenIndex = SCREEN_INDEX_NO_SCREEN;
	};
}


