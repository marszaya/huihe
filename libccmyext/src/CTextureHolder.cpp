#include "CTextureHolder.h"

CCUTextureHolder* CCUTextureHolder::sSharedInstance = NULL;

CCUTextureHolder::CCUTextureHolder(void)
{
	m_pTextures = new CCDictionary();
	m_pFrames = new CCDictionary();
}

CCUTextureHolder::~CCUTextureHolder(void)
{
	delete m_pTextures;
	m_pTextures = NULL;
	delete m_pFrames;
	m_pFrames = NULL;
}

CCUTextureHolder* CCUTextureHolder::getSharedInstance()
{
	if(sSharedInstance==NULL)
	{
		sSharedInstance = new CCUTextureHolder();
	}
	return sSharedInstance;
}

void CCUTextureHolder::removeSharedInstance()
{
	if(sSharedInstance)
	{
		delete sSharedInstance;
		sSharedInstance = NULL;
	}
}

void CCUTextureHolder::retainTexture(const char* name)
{
	do{
		//不重复
		if(m_pTextures->objectForKey(name) != NULL)
			break;
	
		CCTexture2D* tex = CCTextureCache::sharedTextureCache()->textureForKey(name);
		if(tex == NULL)
			break;

		//texture->removeUnuse...就不会影响到这个资源了
		m_pTextures->setObject(tex, name);
	}while(0);
}

void CCUTextureHolder::releaseTextrue(const char* name)
{
	m_pTextures->removeObjectForKey(name);
}

void CCUTextureHolder::retainFrames(map<string, CCSpriteFrame*>& frames)
{
	map<string, CCSpriteFrame*>::iterator it;
	for(it=frames.begin(); it!=frames.end(); ++it)
	{
		if(m_pFrames->objectForKey(it->first.c_str()) != NULL)
			continue;
		
		m_pFrames->setObject(it->second, it->first);
	}
}
