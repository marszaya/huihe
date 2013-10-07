#include "CPreLoad.h"
#include <string.h>
#include <fstream>

CCPreLoad::CCPreLoad(void)
{
	m_dict = NULL;
	m_tmpKeyArr = NULL;
	m_checkSize = false;
	resetFetch();
}

CCPreLoad::~CCPreLoad(void)
{
	if(m_dict)
	{
		m_dict->release();
		m_dict = NULL;
	}
}


CCPreLoad* CCPreLoad::create(const char* configXML, bool checkSize)
{
	CCPreLoad *pRet = new CCPreLoad();
	if(pRet && pRet->initCCPreLoad(configXML,checkSize))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCPreLoad::initCCPreLoad(const char* configXML, bool checkSize)
{
	bool ret=false;
	do{
		if(configXML==NULL || strlen(configXML)==0)
		{
			m_dict = new CCDictionary;
		}
		else
		{
			string pszPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(configXML);
			m_dict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath.c_str());
		}

		if(!m_dict)
			break;

		m_checkSize = checkSize;
		ret = true;
	}while(0);

	return ret;
}

int CCPreLoad::addPreLoadPic(const char* pic)
{
	return addSingle(pic, RESOURCE_TYPE_PIC);
}


int CCPreLoad::addPreLoadFrames(const char* pic)
{
	return addSingle(pic, RESOURCE_TYPE_FRAMES);
}

int CCPreLoad::addSingle(const char* pic, int type, int size)
{
	int ret = -1;
	CCDictionary* dic = new CCDictionary();
	CCString* str = new CCString();
	CCString* str1 = new CCString();
	do{
		str->initWithFormat("%d", type);
		str1->initWithFormat("%d", size);

		dic->setObject(str1, "size");
		dic->setObject(str, "type");
		m_dict->setObject(dic, pic);
		ret = 0;
	}while(0);
	dic->release();
	str->release();
	str1->release();
	return ret;
}

int CCPreLoad::dumpXML(ostream& out)
{
	if(!m_dict)
	{
		CCLOG("m_dict not init");
		return -1;
	}
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	out << "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" << endl;
	out << "<preload version=\"1.0\">" << endl;
	out << "<dict>" << endl;

	CCArray* arr = m_dict->allKeys();

	int ret = -1;
	do{
		unsigned int i;
		for(i=0; i<arr->count(); ++i)
		{
			CCString* p = dynamic_cast<CCString*>(arr->objectAtIndex(i));
			if(!p)
				break;

			CCDictionary* pdic = dynamic_cast<CCDictionary*>(m_dict->objectForKey(p->getCString()));
			if(!pdic)
				break;

			out << "\t<key>" << p->getCString() << "</key>" << endl;
			if(dumpToXMLSingle(pdic, out)!=0)
			{
				CCLOG("dumpToXMLSingle %d fail", i);
				break;
			}
		}
		if(i!=	arr->count())
		{
			break;
		}
		ret = 0;

	}while(0);
	delete arr;

	out << "</dict>" << endl;
	out << "</preload>" << endl;

	return ret;
}

int CCPreLoad::dumpToXMLSingle(CCDictionary* dict, ostream& out)
{
	out << "\t<dict>" << endl;
	CCString* p1 = dynamic_cast<CCString*>(dict->objectForKey("type"));
		if(!p1)
			return -1;

	CCString* p2 = dynamic_cast<CCString*>(dict->objectForKey("size"));
	if(!p1)
		return -1;

	out << "\t\t<key>type</key>" << endl ;
	out << "\t\t<integer>" << p1->intValue()  << "</integer>" << endl ;
	out << "\t\t<key>size</key>" << endl ;
	out << "\t\t<integer>" <<  p2->intValue() << "</integer>" << endl ;
	out << "\t</dict>" << endl;

	return 0;
}

int CCPreLoad::getTotalBytes()
{
	if(!m_dict)
		return -1;
	int ret = -1;
	int total = 0;
	CCArray* arr = m_dict->allKeys();
	if(!arr)
		return 0;
	do
	{
		unsigned int i;
		for(i=0; i<arr->count(); ++i)
		{
			CCString* p = dynamic_cast<CCString*>(arr->objectAtIndex(i));
			if(!p)
				break;
			
			CCDictionary* pdic = dynamic_cast<CCDictionary*>(m_dict->objectForKey(p->getCString()));
			if(!pdic)
				break;

			CCString* p1 = dynamic_cast<CCString*>(pdic->objectForKey("size"));
			if(!p1)
				break;

			total += p1->intValue();
		}
		
		if(i!=arr->count())
		{
			break;
		}

		ret = total;
		m_tmpTotalBytes = total;
	}while(0);

	delete arr;

	return ret;
}

int CCPreLoad::loadAll()
{
	int ret = -1;
	CCArray* arr = m_dict->allKeys();
	do{
		unsigned int i;
		for(i=0; i<arr->count(); ++i)
		{
			CCString* p = dynamic_cast<CCString*>(arr->objectAtIndex(i));
			if(!p)
				break;

			CCDictionary* pdic = dynamic_cast<CCDictionary*>(m_dict->objectForKey(p->getCString()));
			if(!pdic)
				break;

			if(loadSingle(p->getCString(), pdic)!=0)
				break;
		}
			
		if(i!=arr->count())
		{
			break;
		}

		ret = 0;

	}while(0);
	delete arr;

	return ret;
}

int CCPreLoad::initFetch()
{
	m_tmpKeyArr = m_dict->allKeys();
	m_tmpKeyArr->retain();

	return 0;
}

int CCPreLoad::fetchNext()
{
	if(!m_dict)
		return -1;

	if(m_tmpIdx >= (int)m_dict->count() - 1)
		return 0; 

	if(!m_tmpKeyArr && initFetch()!=0)
	{
		return -1;
	}

	++m_tmpIdx;

	CCString* p = dynamic_cast<CCString*>(m_tmpKeyArr->objectAtIndex(m_tmpIdx));
	if(!p)
		return -1;	
	
	m_tmpFileName = p->getCString();

	return 1;
}

int CCPreLoad::loadCurFile()
{
	if(!m_dict || !m_tmpKeyArr || m_tmpIdx >= (int)m_dict->count())
		return -1;

	CCString* p = dynamic_cast<CCString*>(m_tmpKeyArr->objectAtIndex(m_tmpIdx));
	if(!p)
		return -1;

	CCDictionary* pdic = dynamic_cast<CCDictionary*>(m_dict->objectForKey(p->getCString()));
	if(!pdic)
		return -1;

	if(loadSingle(p->getCString(), pdic)!=0)
		return -1;

	return 0;
}

int CCPreLoad::loadSingle(const char* key, CCDictionary* dict)
{
	CCString* p1 = dynamic_cast<CCString*>(dict->objectForKey("type"));
	if(!p1)
		return -1;
	
	if(p1->intValue() == RESOURCE_TYPE_PIC)
	{
		if(CCTextureCache::sharedTextureCache()->addImage(key)==NULL)
		{
			return -1;
		}
	}
	else
	{
		string tmp = key;
		if(!cacheFramesForPlist(tmp.substr(0, tmp.rfind(".")).append(".plist").c_str(), key))
			return -1;
	}

	m_tmpFileSize= 0;
	if(m_checkSize)
	{
		string pszFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(key).c_str();
		FILE *fp = fopen(pszFileName.c_str(), "rb");
		if(fp)
		{
			fseek(fp,0,SEEK_END);
			m_tmpFileSize = ftell(fp);
			fclose(fp);
			//write to dict
			dict->setObject(CCString::createWithFormat("%d",m_tmpFileSize),"size");
		}
	}

	if(m_tmpFileSize== 0)
	{
		CCString* p2 = dynamic_cast<CCString*>(dict->objectForKey("size"));
		if(p2)
			m_tmpFileSize=p2->intValue();
	}

	++m_tmpLoadedFile;
	m_tmpLoadedBytes += m_tmpFileSize;
	return 0;
}


int CCPreLoad::dumpXMLToFile(const char* fileName)
{
	ofstream of(fileName);
	if(!of.good())
	{
		CCLOG("open %s fail", fileName);
		return -1;
	}

	if( dumpXML(of) != 0)
		return -1;
	of.close();
	return 0;
}


bool CCPreLoad::cacheFramesForPlist(const char* plist, const char* textureFileName)
{
	bool ret = false;
	do{
		//private权限不好继承，直接挑出来改，Zwoptex.swf 1.0的version
		CCTexture2D *pobTexture = CCTextureCache::sharedTextureCache()->addImage(textureFileName);
		if(pobTexture == NULL)
			break;

		string pszPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
		CCDictionary *dictionary = CCDictionary::createWithContentsOfFileThreadSafe(pszPath.c_str());

		CCDictionary *framesDict = (CCDictionary*)dictionary->objectForKey("frames");
		int format = 0;

		CCDictElement* pElement = NULL;
		CCDICT_FOREACH(framesDict, pElement)
		{
			CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
			std::string spriteFrameName = pElement->getStrKey();
			CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName.c_str());
			if (spriteFrame)
			{
				continue;
			}
		    
			int format = 0;//就只挑这个
			if(format == 0) 
			{
				float x = frameDict->valueForKey("x")->floatValue();
				float y = frameDict->valueForKey("y")->floatValue();
				float w = frameDict->valueForKey("width")->floatValue();
				float h = frameDict->valueForKey("height")->floatValue();
				float ox = frameDict->valueForKey("offsetX")->floatValue();
				float oy = frameDict->valueForKey("offsetY")->floatValue();
				int ow = frameDict->valueForKey("originalWidth")->intValue();
				int oh = frameDict->valueForKey("originalHeight")->intValue();
				// check ow/oh
				if(!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
				}
				// abs ow/oh
				ow = abs(ow);
				oh = abs(oh);
				// create frame
				spriteFrame = new CCSpriteFrame();
				spriteFrame->initWithTexture(pobTexture, 
											CCRectMake(x, y, w, h), 
											false,
											CCPointMake(ox, oy),
											CCSizeMake((float)ow, (float)oh)
											);
			} 

			// add sprite frame
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(spriteFrame, spriteFrameName.c_str());
			m_tmpFrames.insert(make_pair(spriteFrameName,spriteFrame));
			spriteFrame->release();
		}
		dictionary->release();
		ret = true;
	}while(0);
	return ret;
}