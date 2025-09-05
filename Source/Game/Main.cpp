#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"
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
    viper::file::SetCurrentDirectory("Assets/Platformer");
    std::cout << viper::file::GetCurrentDirectory() << std::endl;

	//initialize engine
	viper::GetEngine().Initialize();
	

    //initialize game
    std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();
	game->Initialize();
    
    SDL_Event e;
    bool quit = false;
    
    //float rotate = 0;
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

        viper::GetEngine().GetRenderer().Present();
    }
   
	game->Shutdown();
    game.release();
	viper::GetEngine().Shutdown();

    return 0;
}