#pragma once

class WindowManagerBase;

class ObjectManagerBase
{
	public:
		virtual void	Loop(const sf::Time &time) = 0;
		virtual void	Init(WindowManagerBase *window) = 0;
		virtual void	JoystickMoved() = 0;
		virtual std::string	GetPlayerInfo() const = 0;
		virtual void	ResetGameState() = 0;
};
