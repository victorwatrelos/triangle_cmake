#pragma once

#include "log.hpp"
#include "ObjectManager.hpp"
#include "WindowManagerBase.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>

class WindowManager : public WindowManagerBase
{
	public:
		WindowManager(ObjectManagerBase *objectManager);
		virtual ~WindowManager(void);

		WindowManager(const WindowManager &obj) = delete;
		WindowManager &operator=(const WindowManager &p) = delete;

		void				Run();
		U16					AddObject(sf::Drawable *drawable, bool visible) override;
		void				SetViewCenter(sf::Vector2f center) override;
		void				SetViewRotation(float rotation) override;
		std::mutex			&GetMutex();
		void				SetDrawableVisible(U16 i) override
		{
			assert(i < m_drawnObjects.size());
			this->m_drawnObjects[i].visible = true;
		}
		void				SetDrawableInvisible(U16 i) override
		{
			assert(i < m_drawnObjects.size());
			this->m_drawnObjects[i].visible = false;
		}
	private:

		//Return false if end of program
		bool	processKeyEvent(const sf::Keyboard::Key& key);

		typedef struct		s_drawable
		{
			sf::Drawable	*drawable;
			bool			visible;
		}					t_drawable;


		std::vector<t_drawable>		m_drawnObjects;
		std::mutex					mutex;
		std::atomic<bool>			m_drawableChange;
		sf::RenderWindow			*m_window;
		sf::View					m_view;
		sf::View					m_hudView;
		ObjectManagerBase			*m_objectManager;
		sf::Font					m_font;
		sf::Text					m_fps;
		sf::Text					m_playerInfo;

		void						drawObject();
		void						manageKePress(const sf::Event &event);
};
