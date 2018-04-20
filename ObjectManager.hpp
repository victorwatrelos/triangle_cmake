#pragma once

#include "Angle.hpp"
#include "Entity.hpp"
#include "ObjectManagerBase.hpp"
#include "WindowManagerBase.hpp"
#include "Types.hpp"
#include "MathUtils.hpp"
#include "EntityFactory.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <cmath>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <array>

#define EPSILON (0.1f)

#define DEG_TO_RADIAN(deg) (deg / static_cast<float>(M_PI) * 180.f)
#define RAD_TO_DEG(rad) (rad * 57.2958f)

class ObjectManager : public ObjectManagerBase
{
	public:
		static constexpr size_t MAX_NB_BULLET = 1024;
		ObjectManager();
		virtual ~ObjectManager(void);
		ObjectManager(const ObjectManager &obj) = delete;
		ObjectManager &operator=(const ObjectManager &p) = delete;

		void	Loop(const sf::Time &time) override;
		void	Init(WindowManagerBase *window) override;
		void	JoystickMoved() override;
		void	Stop();
		std::string	GetPlayerInfo() const override;
		void	ResetGameState() override;
	private:
		void	updateVelocity();//TODO optimized by only calling when update
		void	updateAccFromJoystickPos();
		void	updatePlayerSpeed();
		void	updatePlayerRotation();
		void	updateGameplaySystem();
		void	initGameState();
		void	shoot();

		WindowManagerBase			*m_windowManager;
		std::atomic<bool>			m_running;
		Player						*m_player = nullptr;
		sf::Vector2f				m_playerSpeed;
		float						m_acceleration;
		Angle						m_playerAngle;
		sf::Vertex 					line[2];
		sf::VertexArray				triangle;
		sf::VertexArray				triangle2;
		std::array<Bullet*, MAX_NB_BULLET>	m_bullets;
};
