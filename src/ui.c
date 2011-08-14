#include <ui.h>
#include <stdlib.h>

F_UI*
F_UI_create() {
	F_UI* t_pRet = (F_UI*) malloc(sizeof(F_UI));

	for (int i = 0; i < MESSAGE_ROWS; ++i)
		t_pRet->t_pMessages[i] = 0;

    t_pRet->showFPS = 0;
    t_pRet->playerHealth = 0.f;
    t_pRet->playerEnergy = 0.f;
    t_pRet->playerCash = 0.f;

	return t_pRet;
}

static int
F_UI_update(const F_UI* i_pUI) {

	return AOK;
}
