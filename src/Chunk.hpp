//Chunk object stores a region of map data; chunks are stiched together to
//create the visible portion of the in-game map using an ActiveChunks object.
class Chunk
{
public:
    Chunk(int, int, int);
    ~Chunk();
    int chunkSize;
    int chunkX;
    int chunkY;
    bool readyForUnload;
    std::vector<MapTile> chunkTiles;
    std::vector<GameObject> chunkObjects;
    MapTile setChunkTile();
};

class ActiveChunks
{
public:
    ActiveChunks(int);
    ~ActiveChunks();
    int activeChunkSize;
    std::vector<Chunk> activeChunks;
};
