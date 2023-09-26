﻿/*
				GNU GENERAL PUBLIC LICENSE
				   Version 2, June 1991
COPYRIGHT (C) Bestkakkoii 2023 All Rights Reserved.
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

#pragma once
#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>

#include <threadplugin.h>
#include <indexer.h>
#include <util.h>
#include "lssproto.h"

static const QHash<QString, BUTTON_TYPE> buttonMap = {
	{"OK", BUTTON_OK},
	{"CANCEL", BUTTON_CANCEL},
	{"YES", BUTTON_YES},
	{"NO", BUTTON_NO},
	{"PREVIOUS", BUTTON_PREVIOUS},
	{"NEXT", BUTTON_NEXT},
	{"AUTO", BUTTON_AUTO},

	//big5
	{u8"確認", BUTTON_YES},
	{u8"確定", BUTTON_YES},
	{u8"取消", BUTTON_NO},
	{u8"好", BUTTON_YES},
	{u8"不好", BUTTON_NO},
	{u8"可以", BUTTON_YES},
	{u8"不可以", BUTTON_NO},
	{u8"上一頁", BUTTON_PREVIOUS},
	{u8"上一步", BUTTON_PREVIOUS},
	{u8"下一頁", BUTTON_NEXT},
	{u8"下一步", BUTTON_NEXT},
	{u8"買", BUTTON_BUY},
	{u8"賣", BUTTON_SELL},
	{u8"出去", BUTTON_OUT},
	{u8"回上一頁", BUTTON_BACK},

	//gb2312
	{u8"确认", BUTTON_YES},
	{u8"确定", BUTTON_YES},
	{u8"取消", BUTTON_NO},
	{u8"好", BUTTON_YES},
	{u8"不好", BUTTON_NO},
	{u8"可以", BUTTON_YES},
	{u8"不可以", BUTTON_NO},
	{u8"上一页", BUTTON_PREVIOUS},
	{u8"上一步", BUTTON_PREVIOUS},
	{u8"下一页", BUTTON_NEXT},
	{u8"下一步", BUTTON_NEXT},
	{u8"买", BUTTON_BUY},
	{u8"卖", BUTTON_SELL},
	{u8"出去", BUTTON_OUT},
	{u8"回上一页", BUTTON_BACK},
};

static const QHash<QString, PetState> petStateMap = {
	{ u8"戰鬥", kBattle },
	{ u8"等待", kStandby },
	{ u8"郵件", kMail },
	{ u8"休息", kRest },
	{ u8"騎乘", kRide },

	{ u8"战斗", kBattle },
	{ u8"等待", kStandby },
	{ u8"邮件", kMail },
	{ u8"休息", kRest },
	{ u8"骑乘", kRide },

	{ u8"battle", kBattle },
	{ u8"standby", kStandby },
	{ u8"mail", kMail },
	{ u8"rest", kRest },
	{ u8"ride", kRide },
};

static const QHash<QString, DirType> dirMap = {
	{ u8"北", kDirNorth },
	{ u8"東北", kDirNorthEast },
	{ u8"東", kDirEast },
	{ u8"東南", kDirSouthEast },
	{ u8"南", kDirSouth },
	{ u8"西南", kDirSouthWest },
	{ u8"西", kDirWest },
	{ u8"西北", kDirNorthWest },

	{ u8"北", kDirNorth },
	{ u8"东北", kDirNorthEast },
	{ u8"东", kDirEast },
	{ u8"东南", kDirSouthEast },
	{ u8"南", kDirSouth },
	{ u8"西南", kDirSouthWest },
	{ u8"西", kDirWest },
	{ u8"西北", kDirNorthWest },

	{ u8"A", kDirNorth },
	{ u8"B", kDirNorthEast },
	{ u8"C", kDirEast },
	{ u8"D", kDirSouthEast },
	{ u8"E", kDirSouth },
	{ u8"F", kDirSouthWest },
	{ u8"G", kDirWest },
	{ u8"H", kDirNorthWest },
};

static const QHash<QString, CHAR_EquipPlace> equipMap = {
	{ u8"頭", CHAR_HEAD },
	{ u8"身體", CHAR_BODY },
	{ u8"右手", CHAR_ARM },
	{ u8"左飾", CHAR_DECORATION1 },
	{ u8"右飾", CHAR_DECORATION2 },
	{ u8"腰帶", CHAR_EQBELT },
	{ u8"左手", CHAR_EQSHIELD },
	{ u8"鞋子", CHAR_EQSHOES },
	{ u8"手套", CHAR_EQGLOVE },

	{ u8"头", CHAR_HEAD },
	{ u8"身体", CHAR_BODY },
	{ u8"右手", CHAR_ARM },
	{ u8"左饰", CHAR_DECORATION1 },
	{ u8"右饰", CHAR_DECORATION2 },
	{ u8"腰带", CHAR_EQBELT },
	{ u8"左手", CHAR_EQSHIELD },
	{ u8"鞋子", CHAR_EQSHOES },
	{ u8"手套", CHAR_EQGLOVE },

	{ u8"head", CHAR_HEAD },
	{ u8"body", CHAR_BODY },
	{ u8"right", CHAR_ARM },
	{ u8"las", CHAR_DECORATION1 },
	{ u8"ras", CHAR_DECORATION2 },
	{ u8"belt", CHAR_EQBELT },
	{ u8"left", CHAR_EQSHIELD },
	{ u8"shoe", CHAR_EQSHOES },
	{ u8"glove", CHAR_EQGLOVE },
};

static const QHash<QString, CHAR_EquipPlace> petEquipMap = {
	{ u8"頭", PET_HEAD },
	{ u8"翼", PET_WING },
	{ u8"牙", PET_TOOTH },
	{ u8"身體", PET_PLATE },
	{ u8"背", PET_BACK },
	{ u8"爪", PET_CLAW },
	{ u8"腳", PET_FOOT },

	{ u8"头", PET_HEAD },
	{ u8"翼", PET_WING },
	{ u8"牙", PET_TOOTH },
	{ u8"身体", PET_PLATE },
	{ u8"背", PET_BACK },
	{ u8"爪", PET_CLAW },
	{ u8"脚", PET_FOOT },

	{ u8"head", PET_HEAD },
	{ u8"wing", PET_WING },
	{ u8"tooth", PET_TOOTH },
	{ u8"body", PET_PLATE },
	{ u8"back", PET_BACK },
	{ u8"claw", PET_CLAW },
	{ u8"foot", PET_FOOT },
};

enum BufferControl
{
	BC_NONE,
	BC_NEED_TO_CLEAN,
	BC_HAS_NEXT,
	BC_ABOUT_TO_END,
	BC_INVALID,
};

class MapAnalyzer;
class Server : public ThreadPlugin, public Lssproto
{
	Q_OBJECT
public:
	explicit Server(qint64 index, QObject* parent);

	virtual ~Server();

	Q_REQUIRED_RESULT inline bool isListening() const { return  !server_.isNull() && server_->isListening(); }

	Q_REQUIRED_RESULT inline bool hasClientExist() const { return  !server_.isNull() && !clientSockets_.isEmpty(); }

	bool start(QObject* parent);

	Q_REQUIRED_RESULT inline unsigned short getPort() const { return port_; }

signals:
	void write(QTcpSocket* clientSocket, QByteArray ba, qint64 size);

private slots:
	void onWrite(QTcpSocket* clientSocket, QByteArray ba, qint64 size);
	void onNewConnection();
	void onClientReadyRead();

private:
	qint64 dispatchMessage(char* encoded);

	bool handleCustomMessage(QTcpSocket* clientSocket, const QByteArray& data);

	void handleData(QTcpSocket* clientSocket, QByteArray data);

public://actions
	Q_REQUIRED_RESULT qint64 getWorldStatus();

	Q_REQUIRED_RESULT qint64 getGameStatus();

	Q_REQUIRED_RESULT bool checkWG(qint64  w, qint64 g);

	Q_REQUIRED_RESULT qint64 getUnloginStatus();
	void setWorldStatus(qint64 w);
	void setGameStatus(qint64 g);

	bool login(qint64 s);

	void clientLogin(const QString& userName, const QString& password);
	void playerLogin(qint64 index);

	QString getBadStatusString(qint64 status);

	QString getFieldString(qint64 field);

	void unlockSecurityCode(const QString& code);

	void clearNetBuffer();

	void logOut();

	void logBack();

	void move(const QPoint& p, const QString& dir);

	void move(const QPoint& p);

	void announce(const QString& msg, qint64 color = 4);

	void createCharacter(qint64 dataplacenum
		, const QString& charname
		, qint64 imgno
		, qint64 faceimgno
		, qint64 vit
		, qint64 str
		, qint64 tgh
		, qint64 dex
		, qint64 earth
		, qint64 water
		, qint64 fire
		, qint64 wind
		, qint64 hometown);

	void deleteCharacter(qint64 index, const QString securityCode, bool backtofirst = false);

	void talk(const QString& text, qint64 color = 0, TalkMode mode = kTalkNormal);
	void inputtext(const QString& text, qint64 dialogid = -1, qint64 npcid = -1);

	void windowPacket(const QString& command, qint64 dialogid, qint64 npcid);

	void EO();

	void dropItem(qint64 index);
	void dropItem(QVector<qint64> index);

	void useItem(qint64 itemIndex, qint64 target);


	void swapItem(qint64 from, qint64 to);

	void petitemswap(qint64 petIndex, qint64 from, qint64 to);

	void useMagic(qint64 magicIndex, qint64 target);

	void dropPet(qint64 petIndex);

	void setSwitcher(qint64 flg, bool enable);

	void setSwitcher(qint64 flg);

	void press(BUTTON_TYPE select, qint64 dialogid = -1, qint64 unitid = -1);
	void press(qint64 row, qint64 dialogid = -1, qint64 unitid = -1);

	void buy(qint64 index, qint64 amt, qint64 dialogid = -1, qint64 unitid = -1);
	void sell(const QVector<qint64>& indexs, qint64 dialogid = -1, qint64 unitid = -1);
	void sell(qint64 index, qint64 dialogid = -1, qint64 unitid = -1);
	void sell(const QString& name, const QString& memo = "", qint64 dialogid = -1, qint64 unitid = -1);
	void learn(qint64 skillIndex, qint64 petIndex, qint64 spot, qint64 dialogid = -1, qint64 unitid = -1);

	void craft(util::CraftType type, const QStringList& ingres);

	void createRemoteDialog(qint64 button, const QString& text);

	void mail(const QVariant& card, const QString& text, qint64 petIndex, const QString& itemName, const QString& itemMemo);

	void warp();

	void shopOk(qint64 n);
	void saMenu(qint64 n);

	bool addPoint(qint64 skillid, qint64 amt);

	void pickItem(qint64 dir);

	void dropGold(qint64 gold);

	void depositGold(qint64 gold, bool isPublic);
	void withdrawGold(qint64 gold, bool isPublic);

	void depositPet(qint64 petIndex, qint64 dialogid = -1, qint64 unitid = -1);
	void withdrawPet(qint64 petIndex, qint64 dialogid = -1, qint64 unitid = -1);

	void depositItem(qint64 index, qint64 dialogid = -1, qint64 unitid = -1);
	void withdrawItem(qint64 itemIndex, qint64 dialogid = -1, qint64 unitid = -1);

	bool captchaOCR(QString* pmsg);

	void setAllPetState();
	void setPetState(qint64 petIndex, PetState state);
	void setFightPet(qint64 petIndex);
	void setRidePet(qint64 petIndex);
	void setPetStateSub(qint64 petIndex, qint64 state);
	void setPetStandby(qint64 petIndex, qint64 state);

	void updateItemByMemory();
	void updateDatasFromMemory();

	void doBattleWork(bool async);
	void asyncBattleAction();

	void downloadMap(qint64 floor = -1);
	void downloadMap(qint64 x, qint64 y, qint64 floor = -1);

	bool tradeStart(const QString& name, qint64 timeout);
	void tradeComfirm(const QString& name);
	void tradeCancel();
	void tradeAppendItems(const QString& name, const QVector<qint64>& itemIndexs);
	void tradeAppendGold(const QString& name, qint64 gold);
	void tradeAppendPets(const QString& name, const QVector<qint64>& petIndex);
	void tradeComplete(const QString& name);

	void cleanChatHistory();
	QString getChatHistory(qint64 index);

	bool findUnit(const QString& name, qint64 type, mapunit_t* unit, const QString& freeName = "", qint64 modelid = -1);

	QString getGround();

	void setTeamState(bool join);
	void kickteam(qint64 n);

	void setCharFaceToPoint(const QPoint& pos);
	void setCharFaceDirection(qint64 dir);
	void setCharFaceDirection(const QString& dirStr);

	qint64 getPartySize() const;
	QStringList getJoinableUnitList() const;
	bool getItemIndexsByName(const QString& name, const QString& memo, QVector<qint64>* pv, qint64 from = 0, qint64 to = MAX_ITEM);
	qint64 getItemIndexByName(const QString& name, bool isExact = true, const QString& memo = "", qint64 from = 0, qint64 to = MAX_ITEM);
	qint64 getPetSkillIndexByName(qint64& petIndex, const QString& name) const;
	qint64 getSkillIndexByName(const QString& name) const;
	bool getPetIndexsByName(const QString& name, QVector<qint64>* pv) const;
	qint64 getMagicIndexByName(const QString& name, bool isExact = true) const;
	qint64 getItemEmptySpotIndex();
	bool getItemEmptySpotIndexs(QVector<qint64>* pv);
	void clear();

	bool checkCharMp(qint64 cmpvalue, qint64* target = nullptr, bool useequal = false);
	bool checkCharHp(qint64 cmpvalue, qint64* target = nullptr, bool useequal = false);
	bool checkRideHp(qint64 cmpvalue, qint64* target = nullptr, bool useequal = false);
	bool checkPetHp(qint64 cmpvalue, qint64* target = nullptr, bool useequal = false);
	bool checkPartyHp(qint64 cmpvalue, qint64* target);

	bool isPetSpotEmpty() const;
	qint64 checkJobDailyState(const QString& missionName);

	bool isDialogVisible();

	void setCharFreeName(const QString& name);
	void setPetFreeName(qint64 petIndex, const QString& name);

	Q_REQUIRED_RESULT inline bool getBattleFlag();
	Q_REQUIRED_RESULT inline bool getOnlineFlag() const;

	PC getPC() const { QReadLocker lock(&pcMutex_); return pc_; }
	void setPC(PC pc) { QWriteLocker lock(&pcMutex_); pc_ = pc; }



	void sortItem(bool deepSort = false);

	QPoint getPoint();
	void setPoint(const QPoint& pos);

	qint64 getFloor();
	void setFloor(qint64 floor);

	QString getFloorName();
	void setFloorName(const QString& floorName);

	//battle
	void sendBattleCharAttackAct(qint64 target);
	void sendBattleCharMagicAct(qint64 magicIndex, qint64 target);
	void sendBattleCharJobSkillAct(qint64 skillIndex, qint64 target);
	void sendBattleCharItemAct(qint64 itemIndex, qint64 target);
	void sendBattleCharDefenseAct();
	void sendBattleCharEscapeAct();
	void sendBattleCharCatchPetAct(qint64 petIndex);
	void sendBattleCharSwitchPetAct(qint64 petIndex);
	void sendBattleCharDoNothing();
	void sendBattlePetSkillAct(qint64 skillIndex, qint64 target);
	void sendBattlePetDoNothing();
	void setBattleEnd();

	void updateBattleTimeInfo();

	MAGIC getMagic(qint64 magicIndex) const { return magic[magicIndex]; }
	PROFESSION_SKILL getSkill(qint64 skillIndex) const { return profession_skill[skillIndex]; }
	PET getPet(qint64 petIndex) const { return pet[petIndex]; }
	qint64 getPetSize() const
	{
		qint64 n = 0;
		for (const PET& it : pet)
		{
			if (it.level > 0 && it.valid && it.maxHp > 0)
				++n;
		}
		return n;
	}
	PET_SKILL getPetSkill(qint64 petIndex, qint64 skillIndex) const { return petSkill[petIndex][skillIndex]; }
	PARTY getParty(qint64 partyIndex) const { return party[partyIndex]; }
	ITEM getPetEquip(qint64 petIndex, qint64 equipIndex) const { return pet[petIndex].item[equipIndex]; }
	ADDRESS_BOOK getAddressBook(qint64 index) const { return addressBook[index]; }
	battledata_t getBattleData() const
	{
		QReadLocker locker(&battleDataLocker);
		return battleData;
	}
	JOBDAILY getJobDaily(qint64 index) const { return jobdaily[index]; }

	Q_REQUIRED_RESULT qint64 findInjuriedAllie();

	void refreshItemInfo();

	void updateComboBoxList();


private:
	void setWindowTitle();
	void refreshItemInfo(qint64 index);


	void setBattleFlag(bool enable);
	inline void setOnlineFlag(bool enable)
	{
		{
			QWriteLocker lock(&onlineStateLocker);
			IS_ONLINE_FLAG.store(enable, std::memory_order_release);
		}

		if (!enable)
		{
			setBattleEnd();
		}
	}

	void getCharMaxCarryingCapacity();
	inline Q_REQUIRED_RESULT constexpr bool isItemStackable(qint64 flg) { return ((flg >> 2) & 1); }
	QString getAreaString(qint64 target);
	Q_REQUIRED_RESULT bool matchPetNameByIndex(qint64 index, const QString& name);
	Q_REQUIRED_RESULT qint64 getProfessionSkillIndexByName(const QString& names) const
	{
		qint64 i = 0;
		bool isExact = true;
		QStringList list = names.split(util::rexOR, Qt::SkipEmptyParts);
		for (QString name : list)
		{
			if (name.isEmpty())
				continue;

			if (name.startsWith("?"))
			{
				name = name.mid(1);
				isExact = false;
			}

			for (i = 0; i < MAX_PROFESSION_SKILL; ++i)
			{
				if (!profession_skill[i].valid)
					continue;

				if (isExact && profession_skill[i].name == name)
					return i;
				else if (!isExact && profession_skill[i].name.contains(name))
					return i;

			}
		}
		return -1;
	}

#pragma region BattleFunctions
	qint64 playerDoBattleWork(const battledata_t& bt);
	void handleCharBattleLogics(const battledata_t& bt);
	qint64 petDoBattleWork(const battledata_t& bt);
	void handlePetBattleLogics(const battledata_t& bt);

	bool isCharMpEnoughForMagic(qint64 magicIndex) const;
	bool isCharMpEnoughForSkill(qint64 magicIndex) const;
	bool isCharHpEnoughForSkill(qint64 magicIndex) const;

	void sortBattleUnit(QVector<battleobject_t>& v) const;

	Q_REQUIRED_RESULT qint64 getBattleSelectableEnemyTarget(const battledata_t& bt) const;

	Q_REQUIRED_RESULT qint64 getBattleSelectableEnemyOneRowTarget(const battledata_t& bt, bool front) const;

	Q_REQUIRED_RESULT qint64 getBattleSelectableAllieTarget(const battledata_t& bt) const;

	Q_REQUIRED_RESULT bool matchBattleEnemyByName(const QString& name, bool isExact, const QVector<battleobject_t>& src, QVector<battleobject_t>* v) const;
	Q_REQUIRED_RESULT bool matchBattleEnemyByLevel(qint64 level, const QVector<battleobject_t>& src, QVector<battleobject_t>* v) const;
	Q_REQUIRED_RESULT bool matchBattleEnemyByMaxHp(qint64  maxHp, const QVector<battleobject_t>& src, QVector<battleobject_t>* v) const;

	Q_REQUIRED_RESULT qint64 getGetPetSkillIndexByName(qint64 etIndex, const QString& name) const;

	bool fixCharTargetByMagicIndex(qint64 magicIndex, qint64 oldtarget, qint64* target) const;
	bool fixCharTargetBySkillIndex(qint64 magicIndex, qint64 oldtarget, qint64* target) const;
	bool fixCharTargetByItemIndex(qint64 itemIndex, qint64 oldtarget, qint64* target) const;
	bool fixPetTargetBySkillIndex(qint64 skillIndex, qint64 oldtarget, qint64* target) const;
	void updateCurrentSideRange(battledata_t& bt);
	inline bool checkFlagState(qint64 pos);

	void setBattleData(const battledata_t& data)
	{
		QWriteLocker locker(&battleDataLocker);
		battleData = data;
	}


	//自動鎖寵
	void checkAutoLockPet();
#pragma endregion

#pragma region SAClientOriginal
	//StoneAge Client Original Functions

	void swapItemLocal(qint64 from, qint64 to);

	void realTimeToSATime(LSTIME* lstime);

#pragma endregion

private:
	QMutex ayncBattleCommandMutex;
	std::atomic_bool ayncBattleCommandFlag = false;

	std::atomic_bool IS_BATTLE_FLAG = false;
	std::atomic_bool IS_ONLINE_FLAG = false;

	QElapsedTimer eottlTimer;//伺服器響應時間(MS)
	QElapsedTimer connectingTimer;
	bool petEscapeEnableTempFlag = false;
	qint64 tempCatchPetTargetIndex = -1;
	qint64 JobdailyGetMax = 0;  //是否有接收到資料
	mutable QReadWriteLock battleStateLocker;
	mutable QReadWriteLock onlineStateLocker;
	mutable QReadWriteLock worldStateLocker;
	mutable QReadWriteLock gameStateLocker;

	battledata_t battleData;
	mutable QReadWriteLock battleDataLocker;

	bool IS_WAITFOT_SKUP_RECV = false;
	QFuture<void> skupFuture;

	bool IS_LOCKATTACK_ESCAPE_DISABLE = false;//鎖定攻擊不逃跑 (轉指定攻擊)

	mutable QReadWriteLock petStateMutex_;
	mutable QReadWriteLock pointMutex_;//用於保護人物座標更新順序
	mutable QReadWriteLock pcMutex_;//用於保護人物數據更新順序
	PC pc_ = {};

	PET pet[MAX_PET] = {};

#ifdef MAX_AIRPLANENUM
	PARTY party[MAX_AIRPLANENUM];
#else
	PARTY party[MAX_PARTY] = {};
#endif

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	PROFESSION_SKILL profession_skill[MAX_PROFESSION_SKILL];
#endif

	PET_SKILL petSkill[MAX_PET][MAX_SKILL] = {};

	qint64 swapitemModeFlag = 0; //當前自動整理功能的階段
	QHash<QString, bool>itemStackFlagHash = {};

	QVector<bool> battlePetDisableList_ = {};

	util::SafeData<qint64> nowFloor_;
	util::SafeData<QString> nowFloorName_;
	util::SafeData<QPoint> nowPoint_;

	//client original 目前很多都是沒用處的
#pragma region ClientOriginal
	MAGIC magic[MAX_MAGIC] = {};

	ADDRESS_BOOK addressBook[MAX_ADDRESS_BOOK] = {};

	JOBDAILY jobdaily[MAX_MISSION] = {};

	CHARLISTTABLE chartable[MAX_CHARACTER] = {};

	MAIL_HISTORY mailHistory[MAX_ADDRESS_BOOK] = {};

	bool hasTeam = false;//是否組隊

	//戰鬥相關
	qint64 battleCharCurrentPos = 0;
	qint64 battleBpFlag = 0;
	qint64 battleCharEscapeFlag = 0;
	qint64 battleCharCurrentMp = 0;
	qint64 battleCurrentAnimeFlag = 0;

	QString lastSecretChatName = "";//最後一次收到密語的發送方名稱

	//遊戲內當前時間相關
	LSTIME saTimeStruct = { 0 };
	qint64 serverTime = 0LL;
	qint64 FirstTime = 0LL;
	qint64 saCurrentGameTime = 0;

	//交易相關
	qint64 opp_showindex = 0;
	QString opp_sockfd;
	QString opp_name;
	QString opp_goldmount;
	qint64 showindex[7] = { 0 };
	qint64 tradeWndDropGoldGet = 0;
	QString opp_itemgraph;
	QString opp_itemname;
	QString opp_itemeffect;
	QString opp_itemindex;
	QString opp_itemdamage;
	QString trade_kind;
	QString trade_command;
	qint64 tradeStatus = 0;
	qint64 tradePetIndex = -1;
	PET tradePet[2] = {};
	showitem opp_item[MAX_MAXHAVEITEM];	//交易道具阵列增为15个
	showpet opp_pet[MAX_PET];
	QStringList myitem_tradeList;
	QStringList mypet_tradeList = { "P|-1", "P|-1", "P|-1" , "P|-1", "P|-1" };
	qint64 mygoldtrade = 0;

	//郵件相關
	qint64 mailHistoryWndSelectNo = 0;
	qint64 mailHistoryWndPageNo = 0;

	//選人畫面起算的時間計數
	time_t serverAliveLongTime = 0;
	struct tm serverAliveTime = { 0 };

#pragma endregion

public:
	//custom
	bool IS_TRADING = false;
	bool IS_DISCONNECTED = false;
	bool IS_TCP_CONNECTION_OK_TO_USE = false;

	bool IS_WAITFOR_JOBDAILY_FLAG = false;
	bool IS_WAITFOR_BANK_FLAG = false;
	bool IS_WAITFOR_DIALOG_FLAG = false;
	bool IS_WAITFOR_EXTRA_DIALOG_INFO_FLAG = false;
	bool IS_WAITFOR_CUSTOM_DIALOG_FLAG = false;
	qint64 IS_WAITOFR_ITEM_CHANGE_PACKET = false;

	std::atomic_bool isBattleDialogReady = false;
	std::atomic_bool isEOTTLSend = false;
	std::atomic_llong lastEOTime = 0;

	QElapsedTimer loginTimer;
	QElapsedTimer battleDurationTimer;
	QElapsedTimer normalDurationTimer;
	QElapsedTimer oneRoundDurationTimer;

	std::atomic_llong battleCurrentRound = 0;
	std::atomic_llong battle_total_time = 0;
	std::atomic_llong battle_total = 0;
	std::atomic_llong battle_one_round_time = 0;

	QSharedPointer<MapAnalyzer> mapAnalyzer;

	util::SafeData<currencydata_t> currencyData = {};
	util::SafeData<customdialog_t> customDialog = {};

	util::SafeHash<qint64, mapunit_t> mapUnitHash;
	util::SafeHash<QPoint, mapunit_t> npcUnitPointHash;
	util::SafeQueue<QPair<qint64, QString>> chatQueue;

	QPair<qint64, QVector<bankpet_t>> currentBankPetList;
	util::SafeVector<ITEM> currentBankItemList;

	QElapsedTimer repTimer;
	util::AfkRecorder recorder[1 + MAX_PET] = {};

	util::SafeData<dialog_t> currentDialog = {};

	//用於緩存要發送到UI的數據(開啟子窗口初始化並加載當前最新數據時使用)
	util::SafeHash<qint64, QVariant> playerInfoColContents;
	util::SafeHash<qint64, QVariant> itemInfoRowContents;
	util::SafeHash<qint64, QVariant> equipInfoRowContents;
	util::SafeData<QStringList> enemyNameListCache;
	util::SafeData<QVariant> topInfoContents;
	util::SafeData<QVariant> bottomInfoContents;
	util::SafeData<QString> timeLabelContents;
	util::SafeData<QString> labelCharAction;
	util::SafeData<QString> labelPetAction;

private:
	unsigned short port_ = 0;

	QSharedPointer<QTcpServer> server_;

	QList<QTcpSocket*> clientSockets_;

	QByteArray net_readbuf;

	QMutex net_mutex;

private://lssproto
	qint64 appendReadBuf(const QByteArray& data);
	QByteArrayList splitLinesFromReadBuf();
	qint64 a62toi(const QString& a) const;
	qint64 getStringToken(const QString& src, const QString& delim, qint64 count, QString& out) const;
	qint64 getIntegerToken(const QString& src, const QString& delim, qint64 count) const;
	qint64 getInteger62Token(const QString& src, const QString& delim, qint64 count) const;
	QString makeStringFromEscaped(QString& src) const;

private://lssproto_recv
#pragma region Lssproto_Recv
	virtual void lssproto_XYD_recv(const QPoint& pos, int dir) override;//戰鬥結束後的大地圖座標
	virtual void lssproto_EV_recv(int dialogid, int result) override;
	virtual void lssproto_EN_recv(int result, int field) override;
	virtual void lssproto_RS_recv(char* data) override;
	virtual void lssproto_RD_recv(char* data) override;
	virtual void lssproto_B_recv(char* command) override;
	virtual void lssproto_I_recv(char* data) override;
	virtual void lssproto_SI_recv(int fromindex, int toindex) override;
	virtual void lssproto_MSG_recv(int aindex, char* text, int color) override;	//收到普通郵件或寵物郵件
	virtual void lssproto_PME_recv(int unitid, int graphicsno, const QPoint& pos, int dir, int flg, int no, char* cdata) override;
	virtual void lssproto_AB_recv(char* data) override;
	virtual void lssproto_ABI_recv(int num, char* data) override;
	virtual void lssproto_TK_recv(int index, char* message, int color) override;
	virtual void lssproto_MC_recv(int fl, int x1, int y1, int x2, int y2, int tilesum, int objsum, int eventsum, char* data) override;
	virtual void lssproto_M_recv(int fl, int x1, int y1, int x2, int y2, char* data) override;
	virtual void lssproto_C_recv(char* data) override;
	virtual void lssproto_CA_recv(char* data) override;
	virtual void lssproto_CD_recv(char* data) override;
	virtual void lssproto_R_recv(char* data) override;
	virtual void lssproto_S_recv(char* data) override;
	virtual void lssproto_D_recv(int category, int dx, int dy, char* data) override;
	virtual void lssproto_FS_recv(int flg) override;
	virtual void lssproto_HL_recv(int flg) override;//戰鬥中是否要Help
	virtual void lssproto_PR_recv(int request, int result) override;
	virtual void lssproto_KS_recv(int petarray, int result) override;//指定那一只寵物出場戰鬥
#ifdef _STANDBYPET
	virtual void lssproto_SPET_recv(int standbypet, int result) override;
#endif
	virtual void lssproto_PS_recv(int result, int havepetindex, int havepetskill, int toindex) override;	//寵物合成
	virtual void lssproto_SKUP_recv(int point) override;//取得可加的屬性點數
	virtual void lssproto_WN_recv(int windowtype, int buttontype, int dialogid, int unitid, char* data) override;
	virtual void lssproto_EF_recv(int effect, int level, char* option) override;
	virtual void lssproto_SE_recv(const QPoint& pos, int senumber, int sw) override;
	virtual void lssproto_ClientLogin_recv(char* result) override;
	virtual void lssproto_CreateNewChar_recv(char* result, char* data) override;
	virtual void lssproto_CharDelete_recv(char* result, char* data) override;
	virtual void lssproto_CharLogin_recv(char* result, char* data) override;
	virtual void lssproto_CharList_recv(char* result, char* data) override;
	virtual void lssproto_CharLogout_recv(char* result, char* data) override;
	virtual void lssproto_ProcGet_recv(char* data) override;
	virtual void lssproto_CharNumGet_recv(int logincount, int player) override;
	virtual void lssproto_Echo_recv(char* test) override;
	virtual void lssproto_NU_recv(int AddCount) override;
	virtual void lssproto_WO_recv(int effect) override;//取得轉生的特效
	virtual void lssproto_TD_recv(char* data) override;
	virtual void lssproto_FM_recv(char* data) override;
#ifdef _ITEM_CRACKER
	virtual void lssproto_IC_recv(const QPoint& pos) override;
#endif
#ifdef _MAGIC_NOCAST//沈默
	virtual void lssproto_NC_recv(int flg) override;
#endif
#ifdef _CHECK_GAMESPEED
	virtual void lssproto_CS_recv(int deltimes) override;
#endif
#ifdef _PETS_SELECTCON
	virtual void lssproto_PETST_recv(int petarray, int result) override;
#endif
#ifdef _CHATROOMPROTOCOL			// (不可開) 聊天室頻道
	virtual void lssproto_CHATROOM_recv(char* data) override;
#endif
#ifdef _NEWREQUESTPROTOCOL			// (不可開) 新增Protocol要求細項
	virtual void lssproto_RESIST_recv(char* data) override;
#endif
#ifdef _ALCHEPLUS
	virtual void lssproto_ALCHEPLUS_recv(char* data) override;
#endif

#ifdef _OUTOFBATTLESKILL			// (不可開) Syu ADD 非戰鬥時技能Protocol
	virtual void lssproto_BATTLESKILL_recv(char* data) override;
#endif
	virtual void lssproto_CHAREFFECT_recv(char* data) override;

#ifdef _STREET_VENDOR
	virtual void lssproto_STREET_VENDOR_recv(char* data) override;	// 擺攤功能
#endif

#ifdef _JOBDAILY
	virtual void lssproto_JOBDAILY_recv(char* data) override;
#endif

#ifdef _FAMILYBADGE_
	virtual void lssproto_FamilyBadge_recv(char* data) override;
#endif

#ifdef _TEACHER_SYSTEM
	virtual void lssproto_TEACHER_SYSTEM_recv(char* data) override;
#endif

#ifdef _ADD_STATUS_2
	virtual void lssproto_S2_recv(char* data) override;
#endif
#ifdef _ITEM_FIREWORK
	virtual void lssproto_Firework_recv(int nCharaindex, int nType, int nActionNum) override;	// 煙火功能
#endif
#ifdef _THEATER
	virtual void lssproto_TheaterData_recv(char* pData) override;
#endif
#ifdef _MOVE_SCREEN
	virtual void lssproto_MoveScreen_recv(BOOL bMoveScreenMode, int iXY) override;	// client 移動熒幕
#endif
#ifdef _NPC_MAGICCARD
	virtual void lssproto_MagiccardAction_recv(char* data) override;	//魔法牌功能
	virtual void lssproto_MagiccardDamage_recv(int position, int damage, int offsetx, int offsety) override;
#endif
#ifdef  _NPC_DANCE
	virtual void lssproto_DancemanOption_recv(int option) override;	//動一動狀態
#endif
#ifdef _ANNOUNCEMENT_
	virtual void lssproto_DENGON_recv(char* data, int colors, int nums) override;
#endif
#ifdef _HUNDRED_KILL
	virtual void lssproto_hundredkill_recv(int flag) override;
#endif
#ifdef _PK2007
	virtual void lssproto_pkList_recv(int count, char* data) override;
#endif
#ifdef _PETBLESS_
	virtual void lssproto_petbless_send(int petpos, int type) override;
#endif
#ifdef _PET_SKINS
	virtual void lssproto_PetSkins_recv(char* data) override;
#endif

	//////////////////////////////////

	virtual void lssproto_CustomWN_recv(const QString& data) override;
	virtual void lssproto_CustomTK_recv(const QString& data) override;
#pragma endregion
};
