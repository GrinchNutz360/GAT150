#include "CircleCollider2D.h"

namespace viper {
    FACTORY_REGISTER(CircleCollider2D)
    void CircleCollider2D::Update(float dt)
    {
        //
    }

    bool CircleCollider2D::CheckCollision(ColliderComponent& other)
    {
        float distance = (owner->m_transform.position - other.owner->m_transform.position).Length();
        
		//check circle to circle collision
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
        if (circleCollider) {
            float radii = radius + circleCollider->radius;
            if (distance <= radii) return true;
        }

        //float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();
        //if (distance <= actorA->GetRadius() + actorB->GetRadius()) {


        return false;
    }
}