#include <string>

extern Engine engine;
extern int ACTIVE_CHUNK_SIZE;

//GameCamera is the point from which the view in the game_view console
//is drawn.
class GameCamera
{
public:
    GameCamera(int, int);
    ~GameCamera();
    int posX;
    int posY;
    void refreshPosition(int, int);
};

//Generic actor class from which other actors are derived.
class GameObject
{
public:
    GameObject(int, int);
    ~GameObject();
    int posX;
    int posY;
    int character;
    TCODColor color;
    std::string name;
    AI *ai;
    void move(int, int);
};

class PlayerObject: public GameObject
{
public:
    PlayerObject(int x, int y): GameObject(0, 0)
    {
        posX = x; 
        posY = y; 
        name = "@Player"; 
        color = TCODColor::white;
    };
    ~PlayerObject();
};
