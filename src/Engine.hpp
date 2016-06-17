//Game engine class handles general game operations, manages initialization
//of the game world. GUI, player actions, and individual object interactions
//are handled seperately in their respective classes.
class Engine 
{
public:
    Engine();
    ~Engine();
    bool is_paused;
    void update();
    void handleKeys();
    void handleActionKey(int ascii);
    ActiveChunks *activeChunks;
    Gui *gui;
    PlayerObject *player;
    TCOD_key_t lastKey;
};

extern Engine engine;
