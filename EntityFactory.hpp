#pragma once

#include "Entity.hpp"

//Template factory to prepare memory pool
template <class T>
class EntityFactory
{
	public:
		template<typename... Args>
		static T*	Create(Args... args)
		{
			std::cout << "Create entity" << std::endl << std::flush;
			return new T(args...);
		}

		static void	Delete(T* entity)
		{
			delete entity;
		}
	private:
};
