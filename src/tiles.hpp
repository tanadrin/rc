
#include <vector>
#include <string>

//Generic class from which all tile types must inherit
class MapTile
{
public:
    MapTile();
    ~MapTile();
    bool isBlocked;
    std::vector<int> variations;
    int character;
    TCODColor color;
    std::string name;
    bool isAnimated;
    int setVariation();
};

class GrassTile: public MapTile
{
public:
    GrassTile();
    ~GrassTile();
};

class DirtTile: public MapTile
{
public:
    DirtTile();
    ~DirtTile();
};

class TallGrassTile: public MapTile
{
public:
    TallGrassTile();
    ~TallGrassTile();
};
