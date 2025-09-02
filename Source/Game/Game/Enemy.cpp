#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start()
{
	m_rigidBody = owner->GetComponent<viper::RigidBody>();
	fireTimer = fireTime;
}

void Enemy::Update(float dt)
{
    bool playerSeen = false;

	auto player = owner->scene->GetActorByName<viper::Actor>("Player");
    if (player) {
        viper::vec2 direction{ 1,0 };
		direction = player->m_transform.position - owner->m_transform.position;
		
        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation));
        
        float angle = viper::vec2::SignedAngleBetween(forward, direction);
        angle = viper::math::sign(angle);
        owner->m_transform.rotation += viper::math::radToDeg(angle * 5 * dt);

        angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;
    }



    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
    //velocity += force * dt;
        if (m_rigidBody) {
			m_rigidBody->velocity += force * dt;
        }
    owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 0,1,0 });
        viper::Transform transform{ owner->m_transform.position, owner->m_transform.rotation, 2.0f };
        auto rocket = viper::Instantiate("rocket", transform); // viper::Resources().Get<viper::Texture>("textures/enemymissile.png", viper::GetEngine().GetRenderer()));
        //rocket->speed = 500.0f;
        rocket->tag = "enemy";

        owner->scene->AddActor(std::move(rocket));
    }
    
}

void Enemy::OnCollision(viper::Actor* other)
{
    if (owner->tag != other->tag) {
        owner->destroyed = true;
		owner->scene->GetGame()->AddPoints(100);
        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = owner->m_transform.position;
            particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = viper::vec3{ 1,0.54901960784f,0.0f };
            particle.lifeSpan = 2;
            viper::GetEngine().GetPS().AddParticle(particle);
        }
       
    }
}

void Enemy::Read(const viper::json::value_t& value)
{
    Object::Read(value);
    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
	fireTimer = fireTime;
}
