#pragma once

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void update(float deltaTime);

	inline int getUpdateOrder()const;

private:
	Actor* m_Owner;
	int m_UpdateOrder;
};

inline int Component::getUpdateOrder() const
{
	return this->m_UpdateOrder;
}