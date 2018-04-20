#include "Player.hpp"

Player::Player()
	: Entity("textures/triangle-green-double.png", PLAYER_BASE_ROTATION)
{
}

bool	Player::ShootIfCan()
{
	if (lastShoot.getElapsedTime().asMilliseconds() < m_minTimeBetweenShootInMs)
		return false;
	lastShoot.restart();
	return true;
}
