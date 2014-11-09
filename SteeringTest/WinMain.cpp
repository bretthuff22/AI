#include <HAIL.h>
#include <SGE.h>
using namespace SGE;

#include "Pikachu.h"

SGE_Cursor cursor;
Pikachu pikachu;

void SGE_Initialize()
{
	cursor.Load("carrot.png");	
	pikachu.Load();
}

void SGE_Terminate()
{
	cursor.Unload();
	pikachu.Unload();
}
	
bool SGE_Update(float deltaTime)
{
	cursor.Update(deltaTime);

	// follow the carrot
	return Input_IsKeyPressed(Keys::ESCAPE);
}

void SGE_Render()
{
	cursor.Render();
	pikachu.Render();
}