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

void TileMap::RandomMapSmart()
{
	ResetMap();
	unsigned int lakeNum = (int)(mWidth*mHeight)/100;
	unsigned int castleNum = (int)(mWidth*mHeight)/25;

	for (unsigned int i = 0; i < castleNum; ++i)
	{
		unsigned int randomX = rand() % mWidth;
		unsigned int randomY = rand() % mHeight;

		while (GetTile(randomX, randomY) != 1 || randomX < 3 || randomX > mWidth - 3 || randomY < 3 || randomY > mHeight - 3)
		{
			randomX = rand() % mWidth;
			randomY = rand() % mHeight;
		}

		if (i < castleNum/8)
		{
			SetTile((randomX - 1) % mWidth, (randomY - 1) % mHeight, 2);	SetTile(randomX, (randomY - 1) % mHeight, 2);	SetTile((randomX + 1) % mWidth, (randomY - 1) % mHeight, 2);	
			SetTile((randomX - 1) % mWidth, randomY, 2);					SetTile(randomX, randomY, 2);					SetTile((randomX + 1) % mWidth, randomY, 2);					
			SetTile((randomX - 1) % mWidth, (randomY + 1) % mHeight, 2);	SetTile(randomX, (randomY + 1) % mHeight, 2);	SetTile((randomX + 1) % mWidth, (randomY + 1) % mHeight, 2);		
		}
		else if (i < castleNum/2)
		{
															SetTile(randomX, (randomY - 1) % mHeight, 2);
			SetTile((randomX - 1) % mWidth, randomY, 2);	SetTile(randomX, randomY, 2);					SetTile((randomX + 1) % mWidth, randomY, 2);	
															SetTile(randomX, (randomY + 1) % mHeight, 2);
		}
		else
		{
			SetTile(randomX, randomY, 2);
		}
	}

	
	for (unsigned int i = 0; i < lakeNum; ++i)
	{
		unsigned int randomX = rand() % mWidth;
		unsigned int randomY = rand() % mHeight;

		while (GetTile(randomX, randomY) != 1 || randomX < 4 || randomX > mWidth - 4 || randomY < 4 || randomY > mHeight - 4)
		{
			randomX = rand() % mWidth;
			randomY = rand() % mHeight;
		}

		SetTile((randomX - 2) % mWidth, (randomY - 2) % mHeight, 3);	SetTile((randomX - 1) % mWidth, (randomY - 2) % mHeight, 3);	SetTile(randomX, (randomY - 2) % mHeight, 3);	SetTile((randomX + 1) % mWidth, (randomY - 2) % mHeight, 3);	SetTile((randomX + 2) % mWidth, (randomY - 2) % mHeight, 3);
		SetTile((randomX - 2) % mWidth, (randomY - 1) % mHeight, 3);	SetTile((randomX - 1) % mWidth, (randomY - 1) % mHeight, 4);	SetTile(randomX, (randomY - 1) % mHeight, 4);	SetTile((randomX + 1) % mWidth, (randomY - 1) % mHeight, 4);	SetTile((randomX + 2) % mWidth, (randomY - 1) % mHeight, 3);
		SetTile((randomX - 2) % mWidth, randomY, 3);					SetTile((randomX - 1) % mWidth, randomY, 4);					SetTile(randomX, randomY, 4);					SetTile((randomX + 1) % mWidth, randomY, 4);					SetTile((randomX + 2) % mWidth, randomY, 3);
		SetTile((randomX - 2) % mWidth, (randomY + 1) % mHeight, 3);	SetTile((randomX - 1) % mWidth, (randomY + 1) % mHeight, 4);	SetTile(randomX, (randomY + 1) % mHeight, 4);	SetTile((randomX + 1) % mWidth, (randomY + 1) % mHeight, 4);	SetTile((randomX + 2) % mWidth, (randomY + 1) % mHeight, 3);
		SetTile((randomX - 2) % mWidth, (randomY + 2) % mHeight, 3);	SetTile((randomX - 1) % mWidth, (randomY + 2) % mHeight, 3);	SetTile(randomX, (randomY + 2) % mHeight, 3);	SetTile((randomX + 1) % mWidth, (randomY + 2) % mHeight, 3);	SetTile((randomX + 2) % mWidth, (randomY + 2) % mHeight, 3);
	}
}