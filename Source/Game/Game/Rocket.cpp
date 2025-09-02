#include "../GamePCH.h"
#include "Rocket.h"
#include "Player.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt)
{
    
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
    //velocity = force;
    auto* rb = owner->GetComponent <viper::RigidBody>();
    if (rb) {
        rb->velocity = force ;
    }

    //m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    //m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    
}

void Rocket::OnCollision(viper::Actor* other)
{
    if (owner->tag != other->tag && owner->tag != "Rocket") {
        owner->destroyed = true;
    }
 
}

void Rocket::Read(const viper::json::value_t& value)
{
    Object::Read(value);
	JSON_READ(value, speed);
}
