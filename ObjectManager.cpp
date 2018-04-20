#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_playerSpeed({0.f, 0.f})
	  , m_acceleration(0.f)
	  , m_playerAngle({0.f, 0.f})
	  , triangle(sf::PrimitiveType::Triangles, 3)
	  , triangle2(sf::PrimitiveType::Triangles, 3)
{
}

void	ObjectManager::Stop()
{
	m_running = false;
}

void	ObjectManager::Init(WindowManagerBase *windowManager)
{
	m_running = true;
	m_windowManager = windowManager;
	m_player = EntityFactory<Player>::Create();
	auto ret = m_windowManager->AddObject(m_player, true);
	m_windowManager->AddObject(&triangle, true);
	m_windowManager->AddObject(&triangle2, true);
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;

	triangle2[0].color = sf::Color::Red;
	triangle2[1].color = sf::Color::Red;
	triangle2[2].color = sf::Color::Red;

	m_player->SetId(ret);
	m_player->CenterOrigin();
	m_player->setScale({0.2f, 0.2f});


	for (auto &bullet : m_bullets)
	{
		std::cout << "Create bullet" << std::endl << std::flush;
		bullet = EntityFactory<Bullet>::Create();
		std::cout << "Add bullet" << std::endl << std::flush;
		auto bulletId = m_windowManager->AddObject(bullet, false);
		bullet->SetId(bulletId);
	}

	this->initGameState();
}

void	ObjectManager::initGameState()
{
	triangle2[0].position = sf::Vector2f(600.f, 600.f);
	triangle2[1].position = sf::Vector2f(100.f, 100.f);
	triangle2[2].position = sf::Vector2f(-100.f, 0.f);

	m_player->setPosition({200.f, 200.f});
	m_playerAngle.SetDirection({0.f, 0.f});
	m_player->setRotation(m_playerAngle.GetDegAngle());
	m_playerSpeed = {0.f, 0.f};
	m_acceleration = 0.f;
}

void	ObjectManager::JoystickMoved()
{
}

// Make sure to have call sf::Joystick::update() berfore
void	ObjectManager::updateAccFromJoystickPos()
{
	/*
	float position = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
	position = -100.f;
	if (position < -99.f)
		m_acceleration = 0.f;
	else
		//Acceleration
		m_acceleration = (position + 100.f) * 0.07f;
		*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_acceleration = 8.f;
	else
		m_acceleration = 0.f;
	assert(m_acceleration == m_acceleration && "Magnitude is NaN, ERROR");
}

void	ObjectManager::updatePlayerSpeed()
{
	float	mag = math::magnitude(m_playerSpeed);
	assert(mag == mag && "Magnitude is NaN, ERROR");
	if (m_acceleration < EPSILON)
	{
		if (mag < EPSILON)
			m_playerSpeed = {0.0f, 0.0f};
		else
			//Deceleration
			//To optimize (can be done without normalizing)
			m_playerSpeed = math::normalize(m_playerSpeed, mag) * (mag - 3.f);
	}
	else
	{
		//sf::Vector2f	currentAcc = {m_playerAngle.GetDirection().x/** -m_acceleration*/, m_playerAngle.GetDirection().y /** -m_acceleration*/};
		sf::Vector2f currentAcc = m_playerAngle.GetDirection() + sf::Vector2f(0.866025f, -0.5);
	//	m_playerSpeed = m_playerSpeed + currentAcc;
		m_playerSpeed = m_playerAngle.GetDirection() * 100.f;
	}

	//Update magnitude with new speed
	mag = math::magnitude(m_playerSpeed);

	if (mag > 500.f)
	{
		m_playerSpeed = math::normalize(m_playerSpeed, mag) * 500.f;
	}
	triangle[0].position = m_playerSpeed + m_player->getPosition();
	triangle[1].position = sf::Vector2f(50.f + m_player->getPosition().x, 0.f + m_player->getPosition().y);
	triangle[2].position = sf::Vector2f(-50.f + m_player->getPosition().x, 0.f + m_player->getPosition().y);
	m_player->SetVelocity(m_playerSpeed);
}

void	ObjectManager::updatePlayerRotation()
{
	/*
	float rotation = -sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	if (rotation < 15.f && rotation > -15.f)
		return ;
	if (rotation < 0.f)
		rotation += 15.f;
	else
		rotation -= 15.f;
	m_playerAngle += rotation * 0.001f;
	*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_playerAngle -= 0.02f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_playerAngle += 0.02f;
	m_player->setRotation(m_playerAngle.GetDegAngle());
	m_windowManager->SetViewRotation(m_playerAngle.GetDegAngle());
}

void	ObjectManager::updateVelocity()//To optimized by only calling when update
{
	sf::Joystick::update();
	updateAccFromJoystickPos();
	updatePlayerRotation();
	updatePlayerSpeed();
}

void	ObjectManager::updateGameplaySystem()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		shoot();
}

void	ObjectManager::shoot()
{
	if (!m_player->ShootIfCan())
		return ;
	LOG_INFO("Shoot");
	auto bulletIt = std::find_if(
			m_bullets.begin(),
			m_bullets.end(),
			[] (const Bullet* bullet) {return !bullet->IsAlive();}
		);
	if (bulletIt == m_bullets.end())
	{
		LOG_INFO("No more bullet available");
		return ;
	}
	LOG_INFO("Shoot bullet");
	(*bulletIt)->Shoot(m_playerAngle, m_player->getPosition());
	m_windowManager->SetDrawableVisible((*bulletIt)->GetId());
}

void	ObjectManager::Loop(const sf::Time &time)
{
	LOG_INFO_LOOP1("Update gameplay system");
	updateGameplaySystem();
	LOG_INFO_LOOP1("Update velocity");
	updateVelocity();
	LOG_INFO_LOOP1("Move");
	m_player->Move(time);
	//TODO Maybe a bullets sorted list would have better perf because of the branch predictor
	for (auto& bullet : m_bullets)
	{
		if (bullet->IsAlive())
			bullet->Move(time);
	}
	m_windowManager->SetViewCenter(m_player->GetPosition());
}

//TODO Remake with printf for perf
std::string	ObjectManager::GetPlayerInfo() const
{
	std::stringstream	ss;
	ss << "COORD: " << std::setprecision(2) << m_player->GetPosition().x << "; " << m_player->GetPosition().y << " VEL: " << m_playerSpeed.x << "; " << m_playerSpeed.y << " Acc: " << m_acceleration;
	return ss.str();
}

void	ObjectManager::ResetGameState()
{
	this->initGameState();
}

ObjectManager::~ObjectManager(void) {
	if (m_player != nullptr)
		EntityFactory<Player>::Delete(m_player);
}
