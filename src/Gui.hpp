class Gui
{
public:
    Gui();
    ~Gui();
    int screenWidth;
    int screenHeight;
    int infoBarHeight;
    int cameraWidth;
    int cameraHeight;
    int rightPanelWidth;
    bool showRightPanel;
    bool showPauseDisplay;
    GameCamera *camera;
    void drawObject(GameObject, GameCamera);
    void toggleRightPanel();
    void togglePauseDisplay();
    void render();
    //For x, y coordinates returns an index in a linear data structure,
    //e.g. a 1-dimensional vector.
    int squareToLineIndex(int, int, int);
    //Math functions used in coordinate functions
    //(see Gui.cpp for specifics)
    int positiveModulo(int, int);
    int divDown(int, int);
    //Used to obtain the location of a chunk, given a particular set
    //of map coordinates, or of a coordinate on an arbitrary chunk
    //(see Gui.cpp for specifics)
    int toChunkCoords(int);
    int toLocalCoords(int);
    int toActiveCoords(int, int);

protected:
    //Consoles used in the GUI and the functions used to draw them
    TCODConsole *con;
    TCODConsole *game_view;
    TCODConsole *info_bar;
    TCODConsole *right_panel;
    TCODConsole *gui_background;
    void updateInfoBar();
    void updateGuiBackground();
    void updateGameView();
    void updateRightPanel();
};
