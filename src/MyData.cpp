#include "MyData.h"
#include "MyControl.h"
#include "DataUtil.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "StrTool.h"
#include "tconfManager.h"
#include "mathTools.h"
#include "DEFINED_VALUES.h"
using namespace std;

CMyData* CMyData::m_pdata=NULL;
string CMyData::curUser;

const char* CMyData::USER_DATA_FILE = ".data";

CMyData::CMyData(void)
{
	m_userSave=NULL;
}

CMyData::~CMyData(void)
{
}

void CMyData::bindUser()
{
	m_userName = curUser;
	m_fileName = m_userName;
	m_fileName.append(USER_DATA_FILE);
	//请使用writeable path替代
	string retPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("preload.xml");

	m_fileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(m_fileName.c_str(), retPath.c_str());
}

CMyData* CMyData::getSharedData()
{
	if(!m_pdata)
	{
		m_pdata = new CMyData();
		m_pdata->bindUser();
		if(!m_pdata->loadUser()) 
		{
			m_pdata->initData();
		}
	}

	return m_pdata;
}

void CMyData::initData()
{
	TransactionGuarder guarder(this);
	int i=0;
	Account* paccount = m_user.mutable_account();
	RoleSet* proleset = m_user.mutable_role();
	ItemSet* pitems = m_user.mutable_item();
	Identity* pid = m_user.mutable_id();

	paccount->set_gold(1000);
	paccount->set_money(100);
	paccount->mutable_expr()->set_expr(0);
	paccount->mutable_expr()->set_level(1);
	paccount->mutable_vip()->set_expr(0);
	paccount->mutable_vip()->set_level(0);

	pid->set_id(this->m_userName);
	pid->set_name(this->m_userName);
	
	proleset->set_battlelistmax(6);
	proleset->set_maxid(0);
	
	//创建主将
	Role* prole = createNewRole(proleset, 1);
	prole->set_ismain(1);
	proleset->set_mainroleidx(0);
	//加入作战队列
	proleset->add_battlelist()->CopyFrom(prole->id());

	this->addItem(1001, 1);
	this->addItem(2001, 1);
	this->addItem(2002, 1);
	this->addItem(2004, 1,1);
	guarder.clear();
}

Role* CMyData::createNewRole(RoleSet* rs, int unitid, int whichArray)
{
	Role* ret = NULL;
	do{
		int maxid = rs->maxid();
		Role* prole = NULL;
		if(whichArray==0)
			prole = rs->add_roles();
		else
		{
			prole = rs->add_shoproles();
			prole->set_hireflag(unitid);
		}

		CAutoUnitTab* unitconf = TCONF_GET(CAutoUnitTab);
		if(unitconf == NULL)
			break;

		const TconfRow* pconfrow= unitconf->getRowByKey(CStrTool::strDecimal(unitid).c_str());
		if(pconfrow == NULL)
		{
			CCLog("CAutoUnitTab no id=%d", unitid);
			break;
		}
	
		prole->mutable_id()->set_id(CStrTool::strDecimal(maxid+1));
		prole->mutable_id()->set_name(string(unitconf->getRowValue(pconfrow, unitconf->NAME)).append(prole->mutable_id()->id()));
		prole->set_showtype(atoi(unitconf->getRowValue(pconfrow, unitconf->SHOWTYPE)));
		prole->mutable_expr()->set_expr(0);
		prole->mutable_expr()->set_level(1);

		BattleAttr* pbr = prole->mutable_battr();
		pbr->set_hp(atoi(unitconf->getRowValue(pconfrow, unitconf->BASEHP)));
		pbr->set_ad(atoi(unitconf->getRowValue(pconfrow, unitconf->BASEATK)));
		pbr->set_ap(0);
		pbr->set_arm(atoi(unitconf->getRowValue(pconfrow, unitconf->BASEDEF)));
		pbr->set_mr(0);
		pbr->set_as(100);
		pbr->set_energy(atoi(unitconf->getRowValue(pconfrow, unitconf->BASEENERGY)));

		BattleSkill* pbs = prole->mutable_skill();
		vector<string> vout;
		CStrTool::split(unitconf->getRowValue(pconfrow, unitconf->SKILLS), ",", vout);
		for(unsigned int i=0; i<vout.size(); ++i)
		{
			int skillid = atoi(vout[i].c_str());
			if(skillid > 0)
				pbs->add_ids(skillid);
		}
		

		rs->set_maxid(maxid+1);
		ret = prole;
	}while(0);
	return ret;
}


bool CMyData::loadFromFile(google::protobuf::MessageLite& msg, const char* filePath, bool alert)
{
	ifstream fin(filePath,ios_base::in|ios_base::binary);
	if(!(fin.good()))
	{
		if(alert)
			CCMessageBox("loadFromFile open fail", "error");
		return false;
	}

	char buff[1024*100]; //暂时开这么大

	fin.read(buff,sizeof(buff));
	int readcount = fin.gcount();

	if(!msg.ParseFromArray(buff, readcount))
	{
		if(alert)
			CCMessageBox("loadFromFile ParseFromArray fail", "error");
		return false;
	}

	return true;
}

bool CMyData::saveToFile(google::protobuf::MessageLite& msg, const char* filePath)
{
	ofstream fout(filePath, ios_base::out|ios_base::binary);
	if(!(fout.good()))
	{
		CCMessageBox("writeToFile open fail", "error");
		return false;
	}

	//CCMessageBox(CStrTool::strDecimal(m_role.has_battr()).c_str(), "trace");
	//CCMessageBox(CStrTool::strDecimal(m_role.battr().atk()).c_str(), "trace");

	string output;
	if(!msg.SerializeToString(&output))
	{
		CCMessageBox("writeToFile SerializeToString fail", "error");
		return false;
	}

	fout.write(output.data(), output.length());
	if(!(fout.good()))
	{
		CCMessageBox("writeToFile fail", "error");
		return false;
	}

	//CCMessageBox(CStrTool::strDecimal(output.length()).c_str(), "trace");

	return true;
}

Role* CMyData::mainRole()
{
	Role* ret = NULL;
	RoleSet* proleset = m_user.mutable_role();
	if(proleset->has_mainroleidx() && proleset->mainroleidx() < proleset->roles_size())
	{
		ret = proleset->mutable_roles(proleset->mainroleidx());
	}

	return ret;
}

RoleSet* CMyData::allRoles()
{
	return  m_user.mutable_role();
}

Role* CMyData::getRoleById(const char* sid)
{
	RoleSet* proleset = m_user.mutable_role();
	Role* ret = NULL;
	for(int i=0; i<proleset->roles_size(); ++i)
	{
		if(proleset->roles(i).id().id() == sid)
		{
			ret = proleset->mutable_roles(i);
			break;
		}
	}
	return ret;
}

Role* CMyData::getRoleByIdx(int idx)
{
	RoleSet* proleset = m_user.mutable_role();
	Role* ret = NULL;
	if(idx >=0 && idx < proleset->roles_size())
	{
		ret = proleset->mutable_roles(idx);
	}
	return ret;
}


bool CMyData::delUncountableItem(int subtype,int itemidx)
{
	bool ret = false;
	do{
		CAutoItemTab* itemTab = TCONF_GET(CAutoItemTab);
		if(!itemTab)
			break;

		const char* pval = itemTab->getValue(
			CStrTool::strDecimal(subtype).c_str(), itemTab->COUNTABLE);
		if(pval == NULL)
			break;
		if(atoi(pval) != 0)
			break;

		ItemSet* is = m_user.mutable_item();
		if(itemidx < 0)
		{
			//查找第一个
			for(int i=0; i<is->items_size(); ++i)
			{
				if(is->mutable_items(i)->subtype()==subtype)
				{
					itemidx = i;
					break;
				}
			}
			if(itemidx < 0)
				break;
		}
		else
		{
			if(itemidx <0 || itemidx >= is->items_size())
				break;

			if(is->mutable_items(itemidx)->subtype() != subtype)
				break;
		}

		if(itemidx != is->items_size()-1)
		{
			is->mutable_items()->SwapElements(itemidx, is->items_size()-1);
		}
		is->mutable_items()->RemoveLast();
		throwEvent(CMyControl::CMD_DATA_BAG_MODIFIED);
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::addUncountableItem(int subtype, int level)
{
	bool ret = false;
	do{
		CAutoItemTab* itemTab = TCONF_GET(CAutoItemTab);
		if(!itemTab)
			break;

		const char* pval = itemTab->getValue(
			CStrTool::strDecimal(subtype).c_str(), itemTab->COUNTABLE);
		if(pval == NULL)
			break;
		if(atoi(pval) != 0)
			break;

		appendItem(subtype, 1, level);
		throwEvent(CMyControl::CMD_DATA_BAG_MODIFIED);
		ret = true;
	}while(0);
	return ret;
}

void CMyData::appendItem(int subtype, int num, int level)
{
	ItemSet* pbag = m_user.mutable_item();
	Item* pitem = pbag->add_items();
	int newid = pbag->maxid()+1;
	pbag->set_maxid(newid);
	pitem->mutable_id()->set_id(CStrTool::strDecimal(newid));
	pitem->set_num(num);
	pitem->set_subtype(subtype);
	if(level >= 0)
		pitem->mutable_expr()->set_level(level);
}

bool CMyData::modifyCountableItem(int subtype, int numChange)
{
	bool ret= false;
	ItemSet* pbag = m_user.mutable_item();

	do{
		
		CAutoItemTab* itemTab = TCONF_GET(CAutoItemTab);
		if(!itemTab)
			break;

		const char* pval = itemTab->getValue(
			CStrTool::strDecimal(subtype).c_str(), itemTab->COUNTABLE);
		if(pval == NULL)
			break;
		if(atoi(pval) == 0)
			break;
		
		bool found = false;
		for(int i=0; i<pbag->items_size(); ++i)
		{
			if(pbag->items(i).subtype() == subtype)
			{
				found = true;

				int num = pbag->items(i).num();
				num += numChange;
				if(num< 0)
				{
					break;
				}

				if(num == 0)
				{
					if(i != pbag->items_size() - 1)
					{
						pbag->mutable_items()->SwapElements(i, pbag->items_size()-1);
					}
					pbag->mutable_items()->RemoveLast();
				}
				else 
				{
					pbag->mutable_items(i)->set_num(num);
				}

				ret = true;
				break;
			}
		}

		if(!found && numChange > 0)
		{
			appendItem(subtype, numChange);
			ret = true;
			break;
		}
	}while(0);

	if(ret)
	{
		throwEvent(CMyControl::CMD_DATA_BAG_MODIFIED);
		ret = true;
	}
	return ret;
}

bool CMyData::modifyGold(int goldChange)
{
	TransactionGuarder guarder(this);

	Account* pa = m_user.mutable_account();
	long long gold = pa->gold() + goldChange;
	if(gold < 0)
	{
		return false;
	}

	pa->set_gold(gold);

	this->throwEvent(CMyControl::CMD_DATA_ACCOUNT_MODIFIED);
	guarder.clear();
	return true;
}

bool CMyData::modifyMoney(int goldChange)
{
	TransactionGuarder guarder(this);
	Account* pa = m_user.mutable_account();
	long long v = pa->money() + goldChange;
	if(v < 0)
	{
		return false;
	}

	pa->set_money(v);

	this->throwEvent(CMyControl::CMD_DATA_ACCOUNT_MODIFIED);
	
	guarder.clear();
	return true;
}

bool CMyData::modifyExpr(int exprChange)
{
	TransactionGuarder guarder(this);
	Experience* pexp = m_user.mutable_account()->mutable_expr();
	long long expr =  pexp->expr() + exprChange;
	if(expr < 0)
	{
		return false;
	}

	CAutoExprTab* pexptab  =TCONF_GET(CAutoExprTab);
	if(!pexptab)
		return false;

	int level = 0;
	int newLevel = 0;
	long long levelExp = 0;
	while(true){
		const char* pstr = pexptab->getValue(CStrTool::strDecimal(++level).c_str(), pexptab->BASEEXPR);
		if(pstr==NULL)
		{
			newLevel = level - 1;
			break;
		}
		
		if(CStrTool::strToLL(pstr) > expr)
		{
			break;
		}

		newLevel = level;
		levelExp = expr - atoi(pstr);
	}

	pexp->set_expr(expr);
	pexp->set_level(newLevel);
	pexp->set_levelexpr(levelExp);

	this->throwEvent(CMyControl::CMD_DATA_ACCOUNT_MODIFIED);
	guarder.clear();
	return true;
}

bool CMyData::getLevelExpr(long long& levelExpr, long long& maxLevelExpr)
{
	Experience* pexp = m_user.mutable_account()->mutable_expr();
	levelExpr = pexp->levelexpr();
	CAutoExprTab* pexptab  =TCONF_GET(CAutoExprTab);
	if(!pexptab)
		return false;

	int level = pexp->level();
	if(level <= 0)
		level = 1;
	const char* pstr = pexptab->getValue(CStrTool::strDecimal(level).c_str(), pexptab->LEVELEXPR);
	if(!pstr)
		return false;
	maxLevelExpr=CStrTool::strToLL(pstr);

	return true;
}


bool CMyData::delItem(Item* pitem, int num, int itemidx)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		if(num<=0)
			break;
		CAutoItemTab* itemTab = TCONF_GET(CAutoItemTab);
		if(!itemTab)
			break;

		const char* pval = itemTab->getValue(
			CStrTool::strDecimal(pitem->subtype()).c_str(), itemTab->COUNTABLE);
		if(pval == NULL)
			break;

		if(atoi(pval)!=0)
		{
			if(!modifyCountableItem(pitem->subtype(), 0-num))
				break;
		}
		else
		{
			if(num > 1)
				break;
			if(!delUncountableItem(pitem->subtype(), itemidx))
				break;
		}

		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::addItem(int subtype, int num, int level)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		if(num<=0)
			break;
		CAutoItemTab* itemTab = TCONF_GET(CAutoItemTab);
		if(!itemTab)
			break;

		const char* pval = itemTab->getValue(
			CStrTool::strDecimal(subtype).c_str(), itemTab->COUNTABLE);
		if(pval == NULL)
			break;

		if(atoi(pval)!=0)
		{
			if(!modifyCountableItem(subtype, num))
				break;
		}
		else
		{
			if(num > 1)
				break;
			if(!this->addUncountableItem(subtype, level))
				break;
		}

		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::useItem(int itemidx, int num)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		ItemSet* is=m_user.mutable_item();
		if(itemidx <0 || itemidx >= is->items_size())
			break;

		Item* pitem = is->mutable_items(itemidx);
		int subtype = pitem->subtype();

		if(!delItem(pitem, num, itemidx))
			break;

		if(!itemEffect(subtype,num))
			break;
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::saleItem(int itemidx, int num)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		ItemSet* is = m_user.mutable_item();

		if(itemidx <0 || itemidx >= is->items_size())
			break;

		Item* itm = is->mutable_items(itemidx);
		int price = CDataUtil::getSellPrice(itm->subtype())*num;
		if(!delItem(itm, num, itemidx))
			break;
		if(!modifyGold(price))
			break;
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

int CMyData::positiveModify(int src, int delta)
{
	int ret = src + delta;
	if(ret < 0)
		ret = 0;

	return ret;
}

Item* CMyData::getEquip(Role* r, int tag)
{
	Item* ret = NULL;
	do{
		if(tag < 0 || tag >= Equip::END)
			break;
		Equip* ep = r->mutable_equip(); 
		for(int i=ep->items_size(); i<=tag; ++i)
		{
			ep->add_items();
		}

		ret = ep->mutable_items(tag);
	}while(0);
	return ret;
}

bool CMyData::equip(Role* r, int itemidx)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		ItemSet* is = m_user.mutable_item();

		if(itemidx <0 || itemidx >= is->items_size())
			break;
		
		Item* target = is->mutable_items(itemidx);
		if(CDataUtil::getMajorType(target->subtype()) != Item::MAJOR_TYPE_EQUIP)
			break;

		CAutoEquipTab* peqtab = TCONF_GET(CAutoEquipTab);
		if(!peqtab)
			break;
	
		const char* posStr = peqtab->getValue(
			CStrTool::strDecimal(target->subtype()).c_str(), peqtab->POSITON);
		if(posStr == NULL)
			break;
		int tag = atoi(posStr);

		int level = 0;
		if(target->has_expr())
			level = target->expr().level();

		int attridx = CDataUtil::getEquipAttrIdx(target->subtype());
		if(attridx < 0)
			break;

		int attrvalue = CDataUtil::getEquipAttrValue(target->subtype(), level);
		if(attrvalue < 0)
			break;

		if(!modifyRoleAttr(r, attridx, attrvalue))
			break;

		Item* itm=this->getEquip(r, tag);
		if(itm && itm->has_id())
		{
			int lvl= 0;
			if(itm->has_expr())
				lvl = itm->expr().level();

			int ai = CDataUtil::getEquipAttrIdx(itm->subtype());
			if(ai < 0)
				break;

			int av = CDataUtil::getEquipAttrValue(itm->subtype(), lvl);
			if(av < 0)
				break;			

			if(!modifyRoleAttr(r, ai, 0-av))
				break;	

			is->add_items()->CopyFrom(*itm);
			itm->Clear();
		}

		itm->CopyFrom(*target);

		if(itemidx != is->items_size()-1)
		{
			is->mutable_items()->SwapElements(itemidx, is->items_size()-1);
		}
		is->mutable_items()->RemoveLast();

		this->throwEvent(CMyControl::CMD_DATA_ROLE_EQUIP_MODIFIED);
		this->throwEvent(CMyControl::CMD_DATA_BAG_MODIFIED);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::unequip(Role* r, int tag)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		Item* itm=this->getEquip(r, tag);
		if(!itm || !itm->has_id())
			break;

		int level = 0;
		if(itm->has_expr())
			level = itm->expr().level();

		int attridx = CDataUtil::getEquipAttrIdx(itm->subtype());
		if(attridx < 0)
			break;

		int attrvalue = CDataUtil::getEquipAttrValue(itm->subtype(), level);
		if(attrvalue < 0)
			break;

		if(!modifyRoleAttr(r, attridx, 0-attrvalue))
			break;

		ItemSet* is = m_user.mutable_item();
		is->add_items()->CopyFrom(*itm);
		itm->Clear();

		this->throwEvent(CMyControl::CMD_DATA_ROLE_EQUIP_MODIFIED);
		this->throwEvent(CMyControl::CMD_DATA_BAG_MODIFIED);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}



int CMyData::getItemIdxById(const string& id)
{
	int ret = -1;
	do{
		ItemSet* is = m_user.mutable_item();
		for(int i=0; i<is->items_size(); ++i)
		{
			if(is->items(i).id().id() == id)
			{
				ret = i;
			}
		}
		
	}while(0);
	return ret;
}

bool CMyData::modifyRoleAttr(Role* prole, int attrIdx, int attrValue)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		BattleAttr* ba = prole->mutable_battr();
		if(attrIdx == Item::EFFECT_AD)
		{
			ba->set_ad(this->positiveModify(ba->ad(),attrValue));
		}
		else if(attrIdx == Item::EFFECT_ARMOR)
		{
			ba->set_arm(this->positiveModify(ba->arm(),attrValue));
		}
		else if(attrIdx == Item::EFFECT_HP)
		{
			ba->set_hp(this->positiveModify(ba->hp(),attrValue));
		}
		else if(attrIdx == Item::EFFECT_SPD)
		{
			ba->set_as(this->positiveModify(ba->as(),attrValue));
		}
		else
		{
			break;
		}
		this->throwEvent(CMyControl::CMD_DATA_ROLE_ATTR_MODIFIED);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::payItem(int shopID, int num)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		if(num <=0)
			break;

		CAutoShopTab* ptable = TCONF_GET(CAutoShopTab);
		if(!ptable)
			break;

		const TconfRow* row = ptable->getRowByKey(CStrTool::strDecimal(shopID).c_str());
		if(!row)
			break;

		const char* v = ptable->getRowValue(row, ptable->ITEMTYPE);
		if(v==NULL)
			break;
		int subtype = atoi(v);

		v = ptable->getRowValue(row, ptable->ITEMNUM);
		if(v==NULL)
			break;
		int itemNum = atoi(v);

		v = ptable->getRowValue(row, ptable->PAYTYPE);
		if(v==NULL)
			break;
		int payType = atoi(v);

		v = ptable->getRowValue(row, ptable->PRICEREAL);
		if(v==NULL)
			break;
		int payPrice = atoi(v);

		bool payRet= false;
		if(payType == Item::PAY_GOLD)
		{
			payRet = modifyGold(0-payPrice*num);
		}
		else
		{
			payRet = modifyMoney(0-payPrice*num);
		}

		if(!payRet)
			break;

		if(!addItem(subtype, itemNum*num))
			break;
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::itemEffect(int subtype, int num)
{
	bool ret = false;
	do{
		int effectType = CDataUtil::getEffectType(subtype);
		int effectValue = CDataUtil::getEffectValue(subtype)*num;
		if(effectType == Item::EFFECT_GOLD)
		{
			ret=modifyGold(effectValue);
		}
		else if(effectType == Item::EFFECT_EXP)
		{
			ret=modifyExpr(effectValue);
		}
		else if(effectType == Item::EFFECT_MONEY)
		{
			ret=modifyMoney(effectValue);
		}
		else if(effectType == Item::EFFECT_PACKED)
		{
			ret=openItemPack(subtype);
		}
		else
		{
			break;
		}
	}while(0);
	return ret;
}


bool CMyData::openItemPack(int subtype)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		CAutoItemPackTab* pconf = TCONF_GET(CAutoItemPackTab);
		if(!pconf)
			break;

		const char* v = pconf->getValue(CStrTool::strDecimal(subtype).c_str(),
			pconf->PACKTYPE);
		if(v==NULL)
			break;

		int packtype = atoi(v);
		//暂时不判断packtype

		//这里有隐含规则
		//至少有一个列,列名从item0开始item1，item2 ...
		v = pconf->getValue(CStrTool::strDecimal(subtype).c_str(),
			pconf->ITEM0);
		if(v==NULL)		
			break;
		
		string firstCol = pconf->ITEM0;
		string itemColNameBase = firstCol.substr(0, firstCol.length()-1);
		bool hasError=false;
		for(int i=0; true; ++i)
		{
			string singleItem;
			if(i!=0)
			{
				v = pconf->getValue(CStrTool::strDecimal(subtype).c_str(),
					itemColNameBase.append(CStrTool::strDecimal(i)).c_str());
				if(!v)
					break;
			}
			singleItem = v;

			vector<string> output;
			CStrTool::split(singleItem.c_str(), ":", output);
			if(output.size() < 2)
			{
				hasError = true;
				break;
			}
			
			int itemType = atoi(output[0].c_str());
			int itemNum = atoi(output[1].c_str());
			int level = -1;
			if(output.size() > 2)
				level = atoi(output[2].c_str());

			//虚拟物品直接使用
			if(CDataUtil::getMajorType(itemType) == Item::MAJOR_TYPE_VIRTUAL)
			{
				if(!itemEffect(itemType, itemNum))
				{
					hasError = true;
					break;
				}
			}
			else //加入背包
			{
				if(!addItem(itemType, itemNum, level))
				{
					hasError = true;
					break;
				}
			}
		}

		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}


bool CMyData::refreshRoleHire(int num, bool free, bool noEvent)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		if(free && m_user.role().shoproles_size()!=0)
			break;

		if(!free)
		{
			if(!this->modifyGold(0-DEFINED_VALUE_HIRE_REFRESH_COST))
			{
				throwEvent(CMyControl::CMD_DATA_ROLE_HIRED_NO_MONEY);
				postEventsToControl();
				break;
			}
		}

		RoleSet* proleset = m_user.mutable_role();
		proleset->clear_shoproles();

		//从战将随机表中读取 set=DEFINED_VALUE_HIRE_RANDOM_SET
		CAutoUnitRandomTab* pconfur = TCONF_GET(CAutoUnitRandomTab);
		if(pconfur == NULL)
			break;

		const TconfTable& tur = pconfur->getTable();
		vector<const TconfRow*> rowset;
		for(int ti=0; ti<tur.rows_size(); ++ti)
		{
			const TconfRow& tr = tur.rows(ti);
			if(strcmp(pconfur->getRowValue(&tr, pconfur->RANDOMSET),DEFINED_VALUE_HIRE_RANDOM_SET)==0)
			{
				rowset.push_back(&tr);
			}
		}

		if(rowset.size() == 0)
		{
			CCLog("CAutoUnitRandomTab no randomset=%s", DEFINED_VALUE_HIRE_RANDOM_SET);
			break;
		}
		//随机抽取num个将，不可重复
		const TconfRow* pselect = NULL;
		for(int i=0; i<num && rowset.size()>=0; ++i)
		{
			//概率总数
			int weighttotal = 0;
			unsigned int ri=0;
			for(ri=0; ri<rowset.size();++ri)
			{
				weighttotal += atoi(pconfur->getRowValue(rowset[ri],pconfur->WEIGHT));
			}

			if(weighttotal <= 0)
				break;

			//抽取
			int randweight = gGameTools.rand(0,weighttotal-1);
			for(ri=0; ri<rowset.size();++ri)
			{
				int thisweight = atoi(pconfur->getRowValue(rowset[ri],pconfur->WEIGHT));
				if(randweight < thisweight)
				{
					pselect = rowset[ri];
					//从池子里除去
					if(ri != rowset.size()-1)
						rowset[ri] = rowset[rowset.size()-1];
					rowset.pop_back();
					break;
				}
				else
				{
					randweight -= thisweight;
				}
			}
			
			if(pselect != NULL)
			{
				this->createNewRole(proleset, atoi(pconfur->getRowValue(pselect, pconfur->ID)),1);
			}
		}
	
		if(!noEvent)
		{
			this->throwEvent(CMyControl::CMD_DATA_ROLE_HIRED);
		}
		guarder.clear();
		ret = true;
	}while(0);
	return ret;

}

bool CMyData::hireRole(int idx)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		if(idx < 0 || idx >= m_user.role().shoproles_size())
			break;

		Role* p = m_user.mutable_role()->mutable_shoproles(idx);
		if(p->hireflag()==0)
			break;

		//扣钱
		CAutoUnitRandomTab* pconfur = TCONF_GET(CAutoUnitRandomTab);
		if(pconfur == NULL)
			break;

		int goldNeed = atoi(pconfur->getValue(CStrTool::strDecimal(p->hireflag()).c_str(),pconfur->GOLD));
		if(!this->modifyGold(0-goldNeed))
		{
			this->throwEvent(CMyControl::CMD_DATA_ROLE_HIRED_NO_MONEY);
			this->postEventsToControl();
			break;
		}

		if(m_user.role().roles_size() >= CDataUtil::getOwnUnitMaxByLevel(m_user.account().expr().level()))
		{
			this->throwEvent(CMyControl::CMD_DATA_UNIT_OWN_MAX);
			this->postEventsToControl();
			break;
		}

		m_user.mutable_role()->add_roles()->CopyFrom(*p);
		p->set_hireflag(0);

		this->throwEvent(CMyControl::CMD_DATA_ROLE_ATTR_MODIFIED);
		this->throwEvent(CMyControl::CMD_DATA_ROLE_HIRED);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::fireRole(int idx)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		//第一个不能解雇
		RoleSet* rs= m_user.mutable_role();
		int last = rs->roles_size()-1;
		if(idx <= 0 || idx > last)
			break;

		if(idx != last)
			rs->mutable_roles()->SwapElements(idx, last);

		rs->mutable_roles()->RemoveLast();

		//重新排列battlelist
		updateBattleList();

		this->throwEvent(CMyControl::CMD_DATA_ROLE_FIRED);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::startTransaction()
{
	bool ret = false;
	do{
		if(m_userSave)
			break;
		m_userSave = new User();
		m_userSave->CopyFrom(m_user);
		ret = true;
	}while(0);
	return ret;
}

void CMyData::submitTransaction()
{
	do{
		if(!m_userSave)
			break;
		delete m_userSave;
		m_userSave = NULL;
		postEventsToControl();
		saveUser();
	}while(0);
}

void CMyData::rollbackTransaction()
{
	do{
		if(!m_userSave)
			break;
		m_user.CopyFrom(*m_userSave);
		delete m_userSave;
		m_userSave = NULL;
	}while(0);
}
	
void CMyData::throwEvent(int cmd)
{
	do{
		bool hasSaved = false;
		for(unsigned int i=0; i<m_eventSave.size(); ++i)
		{
			if(m_eventSave[i] == cmd)
			{
				hasSaved = true;
				break;
			}
		}

		if(hasSaved)
			break;
		m_eventSave.push_back(cmd);
	}while(0);
}

void CMyData::postEventsToControl()
{
	for(unsigned int i=0; i<m_eventSave.size(); ++i)
	{
		CMyControl::getSharedControl()->invokeCmd(m_eventSave[i]);
	}
	m_eventSave.clear();
}

CMyData::TransactionGuarder::TransactionGuarder(CMyData* host)
{
	m_host = host;
	m_valid = m_host->startTransaction();
}

CMyData::TransactionGuarder::~TransactionGuarder()
{
	if(m_valid)
		m_host->rollbackTransaction();
}

void CMyData::TransactionGuarder::clear()
{
	if(m_valid)
	{
		m_valid = false;
		m_host->submitTransaction();
	}
}

bool CMyData::createIdxForRoles(vector<int>& output)
{
	bool ret = false;
	do{
		//冒泡排序
		RoleSet* rs = m_user.mutable_role();
		int total = rs->roles_size();
		int i=0;
		output.clear();
		for(i=0; i<total; ++i)
		{
			output.push_back(i);
		}

		//第一个是主将，永远不动
		for(i=1; i<total-1; ++i)
		{
			for(int j=total-1; j>i; --j)
			{
				const Role& left = rs->roles(output[j-1]);
				const Role& right = rs->roles(output[j]);

				bool needSwap = false;
				//等级高的优先，经验多的优先，id小的优先
				if(right.expr().level() > left.expr().level())
				{
					needSwap = true;
				}
				else if(right.expr().level() == left.expr().level())
				{
					if(right.expr().expr() > left.expr().expr())
					{
						needSwap = true;
					}
					else if(right.expr().expr() == left.expr().expr())
					{
						if(atoi(right.id().id().c_str()) < atoi(left.id().id().c_str()))
						{
							needSwap = true;
						}
					}
				}

				if(needSwap)
				{
					int tmp = output[j-1];
					output[j-1] = output[j];
					output[j] = tmp;
				}
			}
		}

		ret = true;
	}while(0);
	return ret;
}

void CMyData::updateBattleList()
{
	do{
		RoleSet* prs = allRoles();
		for(int i=0; i<prs->battlelist_size(); ++i)
		{
			if(this->getRoleById(prs->battlelist(i).id().c_str())==NULL)
			{
				prs->mutable_battlelist(i)->set_id("");
			}
		}
	}while(0);
}

bool CMyData::isInBattleList(const char* sid)
{
	bool ret = false;
	do{
		RoleSet* prs = allRoles();
		for(int i=0; i<prs->battlelist_size(); ++i)
		{
			if(sid == prs->battlelist(i).id())
			{
				ret = true;
				break;
			}
		}
	}while(0);
	return ret;
}

bool CMyData::saveBattleList(vector<int>& roleIdxes, bool onlyCheck)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		RoleSet* prs = allRoles();
		bool reset = false;
		int total=0;
		bool mainFound = false;

		//检查
		unsigned int i=0;
		for(i=0; i<roleIdxes.size(); ++i)
		{
			int roleIdx = roleIdxes[i];

			if(roleIdx >= 0)
			{
				//不跟之前的重复
				unsigned int j=0;
				for(j=0; j<i; ++j)
				{
					if(roleIdxes[j] == roleIdxes[i])
						break;
				}

				if(j!=i)
					break;

				//主将需要在内
				if(roleIdx == prs->mainroleidx())
				{
					mainFound = true;
				}

				//必须实际拥有
				Role* prole = getRoleByIdx(roleIdx);
				if(prole==NULL)
					break;

				++total;
			}
		}

		if(i!=roleIdxes.size())
			break;

		if(total > CDataUtil::getFightUnitMaxByLevel(m_user.account().expr().level()))
		{
			this->throwEvent(CMyControl::CMD_DATA_UNIT_FIGHT_MAX);
			this->postEventsToControl();
			break;
		}

		if(!mainFound)
			break;

		if(!onlyCheck)
		{
			//重置出战队列
			prs->clear_battlelist();
			for(i=0; i<roleIdxes.size(); ++i)
			{
				Identity* pId = prs->add_battlelist();
				Role* prole = getRoleByIdx(roleIdxes[i]);
				if(prole)
				{
					pId->CopyFrom(prole->id());
				}
			}
			this->throwEvent(CMyControl::CMD_DATA_BATTLE_LIST_CHANGED);
		}
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::setCurrentBattle(int battleId)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		PveInfo* pve = m_user.mutable_pve();
		pve->set_curbattle(battleId);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}

bool CMyData::setCurrentMap(int mapId)
{
	TransactionGuarder guarder(this);
	bool ret = false;
	do{
		PveInfo* pve = m_user.mutable_pve();
		pve->set_curmap(mapId);
		guarder.clear();
		ret = true;
	}while(0);
	return ret;
}


int CMyData::getCurrentBattle()
{
	return m_user.mutable_pve()->curbattle();
}

int CMyData::getCurrentMap()
{
	return m_user.mutable_pve()->curmap();
}

