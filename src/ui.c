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
	
	for (int i = 0; i < MESSAGE_ROWS; ++i)
		t_ret->pMessages[i] = 0;

	t_ret->pInfos = (fUI_info*) malloc(2 * sizeof(fUI_info));
	t_ret->pInfos[0].pKey = "HP";
	t_ret->pInfos[0].type = FLOAT;
	t_ret->pInfos[0].fValue = 1;
	t_ret->pInfos[1].pKey = "MP";
	t_ret->pInfos[1].type = FLOAT;
	t_ret->pInfos[1].fValue = .5f;

	t_ret->showFPS = 0; //???
	t_ret->playerHealth = 0.f; // ???
	t_ret->playerEnergy = 0.f; // ???
	t_ret->playerCash = 0.f; // ???
	
	t_ret->pText = sfString_Create();
	sfString_SetSize(t_ret->pText, 15);
	sfString_SetFont(t_ret->pText, sfFont_GetDefaultFont());

	return t_ret;
}

const int
fUI_update(const fUI* i_pUI) {
	return AOK;
}

const int
fUI_draw(fUI* i_pUI, sfRenderWindow* i_pApp) {
	
	int t_value = 0;
	char* t_string;

	for (int i = 0; i < 2; i++) { 
		t_value = 10 * i_pUI->pInfos[i].fValue;
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
		snprintf(t, BUFFER_SIZE, "%s: %s", i_pUI->pInfos[i].pKey, t_string);
		sfString_SetText(i_pUI->pText, t);
		sfString_SetPosition(i_pUI->pText, 700, 550 - i * 20);
		sfRenderWindow_DrawString(i_pApp, i_pUI->pText);

	}

	// Printing messages
	for (int i = 0; i < MESSAGE_ROWS; i++) {
		sfString_SetText(i_pUI->pText, i_pUI->pMessages[i]);
		sfString_SetPosition(i_pUI->pText, 10, 550 - i * 20);
		sfRenderWindow_DrawString(i_pApp, i_pUI->pText);
	}

	//i_pUI
	return AOK;
}

const int
fUI_setMessage(fUI* i_pUI, char* i_pMessage) {
	// 9 = mem leak!!!!!!!!one1!!!!!!!!!!!!!!!
	i_pUI->pMessages[9] = i_pUI->pMessages[8];
	i_pUI->pMessages[8] = i_pUI->pMessages[7];
	i_pUI->pMessages[7] = i_pUI->pMessages[6];
	i_pUI->pMessages[6] = i_pUI->pMessages[5];
	i_pUI->pMessages[5] = i_pUI->pMessages[4];
	i_pUI->pMessages[4] = i_pUI->pMessages[3];
	i_pUI->pMessages[3] = i_pUI->pMessages[2];
	i_pUI->pMessages[2] = i_pUI->pMessages[1];
	i_pUI->pMessages[1] = i_pUI->pMessages[0];
	i_pUI->pMessages[0] = i_pMessage;

	return AOK;
}

