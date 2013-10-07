#pragma once

#define CONST_STR_FONT_BTN CStrTableHelper::getStrById("10001")
#define CONST_STR_FONT_LABEL CStrTableHelper::getStrById("10001")
#define CONST_STR_BTN_LOGIN CStrTableHelper::getStrById("20001")
#define CONST_STR_BTN_USE CStrTableHelper::getStrById("20002")
#define CONST_STR_BTN_PREPAGE CStrTableHelper::getStrById("20003")
#define CONST_STR_BTN_NEXTPAGE CStrTableHelper::getStrById("20004")
#define CONST_STR_BTN_REFRESH CStrTableHelper::getStrById("20005")
#define CONST_STR_BTN_SALE CStrTableHelper::getStrById("20006")
#define CONST_STR_BTN_TAB_ALL CStrTableHelper::getStrById("20007")
#define CONST_STR_BTN_TAB_USABLE CStrTableHelper::getStrById("20008")
#define CONST_STR_BTN_EQUIP CStrTableHelper::getStrById("20009")
#define CONST_STR_BTN_UNEQUIP CStrTableHelper::getStrById("20010")
#define CONST_STR_BTN_TAB_EQUIP CStrTableHelper::getStrById("20011")
#define CONST_STR_BTN_PAY CStrTableHelper::getStrById("20012")
#define CONST_STR_BTN_HIRE CStrTableHelper::getStrById("20014")
#define CONST_STR_BTN_FIRE CStrTableHelper::getStrById("20013")
#define CONST_STR_BTN_HIRED CStrTableHelper::getStrById("20015")
#define CONST_STR_BTN_BATTLE_LIST_PUSH CStrTableHelper::getStrById("20016")
#define CONST_STR_BTN_BATTLE_LIST_SAVE CStrTableHelper::getStrById("20017")
#define CONST_STR_BTN_DIALOGUE_OK CStrTableHelper::getStrById("20018")
#define CONST_STR_BTN_DIALOGUE_CANCEL CStrTableHelper::getStrById("20019")
#define CONST_STR_LABEL_REFESHHIRE CStrTableHelper::getStrById("100001")

class CStrTableHelper
{
public:
	static const char* sStrNotFound;
	static const char* getStrById(const char* id);
};