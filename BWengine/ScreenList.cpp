#include "ScreenList.h"
#include<iostream>
#include "IGameScreen.h"

namespace BWengine {

    ScreenList::ScreenList(IMainGame* game)
    {
        m_game = game;
    }

    ScreenList::~ScreenList(){
        destroy();
    }

    IGameScreen* ScreenList::moveNext()
    {
        IGameScreen* currentScreen = getCurrent();
        if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
            m_currentScreenIndex = currentScreen->getNextScreenIndex();
        }
        //return the same screen if no next screen
        return getCurrent();
    }

    IGameScreen* ScreenList::movePrevious()
    {
        IGameScreen* currentScreen = getCurrent();
        if (currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
            m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
        }
        //return the same screen if no next screen
        return getCurrent();
    }

    void ScreenList::setScreen(int nextScreen)
    {
        m_currentScreenIndex = nextScreen;
    }

    void ScreenList::addScreen(IGameScreen* newScreen)
    {
        newScreen->m_screenIndex = m_screens.size();
        m_screens.push_back(newScreen);
        newScreen->build();
        newScreen->setParentGame(m_game);
    }

    void ScreenList::destroy()
    {
        for (size_t i = 0; i < m_screens.size(); i++) {
            m_screens[i]->destroy();
        }
        m_screens.resize(0);
        m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
    }

    IGameScreen* ScreenList::getCurrent()
    {
        if (m_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) {
            return nullptr;
        }
        return m_screens[m_currentScreenIndex];
    }
}
