#include "MathUtils.hpp"

namespace math
{
	float			magnitude(const sf::Vector2f &vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	sf::Vector2f	normalize(const sf::Vector2f &vector)
	{
		float mag = magnitude(vector);
		return normalize(vector, mag);
	}

	sf::Vector2f	normalize(const sf::Vector2f &vector, float mag)
	{
		return {vector.x / mag, vector.y / mag};
	}
}
