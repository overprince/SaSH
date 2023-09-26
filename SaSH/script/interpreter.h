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
#include <QObject>
#include <QScopedPointer>
#include <atomic>
#include "parser.h"
#include "util.h"

constexpr qint64 DEFAULT_FUNCTION_TIMEOUT = 5000;

class Interpreter : public ThreadPlugin
{
	Q_OBJECT
public:
	enum VarShareMode
	{
		kNotShare,
		kShare,
	};

public:
	explicit Interpreter(qint64 index);
	virtual ~Interpreter();

	inline bool isRunning() const { return isRunning_.load(std::memory_order_acquire) && !isInterruptionRequested(); }

	void preview(const QString& fileName);

	void doString(const QString& script, Interpreter* parent, VarShareMode shareMode);

	void doFileWithThread(qint64 beginLine, const QString& fileName);

	bool doFile(qint64 beginLine, const QString& fileName, Interpreter* parent, VarShareMode shareMode, Parser::Mode noShow = Parser::kSync);

	void stop();

	inline void setSubScript(bool is) { parser_.setSubScript(is); }

	Q_REQUIRED_RESULT inline bool isSubScript() const { return parser_.isSubScript(); }

signals:
	void finished();
	void stoped();

public slots:
	void proc();

private:
	qint64 mainScriptCallBack(qint64 currentIndex, qint64 currentLine, const TokenMap& token);

private:

	template<typename Func>
	void registerFunction(const QString functionName, Func fun);
	void openLibsBIG5();
	void openLibsGB2312();
	void openLibsUTF8();
	void openLibs();

private:
	bool checkBattleThenWait();
	bool checkOnlineThenWait();
	bool findPath(qint64 currentIndex, qint64 currentLine, QPoint dst, qint64 steplen, qint64 step_cost = 0, qint64 timeout = DEFAULT_FUNCTION_TIMEOUT * 36, std::function<qint64(QPoint& dst)> callback = nullptr, bool noAnnounce = false);

	bool waitfor(qint64 timeout, std::function<bool()> exprfun);
	bool checkString(const TokenMap& TK, qint64 idx, QString* ret);
	bool checkInteger(const TokenMap& TK, qint64 idx, qint64* ret);
	bool checkNumber(const TokenMap& TK, qint64 idx, double* ret);
	bool checkBoolean(const TokenMap& TK, qint64 idx, bool* ret);
	bool toVariant(const TokenMap& TK, qint64 idx, QVariant* ret);

	qint64 checkJump(const TokenMap& TK, qint64 idx, bool expr, JumpBehavior behavior);
	bool checkRange(const TokenMap& TK, qint64 idx, qint64* min, qint64* max);
	bool checkRelationalOperator(const TokenMap& TK, qint64 idx, RESERVE* ret) const;

	void logExport(qint64 currentIndex, qint64 currentLine, const QString& text, qint64 color = 0);

private: //註冊給Parser的函數
	//system
	qint64 sleep(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 press(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 eo(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 announce(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 input(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 messagebox(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 talk(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 talkandannounce(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 logout(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 logback(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 cleanchat(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 savesetting(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 loadsetting(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 run(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 dostring(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 reg(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 timer(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 menu(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 dofile(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 createch(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 delch(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 send(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	//check
	qint64 checkdaily(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 waitmap(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 waitdlg(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 waitsay(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 waititem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 waitpet(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	//check-group
	qint64 waitteam(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);


	//move
	qint64 setdir(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 move(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 fastmove(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 packetmove(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 findpath(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 movetonpc(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 warp(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);


	//action
	qint64 useitem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 dropitem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 swapitem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 playerrename(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 petrename(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 setpetstate(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 droppet(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 buy(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 sell(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 sellpet(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 make(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 cook(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 usemagic(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 pickitem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 depositgold(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 withdrawgold(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 teleport(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 addpoint(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 learn(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 trade(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 doffstone(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	qint64 recordequip(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 wearequip(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 unwearequip(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 petequip(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 petunequip(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	qint64 depositpet(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 deposititem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 withdrawpet(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 withdrawitem(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	qint64 mail(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	//action-group
	qint64 join(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 leave(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 kick(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	qint64 leftclick(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 rightclick(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 leftdoubleclick(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 mousedragto(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	//hide
	qint64 ocr(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);
	qint64 dlg(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);

	//battle
	qint64 bh(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//atk
	qint64 bj(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//magic
	qint64 bp(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//skill
	qint64 bs(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//switch
	qint64 be(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//escape
	qint64 bd(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//defense
	qint64 bi(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//item
	qint64 bt(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//catch
	qint64 bn(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//nothing
	qint64 bw(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//petskill
	qint64 bwf(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//pet nothing
	qint64 bwait(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//wait
	qint64 bend(qint64 currentIndex, qint64 currentLine, const TokenMap& TK);//wait

private:
	QThread* thread_ = nullptr;
	Parser parser_;

	std::atomic_bool isRunning_ = false;
	ParserCallBack pCallback = nullptr;
	QList<QSharedPointer<Interpreter>> subInterpreterList_;
	QFutureSynchronizer<bool> futureSync_;
	QHash<QString, QSharedPointer<QElapsedTimer>> customTimer_;


};