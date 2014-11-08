#ifndef _TILEMAP_H
#define _TILEMAP_H

class TileMap
{
public: 
	TileMap(unsigned int x, unsigned int y);

	void SetTile(unsigned int x, unsigned int y, unsigned int value);
	void IncrementTile(unsigned int x, unsigned int y);
	void ModTile(unsigned int x, unsigned int y, unsigned int mod);
	unsigned int GetTile(unsigned int x, unsigned int y);
	void ResetMap();
	void NoBorder();
	void RandomMap(unsigned int range);
	
protected:
	unsigned int* mMap;
	unsigned int mWidth;
	unsigned int mHeight;

};

#endif