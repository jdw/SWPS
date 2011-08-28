#include "actor.h"

#include "define.h"

fActor*
fActor_create() {
	fActor* t_ret = (fActor*) malloc(sizeof(fActor));

	fActor_reset(t_ret);
	return t_ret;
}

int
fActor_reset(fActor* a) {
	a->health = 1.0f;
	a->energy = 1.0f;
	a->items = 0;
	a->name = 0;

	return AOK;
}

int
fActor_setName(fActor* a, char* n) {
	a->name = n;
	return AOK;
}

int
fActor_getName(fActor* a, char** n) {
	*n = a->name;
	return AOK;
}

int
fActor_setHealth(fActor* a, float h) {
	a->health = h;
	return AOK;
}

int
fActor_getHealth(fActor* a, float* h) {
	*h = a->health;
	return AOK;
}

int
fActor_setEnergy(fActor* a, float e) {
	a->energy = e;
	return AOK;
}

int
fActor_getEnergy(fActor* a, float* e) {
	*e = a->energy;
	return AOK;
}


