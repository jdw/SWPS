#ifndef F_ACTOR_H
#define F_ACTOR_H

struct fActor {
	float health;
	float energy;
	struct fItem* items;
	char* name;		
};

typedef struct fActor fActor;

fActor*
fActor_create();

int
fActor_reset(fActor*);

int
fActor_setName(fActor*, char*);

int
fActor_getName(fActor*, char**);

int
fActor_setHealth(fActor*, float);

int
fActor_getHealth(fActor*, float*);

int
fActor_setEnergy(fActor*, float);

int
fActor_getEnergy(fActor*, float*);

#endif // F_ACTOR_H
