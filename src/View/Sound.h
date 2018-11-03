#include <string>
#include <iostream>
#include "../Common/Thread.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

// g++ -Wall -Werror -std=c++11 Sound.cpp SdlException.cpp -lSDL2 -lSDL2_mixer -o sound-test

class Sound : public Thread {
public:
    explicit Sound(const std::string &filename);
    ~Sound();
    void run() override;
private:
    const std::string& filename;
    Mix_Music* music;
};

/*int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " <sound-file>" << std::endl;
    } else {
        Sound background(argv[1]);
        background.play();
    }
    return 0;
}*/