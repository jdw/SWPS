#include "ui.h"
#include <stdlib.h>
#include <define.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>

#include <SFML/Graphics/Font.h>

F_UI*
F_UI_create() {
	F_UI* t_pRet = (F_UI*) malloc(sizeof(F_UI));
	
	for (int i = 0; i < MESSAGE_ROWS; ++i)
		t_pRet->pMessages[i] = 0;

	t_pRet->pInfos = (fUI_info*) malloc(2 * sizeof(fUI_info));
	t_pRet->showFPS = 0;
	t_pRet->playerHealth = 0.f;
	t_pRet->playerEnergy = 0.f;
	t_pRet->playerCash = 0.f;
	
	t_pRet->pText = sfString_Create();
	sfString_SetFont(t_pRet->pText, sfFont_GetDefaultFont());

	return t_pRet;
}

const int
F_UI_update(const F_UI* i_pUI) {
	return AOK;
}

const int
F_UI_draw(const F_UI* i_pUI, const sfRenderWindow* i_pApp) {
	// Printing messages
	for (int i = 0; i < MESSAGE_ROWS; i++) {
		sfString_SetText(i_pUI->pText, i_pUI->pMessages[i]);
		sfString_SetSize(i_pUI->pText, 15);
		sfString_SetPosition(i_pUI->pText, 10, 550 - i * 20);
		sfRenderWindow_DrawString(i_pApp, i_pUI->pText);
	}

	//i_pUI
	return AOK;
}

const int
fUI_setMessage(F_UI* i_pUI, char* i_pMessage) {
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

