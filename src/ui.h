#ifndef F_UI_H
#define F_UI_H

#define MESSAGE_ROWS 10
struct sfRenderWindow;
#include <SFML/Graphics.h>

typedef enum {
	STRING,
	INT,
	FLOAT
} fUI_info_type;

typedef struct fUI_info {
	char* pKey;
	fUI_info_type type;
	int iValue;
	float fValue;
	char* pValue;
} fUI_info;

typedef struct F_UI {
	char* pMessages[MESSAGE_ROWS];
	fUI_info* pInfos;
	int showFPS;
	float playerHealth;
	float playerEnergy;
	float playerCash;
	sfString* pText;
} F_UI;

F_UI*
F_UI_create();

const int
F_UI_update(const F_UI* i_pUI);

const int
F_UI_draw(const F_UI* i_pUI, const sfRenderWindow* i_pApp);

const int
fUI_setMessage(F_UI* i_pUI, char* i_pMessage);
#endif // F_UI_H
