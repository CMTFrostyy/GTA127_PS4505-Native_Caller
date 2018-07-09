#include "lib.h"
#include "natives.h"

bool init = false;
int frameCount = 0;

void teleportPlayer(float x, float y, float z) {
	Entity teleportEntity = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(teleportEntity, false)) {
		teleportEntity = PED::GET_VEHICLE_PED_IS_USING(teleportEntity);
	}

	ENTITY::SET_ENTITY_COORDS(teleportEntity, x, y, z, false, false, false, false);
}

extern "C" void _main(void) {
	if (!init) {
		initLibs();
		init = true;
	}

	int newFrameCount = GAMEPLAY::GET_FRAME_COUNT();
	if (newFrameCount > frameCount) {
		frameCount = newFrameCount;

		Player player = PLAYER::PLAYER_ID();
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
		PLAYER::SET_PLAYER_INVINCIBLE(player, true);

		if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_LB) && CONTROLS::IS_CONTROL_JUST_PRESSED(2, INPUT_SCRIPT_RB)) {
			teleportPlayer(-74.94243f, -818.63446f, 326.174347f); // Top of Maze Bank
		}
	}
}