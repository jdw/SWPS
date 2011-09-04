#ifndef F_UI_H
#define F_UI_H

#define MESSAGE_ROWS 10

enum fUI_infoType {
	STRING,
	INT,
	FLOAT
};
typedef enum fUI_infoType fUI_infoType;

struct fUI_info {
	char* pKey;
	fUI_infoType type;
	int iValue;
	float fValue;
	char* pValue;
};
typedef struct fUI_info fUI_info;

struct fUI {
	char* pMessages[MESSAGE_ROWS];
	fUI_info* pInfos;
	int showFPS;
	float playerHealth;
	float playerEnergy;
	float playerCash;
	struct sfString* pText;
	const int (*draw)(struct fUI* const);
};
typedef struct fUI fUI;

fUI*
fUI_create();

const int
fUI_reset(fUI* const);

const int
fUI_update(fUI* const);

const int
fUI_draw(fUI* const);

const int
fUI_setMessage(fUI* const, char*);

#endif // F_UI_H
