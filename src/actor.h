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

void
fActor_setName(fActor*, char*);

char*
fActor_getName(fActor*);

void
fActor_setHealth(fActor*, float);

float
fActor_getHealth(fActor*);

void
fActor_setEnergy(fActor*, float);

float
fActor_getEnergy(fActor* c) { return c->energy; } 

#endif // F_ACTOR_H
