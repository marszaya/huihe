#include "CSlideWindow.h"
#include "CNode9Grid.h"
#include "CMyHelper.h"

CCESlideWindow::CCESlideWindow(void)
{
	m_dt = 1.0;
	m_play = false;
	m_cur = -1;
}

CCESlideWindow::~CCESlideWindow(void)
{
	if(m_play)
		stopPlay();
}

CCESlideWindow* CCESlideWindow::create()
{
	CCESlideWindow *pRet = new CCESlideWindow();
	if(pRet && pRet->initCCESlideWindow())
    {
        pRet->autorelease();
 		return pRet;
   }

    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCESlideWindow::initCCESlideWindow()
{
	bool ret = false;
	do{

		ret = true;
	}while(0);

	return ret;
}

int CCESlideWindow::findSlide(const string& id)
{
	TEYP_INDEX_MAP::iterator it = m_index.find(id);
	if(it == m_index.end())
		return -1;

	for(unsigned int i=0; i<m_slides.size(); ++i)
	{
		if(it->second.target == m_slides[i])
		{
			return i;
		}
	}

	//不一致，更新
	m_index.erase(it);
	return -1;
}

void CCESlideWindow::updateCallBack(float dt)
{
	if(m_slides.size() > 0)
	{
		if(m_cur == -1)
		{
			m_cur = 0;
		}
		showCurSlide();
		m_cur = (m_cur+1)%m_slides.size();
	}
}

//增加一个
int CCESlideWindow::addSlide(CCNode* slide, const string& id)
{
	TEYP_INDEX_MAP::iterator it = m_index.find(id);
	if(it != m_index.end())
	{
		it->second.refCnt += 1;
		return 0;
	}

	INDEX_ITEM tmp;
	tmp.target = slide;
	tmp.refCnt = 1;
	m_index.insert(make_pair(id, tmp));
	this->addChild(slide);
	m_slides.push_back(slide);
	return 0;
}

//删除一个
int CCESlideWindow::delSlide(const string& id)
{
	TEYP_INDEX_MAP::iterator it = m_index.find(id);
	if(it == m_index.end())
		return -1;

	it->second.refCnt -= 1;
	if(it->second.refCnt > 0)
	{
		return 0;
	}

	bool nextShow = false;
	CCNode* ptarget = it->second.target;
	//正在显示的过程中
	if(ptarget->isVisible())
	{
		nextShow = true;
	}

	//去掉显示
	this->removeChild(ptarget);
	//删除索引
	m_index.erase(it);

	//寻找删除位置
	unsigned int i=0;
	for(; i<m_slides.size(); ++i)
	{
		if(ptarget == m_slides[i])
		{
			break;
		}
	}

	//后面的迁移
	for(unsigned int j=i; j<m_slides.size()-1; ++j)
	{
		m_slides[j] = m_slides[j+1];
	}

	//从数组中删除指针
	m_slides.pop_back();


	//修正m_cur
	if(m_cur > (int)i)
	{
		m_cur -= 1;
	}
	else if(m_cur == (int)i && m_cur >= m_slides.size())
	{
		 //i在最后
		 if(m_slides.size() == 0)
			 m_cur = -1;
		 else
			 m_cur = 0;
	}

	if(nextShow) //需要立即显示下一个
	{
		if(m_cur >= 0)
		{
			m_slides[m_cur]->setVisible(true);
		}
	}

	return 0;
}

int CCESlideWindow::showCurSlide()
{
	for(unsigned int i=0; i<m_slides.size(); ++i)
	{
		if(i == m_cur)
		{
			m_slides[i]->setVisible(true);
		}
		else
		{
			m_slides[i]->setVisible(false);
		}
	}

	return 0;
}
