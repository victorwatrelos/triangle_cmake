#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace math
{
	float			magnitude(const sf::Vector2f &vector);
	sf::Vector2f	normalize(const sf::Vector2f &vector);
	sf::Vector2f	normalize(const sf::Vector2f &vector, float mag);
}
