#pragma once

#include "CWindowBase.h"
using namespace std;

class CCEActionEffectAfterImage:public CCWindowBase
{
public:
	class CAfterImageConfig
	{
	public:
		string m_srcName;
		int m_srcType; //0=img 1=frame
		unsigned int m_num; 
		float m_createDt;
		float m_firstScale; //第一个的缩放
		float m_lastScale; //最后一个影子的缩放
		int m_firstOpacity; //第一个的透明度
		int m_lastOpacity; //最后一个影子的透明度

		CAfterImageConfig(){}

		CAfterImageConfig(const char* name, int type, float createDt=0.1, unsigned int num=5, 
			float firstScale=1.0, float lastScale=1.0, 
			int firstOpacity=255, int lastOpacity=45)
		{
			m_srcName = name;
			m_srcType = type;
			m_num = num;
			m_lastScale = lastScale;
			m_lastOpacity = lastOpacity;
			m_createDt = createDt;
			m_firstScale = firstScale;
			m_firstOpacity = firstOpacity;
		}

		CAfterImageConfig(const CAfterImageConfig& c)
		{
			this->m_srcName = c.m_srcName; 
			this->m_srcType = c.m_srcType; 
			this->m_num = c.m_num; 
			this->m_lastScale = c.m_lastScale; 
			this->m_lastOpacity = c.m_lastOpacity; 
			this->m_createDt = c.m_createDt;
			this->m_firstScale = m_firstScale;
			this->m_firstOpacity = m_firstOpacity;
		}
	};
public:
	CCEActionEffectAfterImage(void);
	virtual ~CCEActionEffectAfterImage(void);

	static CCEActionEffectAfterImage* create(const CAfterImageConfig& conf );
	bool initCCEActionEffectAfterImage(const CAfterImageConfig& conf);

	void addActionToImage(CCAction *paction);

	bool beginAfterImage();

	bool stopAfterImage();

	void afterImgSchedule(float dt);
	
	inline void setChildAnchorPoint(CCPoint p)
	{
		m_childAnchorPoint = p;
	}

protected:
	void cleanAfterImg();	
	CCSprite* createNewSprite();
	bool lazyCreateBatchNode(CCSprite* sp);

protected:
	CAfterImageConfig m_conf;
	unsigned int m_createdNum;
	bool m_enableCreate;
	bool m_enableDel;
	float m_dtAdd;
	CCSpriteBatchNode* m_pbatchnode;
	CCArray m_actionArray;
	CCPoint m_childAnchorPoint;
};

