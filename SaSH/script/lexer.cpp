﻿#include "stdafx.h"
#include "lexer.h"

//全局關鍵字映射表
static const QHash<QString, RESERVE> keywords = {
#pragma region BIG5
	//test
	{ u8"測試", TK_CMD },

	//keyword
	{ u8"調用", TK_CALL },
	{ u8"行數", TK_JMP },
	{ u8"跳轉", TK_JMP },
	{ u8"返回", TK_RETURN },
	{ u8"結束", TK_END },
	{ u8"暫停", TK_PAUSE },
	{ u8"標記", TK_LABEL, },
	{ u8"變數", TK_VARDECL },
	{ u8"變數移除", TK_VARFREE },
	{ u8"變數清空", TK_VARCLR },
	{ u8"格式化", TK_FORMAT },

	//system
	{ u8"執行", TK_CMD },
	{ u8"延時", TK_CMD },
	{ u8"取消", TK_CMD },
	{ u8"提示", TK_CMD },
	{ u8"消息", TK_CMD },
	{ u8"提示", TK_CMD },
	{ u8"登出", TK_CMD },
	{ u8"登入", TK_CMD },
	{ u8"切換分流", TK_CMD },
	{ u8"元神歸位", TK_CMD },
	{ u8"回點", TK_CMD },
	{ u8"按鈕", TK_CMD },
	{ u8"說話", TK_CMD },
	{ u8"輸入", TK_CMD },
	{ u8"密語", TK_CMD },
	{ u8"說出", TK_CMD },
	{ u8"清屏", TK_CMD },
	{ u8"改時間", TK_CMD },
	{ u8"允許開關", TK_CMD },
	{ u8"設置", TK_CMD },
	{ u8"判斷", TK_CMD },
	{ u8"讀取設置", TK_CMD },
	{ u8"儲存設置", TK_CMD },


	//check info
	{ u8"戰鬥中", TK_CMD },
	{ u8"查坐標", TK_CMD },
	{ u8"查座標", TK_CMD },
	{ u8"地圖", TK_CMD },
	{ u8"地圖快判", TK_CMD },
	{ u8"對話", TK_CMD },
	{ u8"看見", TK_CMD },
	{ u8"聽見", TK_CMD },
	{ u8"道具", TK_CMD },
	{ u8"道具數量", TK_CMD },
	{ u8"堆疊數量", TK_CMD },
	{ u8"背包滿", TK_CMD },
	{ u8"人物狀態", TK_CMD },
	{ u8"寵物有", TK_CMD },
	{ u8"寵物狀態", TK_CMD },
	{ u8"寵物數量", TK_CMD },
	{ u8"任務狀態", TK_CMD },

	//actions
	{ u8"人物改名", TK_CMD },
	{ u8"使用咒術", TK_CMD },
	{ u8"寵物改名", TK_CMD },
	{ u8"寵物郵件", TK_CMD },
	{ u8"更換寵物", TK_CMD },
	{ u8"丟棄寵物", TK_CMD },
	{ u8"購買", TK_CMD },
	{ u8"售賣", TK_CMD },
	//{ u8"賣肉", TK_CMD },
	{ u8"使用道具", TK_CMD },
	{ u8"丟棄道具", TK_CMD },
	{ u8"撿物", TK_CMD },
	//{ u8"存入", TK_CMD },
	{ u8"存入道具", TK_CMD },
	{ u8"提出道具", TK_CMD },
	//{ u8"存入道具倉庫", TK_CMD },
	{ u8"存入寵物", TK_CMD },
	//{ u8"存入寵物倉庫", TK_CMD },
	{ u8"提出寵物", TK_CMD },
	//{ u8"提出寵物倉庫", TK_CMD },
	{ u8"存錢", TK_CMD },
	{ u8"提錢", TK_CMD },
	{ u8"加工", TK_CMD },
	{ u8"料理", TK_CMD },
	{ u8"修復", TK_CMD },
	{ u8"轉移", TK_CMD },
	{ u8"卸下裝備", TK_CMD },
	{ u8"記錄身上裝備", TK_CMD },
	//{ u8"檢測記錄裝備", TK_CMD },
	{ u8"裝上記錄裝備", TK_CMD },
	{ u8"加點", TK_CMD },

	//action with sub cmd
	{ u8"組隊", TK_CMD },
	{ u8"離隊", TK_CMD },
	{ u8"組隊有", TK_CMD },
	{ u8"組隊人數", TK_CMD },
	//{ u8"加入", TK_SUBCMD },
	//{ u8"離隊", TK_SUBCMD },
	//{ u8"狀態", TK_SUBCMD },
	//{ u8"人數", TK_SUBCMD },

	//{ u8"捉寵設定", TK_CMD },
	//{ u8"捉寵模式", TK_SUBCMD },
	//{ u8"捉寵目標寵物", TK_SUBCMD },
	//{ u8"捉寵等級", TK_SUBCMD },
	//{ u8"捉寵血量", TK_SUBCMD },
	//{ u8"捉寵人物技能", TK_SUBCMD },
	//{ u8"捉寵寵物技能", TK_SUBCMD },

	{ u8"切換掛機座標", TK_CMD },
	//{ u8"加入", TK_SUBCMD },
	//{ u8"清空", TK_SUBCMD },
	//{ u8"間隔時間", TK_SUBCMD },

	//move
	{ u8"坐標", TK_CMD },
	{ u8"座標", TK_CMD },
	{ u8"移動", TK_CMD },
	{ u8"封包移動", TK_CMD },
	{ u8"方向", TK_CMD },
	{ u8"最近坐標", TK_CMD },
	{ u8"尋路", TK_CMD },
	{ u8"尋找NPC", TK_CMD },
	{ u8"移動至NPC", TK_CMD },

	//mouse
	//{ u8"左雙擊", TK_CMD },
	//{ u8"右雙擊", TK_CMD },
	//{ u8"鼠移", TK_CMD },
	{ u8"左擊", TK_CMD },
	//{ u8"右擊", TK_CMD },
	//{ u8"左拖", TK_CMD },
#pragma endregion

	////////////////////////////////////////////////////
	////////////// GB2312 //////////////////////////////
	////////////////////////////////////////////////////

#pragma region GB2312

	//test
	{ u8"测试", TK_CMD },

	//keyword
	{ u8"调用", TK_CALL },
	{ u8"行数", TK_JMP },
	{ u8"跳转", TK_JMP },
	{ u8"返回", TK_RETURN },
	{ u8"结束", TK_END },
	{ u8"暂停", TK_PAUSE },
	{ u8"标记", TK_LABEL, },
	{ u8"变数", TK_VARDECL },
	{ u8"变数移除", TK_VARFREE },
	{ u8"变数清空", TK_VARCLR },
	{ u8"格式化", TK_FORMAT },

	//system
	{ u8"执行", TK_CMD },
	{ u8"延时", TK_CMD },
	{ u8"取消", TK_CMD },
	{ u8"提示", TK_CMD },
	{ u8"消息", TK_CMD },
	{ u8"提示", TK_CMD },
	{ u8"登出", TK_CMD },
	{ u8"登入", TK_CMD },
	{ u8"切换分流", TK_CMD },
	{ u8"元神归位", TK_CMD },
	{ u8"回点", TK_CMD },
	{ u8"按钮", TK_CMD },
	{ u8"说话", TK_CMD },
	{ u8"输入", TK_CMD },
	{ u8"密语", TK_CMD },
	{ u8"说出", TK_CMD },
	{ u8"清屏", TK_CMD },
	{ u8"改时间", TK_CMD },
	{ u8"允许开关", TK_CMD },
	{ u8"设置", TK_CMD },
	{ u8"判断", TK_CMD },
	{ u8"读取设置", TK_CMD },
	{ u8"储存设置", TK_CMD },


	//check info
	{ u8"战斗中", TK_CMD },
	{ u8"查坐标", TK_CMD },
	{ u8"查座标", TK_CMD },
	{ u8"地图", TK_CMD },
	{ u8"地图快判", TK_CMD },
	{ u8"对话", TK_CMD },
	{ u8"看见", TK_CMD },
	{ u8"听见", TK_CMD },
	{ u8"道具", TK_CMD },
	{ u8"道具数量", TK_CMD },
	{ u8"堆迭数量", TK_CMD },
	{ u8"背包满", TK_CMD },
	{ u8"人物状态", TK_CMD },
	{ u8"宠物有", TK_CMD },
	{ u8"宠物状态", TK_CMD },
	{ u8"宠物数量", TK_CMD },
	{ u8"任务状态", TK_CMD },

	//actions
	{ u8"人物改名", TK_CMD },
	{ u8"使用咒术", TK_CMD },
	{ u8"宠物改名", TK_CMD },
	{ u8"宠物邮件", TK_CMD },
	{ u8"更换宠物", TK_CMD },
	{ u8"丢弃宠物", TK_CMD },
	{ u8"购买", TK_CMD },
	{ u8"售卖", TK_CMD },
	//{ u8"卖肉", TK_CMD },
	{ u8"使用道具", TK_CMD },
	{ u8"丢弃道具", TK_CMD },
	{ u8"捡物", TK_CMD },
	//{ u8"存入", TK_CMD },
	{ u8"存入道具", TK_CMD },
	{ u8"提出道具", TK_CMD },
	//{ u8"存入道具仓库", TK_CMD },
	{ u8"存入宠物", TK_CMD },
	//{ u8"存入宠物仓库", TK_CMD },
	{ u8"提出宠物", TK_CMD },
	//{ u8"提出宠物仓库", TK_CMD },
	{ u8"存钱", TK_CMD },
	{ u8"提钱", TK_CMD },
	{ u8"加工", TK_CMD },
	{ u8"料理", TK_CMD },
	{ u8"修復", TK_CMD },
	{ u8"转移", TK_CMD },
	{ u8"卸下装备", TK_CMD },
	{ u8"记录身上装备", TK_CMD },
	//{ u8"检测记录装备", TK_CMD },
	{ u8"装上记录装备", TK_CMD },
	{ u8"加点", TK_CMD },

	//action with sub cmd
	{ u8"组队", TK_CMD },
	{ u8"离队", TK_CMD },
	{ u8"组队有", TK_CMD },
	{ u8"组队人数", TK_CMD },
	//{ u8"加入", TK_SUBCMD },
	//{ u8"离队", TK_SUBCMD },
	//{ u8"状态", TK_SUBCMD },
	//{ u8"人数", TK_SUBCMD },

	//{ u8"捉宠设定", TK_CMD },
	//{ u8"捉宠模式", TK_SUBCMD },
	//{ u8"捉宠目标宠物", TK_SUBCMD },
	//{ u8"捉宠等级", TK_SUBCMD },
	//{ u8"捉宠血量", TK_SUBCMD },
	//{ u8"捉宠人物技能", TK_SUBCMD },
	//{ u8"捉宠宠物技能", TK_SUBCMD },

	{ u8"切换挂机座标", TK_CMD },
	//{ u8"加入", TK_SUBCMD },
	//{ u8"清空", TK_SUBCMD },
	//{ u8"间隔时间", TK_SUBCMD },

	//move
	{ u8"坐标", TK_CMD },
	{ u8"座标", TK_CMD },
	{ u8"移动", TK_CMD },
	{ u8"封包移动", TK_CMD },
	{ u8"方向", TK_CMD },
	{ u8"最近坐标", TK_CMD },
	{ u8"寻路", TK_CMD },
	{ u8"寻找NPC", TK_CMD },
	{ u8"移动至NPC", TK_CMD },

	//mouse
	//{ u8"左双击", TK_CMD },
	//{ u8"右双击", TK_CMD },
	//{ u8"鼠移", TK_CMD },
	{ u8"左击", TK_CMD },
	//{ u8"右击", TK_CMD },
	//{ u8"左拖", TK_CMD },

#pragma endregion

	//... 其他後續增加的關鍵字
};

void Lexer::createToken(int index, RESERVE type, const QVariant& data, const QString& raw, TokenMap* ptoken)
{
	ptoken->insert(index, { type, data, raw });
}

void Lexer::createEmptyToken(int index, TokenMap* ptoken)
{
	ptoken->insert(index, { TK_WHITESPACE, "", "" });
}

void Lexer::tokenized(int currentLine, const QString& line, TokenMap* ptoken, QHash<QString, int>* plabel)
{
	if (ptoken == nullptr || plabel == nullptr)
		return;

	int pos = 0;
	QString token;
	QVariant data;
	QString raw = line.trimmed();

	ptoken->clear();

	do
	{
		int commentIndex = raw.indexOf("//");
		if (commentIndex > 0)
		{
			//當前token移除註釋
			raw = raw.mid(0, commentIndex).trimmed();
		}


		if (!getStringToken(raw, " ", token))
		{
			createEmptyToken(pos, ptoken);
			break;
		}

		if (token.isEmpty())
		{
			createEmptyToken(pos, ptoken);
			break;
		}

		//遇到註釋
		if (token.startsWith("//"))
		{
			createToken(pos, TK_COMMENT, "", "", ptoken);
			createToken(pos + 1, TK_COMMENT, data, token, ptoken);
			break;
		}

		RESERVE type = keywords.value(token, TK_UNK);
		if (type == TK_UNK)
		{
			createEmptyToken(pos, ptoken);
			break;
		}


		createToken(pos, type, QVariant::fromValue(token), token, ptoken);
		++pos;

		for (;;)
		{

			if (!getStringToken(raw, ",", token))
				break;

			if (token.isEmpty())
			{
				break;
			}
			RESERVE prevType = type;
			type = getTokenType(pos, prevType, token, raw);

			if (type == TK_INT)
			{
				bool ok;
				int intValue = token.toInt(&ok);
				if (ok)
				{
					data = QVariant::fromValue(intValue);
				}
			}
			else if (type == TK_DOUBLE)
			{
				bool ok;
				double floatValue = token.toDouble(&ok);
				if (ok)
				{
					data = QVariant::fromValue(floatValue);
				}
			}
			else if (type == TK_STRING)
			{
				if (token.startsWith("\"") && token.endsWith("\""))
					token = token.mid(1, token.length() - 2);
				data = QVariant::fromValue(token);
			}
			else if (type == TK_NAME)
			{
				data = QVariant::fromValue(token);
				if (prevType == TK_LABEL)
					plabel->insert(token, currentLine);
			}
			else
			{
				data = QVariant::fromValue(token);
			}

			createToken(pos, type, data, token, ptoken);
			++pos;
		}
	} while (false);
}

bool Lexer::tokenized(const QString& script, QHash<int, TokenMap>* ptokens, QHash<QString, int>* plabel)
{
	Lexer lexer;
	QHash<int, TokenMap> tokens;
	QHash<QString, int> labels;
	QStringList lines = script.split("\n");
	int size = lines.size();
	for (int i = 0; i < size; ++i)
	{
		TokenMap tk;
		lexer.tokenized(i, lines.at(i), &tk, &labels);
		tokens.insert(i, tk);
	}

	if (ptokens != nullptr && plabel != nullptr)
	{
		*ptokens = tokens;
		*plabel = labels;
		return true;
	}

	return false;
}

bool Lexer::isDouble(const QString& str) const
{
	if (str.count('.') != 1)
		return false;
	bool ok;
	str.toDouble(&ok);
	return ok;
}

bool Lexer::isInteger(const QString& str) const
{
	bool ok;
	str.toInt(&ok);
	return ok;
}

bool Lexer::isBool(const QString& str) const
{
	return (str == QString(u8"真") || str == QString(u8"假") || str == "true" || str == "false");
}

bool Lexer::isName(const QString& str, RESERVE previousType) const
{
	//check not start from number
	if (str.isEmpty() || str.at(0).isDigit())
		return false;

	return previousType == TK_LABEL || previousType == TK_CALL || previousType == TK_JMP;
}

bool Lexer::isString(const QString& str) const
{
	return (str.startsWith("\"") && str.endsWith("\""));
}

bool Lexer::isVariable(const QString& str) const
{
	return str.startsWith(kVariablePrefix) && !str.endsWith(kVariablePrefix);
}

bool Lexer::isLabel(const QString& str) const
{
	return  keywords.value(str, TK_UNK) == TK_LABEL;
}

bool Lexer::isSpace(const QChar& ch) const
{
	static const QRegularExpression re("\\s?");
	return re.match(ch).hasMatch();
}

bool Lexer::isComment(const QChar& ch) const
{
	return (ch == '/');
}

bool Lexer::isOperator(const QChar& ch) const
{
	return (
		(ch == '<') || (ch == '>') ||
		(ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
		(ch == '%') ||
		(ch == '&') || (ch == '|') || (ch == '~') || (ch == '^') ||
		(ch == '!')
		);
}

bool Lexer::isDelimiter(const QChar& ch) const
{
	return ((ch == ',') || (ch == ' '));
}

RESERVE Lexer::getTokenType(int& pos, RESERVE previous, QString& str, const QString raw) const
{


	int index = 0;

	if (str == "<<")
	{
		return TK_SHL;
	}
	else if (str == ">>")
	{
		return TK_SHR;
	}
	else if (str == "<")
	{
		return TK_LT;
	}
	else if (str == ">")
	{
		return TK_GT;
	}
	else if (str == "==")
	{
		return TK_EQ;
	}
	else if (str == "!=")
	{
		return TK_NEQ;
	}
	else if (str == ">=")
	{
		return TK_GEQ;
	}
	else if (str == "<=")
	{
		return TK_LEQ;
	}
	else if (str == "+")
	{
		return TK_ADD;
	}
	else if (str == "++")
	{
		return TK_INC;
	}
	else if (str == "-")
	{
		return TK_SUB;
	}
	else if (str == "--")
	{
		return TK_DEC;
	}
	else if (str == "*")
	{
		return TK_MUL;
	}
	else if (str == "/")
	{
		return TK_DIV;
	}
	else if (str == "%")
	{
		return TK_MOD;
	}
	else if (str == "&")
	{
		return TK_AND;
	}
	else if (str == "|")
	{
		return TK_OR;
	}
	else if (str == "~")
	{
		return TK_NOT;
	}
	else if (str == "^")
	{
		return TK_XOR;
	}
	else if (str == "!")
	{
		return TK_NEG;
	}
	else if (str == kFuzzyPrefix)
	{
		return TK_FUZZY;
	}
	else if (isVariable(str))
	{
		QChar nextChar = next(raw, index);
		if (nextChar.isLetterOrNumber() || nextChar == '\0')
		{
			return TK_REF;
		}
		else
		{
			return TK_UNK;
		}
	}
	else if (previous == TK_NAME || previous == TK_LABELVAR)
	{
		return TK_LABELVAR;
	}
	else if (isString(str))
	{
		return TK_STRING;
	}
	else if (isDouble(str))
	{
		return  TK_DOUBLE;
	}
	else if (isInteger(str))
	{
		return TK_INT;
	}
	else if (isBool(str))
	{
		return TK_BOOL;
	}
	else if (isName(str, previous))
	{
		return TK_NAME;
	}
	else if (str.startsWith("//"))
	{
		return TK_COMMENT;
	}

	return TK_STRING;
}

QChar Lexer::next(const QString& str, int& index) const
{
	if (index < str.length() - 1)
	{
		++index;
		return str[index];
	}
	else
	{
		return QChar();
	}
}

bool Lexer::getStringToken(QString& src, const QString& delim, QString& out)
{
	if (src.isEmpty())
		return false;

	if (delim.isEmpty())
		return false;

	QStringList list = src.split(delim);
	if (list.isEmpty())
		return false;

	out = list.first().trimmed();
	int size = out.size();
	//remove frist out and delim from src
	src.remove(0, size + delim.size());
	if (src.startsWith(delim))
		src.remove(0, delim.size());
	src = src.trimmed();
	return true;
}

