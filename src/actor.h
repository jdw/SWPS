#ifndef F_CHARACTER_H
#define F_CHARACTER_H

//struct sfRenderWindow;
//#include <SFML/Graphics.h>


typedef struct {
	float health;
	float energy;
	struct fItem* items;
	char* name;		
} fCharacter;

fCharacter*
fCharacter_create();

int
fCharacter_reset(fCharacter*);

void
fCharacter_setName(fCharacter*, char*);

char*
fCharacter_getName(fCharacter*);

void
fCharacter_setHealth(fCharacter*, float);

float
fCharacter_getHealth(fCharacter*);

void
fCharacter_setEnergy(fCharacter*, float);

float fCharacter_getEnergy(fCharacter* c) { return c->energy; } 

#endif // F_CHARACTER_H
