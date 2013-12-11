#pragma once
#include "cocos2d.h"
#include "user.pb.h"
#include "mail.pb.h"
#include <string>
USING_NS_CC;
using namespace std;

class CMyData
{
public:
	static const char* USER_DATA_FILE;
	static string curUser;

protected:
	class TransactionGuarder
	{
	public:
		TransactionGuarder(CMyData* host);
		~TransactionGuarder();
		void clear();
	public:
		bool m_valid;
		CMyData* m_host;
	};
public:
	CMyData(void);
	~CMyData(void);

	static CMyData* getSharedData();

	inline bool loadUser()
	{
		return loadFromFile(m_user, m_fileName.c_str(), false);
	}

	inline bool saveUser()
	{
		return saveToFile(m_user, m_fileName.c_str());
	}

	bool loadFromFile(google::protobuf::MessageLite& msg, const char* fileName, bool alert=true);

	bool saveToFile(google::protobuf::MessageLite& msg, const char* fileName);

	//get functions
	inline User& user()
	{
		return m_user;
	}

	Role* mainRole();
	RoleSet* allRoles();
	Role* getRoleById(const char* sid);
	Role* getRoleByIdx(int idx);

	bool getLevelExpr(long long& levelExpr, long long& maxLevelExpr);
	int getItemIdxById(const string& id);
	Item* getEquip(Role* r, int tag);

	int getCurrentBattle();
	int getCurrentMap();

//modify functions
	bool modifyMoney(int goldChange);
	bool modifyGold(int goldChange);
	bool modifyExpr(int exprChange);
	bool modifyRoleAttr(Role* prole, int attrIdx, int attrValue);

	bool useItem(int itemIdx, int num);
	bool saleItem(int itemIdx, int num);

	bool equip(Role* r, int itemidx);
	bool unequip(Role* r, int tag);

	bool payItem(int shopID, int num);
	bool delItem(Item* pitem, int num, int itemidx);
	bool addItem(int subtype, int num, int level=-1);

	bool openItemPack(int subtype);

	bool refreshRoleHire(int num, bool free=false, bool noEvent =false);
	bool hireRole(int idx);
	bool fireRole(int idx);

	bool createIdxForRoles(vector<int>& output);

	//battlelist操作
	bool isInBattleList(const char* sid);
	bool saveBattleList(vector<int>& roleIdxes, bool onlyCheck=false);

	//pve操作
	bool setCurrentBattle(int battleId);
	bool setCurrentMap(int mapId);

protected:
	void initData();
	void bindUser();
	int positiveModify(int src, int delta);
	void appendItem(int subtype, int num, int level=-1);
	//subtype必须是可堆叠的
	//numChange<0是扣除，不足返回false
	bool modifyCountableItem(int subtype, int numChange);
	//不可堆叠物品删除
	//itemidx=-1删除最靠前的一个，否则会匹配itemidx
	bool delUncountableItem(int subtype,int itemidx=-1);
	bool addUncountableItem(int subtype, int level=-1);
	bool itemEffect(int subtype, int num);

	bool startTransaction();
	void submitTransaction();
	void rollbackTransaction();
	//缓存event
	void throwEvent(int cmd);
	//将events发送出去
	void postEventsToControl();

	//unitid >=0 指定id创建，否则随机一个
	//whichArray=0直接添加到列表，否则放到旅馆
	Role* createNewRole(RoleSet* rs,  int unitid, int whichArray=0);

	void updateBattleList();

protected:
	static CMyData* m_pdata;
	User m_user;
	string m_userName;
	string m_fileName;
	User* m_userSave;
	vector<int> m_eventSave;
};
