#include "Entity.hpp"

Entity::Entity(const char *texturePath, float defaultRotation)
	: m_velocity(0.f, 0.f)
	, m_defaultRotation(defaultRotation)
	, m_angle()
{
	if (!this->m_texture.loadFromFile(texturePath))
	{
		std::cerr << "Unable to load texture " << texturePath << std::endl;
	}
	m_texture.setSmooth(true);
	this->setTexture(m_texture);
	m_angle.SetDegAngle(defaultRotation);
}

Entity::Entity(const Entity &obj) {
	*this = obj;
}

Entity::~Entity(void) {

}

void		Entity::setRotation(float degAngle)
{
	sf::Sprite::setRotation(degAngle + m_defaultRotation);
}

Entity    &Entity::operator=(const Entity &p) {
	this->m_texture = p.m_texture;
	sf::Sprite::operator=(p);
	return *this;
}

void		Entity::SetId(U16 id)
{
	this->m_id = id;
}

void		Entity::CenterOrigin()
{
	auto size = m_texture.getSize();
	this->setOrigin(size.x / 2.f, size.y / 2.f);
}

void		Entity::AddPosition(const sf::Vector2f& pos)//To remove
{
	this->setPosition(this->getPosition() + pos);
}

void		Entity::SetVelocity(const sf::Vector2f &velocity)
{
	this->m_velocity = velocity;
}

void		Entity::Move(const sf::Time &time)
{
	sf::Vector2f	currentPosition = this->getPosition();
	this->setPosition((time.asSeconds() * m_velocity) + currentPosition);
}
