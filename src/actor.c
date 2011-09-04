#include "actor.h"

#include "define.h"

#include <stdlib.h>
fActor*
fActor_create() {
	fActor* t_ret = (fActor*) malloc(sizeof(fActor));

	fActor_reset(t_ret);
	return t_ret;
}

const int
fActor_reset(fActor* const a) {
	a->health = 1.0f;
	a->energy = 1.0f;
	a->items = 0;
	a->name = 0;

	return AOK;
}

const int
fActor_setName(fActor* const a, char* n) {
	a->name = n;
	return AOK;
}

const int
fActor_getName(fActor* const a, char** n) {
	*n = a->name;
	return AOK;
}

const int
fActor_setHealth(fActor* const a, float h) {
	a->health = h;
	return AOK;
}

const int
fActor_getHealth(fActor* const a, float* h) {
	*h = a->health;
	return AOK;
}

const int
fActor_setEnergy(fActor* const a, float e) {
	a->energy = e;
	return AOK;
}

const int
fActor_getEnergy(fActor* const a, float* e) {
	*e = a->energy;
	return AOK;
}


