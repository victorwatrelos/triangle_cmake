#pragma once

#include "Entity.hpp"

#define PLAYER_BASE_ROTATION (46.f)

class Player : public Entity
{
	public:
		Player();//TODO remove cpp and put it inline
		bool	ShootIfCan();
	private:
		sf::Clock	lastShoot;
		float		m_minTimeBetweenShootInMs = 100;
};
