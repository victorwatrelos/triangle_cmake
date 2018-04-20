#pragma once

#include "MathUtils.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cassert>
#include <iostream>
#define	PI2 (2.f * M_PI)

class Angle
{
	public:
		Angle();
		Angle(const sf::Vector2f & direction);
		Angle(const Angle &obj);
		Angle &operator=(const Angle &p);
		virtual ~Angle(void);
		void				SetDegAngle(float angle);
		void				SetRadAngle(float angle);
		void				SetDirection(const sf::Vector2f direction);
		float				GetRadAngle() const;
		float				GetDegAngle() const;
		const sf::Vector2f	&GetDirection() const;
		void				Display(const char *context = nullptr) const;

		Angle& operator+=(float radAngle);
		Angle& operator+=(const Angle& rhs);
		Angle& operator-=(float radAngle);
		Angle& operator-=(const Angle& rhs);
		
	private:
		void			dirFromRad();
		void			degFromRad();

		sf::Vector2f	m_direction;
		float			m_radAngle;
		float			m_degAngle;
};
