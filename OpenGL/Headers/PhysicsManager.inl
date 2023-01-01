#include "PhysicManager.hpp"

template<class T,class I>
void Physics::PhysicsManager::TestCollider(Physics::Collider& a,Physics::Collider& b)
{
	if (typeid(a) == typeid(T) && typeid(b) == typeid(I))
	{
		T* aCast = dynamic_cast<T*>(&a);
		I* bCast = dynamic_cast<I*>(&b);
		if (TestCollision<T,I>(*aCast,*bCast))
		{
			a.SetCollide(true);
			b.SetCollide(true);
		}
		return;
	}
	if (typeid(a) == typeid(I) && typeid(b) == typeid(T))
	{
		I* aCast = dynamic_cast<I*>(&a);
		T* bCast = dynamic_cast<T*>(&b);
		if (TestCollision<I,T>(*aCast,*bCast))
		{
			a.SetCollide(true);
			b.SetCollide(true);
		}
		return;
	}

}
