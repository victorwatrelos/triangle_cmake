#pragma once

#include "Angle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Types.hpp"

class Entity : public sf::Sprite
{
	public:
		Entity(const char *texturePath, float defaultRotation = 0.f);
		Entity(const Entity &obj);
		Entity &operator=(const Entity &p);
		virtual ~Entity();

		void	SetId(U16 id);
		U16		GetId() const {return m_id;}
		void	CenterOrigin();
		void	AddPosition(const sf::Vector2f& pos);
		virtual void	Move(const sf::Time &time);
		void	SetVelocity(const sf::Vector2f &velocity);
		const sf::Vector2f	&GetPosition() const { return this->getPosition(); }
		const Angle			&GetAngle() const { return m_angle; }

		void	setRotation(float degAngle);
	private:
		sf::Texture		m_texture;
		U16				m_id;
		sf::Vector2f	m_velocity;
		float			m_defaultRotation;
		Angle			m_angle;
};
