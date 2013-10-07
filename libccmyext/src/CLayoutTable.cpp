#include "CLayoutTable.h"

CCLayoutTable::CCLayoutTable(void)
{
	m_cellWidth=0;
	m_cellHeight=0;
	m_widthAlign = ALIGN_CENTER;
	m_heightAlign = ALIGN_CENTER;
	m_showLines = false;
}

CCLayoutTable::~CCLayoutTable(void)
{
}

CCLayoutTable* CCLayoutTable::create(float cellWidth, float cellHeight, 
	unsigned int rowMax, unsigned int colMax,
	ALIGN_TYPE wAlign, ALIGN_TYPE hAlign)
{
	CCLayoutTable *pRet = new CCLayoutTable();
	if(pRet)
	{
		pRet->autorelease();
		pRet->setItemParam(cellWidth, cellHeight, rowMax, colMax, wAlign, hAlign);
	}
	return pRet;
}

void CCLayoutTable::setItemParam(float cellWidth, float cellHeight, 
	 unsigned int rowMax, unsigned int colMax,
	ALIGN_TYPE wAlign, ALIGN_TYPE hAlign)
{
	m_cellWidth=cellWidth;
	m_cellHeight=cellHeight;
	m_widthAlign = wAlign;
	m_heightAlign = hAlign;
	m_rowMax = rowMax;
	m_colMax = colMax;
	this->setContentSize(CCSizeMake(cellWidth*colMax, cellHeight*rowMax));
}

void CCLayoutTable::addItem(CCNode* pitem, unsigned int row, unsigned int col, int tag)
{
	updateItemPosition(pitem, row, col);
	if(tag != -1)
	{
		this->addChild(pitem, 1, tag);
	}
	else
	{
		this->addChild(pitem);
	}
}

void CCLayoutTable::updateItemsPosition()
{
    if(m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* child;
		int i=0;
        CCARRAY_FOREACH(m_pChildren, child)
        {
            CCNode* pNode = (CCNode*) child;
			updateItemPosition(pNode, i/m_rowMax, i%m_rowMax);
			++i;
        }
    }
}

void CCLayoutTable::updateItemPosition(CCNode* pitem, unsigned int row, unsigned int col)
{
	CCPoint* ccp = new CCPoint();
	getPos(row, col, ccp, pitem);
	CCMyHelper::setPosBL(pitem, ccp->x, ccp->y);
	delete ccp;
}

void CCLayoutTable::getPos(unsigned int row, unsigned int col, CCPoint* ccpRet, CCNode* pitem)
{
	float posX = col*m_cellWidth;
	//y反转，从上到下
	float posY = (m_rowMax - 1 - row)*m_cellHeight;
	float deltaX = m_cellWidth - pitem->getContentSize().width;
	float deltaY = m_cellHeight - pitem->getContentSize().height;
	switch(m_widthAlign)
	{
		case ALIGN_LEFT:
			break;
		case ALIGN_RIGHT:
			posX += deltaX;
			break;
		default:
			posX += deltaX/2;
			break;
	}

	switch(m_heightAlign)
	{
		case ALIGN_TOP:
			break;
		case ALIGN_BOTTOM:
			posY += deltaY;
			break;
		default:
			posY += deltaY/2;
			break;
	}

	ccpRet->x=posX;
	ccpRet->y=posY;
}

void CCLayoutTable::draw()
{
	if(!m_showLines)
		return;

	for(unsigned int i=0; i <= this->m_rowMax; ++i)
	{
		ccDrawLine(CCPointMake(0, this->m_cellHeight*i), 
			CCPointMake(this->m_cellWidth*this->m_colMax, this->m_cellHeight*i));
	}

	for(unsigned int j=0; j <= this->m_colMax; ++j)
	{
		ccDrawLine(CCPointMake(this->m_cellWidth*j, 0), 
			CCPointMake(this->m_cellWidth*j, this->m_cellHeight*this->m_rowMax));
	}
}
