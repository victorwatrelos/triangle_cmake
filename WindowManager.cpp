#include "WindowManager.hpp"

WindowManager::WindowManager(ObjectManagerBase *objectManager)
	: m_drawableChange(false)
	  , m_view(sf::Vector2f(20.f, 20.f), sf::Vector2f(2000, 1500))
	  , m_objectManager(objectManager)
{
	this->m_window = new sf::RenderWindow(sf::VideoMode(2900 / 1.5f, 2175 / 1.5f), "Triangle");
	this->m_window->setVerticalSyncEnabled(true);
	//this->m_window->setFramerateLimit(30);
	this->m_objectManager->Init(this);
	if (!this->m_font.loadFromFile("ressources/fonts/absender1.ttf"))
	{
		std::cerr << "Unable to load font" << std::endl;
		assert(false);
	}
	m_fps.setFont(m_font);
	m_fps.setScale({0.5f, 0.5f});
	m_playerInfo.setScale({0.5f, 0.5f});
	m_playerInfo.setFont(m_font);
	m_playerInfo.setPosition({0.f, 30.f});
}

WindowManager::~WindowManager(void) {
	delete this->m_window;
}

std::mutex	&WindowManager::GetMutex()
{
	return this->mutex;
}

U16		WindowManager::AddObject(sf::Drawable *drawable, bool visible)
{
	U16	ret;

	ret = this->m_drawnObjects.size();
	this->m_drawnObjects.push_back({drawable, visible});
	this->m_drawableChange = true;
	std::cout << "Add object" << std::endl;
	return ret;
}

void	WindowManager::drawObject()
{
	m_window->setView(m_view);
	std::lock_guard<std::mutex> guard(this->mutex);
	for (const auto &drawable : this->m_drawnObjects)
	{
		if (drawable.visible)
			m_window->draw(*drawable.drawable);
	}
	m_window->setView(m_hudView);
	m_window->draw(m_fps);
	m_window->draw(m_playerInfo);
}

void	WindowManager::SetViewCenter(sf::Vector2f center)
{
	m_view.setCenter(center);
}

void 	WindowManager::SetViewRotation(float rotation)
{
	m_view.setRotation(rotation);
}

void	WindowManager::Run()
{
	U64		nbLoop = 0;
	sf::Clock	clock;
	sf::Time	time;
	U64			fps;

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyPressed:
					if (processKeyEvent(event.key.code))
						break;
				case sf::Event::Closed:
					m_window->close();
					break;
				case sf::Event::JoystickMoved:
					m_objectManager->JoystickMoved();	
				break;
				default:
				break;
			}

		}
		time = clock.restart();
		fps = 1.f / time.asSeconds();
		std::stringstream	ss;
		ss << "FPS: " << fps << " (" << time.asMilliseconds() << " ms)" << " Loop: " << nbLoop;
		m_fps.setString(ss.str());
		if (nbLoop % 20 == 0)
			m_playerInfo.setString(m_objectManager->GetPlayerInfo());
		m_objectManager->Loop(time);
		this->m_window->clear();
		this->drawObject();
		this->m_window->display();
		++nbLoop;
	}
}

bool	WindowManager::processKeyEvent(const sf::Keyboard::Key& key)
{
	if (key == sf::Keyboard::Escape)
		return false;
	if (key == sf::Keyboard::P)
		m_objectManager->ResetGameState();
	return true;
}
