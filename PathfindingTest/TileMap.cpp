#include "TileMap.h"
#include <stdlib.h>

TileMap::TileMap(unsigned int x, unsigned int y)
{
	mMap = new unsigned int[x*y];
	mWidth = x;
	mHeight = y;
	ResetMap();
}

	
void TileMap::SetTile(unsigned int x, unsigned int y, unsigned int value)
{
	if (x < mWidth && y < mHeight)
	{
		mMap[y*mWidth + x] = value;
	}
}

void TileMap::IncrementTile(unsigned int x, unsigned int y)
{
	if (x < mWidth && y < mHeight)
	{
		mMap[y*mWidth + x]++;
	}
}
	
void TileMap::ModTile(unsigned int x, unsigned int y, unsigned int mod)
{
	if (x < mWidth && y < mHeight)
	{
		mMap[y*mWidth + x] %= mod;
	}
}

unsigned int TileMap::GetTile(unsigned int x, unsigned int y)
{
	if (x < mWidth && y < mHeight)
	{
		return mMap[y*mWidth + x];
	}

	return 0;
}

void TileMap::ResetMap()
{
	for ( unsigned int i = 0; i < mWidth; ++i)
	{
		for ( unsigned int j = 0; j < mHeight; ++j)
		{
			if (j == 0 || j == mHeight - 1 || i == 0 || i == mWidth - 1)
			{
				SetTile(i, j, 0);
			}
			else
			{
				SetTile(i, j, 1);
			}
		}
	}
}

void TileMap::NoBorder()
{
	for ( unsigned int i = 0; i < mWidth; ++i)
	{
		for ( unsigned int j = 0; j < mHeight; ++j)
		{
			SetTile(i, j, 1);
		}
	}
}

void TileMap::RandomMap(unsigned int range)
{
	for ( unsigned int i = 0; i < mWidth; ++i)
	{
		for ( unsigned int j = 0; j < mHeight; ++j)
		{
			unsigned int random = rand() % range;
			SetTile(i, j, random);
		}
	}
}