#ifndef F_DEFINE_H
#define F_DEFINE_H

typedef enum {
	AOK,
	// Exit reasons for program
	NO_DEBUG_FONT,
	FAILED_VIDEO_MODE,
	FAILED_LOADING_FONT_FILE,
	// Reason why a tile could be blocked
	TILE_BLOCKED_ITEM,
	TILE_BLOCKED_ACTOR,
	TILE_BLOCKED_TYPE,
	// Map
	MAP_POS_X_OUTSIDE,
	MAP_POS_Y_OUTSIDE
} F_EXIT;

#endif // F_DEFINE_H
