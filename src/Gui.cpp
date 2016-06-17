#include "main.hpp"
#include <string>

//Parameters for the size of the GUI elements
static const int SCREEN_WIDTH = 160;
static const int SCREEN_HEIGHT = 80;
static       int INFO_BAR_HEIGHT = 1;
static       int CAMERA_WIDTH = SCREEN_WIDTH-2;
static       int CAMERA_HEIGHT = SCREEN_HEIGHT-INFO_BAR_HEIGHT-3;
static       int RIGHT_PANEL_WIDTH = SCREEN_WIDTH/4-10;
extern int CHUNK_SIZE;
extern int ACTIVE_CHUNK_SIZE;

Gui::Gui()
{
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    infoBarHeight = INFO_BAR_HEIGHT;
    cameraWidth = CAMERA_WIDTH;
    cameraHeight = CAMERA_HEIGHT;
    rightPanelWidth = RIGHT_PANEL_WIDTH;

    showRightPanel = false;
    showPauseDisplay = false;

    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT,"Migration Age",false);
    con = new TCODConsole(screenWidth, screenHeight);
    game_view = new TCODConsole(cameraWidth, cameraHeight);
    info_bar = new TCODConsole(cameraWidth, infoBarHeight);
    right_panel = new TCODConsole(rightPanelWidth, screenHeight-2);
    gui_background = new TCODConsole(screenWidth, screenHeight);
    
    camera = new GameCamera(0,0);
}

Gui::~Gui()
{
    delete con;
    delete game_view;
    delete info_bar;
    delete right_panel;
    delete gui_background;
}

//Method for drawing objects in the game world on the game view
void Gui::drawObject(GameObject drawnObject, GameCamera targetCamera)
{
    int cameraX = drawnObject.posX - targetCamera.posX + cameraWidth/2;
    int cameraY = drawnObject.posY - targetCamera.posY + cameraHeight/2;
    if ((cameraX >= 0 && cameraX <= cameraWidth) && (cameraY >= 0 && cameraY <= cameraHeight))
        {
            game_view->putChar(cameraX, cameraY, drawnObject.character);
            game_view->setCharForeground(cameraX, cameraY, drawnObject.color);
        }
}

void Gui::updateInfoBar()
{
    info_bar->setDefaultBackground(TCODColor::black);
    info_bar->clear();
}

void Gui::updateGuiBackground()
{
    gui_background->setDefaultBackground(TCODColor::copper);
    gui_background->clear();
    if (showPauseDisplay == true)
    {
        std::string pause_text = "***PAUSED***";
        int len = pause_text.size();
        for (int i = 0; i < len; ++i)
        {
            gui_background->putChar(cameraWidth-20+i, 0, pause_text[i]);
            gui_background->setCharBackground(cameraWidth-20+i, 0, TCODColor::blue);
            gui_background->setCharForeground(cameraWidth-20+i, 0, TCODColor::yellow);
        }
    }
}

void Gui::updateGameView()
{
    game_view->setDefaultBackground(TCODColor::black);
    game_view->clear();
    for (int x=0; x < cameraWidth; x++)
    {
        for (int y=0; y < cameraHeight; y++)
        {
            int map_x = camera->posX+x-cameraWidth/2;
            int map_y = camera->posY+y-cameraHeight/2;
            int local_x = toLocalCoords(map_x);
            int local_y = toLocalCoords(map_y);
            int active_x = toActiveCoords(map_x, 'x');
            int active_y = toActiveCoords(map_y, 'y');
            int idx_a = squareToLineIndex(active_x, active_y, ACTIVE_CHUNK_SIZE);
            int idx_b = squareToLineIndex(local_x, local_y, CHUNK_SIZE);         
            game_view->putChar(x, y, engine.activeChunks->activeChunks[idx_a].chunkTiles[idx_b].character);      
            game_view->setCharForeground(x, y, engine.activeChunks->activeChunks[idx_a].chunkTiles[idx_b].color);
        }
    }   
    drawObject(*engine.player, *camera);
}

void Gui::updateRightPanel()
{
    right_panel->setDefaultBackground(TCODColor::black);
    right_panel->clear();
}

void Gui::toggleRightPanel()
{
    if (showRightPanel == false)
    {
        showRightPanel = true;
        cameraWidth = cameraWidth - rightPanelWidth-1;
    }
    else
    {
        showRightPanel = false;
        cameraWidth = cameraWidth + rightPanelWidth+1;
    }
}

void Gui::togglePauseDisplay()
{
    if (showPauseDisplay == false)
    {
        showPauseDisplay = true;
    }
    else
    {
        showPauseDisplay = false;
    }
}

void Gui::render()
{
    TCODConsole::root->clear();
    con->setDefaultBackground(TCODColor::black);
    con->clear();
    TCODConsole::blit(con,0,0,screenWidth,screenHeight,
                      TCODConsole::root,0,0);
    this->updateGuiBackground();
    TCODConsole::blit(gui_background,0,0,screenWidth,screenHeight,
                      TCODConsole::root,0,0);
    this->updateGameView();
    TCODConsole::blit(game_view,0,0,cameraWidth,cameraHeight,
                      TCODConsole::root,1,1);
    this->updateInfoBar();
    TCODConsole::blit(info_bar,0,0,cameraWidth,infoBarHeight,
                      TCODConsole::root,1,screenHeight-2);
    if ( showRightPanel == true )
    {
        this->updateRightPanel();
        TCODConsole::blit(right_panel,0,0,rightPanelWidth,screenHeight-2,
                          TCODConsole::root,screenWidth-rightPanelWidth-1,1);
    }
}

//Modulus operation that always returns positive result (e.g., -5%4 = 1)
int Gui::positiveModulo(int i, int n)
{
    return (i % n + n) % n;
}

//Division rounding down, instead of toward zero; i is numerator, n
//is denominator.
int Gui::divDown(int i, int n)
{
    if (i>=0) { return i/n; }
    else { return (i/n)-1; }
}

//Takes a map coordinate (x or y) and returns the x or y coordinate of
//the chunk it lies on, with respect to the whole map
int Gui::toChunkCoords(int map_i)
{
    return divDown(map_i, CHUNK_SIZE);
}

//Takes a map coordinate (x or y) and returns its coordinate on the
//chunk that it lies on
int Gui::toLocalCoords(int map_i)
{
    return positiveModulo(map_i, CHUNK_SIZE);
}

//Takes a map coordinate (x or y) and the coordinate axis ('x' or 'y'
//as ASCII characters) as arguments; returns which active chunk the 
//coordinate lies on.
int Gui::toActiveCoords(int map_i, int xy)
{
    if (xy == 'x') { return toChunkCoords(map_i)-toChunkCoords(0)+ACTIVE_CHUNK_SIZE/2; }
    else { return toChunkCoords(map_i)-toChunkCoords(0)+ACTIVE_CHUNK_SIZE/2; }
}

//Takes (x, y) coordinates and returns an index i on the corresponding
//1-dimensional vector or array.
int Gui::squareToLineIndex(int x, int y, int grid_size)
{
    return x+y*grid_size;
}
