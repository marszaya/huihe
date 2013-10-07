#include "tconfHelper.h"
#include <string.h>
#ifdef TCONF_USE_XML
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
using namespace rapidxml;
#endif

CTconfHelper::CTconfHelper()
{
}

CTconfHelper::~CTconfHelper()
{
}

void CTconfHelper::init(const char* filePath, int colIdx)
{
	m_valid = false;
	m_colIdx = colIdx;

	int ret=0;
#ifdef TCONF_USE_XML
	if(strstr(filePath, ".xml")!=NULL)
	{
		ret = loadFromXML(filePath);
	}
	else
	{
		ret = loadFromFile(filePath);
	}
#else
	ret = loadFromFile(filePath);
#endif
	if(ret==0)
	{
		if(createIdx() == 0)
		{
			if(selfCheck()==0)
			{
				m_valid = true;
			}
		}
	}
}

const TconfRow* CTconfHelper::getRowByKey(const char* key)
{
	if(this->m_colIdx < 0)
	{
		m_err << "no index exist" << endl;
		return NULL;
	}

	map<string, int>::iterator it = this->m_rowIdxMap.find(key);
	if(it == this->m_rowIdxMap.end())
	{
		m_err << "no row for key " << key << endl;
		return NULL;
	}

	return &(m_table.rows(it->second));
}

#ifdef TCONF_USE_XML
int CTconfHelper::loadFromXML(const char* filePath)
{
	try{
		file<> theXmlFile(filePath);
		xml_document<> theDoc;
		xml_node<> * ptheNode;
		theDoc.parse<parse_default>(theXmlFile.data());

		ptheNode = theDoc.first_node();
		if(!ptheNode)
		{
			m_err << "no root node" << endl;
			return -1;
		}

		ptheNode = ptheNode->first_node();
		if(!ptheNode)
		{
			m_err << "no first row" << endl;
			return -1;
		}

		bool colParsed = false;
		int rowCount = 1;
		while(ptheNode != NULL)
		{
			xml_node<>* pcol = ptheNode->first_node();
			int ci=0;
			while(pcol!=NULL)
			{
				if(!colParsed)
				{
					TconfColDef* p = m_table.add_coldefs();
					p->set_name(pcol->name());
					p->set_type("string");
				}
				else
				{
					//check col
					if(ci >= m_table.coldefs_size() || m_table.coldefs(ci).name() != pcol->name())
					{
						m_err << "row " << rowCount << " format not match first row" << endl;
						return -1;
					}
				}

				TconfRow* pr = m_table.add_rows();
				pr->add_values(pcol->value());
			
				pcol = pcol->next_sibling();
				++ci;
			}

			if(ci != m_table.coldefs_size())
			{
				m_err << "row " << rowCount << " format not match first row" << endl;
				return -1;
			}

			colParsed = true;
			ptheNode = ptheNode->next_sibling();
			++rowCount;
		}
	}
	catch(exception& e)
	{
		m_err << "xml exception: " << e.what() << endl;
		return -1;
	}

	return 0;
}
#endif

int CTconfHelper::loadFromFile(const char* filePath)
{
	FILE* f = fopen(filePath, "rb");
	if(f == NULL)
	{
		m_err << "open [" << filePath << "] fail errno=" << errno << endl;
		return -1;
	}
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	char* buff = new char[size];
	if(buff == NULL)
	{
		m_err << "new char[" << size << "] fail" << endl;
		fclose(f);
		return -1;
	}

	rewind(f);
	int readed=fread(buff, 1, size, f);
	if(readed != size)
	{
		m_err << "readed[" << readed << "] != [" << size << "]" << endl;
		fclose(f);
		return -1;
	}

	if(!m_table.ParseFromArray(buff, readed))
	{
		m_err << "ParseFromArray fail" << endl;
		fclose(f);
		return -1;
	}

	fclose(f);
	return 0;
}

int CTconfHelper::selfCheck()
{
	return 0;
}

int CTconfHelper::getColIdx(const char* col)
{
	map<string, int>::iterator it = this->m_colIdxMap.find(col);
	if(it == this->m_colIdxMap.end())
	{
		m_err << "no col " << col << endl;
		return -1;
	}

	return it->second;
}

int CTconfHelper::createIdx()
{
	//列名->下标
	for(int i=0; i<m_table.coldefs_size(); ++i)
	{
		m_colIdxMap[m_table.coldefs(i).name()] = i;
	}

	if(m_colIdx < 0)
		return 0;

	if(m_colIdx >= m_table.coldefs_size())
	{
		m_err << "m_colIdx[" << m_colIdx << "] >= " <<   m_table.coldefs_size() << endl;
		m_colIdx = -1;
		return -1;
	}

	for(int i=0; i<m_table.rows_size();++i)
	{
		this->m_rowIdxMap[m_table.rows(i).values(m_colIdx)] = i;
	}

	return 0;
}