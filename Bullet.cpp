#include "Bullet.hpp"

Bullet::Bullet()
	: Entity("textures/bullet.png", 0.f)
{

}

void	Bullet::Shoot(const Angle& angle, const sf::Vector2f& pos)
{
	this->m_isAlive = true;
	this->SetVelocity(angle.GetDirection() * 100.f);
	//TODO Fix this shit
	this->setPosition(pos + sf::Vector2f({0.f, -44.f}) + (angle.GetDirection() * 30.f));
}
