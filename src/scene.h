#ifndef F_SCENE_H
#define F_SCENE_H

#include <SFML/Graphics.h>

// Scene states
enum fScene_state {
	SETUP,
	UPDATE,
	TEARDOWN,
	DONE
};

typedef enum fScene_state fScene_state;

struct fScene {
	fScene_state state;
	struct fActor** actors;
	int player_pos;
	struct fMap* map;

	// Functions
	int (*setup)(struct fScene*);
	int (*update)(struct fScene*);
	int (*teardown)(struct fScene*);
	int (*draw)(struct fScene*);
	int (*input)(struct fScene*);
	
};

typedef struct fScene fScene;

fScene*
fScene_create();

int
fScene_reset(fScene* s);

int
fScene_setup(fScene* s);

int
fScene_update(fScene* s);

int
fScene_teardown(fScene* s);

int
fScene_draw(fScene* s);

int
fScene_input(fScene* s);

int
fScene_setMap(fScene* s, struct fMap* m);

int
fScene_addActor(fScene* s, struct fActor* a);
#endif // F_SCENE_H
