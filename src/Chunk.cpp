#include "main.hpp"

extern TCODRandom * rng;
extern int CHUNK_SIZE;

Chunk::Chunk(int chunk_size, int chunk_x, int chunk_y)
{
    chunkSize = chunk_size;
    chunkX = chunk_x;
    chunkY = chunk_y;
    readyForUnload = false;
    for (int x=0; x < chunkSize; x++)
    {
        for (int y=0; y < chunkSize; y++)
        {
            chunkTiles.push_back(setChunkTile());
        }
    }
    
}

Chunk::~Chunk()
{
}

MapTile Chunk::setChunkTile()
{
    int random = rng->getInt(0,1000);
    MapTile tile;
    if (random > 900)
    {
        tile = TallGrassTile();
    }
    else
    {
        tile = GrassTile();
    }
    return tile;
}

ActiveChunks::ActiveChunks(int size)
{
    activeChunkSize = size;
    for (int i=0; i < activeChunkSize*activeChunkSize; i++)
    {
        activeChunks.push_back(Chunk(CHUNK_SIZE, i%size, i/activeChunkSize));
    }
}

ActiveChunks::~ActiveChunks()
{
}
