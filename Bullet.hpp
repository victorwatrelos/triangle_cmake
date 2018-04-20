#pragma once

#include "Entity.hpp"

class Bullet : public Entity
{
	public:
		Bullet();
		bool	IsAlive() const {return m_isAlive;}
		void	Shoot(const Angle& angle, const sf::Vector2f& pos);
		virtual void Move(const sf::Time& time) override {
			Entity::Move(time);
		}
	private:
		bool	m_isAlive = false;
		int32_t	m_id = -1;
};
