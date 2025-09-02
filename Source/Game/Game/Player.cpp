#include "../GamePCH.h"
#include "Player.h"
#include "GameData.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{

	viper::Particle particle;
	particle.position = owner->m_transform.position;
	particle.velocity = viper::vec2{ viper::random::getReal(-200.0f, 200.0f), viper::random::getReal(-200.0f, 200.0f) };
	particle.color = viper::vec3{ 1,1,1 };
	particle.lifeSpan = 2;
	//viper::GetEngine().GetPS().AddParticle(particle);

	//rotation
	float rotate = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	owner->m_transform.rotation += (rotate * rotationRate) * dt;

	//thrust
	float thrust = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Z) && viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +3;


	viper::vec2 direction{ 1,0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * thrust * speed;
	//velocity += force * dt;
	
	auto* rb = owner->GetComponent <viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}
	else {
		viper::Logger::Warning("Player has no rigidbody");
	}

	owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());

	//check fire key pressed
	//spawn rocket at player position and rotation
	fireTimer -= dt;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
		fireTimer = fireTime;
		viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("laserShoot.wav", viper::GetEngine().GetAudio()).get());


		viper::Transform transform{ owner->m_transform.position, owner->m_transform.rotation, 2.0f };
		auto rocket = viper::Instantiate("rocket", transform);
		rocket->tag = "player";
		owner->scene->AddActor(std::move(rocket));
	}

		//////fire machine gun
		//if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_C)) {

		//    //viper::GetEngine().GetAudio().PlaySound("machineGun");
		//    viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("machineGun.wav", viper::GetEngine().GetAudio()).get());

		//    //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 157,0,255 });
		//    viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
		//    auto rocket = std::make_unique<Rocket>(transform);// viper::Resources().Get<viper::Texture>("textures/machinegun.png", viper::GetEngine().GetRenderer()));
		//    //auto rocket = std::make_unique<Rocket>(transform, model);
		//    rocket->speed = 1500.0f;
		//    rocket->tag = "Player";
		//    rocket->name = "Rocket";

		//    auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		//    spriteRenderer->textureName = "textures/machinegun.png";
		//    rocket->AddComponent(std::move(spriteRenderer));
		//    auto rb = std::make_unique<viper::RigidBody>();
		//    rocket->AddComponent(std::move(rb));

		//    auto collider = std::make_unique<viper::CircleCollider2D>();
		//    collider->radius = 10;
		//    rocket->AddComponent(std::move(collider));

		//    scene->AddActor(std::move(rocket));

		//}

		//////fire shotgun
		//fireTimer -= dt;
		//if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_V) && fireTimer <= 0) {
		//    fireTimer = fireTime;
		//   // std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 1,0,0 });
		//   // viper::GetEngine().GetAudio().PlaySound("shotGun");
		//    viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("shotGun.wav", viper::GetEngine().GetAudio()).get());

		//    //viper::Transform transform{ this->m_transform.position, viper::random::getReal(this->m_transform.rotation + 20.0f, this->m_transform.rotation -20.0f), 2.0f};
		//    for (int i = 0; i < 10; i++) {
		//        // Assume you have some base rotation:
		//        float baseRotation = this->m_transform.rotation;

		//        // Add random spread, e.g., ±15 degrees
		//        float spread = viper::random::getReal(-15.0f, 15.0f);

		//        float newRotation = baseRotation + spread;

		//        viper::Transform transform{
		//            this->m_transform.position,
		//            newRotation,
		//            2.0f
		//        };

		//        //auto rocket = std::make_unique<Rocket>(transform, model);
		//        auto rocket = std::make_unique<Rocket>(transform);// viper::Resources().Get<viper::Texture>("textures/shotgun.png", viper::GetEngine().GetRenderer()));
		//        rocket->speed = 1500.0f;
		//        rocket->tag = "Player";
		//        rocket->name = "Rocket";
		//        fireTimer = 3;
		//        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		//        spriteRenderer->textureName = "textures/shotgun.png";
		//        rocket->AddComponent(std::move(spriteRenderer));
		//        auto rb = std::make_unique<viper::RigidBody>();

		//        rocket->AddComponent(std::move(rb));

		//        auto collider = std::make_unique<viper::CircleCollider2D>();
		//        collider->radius = 10;
		//        rocket->AddComponent(std::move(collider));

		//        scene->AddActor(std::move(rocket));


		//    }
		//}

		//////explosive
		//fireTimer -= dt;
		//if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_O)&& viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_P)) {
		//    //viper::GetEngine().GetAudio().PlaySound("nuke");
		//    viper::GetEngine().GetAudio().PlaySound(*viper::Resources().Get<viper::AudioClip>("nuke.wav", viper::GetEngine().GetAudio()).get());

		//    //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::rocketPoints, viper::vec3{ 255, 165, 0 });
		//    viper::Transform transform{ this->m_transform.position, this->m_transform.rotation, 55.0f };
		//    //auto rocket = std::make_unique<Rocket>(transform, model);
		//    auto rocket = std::make_unique<Rocket>(transform);// viper::Resources().Get<viper::Texture>("textures/op.png", viper::GetEngine().GetRenderer()));
		//    rocket->speed = 1500.0f;
		//    rocket->tag = "Rocket";
		//    rocket->name = "Rocket";
		//    auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		//    spriteRenderer->textureName = "textures/op.png";
		//    rocket->AddComponent(std::move(spriteRenderer));
		//    auto rb = std::make_unique<viper::RigidBody>();

		//    rocket->AddComponent(std::move(rb));

		//    auto collider = std::make_unique<viper::CircleCollider2D>();
		//    collider->radius = 1000;
		//    rocket->AddComponent(std::move(collider));

		//    scene->AddActor(std::move(rocket));
		//}    
}

void Player::OnCollision(viper::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
	}
}

void Player::Read(const viper::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, rotationRate);
	JSON_READ(value, fireTime);


}
