#include "BattleMapScene.h"
#include "PveMap.h"
#include "MyData.h"
CBattleMapScene::CBattleMapScene(void)
{
}

CBattleMapScene::~CBattleMapScene(void)
{
}

bool CBattleMapScene::showMainWindow()
{
	bool ret = false;
	do{
		int mapId = CMyData::getSharedData()->getCurrentMap();
		CPveMap* mapWin = CPveMap::create(mapId);
		if(!mapWin)
			break;

		this->addChild(mapWin);
		ret = true;
	}while(0);
	return ret;
}
