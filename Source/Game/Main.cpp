#include "Game/SpaceGame.h"
//#define JSON_READ(value, data) viper::json::Read(value, #data, data)

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets");

    std::cout << viper::file::GetCurrentDirectory() << std::endl;

    //auto spriteRenderer = viper::Factory::Instance().Create("SpriteRenderer");
   // spriteRenderer->name = "Steve";

   // return 0;

	//initialize engine
	viper::GetEngine().Initialize();
	

    //initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();
    
    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }



	//iniialize sounds
	viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
	viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
	viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");
	viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
	viper::GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    //viper::GetEngine().GetAudio().AddSound("laserShoot.wav", "laser");
    //viper::GetEngine().GetAudio().AddSound("machineGun.wav", "machineGun");
    //viper::GetEngine().GetAudio().AddSound("shotGun.wav", "shotGun");
    //viper::GetEngine().GetAudio().AddSound("nuke.wav", "nuke");
    
    
    float rotate = 0;
    //MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		viper::GetEngine().Update();
		game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
        }

        //draw
        viper::vec3 color{ 0,0,0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

		game->Draw(viper::GetEngine().GetRenderer());
        rotate += 90 * viper::GetEngine().GetTime().GetDeltaTime();
       

        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
			star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(256), viper::random::getInt(256), viper::random::getInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        for(int i = 0; i < stars.size(); i++)

            viper::GetEngine().GetRenderer().Present();
    }
   
	game->Shutdown();
    game.release();
	viper::GetEngine().Shutdown();

        return 0;
}