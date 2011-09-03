#include "scene.h"

#include "define.h"

#include <stdio.h>

fScene*
fScene_create() {
	fScene* t_ret = (fScene*) malloc(sizeof(fScene));

	fScene_reset(t_ret);
	return t_ret;
}

int
fScene_reset(fScene* s) {
	s->state = SETUP;
	s->actors = 0;
	s->map = 0;
	s->setup = 0;
	s->update = 0;
	s->teardown = 0;
	s->draw = 0;
	s->input = 0;

	return AOK;
}

int
fScene_update(fScene* s) {
	switch (s->state) {
	case SETUP: return s->setup(s); break;
	case UPDATE: return s->update(s); break;
	case TEARDOWN: return s->teardown(s); break;
	}

	return AOK;
}

int
fScene_draw(fScene* s) {
	if (s->draw) return s->draw(s);
 		
	return AOK;
}

int
fScene_input(fScene* s) {
	if (s->input) return s->input(s);
 		
	return AOK;
}
