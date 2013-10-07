#pragma once
#include "cocos2d.h"
#include "CMyHelper.h"

USING_NS_CC;

class CCLayoutTable:
	public CCNode
{
public:
	enum ALIGN_TYPE{
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_TOP,
		ALIGN_BOTTOM,
		ALIGN_CENTER
	};
public:
	CCLayoutTable(void);
	virtual ~CCLayoutTable(void);

	static CCLayoutTable* create(float cellWidth, float cellHeight, 
		unsigned int rowMax, unsigned int colMax,
		ALIGN_TYPE wAlign=ALIGN_CENTER, ALIGN_TYPE hAlign=ALIGN_CENTER);

	void setItemParam(float cellWidth, float cellHeight, 
		unsigned int rowMax, unsigned int colMax,
		ALIGN_TYPE wAlign=ALIGN_CENTER, ALIGN_TYPE hAlign=ALIGN_CENTER);

	void addItem(CCNode* pitem, unsigned int row, unsigned int col, int tag=-1);

	//按children内置顺序重新排列
	void updateItemsPosition();

	void getPos(unsigned int row, unsigned int col, CCPoint* ccpRet, CCNode* pitem=NULL);

	inline void showLines()
	{
		m_showLines = true;
	}

	inline void setLineColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		ccDrawColor4B(r,g,b,a);
	}

	inline void hideLines()
	{
		m_showLines = false;
	}
	
	virtual void draw();

protected:
	void updateItemPosition(CCNode* pitem, unsigned int row, unsigned int col);

protected:
	float m_cellWidth;
	float m_cellHeight;
	ALIGN_TYPE m_widthAlign;
	ALIGN_TYPE m_heightAlign;
	unsigned int m_rowMax;
	unsigned int m_colMax;
	bool m_showLines;
};
