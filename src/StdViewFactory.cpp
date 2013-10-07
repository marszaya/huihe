#include "StdViewFactory.h"
#include "STRTABLE.h"
#include "StrTool.h"
#include "CNode9Grid.h"
#include "CCTouchDispatcherExt.h"

const float CStdViewFactory::STD_POP_WINDOW_WIDTH=700;
const float CStdViewFactory::STD_POP_WINDOW_HEIGHT=500;

CCMyHelper::FONT_INFO CStdViewFactory::LABEL_FONT;


CStdViewFactory::CStdViewFactory(void)
{
}

CStdViewFactory::~CStdViewFactory(void)
{
}

CCMenu* CStdViewFactory::createBtn(CCObject *rec, SEL_MenuHandler selector, const char* label,
	int tagId, float posx, float posy, CCMyHelper::POSITION_TYPE postype)
{
	CCBtnBase::Config config;
	config.normalImg = "mainScene/btnBase.png";
	config.selectedImg = "mainScene/btnBaseSel.png";
	config.disableImg = "mainScene/btnBaseDis.png";
	config.fontName = CONST_STR_FONT_BTN;
	config.fontSize = 14;
	config.fontColor = ccBLACK;
	config.x1 = 6;
	config.x2 = 66;
	config.y1 = 6;
	config.y2 = 20;
	return CCBtnBase::createMenu(rec, selector, &config, label, tagId, posx, posy, postype);
}

CCMenu* CStdViewFactory::createCloseBtn(CCObject *rec, SEL_MenuHandler selector, int tag)
{
	return CCMyHelper::createFrameButton("close.png", rec, selector, tag, "closeSel.png");
}

void CStdViewFactory::initFactory()
{
	//默认字体定义
	LABEL_FONT.color = ccWHITE;
	LABEL_FONT.name = CONST_STR_FONT_LABEL;
	LABEL_FONT.size = 16;
}

CCCheckBox* CStdViewFactory::createCheckBox(const char* onImg, const char* offImg,
		bool isopen, int tag)
{
	CCCheckBox* ret = NULL;
	do{
		//init
		CCCheckBox* pcheckbox = CCCheckBox::create(onImg, offImg, 
			NULL, NULL, true, tag);
		CC_BREAK_IF(!pcheckbox);
	

		if(isopen)
		{
			pcheckbox->setState(true);
		}

		ret = pcheckbox;
	}while(0);

	return ret;
}

CCLabelAtlas* CStdViewFactory::createNum(unsigned int num, int sign, float scale)
{
	CCLabelAtlas*  ret = NULL;
	do{
		CCLabelAtlas* pat = NULL;
		if(sign<0)
		{
			//use red num;
			pat = CCLabelAtlas::create(string("-").append(CStrTool::strDecimal(num)).c_str(), 
				"number/numberRed.png", 18, 26, '-');
		}
		else if(sign == 0)
		{
			//green num;
			pat = CCLabelAtlas::create(CStrTool::strDecimal(num).c_str(), 
				"number/numberGreen.png", 18, 26, '+');
		}
		else
		{
			//green num;
			pat = CCLabelAtlas::create(string("+").append(CStrTool::strDecimal(num)).c_str(), 
				"number/numberGreen.png", 18, 26, '+');
		}

		if(!pat)
			break;

		if(scale!=0)
			pat->setScale(scale);

		ret = pat;
	}while(0);

	return ret;
}

CCNode* CStdViewFactory::create9ScaleBg(
		const char* img, float width, float height,float cornerX, float cornerY,  int type)
{
	CCNode* ret=NULL;
	do{
		CCNode* bg=NULL;
		if(type == 0)
		{
			bg=CCNode9Grid::createWithTargetSize(img, cornerX, cornerY, width, height);
		}
		else
		{
			bg=CCNode9GridFillTex::createWithTargetSize(img, cornerX, cornerY, width, height);
		}

		if(!bg)
			break;

		ret = bg;
	}while(0);
	return ret;
}

bool CStdViewFactory::configPageNav(CCEPageNav* pageNav)
{
	bool ret = false;
	do{
		CCSprite* pre = CCMyHelper::createZeroAnchorFrameSprite("gonext.png");
		if(!pre)
			break;
		pre->setFlipX(true);

		CCSprite* preSel = CCMyHelper::createZeroAnchorFrameSprite("gonextSel.png");
		if(!preSel)
			break;
		preSel->setFlipX(true);

		CCSprite* next = CCMyHelper::createZeroAnchorFrameSprite("gonext.png");
		if(!next)
			break;

		CCSprite* nextSel = CCMyHelper::createZeroAnchorFrameSprite("gonextSel.png");
		if(!nextSel)
			break;

		pageNav->setPreBtn(pre, preSel);
		pageNav->setNextBtn(next, nextSel);
		pageNav->setLabel(LABEL_FONT);
		ret = true;
	}while(0);

	return ret;
}

bool CStdViewFactory::createTabNode(const char* label,CCNode*& outputSel, CCNode*& outputUnSel)
{
	bool ret = false;
	do{
		CCWindowBase* psel = CCWindowBase::create();
		CCWindowBase* punsel = CCWindowBase::create();
		if(!psel || !punsel)
			break;
		psel->setWindowBG(CCSprite::create("mainScene/tabSel.png"));
		psel->windowSizeFitBG();
		psel->updateLabel(-1, label, 
			CStdViewFactory::LABEL_FONT,
			CCMyHelper::POS_INFO(psel->getWindowWidth()/2,
				psel->getWindowHeight()/2, CCMyHelper::POSITION_TYPE_CENTER)
		);

		punsel->setWindowBG(CCSprite::create("mainScene/tabUnSel.png"));
		punsel->windowSizeFitBG();
		punsel->updateLabel(-1, label, 
			CStdViewFactory::LABEL_FONT,
			CCMyHelper::POS_INFO(punsel->getWindowWidth()/2,
				punsel->getWindowHeight()/2, CCMyHelper::POSITION_TYPE_CENTER)
		);

		outputUnSel = punsel;
		outputSel = psel;

		ret = true;
	}while(0);
	return ret;
}

CCNode* CStdViewFactory::createBorderForNode(CCNode* target)
{
	CCNode* ret = NULL;
	do{
		CCNode* border = create9ScaleBg("mainScene/border.png", 
			target->getContentSize().width+20, target->getContentSize().height+20, 
			20, 20, 1);
		if(!border)
			break;
		CCMyHelper::setPosBL(border, -10, -10);
		ret = border;
	}while(0);

	return ret;
}

CCWindowBase* CStdViewFactory::createDialog(const char* msg, CCUCommonDelegate* pdelegate,
		DIALOG_TYPE type, bool needSwitchTouch)
{
	CCWindowBase* ret = NULL;
	do{
		CCWindowBase* tmpVal = NULL;
		if(needSwitchTouch)
		{
			tmpVal = CSwitchTouchWindow::create();
		}
		else
		{
			tmpVal = CCWindowBase::create();
		}
		if(!tmpVal)
			break;

		int width = 400;
		int height = 300;
		CCNode* bg = createPopUpBg(400, 300);
		if(!bg)
			break;

		tmpVal->setWindowBG(bg);
		tmpVal->windowSizeFitBG();

		CCLabelTTF* label = CCLabelTTF::create(msg, LABEL_FONT.name.c_str(),
			LABEL_FONT.size, CCSizeMake(300,160), kCCTextAlignmentLeft);

		if(!label)
			break;

		CCMyHelper::setPosBL(label, 50, 70);
		tmpVal->addChild(label);

		tmpVal->setDelegate(pdelegate);

		if(type == DIALOG_TYPE_CONFIRM)
		{
			CCMenu* btnOK = createBtn(tmpVal, menu_selector(CCWindowBase::passCmdToDelegateFromNodeTag), 
				CONST_STR_BTN_DIALOGUE_OK, DIALOG_OK, 120, 40);
			if(!btnOK)
				break;
			tmpVal->addChild(btnOK);

			CCMenu* btnCancel = createBtn(tmpVal, menu_selector(CCWindowBase::passCmdToDelegateFromNodeTag), 
				CONST_STR_BTN_DIALOGUE_CANCEL, DIALOG_CANCEL, 280, 40);
			if(!btnCancel)
				break;
			tmpVal->addChild(btnCancel);
		}
		else
		{
			CCMenu* btnOK = createBtn(tmpVal, menu_selector(CCWindowBase::passCmdToDelegateFromNodeTag), 
				CONST_STR_BTN_DIALOGUE_OK, DIALOG_OK, 200, 40);
			if(!btnOK)
				break;
			tmpVal->addChild(btnOK);
		}

		ret = tmpVal;
	}while(0);
	return ret;
}
