#include "LoLProcess/LoLProcess.h"

int main()
{
	LoLProcess *LoL = LoLProcess_new ();

	printf("x = %f / y = %f\n", LoL->hud->camPos.x, LoL->hud->camPos.y);


    return 0;
}
