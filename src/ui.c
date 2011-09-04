#include "ui.h"
#include <stdlib.h>
#include <define.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>

#include <SFML/Graphics/Font.h>

fUI*
fUI_create() {
	fUI* t_ret = (fUI*) malloc(sizeof(fUI));

	return t_ret;
}

const int
fUI_reset(fUI* const u) {	
	for (int i = 0; i < MESSAGE_ROWS; ++i)
		u->pMessages[i] = 0;

	u->pInfos = (fUI_info*) malloc(2 * sizeof(fUI_info));
	u->pInfos[0].pKey = "HP";
	u->pInfos[0].type = FLOAT;
	u->pInfos[0].fValue = 1;
	u->pInfos[1].pKey = "MP";
	u->pInfos[1].type = FLOAT;
	u->pInfos[1].fValue = .5f;

	u->showFPS = 0; //???
	u->playerHealth = 0.f; // ???
	u->playerEnergy = 0.f; // ???
	u->playerCash = 0.f; // ???
	
	u->pText = sfString_Create();
	sfString_SetSize(u->pText, 15);
	sfString_SetFont(u->pText, sfFont_GetDefaultFont());

	return AOK;
}

const int
fUI_update(fUI* const u) {
	return AOK;
}

const int
fUI_draw(fUI* const u, sfRenderWindow* i_pApp) {
	
	int t_value = 0;
	char* t_string;

	for (int i = 0; i < 2; i++) { 
		t_value = 10 * u->pInfos[i].fValue;
		switch(t_value) {
			case 0: t_string = "[          ]\0"; break;
			case 1: t_string = "[|         ]\0"; break;
			case 2: t_string = "[||        ]\0"; break;
			case 3: t_string = "[|||       ]\0"; break;
			case 4: t_string = "[||||      ]\0"; break;
			case 5: t_string = "[|||||     ]\0"; break;
			case 6: t_string = "[||||||    ]\0"; break;
			case 7: t_string = "[|||||||   ]\0"; break;
			case 8: t_string = "[||||||||  ]\0"; break;
			case 9: t_string = "[||||||||| ]\0"; break;
			default: t_string = "[||||||||||]\0"; break;
		
		}

		const int BUFFER_SIZE = 100;
		char buf[BUFFER_SIZE];
		const char* t = &buf;
		snprintf(t, BUFFER_SIZE, "%s: %s", u->pInfos[i].pKey, t_string);
		sfString_SetText(u->pText, t);
		sfString_SetPosition(u->pText, 700, 550 - i * 20);
		sfRenderWindow_DrawString(i_pApp, u->pText);

	}

	// Printing messages
	for (int i = 0; i < MESSAGE_ROWS; i++) {
		sfString_SetText(u->pText, u->pMessages[i]);
		sfString_SetPosition(u->pText, 10, 550 - i * 20);
		sfRenderWindow_DrawString(i_pApp, u->pText);
	}

	//u
	return AOK;
}

const int
fUI_setMessage(fUI* const u, char* i_pMessage) {
	// 9 = mem leak!!!!!!!!one1!!!!!!!!!!!!!!!
	u->pMessages[9] = u->pMessages[8];
	u->pMessages[8] = u->pMessages[7];
	u->pMessages[7] = u->pMessages[6];
	u->pMessages[6] = u->pMessages[5];
	u->pMessages[5] = u->pMessages[4];
	u->pMessages[4] = u->pMessages[3];
	u->pMessages[3] = u->pMessages[2];
	u->pMessages[2] = u->pMessages[1];
	u->pMessages[1] = u->pMessages[0];
	u->pMessages[0] = i_pMessage;

	return AOK;
}

