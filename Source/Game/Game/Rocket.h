#pragma once
#include "Framework/Component.h"



class Rocket : public viper::Component {
public:
	float speed = 200;
public:
	Rocket() = default;

	void Update(float dt) override;

	// Inherited via Actor
	void OnCollision(class viper::Actor* other) ;

};