#ifndef F_ACTOR_H
#define F_ACTOR_H

struct fActor {
	float health;
	float energy;
	struct fItem* items;
	char* name;
	int x, y;
	// id for net?		
};
typedef struct fActor fActor;

fActor*
fActor_create();

const int
fActor_reset(fActor* const);

const int
fActor_setName(fActor* const, char*);

const int
fActor_getName(fActor* const, char**);

const int
fActor_setHealth(fActor* const, float);

const int
fActor_getHealth(fActor* const, float*);

const int
fActor_setEnergy(fActor* const, float);

const int
fActor_getEnergy(fActor* const, float*);

#endif // F_ACTOR_H
