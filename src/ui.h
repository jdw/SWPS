#ifndef F_UI_H
#define F_UI_H

#define MESSAGE_ROWS 10

typedef struct F_UI {
	char* t_pMessages[MESSAGE_ROWS];
	int showFPS;
	float playerHealth;
	float playerEnergy;
	float playerCash;
} F_UI;

F_UI*
F_UI_create();

static int
F_UI_update();

#endif // F_UI_H
