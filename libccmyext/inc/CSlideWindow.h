#pragma once
#include "cocos2d.h"
#include "CWindowBase.h"
#include <vector>
#include <map>
#include <string>
using namespace std;
USING_NS_CC;

//幻灯片播放
class CCESlideWindow: public CCWindowBase
{
public:
	struct INDEX_ITEM
	{
		int refCnt;
		CCNode* target;
	};

	typedef map<string, INDEX_ITEM> TEYP_INDEX_MAP;
protected:
	vector<CCNode*> m_slides;
	TEYP_INDEX_MAP m_index;
	float m_dt;
	bool m_play;
	int m_cur;

public:
	CCESlideWindow(void);
	virtual ~CCESlideWindow(void);

	static CCESlideWindow* create();

	bool initCCESlideWindow();

	//增加一个
	int addSlide(CCNode* slide, const string& id);

	//删除一个
	int delSlide(const string& id);

	inline void setDt(float dt)
	{
		m_dt = dt;
		if(m_play)
		{
			stopPlay();
			startPlay();
		}
	}

	inline int startPlay()
	{
		if(!m_play)
		{
			this->schedule(schedule_selector(CCESlideWindow::updateCallBack) , m_dt);
			m_play = true;
		}

		return 0;
	}

	inline int stopPlay()
	{
		if(m_play)
		{
			this->unschedule(schedule_selector(CCESlideWindow::updateCallBack));
			m_play = false;
		}

		return 0;
	}

	int gotoSlide(const string& id)
	{
		int ret = findSlide(id);
		if(ret < 0)
			return -1;

	 	m_cur = ret;

		if(m_play)
		{
			stopPlay();
			startPlay();
		}
	}

	void updateCallBack(float dt);

protected:
	int findSlide(const string& id);
	int showCurSlide();
};
