#include "Game/SpaceGame.h"
//#define JSON_READ(value, data) viper::json::Read(value, #data, data)

//class A {
//public:
//    A() = default;
//    A(int size) : size{ size } {
//		buffer = new int[size];
//        for (int i = 0; i < size; i++) buffer[i] = i;
//    }
//	A(const A& other) : 
//        size{ other.size }
//    {
//        buffer = new int [other.size];
//        for (int i = 0; i < size; i++) buffer[i] = i;
//    }
//    A& operator = (const A& other) {
//        size = other.size*2;
//		buffer = other.buffer;
//        return *this;
//    }
//    ~A() = default;
//public:
//    int size{ 0 };
//	int* buffer{ nullptr };
//};

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets");
    std::cout << viper::file::GetCurrentDirectory() << std::endl;

 //   A a1{ 4 };
 //   std::cout << a1.size << std::endl;
	//std::cout << a1.buffer[2] << std::endl;

	//A a2{ a1 };// copy constructor

 //   a1.buffer[2] = 45;

 //   std:: cout << a2.size << std::endl;
	//std::cout << a2.buffer[2] << std::endl;


 //   A a3;
 //   a3 = a1; //assignment operator
 //   std:: cout << a3.size << std::endl;

 //   return 0;

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