#include "ui.h"
#include <stdlib.h>
#include <define.h>

#include <stdio.h>

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
	u->pInfos[0].pKey = "HP"; // TODO: Should not be in reset... /JDW
	u->pInfos[0].type = FLOAT;
	u->pInfos[0].fValue = 1;
	u->pInfos[1].pKey = "MP";
	u->pInfos[1].type = FLOAT;
	u->pInfos[1].fValue = .5f;

	u->showFPS = 0; //???
	u->playerHealth = 0.f; // ???
	u->playerEnergy = 0.f; // ???
	u->playerCash = 0.f; // ???
	
	u->pText = 0;

	return AOK;
}

const int
fUI_update(fUI* const u) {
	return AOK;
}

const int
fUI_draw(fUI* const u) {
	if (u->draw) return u->draw(u);
	
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

