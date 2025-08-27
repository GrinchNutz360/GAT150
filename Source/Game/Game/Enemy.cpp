#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
    /*
    bool playerSeen = false;

	Actor* player = owner->scene->GetActorByName<Actor>("Player");
    if (player) {
        viper::vec2 direction{ 1,0 };
		direction = player->m_transform.position - owner->m_transform.position;
		
        direction = direction.Normalized();
        viper::vec2 forward = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(m_transform.rotation));
        
        float angle = viper::vec2::SignedAngleBetween(forward, direction);
        angle = viper::math::sign(angle);
        m_transform.rotation += viper::math::radToDeg(angle * 5 * dt);

        angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
        playerSeen = angle <= 30;
    }



    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
    //velocity += force * dt;
    auto* rb = owner->GetComponent <viper::RigidBody>();
        if (rb) {
			rb->velocity += force * dt;
        }
    owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;

        //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 0,1,0 });
        viper::Transform transform{ owner->m_transform.position, owner->m_transform.rotation, 2.0f };
        auto rocket = std::make_unique<Actor>(transform); // viper::Resources().Get<viper::Texture>("textures/enemymissile.png", viper::GetEngine().GetRenderer()));
        rocket->speed = 500.0f;
        rocket->tag = "Enemy";
        rocket->name = "Rocket";

        //components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		spriteRenderer->textureName = "textures/enemymissile.png";

        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
    */
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
