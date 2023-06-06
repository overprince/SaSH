﻿#pragma once
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>


#include <util.h>


#pragma region MACROS

#define _PETS_SELECTCON
#define _NEW_SYSTEM_MENU
#define _ANNOUNCEMENT_
#define _JOBDAILY
#define _TEACHER_SYSTEM
#define _MAGIC_NOCAST
#define _TEAM_KICKPARTY
#define _CHECK_GAMESPEED
#define _PET_ITEM
#define _ITEM_FIREWORK
#define _ITEM_EQUITSPACE
#define _CHAR_PROFESSION
#define _STANDBYPET
#define _ITEM_PILENUMS
#define _ALCHEMIST
#define _ITEM_JIGSAW
#define _SHOW_FUSION
#define _CHAR_NEWLOGOUT
#define _CHANNEL_MODIFY
#define _FMVER21
#define _CHANNEL_WORLD
#define _EQUIT_NEWGLOVE
#define __ATTACK_MAGIC
#define _SKILL_ADDBARRIER
#define _OBJSEND_C
#pragma endregion

#pragma region Const

constexpr unsigned char BitTable[] = {
		0x00 , 0x80 , 0x40 , 0xC0 , 0x20 , 0xA0 , 0x60 , 0xE0 ,
		0x10 , 0x90 , 0x50 , 0xD0 , 0x30 , 0xB0 , 0x70 , 0xF0 ,
		0x08 , 0x88 , 0x48 , 0xC8 , 0x28 , 0xA8 , 0x68 , 0xE8 ,
		0x18 , 0x98 , 0x58 , 0xD8 , 0x38 , 0xB8 , 0x78 , 0xF8 ,
		0x04 , 0x84 , 0x44 , 0xC4 , 0x24 , 0xA4 , 0x64 , 0xE4 ,
		0x14 , 0x94 , 0x54 , 0xD4 , 0x34 , 0xB4 , 0x74 , 0xF4 ,
		0x0C , 0x8C , 0x4C , 0xCC , 0x2C , 0xAC , 0x6C , 0xEC ,
		0x1C , 0x9C , 0x5C , 0xDC , 0x3C , 0xBC , 0x7C , 0xFC ,
		0x02 , 0x82 , 0x42 , 0xC2 , 0x22 , 0xA2 , 0x62 , 0xE2 ,
		0x12 , 0x92 , 0x52 , 0xD2 , 0x32 , 0xB2 , 0x72 , 0xF2 ,
		0x0A , 0x8A , 0x4A , 0xCA , 0x2A , 0xAA , 0x6A , 0xEA ,
		0x1A , 0x9A , 0x5A , 0xDA , 0x3A , 0xBA , 0x7A , 0xFA ,
		0x06 , 0x86 , 0x46 , 0xC6 , 0x26 , 0xA6 , 0x66 , 0xE6 ,
		0x16 , 0x96 , 0x56 , 0xD6 , 0x36 , 0xB6 , 0x76 , 0xF6 ,
		0x0E , 0x8E , 0x4E , 0xCE , 0x2E , 0xAE , 0x6E , 0xEE ,
		0x1E , 0x9E , 0x5E , 0xDE , 0x3E , 0xBE , 0x7E , 0xFE ,
		0x01 , 0x81 , 0x41 , 0xC1 , 0x21 , 0xA1 , 0x61 , 0xE1 ,
		0x11 , 0x91 , 0x51 , 0xD1 , 0x31 , 0xB1 , 0x71 , 0xF1 ,
		0x09 , 0x89 , 0x49 , 0xC9 , 0x29 , 0xA9 , 0x69 , 0xE9 ,
		0x19 , 0x99 , 0x59 , 0xD9 , 0x39 , 0xB9 , 0x79 , 0xF9 ,
		0x05 , 0x85 , 0x45 , 0xC5 , 0x25 , 0xA5 , 0x65 , 0xE5 ,
		0x15 , 0x95 , 0x55 , 0xD5 , 0x35 , 0xB5 , 0x75 , 0xF5 ,
		0x0D , 0x8D , 0x4D , 0xCD , 0x2D , 0xAD , 0x6D , 0xED ,
		0x1D , 0x9D , 0x5D , 0xDD , 0x3D , 0xBD , 0x7D , 0xFD ,
		0x03 , 0x83 , 0x43 , 0xC3 , 0x23 , 0xA3 , 0x63 , 0xE3 ,
		0x13 , 0x93 , 0x53 , 0xD3 , 0x33 , 0xB3 , 0x73 , 0xF3 ,
		0x0B , 0x8B , 0x4B , 0xCB , 0x2B , 0xAB , 0x6B , 0xEB ,
		0x1B , 0x9B , 0x5B , 0xDB , 0x3B , 0xBB , 0x7B , 0xFB ,
		0x07 , 0x87 , 0x47 , 0xC7 , 0x27 , 0xA7 , 0x67 , 0xE7 ,
		0x17 , 0x97 , 0x57 , 0xD7 , 0x37 , 0xB7 , 0x77 , 0xF7 ,
		0x0F , 0x8F , 0x4F , 0xCF , 0x2F , 0xAF , 0x6F , 0xEF ,
		0x1F , 0x9F , 0x5F , 0xDF , 0x3F , 0xBF , 0x7F , 0xFF
};
constexpr unsigned short crctab16[] = {
		0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50a5,  0x60c6,  0x70e7,
		0x8108,  0x9129,  0xa14a,  0xb16b,  0xc18c,  0xd1ad,  0xe1ce,  0xf1ef,
		0x1231,  0x0210,  0x3273,  0x2252,  0x52b5,  0x4294,  0x72f7,  0x62d6,
		0x9339,  0x8318,  0xb37b,  0xa35a,  0xd3bd,  0xc39c,  0xf3ff,  0xe3de,
		0x2462,  0x3443,  0x0420,  0x1401,  0x64e6,  0x74c7,  0x44a4,  0x5485,
		0xa56a,  0xb54b,  0x8528,  0x9509,  0xe5ee,  0xf5cf,  0xc5ac,  0xd58d,
		0x3653,  0x2672,  0x1611,  0x0630,  0x76d7,  0x66f6,  0x5695,  0x46b4,
		0xb75b,  0xa77a,  0x9719,  0x8738,  0xf7df,  0xe7fe,  0xd79d,  0xc7bc,
		0x48c4,  0x58e5,  0x6886,  0x78a7,  0x0840,  0x1861,  0x2802,  0x3823,
		0xc9cc,  0xd9ed,  0xe98e,  0xf9af,  0x8948,  0x9969,  0xa90a,  0xb92b,
		0x5af5,  0x4ad4,  0x7ab7,  0x6a96,  0x1a71,  0x0a50,  0x3a33,  0x2a12,
		0xdbfd,  0xcbdc,  0xfbbf,  0xeb9e,  0x9b79,  0x8b58,  0xbb3b,  0xab1a,
		0x6ca6,  0x7c87,  0x4ce4,  0x5cc5,  0x2c22,  0x3c03,  0x0c60,  0x1c41,
		0xedae,  0xfd8f,  0xcdec,  0xddcd,  0xad2a,  0xbd0b,  0x8d68,  0x9d49,
		0x7e97,  0x6eb6,  0x5ed5,  0x4ef4,  0x3e13,  0x2e32,  0x1e51,  0x0e70,
		0xff9f,  0xefbe,  0xdfdd,  0xcffc,  0xbf1b,  0xaf3a,  0x9f59,  0x8f78,
		0x9188,  0x81a9,  0xb1ca,  0xa1eb,  0xd10c,  0xc12d,  0xf14e,  0xe16f,
		0x1080,  0x00a1,  0x30c2,  0x20e3,  0x5004,  0x4025,  0x7046,  0x6067,
		0x83b9,  0x9398,  0xa3fb,  0xb3da,  0xc33d,  0xd31c,  0xe37f,  0xf35e,
		0x02b1,  0x1290,  0x22f3,  0x32d2,  0x4235,  0x5214,  0x6277,  0x7256,
		0xb5ea,  0xa5cb,  0x95a8,  0x8589,  0xf56e,  0xe54f,  0xd52c,  0xc50d,
		0x34e2,  0x24c3,  0x14a0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
		0xa7db,  0xb7fa,  0x8799,  0x97b8,  0xe75f,  0xf77e,  0xc71d,  0xd73c,
		0x26d3,  0x36f2,  0x0691,  0x16b0,  0x6657,  0x7676,  0x4615,  0x5634,
		0xd94c,  0xc96d,  0xf90e,  0xe92f,  0x99c8,  0x89e9,  0xb98a,  0xa9ab,
		0x5844,  0x4865,  0x7806,  0x6827,  0x18c0,  0x08e1,  0x3882,  0x28a3,
		0xcb7d,  0xdb5c,  0xeb3f,  0xfb1e,  0x8bf9,  0x9bd8,  0xabbb,  0xbb9a,
		0x4a75,  0x5a54,  0x6a37,  0x7a16,  0x0af1,  0x1ad0,  0x2ab3,  0x3a92,
		0xfd2e,  0xed0f,  0xdd6c,  0xcd4d,  0xbdaa,  0xad8b,  0x9de8,  0x8dc9,
		0x7c26,  0x6c07,  0x5c64,  0x4c45,  0x3ca2,  0x2c83,  0x1ce0,  0x0cc1,
		0xef1f,  0xff3e,  0xcf5d,  0xdf7c,  0xaf9b,  0xbfba,  0x8fd9,  0x9ff8,
		0x6e17,  0x7e36,  0x4e55,  0x5e74,  0x2e93,  0x3eb2,  0x0ed1,  0x1ef0,
};

#ifdef _MORECHARACTERS_
constexpr int MAXCHARACTER = 4;
#else
constexpr int MAXCHARACTER = 2;
#endif
constexpr int CHAR_NAME_LEN = 16;
constexpr int CHAR_FREENAME_LEN = 32;
constexpr int MAGIC_NAME_LEN = 28;
constexpr int MAGIC_MEMO_LEN = 72;
constexpr int ITEM_NAME_LEN = 28;
constexpr int ITEM_NAME2_LEN = 16;
constexpr int ITEM_MEMO_LEN = 84;
constexpr int PET_NAME_LEN = 16;
constexpr int PET_FREENAME_LEN = 32;
constexpr int CHAR_FMNAME_LEN = 33;     // 家族名稱

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
constexpr int PROFESSION_MEMO_LEN = 84;
#endif

#ifdef _GM_IDENTIFY		// Rog ADD GM識別
constexpr int GM_NAME_LEN = 32;
#endif

constexpr int CHARNAMELEN = 256;

constexpr int MAX_PET = 5;

constexpr int MAX_MAGIC = 9;

constexpr int MAX_PARTY = 5;

constexpr int MAX_ADR_BOOK_COUNT = 4;
#ifdef _EXTEND_AB
constexpr int MAX_ADR_BOOK_PAGE = 20;//20  //10   20050214 cyg 10 add to 20
#else
constexpr int MAX_ADR_BOOK_PAGE = 10;
#endif
constexpr int MAX_ADR_BOOK = (MAX_ADR_BOOK_COUNT * MAX_ADR_BOOK_PAGE);

#ifdef _PRO3_ADDSKILL
constexpr int MAX_PROFESSION_SKILL = 30;
#else
constexpr int MAX_PROFESSION_SKILL = 26;
#endif

constexpr int BATTLE_BUF_SIZE = 4;
constexpr int BATTLE_COMMAND_SIZE = 4096;

//#define FLOOR_NAME_LEN	24

constexpr int RESULT_ITEM_COUNT = 3;
//#define RESULT_ITEM_NAME_LEN	24
//#define RESULT_CHR_EXP			4
constexpr int RESULT_CHR_EXP = 5;

//#define SKILL_NAME_LEN			24
//#define SKILL_MEMO_LEN			72
constexpr int MAX_SKILL = 7;



constexpr int MAX_GOLD = 1000000;
constexpr int MAX_BANKGOLD = 10000000;
constexpr int MAX_FMBANKGOLD = 100000000;


constexpr int MAX_PERSONAL_BANKGOLD = 50000000;

#ifdef _FMVER21
constexpr int FAMILY_MAXMEMBER = 100;    // 家族人數
#else
constexpr int FAMILY_MAXMEMBER = 50;    // 家族人數
#endif

constexpr int MAP_TILE_GRID_X1 = -20;
constexpr int MAP_TILE_GRID_X2 = +17;
constexpr int MAP_TILE_GRID_Y1 = -16;
constexpr int MAP_TILE_GRID_Y2 = +21;
constexpr int MAP_X_SIZE = (MAP_TILE_GRID_X2 - MAP_TILE_GRID_X1);
constexpr int MAP_Y_SIZE = (MAP_TILE_GRID_Y2 - MAP_TILE_GRID_Y1);

constexpr int MAP_READ_FLAG = 0x8000;
constexpr int  MAP_SEE_FLAG = 0x4000;

constexpr int BC_FLG_NEW = (1 << 0);
constexpr int BC_FLG_DEAD = (1 << 1);	  //死亡
constexpr int BC_FLG_PLAYER = (1 << 2);	  //玩家,玩家有异常状态时要有此值
constexpr int BC_FLG_POISON = (1 << 3);	  //中毒
constexpr int BC_FLG_PARALYSIS = (1 << 4); //麻痹
constexpr int BC_FLG_SLEEP = (1 << 5);  //昏睡
constexpr int BC_FLG_STONE = (1 << 6);	  //石化
constexpr int BC_FLG_DRUNK = (1 << 7);  //眩晕
constexpr int BC_FLG_CONFUSION = (1 << 8); //混乱
constexpr int BC_FLG_HIDE = (1 << 9);	  //是否隐藏，地球一周
constexpr int BC_FLG_REVERSE = (1 << 10);  //反转

inline constexpr bool hasBadStatus(int status)
{
	int allAbnormalFlags = BC_FLG_POISON | BC_FLG_PARALYSIS | BC_FLG_SLEEP | BC_FLG_STONE | BC_FLG_DRUNK | BC_FLG_CONFUSION;
	return (status & allAbnormalFlags) != 0;
}


constexpr int ITEM_FLAG_PET_MAIL = (1 << 0);
constexpr int ITEM_FLAG_MIX = (1 << 1);
constexpr int ITEM_FLAG_COOKING_MIX = (1 << 2);
constexpr int ITEM_FLAG_METAL_MIX = (1 << 3);	//金屬
constexpr int ITEM_FLAG_JEWEL_MIX = (1 << 4);	//寶石
constexpr int ITEM_FLAG_FIX_MIX = (1 << 5);	//修理
#ifdef _ITEM_INTENSIFY
constexpr int ITEM_FLAG_INTENSIFY_MIX = (1 << 6);	//強化
#endif
#ifdef _ITEM_UPINSLAY
constexpr int ITEM_FLAG_UPINSLAY_MIX = (1 << 7);	//鑿孔
#endif

constexpr int JOY_RIGHT = (1 << 15);/* Right Key				*/
constexpr int JOY_LEFT = (1 << 14);/*  Left Key				*/
constexpr int JOY_DOWN = (1 << 13);/*  Down Key				*/
constexpr int JOY_UP = (1 << 12);	/*    Up Key				*/
constexpr int JOY_START = (1 << 11);	/* Start					*/
constexpr int JOY_A = (1 << 10);	/* A Trigger				*/
constexpr int JOY_C = (1 << 9);/* C Trigger				*/
constexpr int JOY_B = (1 << 8);	/* B Trigger				*/
constexpr int JOY_R = (1 << 7);	/* R Trigger				*/
constexpr int JOY_X = (1 << 6);	/* X Trigger				*/
constexpr int JOY_DEL = (1 << 5);	/* DELETE					*/
constexpr int JOY_INS = (1 << 4);	/* INSERT					*/
constexpr int JOY_END = (1 << 3);/* END						*/
constexpr int JOY_HOME = (1 << 2);	/* HOME						*/
constexpr int JOY_P_DOWN = (1 << 1);	/* PAGE_UP					*/
constexpr int JOY_P_UP = (1 << 0);	/* PAGE_DOWN				*/

constexpr int JOY_ESC = (1 << 31);/* ESC Key					*/
constexpr int JOY_CTRL_M = (1 << 30);	/* Ctrl + M					*/
constexpr int JOY_CTRL_S = (1 << 29);	/* Ctrl + S					*/
constexpr int JOY_CTRL_P = (1 << 28);	/* Ctrl + P					*/
constexpr int JOY_CTRL_I = (1 << 27);	/* Ctrl + I					*/
constexpr int JOY_CTRL_E = (1 << 26);	/* Ctrl + E					*/
constexpr int JOY_CTRL_A = (1 << 25);	/* Ctrl + A					*/

constexpr int JOY_CTRL_C = (1 << 24);	/* Ctrl + C					*/
constexpr int JOY_CTRL_V = (1 << 23);	/* Ctrl + V					*/
constexpr int JOY_CTRL_T = (1 << 22);	/* Ctrl + T					*/

//#define MAIL_STR_LEN 140		
//#define MAIL_DATE_STR_LEN 20
constexpr int MAIL_MAX_HISTORY = 20;
constexpr int MAX_CHAT_REGISTY_STR = 8;

constexpr int MAX_DIR = 8;

constexpr const char* SUCCESSFULSTR = u8"successful";
constexpr const char* FAILEDSTR = u8"failed";
constexpr const char* OKSTR = u8"ok";
constexpr const char* CANCLE = u8"cancle";

constexpr int BATTLE_MAP_FILES = 220;
constexpr int GRID_SIZE = 64;

constexpr unsigned long long LSTIME_SECONDS_PER_DAY = 5400ULL;
constexpr unsigned long long LSTIME_HOURS_PER_DAY = 1024ULL;
constexpr unsigned long long LSTIME_DAYS_PER_YEAR = 100ULL;

#if 0

constexpr int NIGHT_TO_MORNING = 906;
constexpr int MORNING_TO_NOON = 1006;
constexpr int  NOON_TO_EVENING = 356;
constexpr int EVENING_TO_NIGHT = 456;

#else

constexpr int NIGHT_TO_MORNING = 700;
constexpr int MORNING_TO_NOON = 930;
constexpr int NOON_TO_EVENING = 200;
constexpr int EVENING_TO_NIGHT = 300;

#endif

static const char* palFileName[] = {
	"data\\pal\\Palet_1.sap",	// 
	"data\\pal\\Palet_2.sap",	// 
	"data\\pal\\Palet_3.sap",	// 
	"data\\pal\\Palet_4.sap",	//

	"data\\pal\\Palet_5.sap",	// 
	"data\\pal\\Palet_6.sap",	//
	"data\\pal\\Palet_7.sap",	// 
	"data\\pal\\Palet_8.sap",	//
	"data\\pal\\Palet_9.sap",	// 
	"data\\pal\\Palet_10.sap",	// 
	"data\\pal\\Palet_11.sap",	// 
	"data\\pal\\Palet_12.sap",	//
	"data\\pal\\Palet_13.sap",	//
	"data\\pal\\Palet_14.sap",	//
	"data\\pal\\Palet_15.sap",	//
	"data\\pal\\Palet_0.sap",	//Waei logo
	"white.sap",				// 
	"black.sap",				// 
};

constexpr int MAX_PAL = sizeof(palFileName) / sizeof(palFileName[0]);


#pragma endregion

#pragma region Enums

enum FUNCTIONTYPE
{
	LSSPROTO_ERROR_RECV = -23,
	LSSPROTO_W_SEND = 0,
	LSSPROTO_W2_SEND = 1,
	LSSPROTO_XYD_RECV = 2,
	LSSPROTO_EV_SEND = 3,
	LSSPROTO_EV_RECV = 4,
	LSSPROTO_EN_SEND = 5,
	LSSPROTO_DU_SEND = 6,
	LSSPROTO_EN_RECV = 7,
	LSSPROTO_EO_SEND = 8,
	LSSPROTO_BU_SEND = 9,
	LSSPROTO_JB_SEND = 10,
	LSSPROTO_LB_SEND = 11,
	LSSPROTO_RS_RECV = 12,
	LSSPROTO_RD_RECV = 13,
	LSSPROTO_B_SEND = 14,
	LSSPROTO_B_RECV = 15,
	LSSPROTO_SKD_SEND = 16,
	LSSPROTO_ID_SEND = 17,
	LSSPROTO_PI_SEND = 18,
	LSSPROTO_DI_SEND = 19,
	LSSPROTO_DG_SEND = 20,
	LSSPROTO_DP_SEND = 21,
	LSSPROTO_I_RECV = 22,
	LSSPROTO_MI_SEND = 23,
	LSSPROTO_SI_RECV = 24,
	LSSPROTO_MSG_SEND = 25,
	LSSPROTO_MSG_RECV = 26,
	LSSPROTO_PMSG_SEND = 27,
	LSSPROTO_PME_RECV = 28,
	LSSPROTO_AB_SEND = 29,
	LSSPROTO_AB_RECV = 30,
	LSSPROTO_ABI_RECV = 31,
	LSSPROTO_DAB_SEND = 32,
	LSSPROTO_AAB_SEND = 33,
	LSSPROTO_L_SEND = 34,
	LSSPROTO_TK_SEND = 35,
	LSSPROTO_TK_RECV = 36,
	LSSPROTO_MC_RECV = 37,
	LSSPROTO_M_SEND = 38,
	LSSPROTO_M_RECV = 39,
	LSSPROTO_C_SEND = 40,
	LSSPROTO_C_RECV = 41,
	LSSPROTO_CA_RECV = 42,
	LSSPROTO_CD_RECV = 43,
	LSSPROTO_R_RECV = 44,
	LSSPROTO_S_SEND = 45,
	LSSPROTO_S_RECV = 46,
	LSSPROTO_D_RECV = 47,
	LSSPROTO_FS_SEND = 48,
	LSSPROTO_FS_RECV = 49,
	LSSPROTO_HL_SEND = 50,
	LSSPROTO_HL_RECV = 51,
	LSSPROTO_PR_SEND = 52,
	LSSPROTO_PR_RECV = 53,
	LSSPROTO_KS_SEND = 54,
	LSSPROTO_KS_RECV = 55,
	LSSPROTO_AC_SEND = 56,
	LSSPROTO_MU_SEND = 57,
	LSSPROTO_PS_SEND = 58,
	LSSPROTO_PS_RECV = 59,
	LSSPROTO_ST_SEND = 60,
	LSSPROTO_DT_SEND = 61,
	LSSPROTO_FT_SEND = 62,
	LSSPROTO_SKUP_RECV = 63,
	LSSPROTO_SKUP_SEND = 64,
	LSSPROTO_KN_SEND = 65,
	LSSPROTO_WN_RECV = 66,
	LSSPROTO_WN_SEND = 67,
	LSSPROTO_EF_RECV = 68,
	LSSPROTO_SE_RECV = 69,
	LSSPROTO_SP_SEND = 70,
	LSSPROTO_CLIENTLOGIN_SEND = 71,
	LSSPROTO_CLIENTLOGIN_RECV = 72,
	LSSPROTO_CREATENEWCHAR_SEND = 73,
	LSSPROTO_CREATENEWCHAR_RECV = 74,
	LSSPROTO_CHARDELETE_SEND = 75,
	LSSPROTO_CHARDELETE_RECV = 76,
	LSSPROTO_CHARLOGIN_SEND = 77,
	LSSPROTO_CHARLOGIN_RECV = 78,
	LSSPROTO_CHARLIST_SEND = 79,
	LSSPROTO_CHARLIST_RECV = 80,
	LSSPROTO_CHARLOGOUT_SEND = 81,
	LSSPROTO_CHARLOGOUT_RECV = 82,
	LSSPROTO_PROCGET_SEND = 83,
	LSSPROTO_PROCGET_RECV = 84,
	LSSPROTO_PLAYERNUMGET_SEND = 85,
	LSSPROTO_PLAYERNUMGET_RECV = 86,
	LSSPROTO_ECHO_SEND = 87,
	LSSPROTO_ECHO_RECV = 88,
	LSSPROTO_SHUTDOWN_SEND = 89,
	LSSPROTO_NU_RECV = 90,
	LSSPROTO_TD_SEND = 91,
	LSSPROTO_TD_RECV = 92,
	LSSPROTO_FM_RECV = 93,
	LSSPROTO_FM_SEND = 94,
	LSSPROTO_WO_RECV = 95,
	LSSPROTO_PETST_SEND = 96,
	LSSPROTO_BM_SEND = 97,   // _BLACK_MARKET,
#ifdef _MIND_ICON
	LSSPROTO_MA_SEND = 98,
#endif
#ifdef _FIX_DEL_MAP
	LSSPROTO_DM_SEND = 99   // 玩家抽地圖送監獄,
#endif
#ifdef _ITEM_CRACKER
	LSSPROTO_IC_RECV = 100,
#endif
#ifdef _MAGIC_NOCAST//沈默,
	LSSPROTO_NC_RECV = 101,
#endif
#ifdef _CHECK_GAMESPEED
	LSSPROTO_CS_SEND = 103,
	LSSPROTO_CS_RECV = 104,
#endif
#ifdef _TEAM_KICKPARTY
	LSSPROTO_KTEAM_SEND = 106,
#endif

#ifdef _PETS_SELECTCON
	LSSPROTO_PETST_RECV = 107,
#endif
#ifdef _NEWREQUESTPROTOCOL			// (不可開) Syu ADD 新增Protocol要求細項,
	LSSPROTO_RESIST_SEND = 108,
	LSSPROTO_RESIST_RECV = 109,
#endif
#ifdef _OUTOFBATTLESKILL			// (不可開) Syu ADD 非戰鬥時技能Protocol,
	LSSPROTO_BATTLESKILL_SEND = 110,
	LSSPROTO_BATTLESKILL_RECV = 111,
#endif
#ifdef _CHATROOMPROTOCOL			// (不可開) Syu ADD 聊天室頻道,
	LSSPROTO_CHATROOM_SEND = 112,
	LSSPROTO_CHATROOM_RECV = 113,
#endif
	LSSPROTO_SPET_SEND = 114,		// Robin 待機寵,
	LSSPROTO_SPET_RECV = 115,
#ifdef _STREET_VENDOR
	LSSPROTO_STREET_VENDOR_SEND = 116		// 擺攤功能,
	LSSPROTO_STREET_VENDOR_RECV = 117,
#endif
#ifdef _JOBDAILY
	LSSPROTO_JOBDAILY_SEND = 121,		// CYG　任務日志功能,
	LSSPROTO_JOBDAILY_RECV = 120,
#endif

#ifdef _TEACHER_SYSTEM
	LSSPROTO_TEACHER_SYSTEM_SEND = 122,		// 導師功能,
	LSSPROTO_TEACHER_SYSTEM_RECV = 123,
#endif

#ifdef _ADD_STATUS_2
	LSSPROTO_S2_SEND = 124,
	LSSPROTO_S2_RECV = 125,
#endif

#ifdef _ITEM_FIREWORK
	LSSPROTO_FIREWORK_RECV = 126,
#endif
#ifdef _PET_ITEM
	LSSPROTO_PET_ITEM_EQUIP_SEND = 127,
#endif
#ifdef _MOVE_SCREEN
	LSSPROTO_MOVE_SCREEN_RECV = 128,
#endif
#ifdef _GET_HOSTNAME
	LSSPROTO_HOSTNAME_SEND = 129,
	LSSPROTO_HOSTNAME_RECV = 130,
#endif
#ifdef _THEATER
	LSSPROTO_THEATER_DATA_RECV = 131,
	LSSPROTO_THEATER_DATA_SEND = 132,
#endif

#ifdef _NPC_MAGICCARD
	LSSPROTO_MAGICCARD_ACTION_RECV = 133,
	LSSPROTO_MAGICCARD_DAMAGE_RECV = 134,
#endif

#ifdef _SECONDARY_WINDOW_DATA_
	LSSPROTO_SECONDARY_WINDOW_RECV = 137,
#endif

#ifdef _ICONBUTTONS_
	LSSPROTO_TRUNTABLE_RECV = 138,
#endif

#ifdef _ALCHEPLUS
	LSSPROTO_ALCHEPLUS_SEND = 135,
	LSSPROTO_ALCHEPLUS_RECV = 136,
#endif

#ifdef _NPC_DANCE
	LSSPROTO_DANCEMAN_OPTION_RECV = 137,
#endif

#ifdef _HUNDRED_KILL
	LSSPROTO_HUNDREDKILL_RECV = 138,
#endif

#ifdef _PK2007
	LSSPROTO_PKLIST_SEND = 139,
	LSSPROTO_PKLIST_RECV = 140,
#endif

#ifdef _CHARSIGNDAY_
	LSSPROTO_SIGNDAY_SEND = 141,
#endif

	LSSPROTO_CHAREFFECT_RECV = 146,
#ifdef _RED_MEMOY_
	LSSPROTO_REDMEMOY_SEND = 147,
	LSSPROTO_REDMEMOY_RECV = 148,
#endif

#ifdef _ANNOUNCEMENT_
	LSSPROTO_DENGON_RECV = 200,
#endif
#ifdef _NEW_SYSTEM_MENU
	LSSPROTO_SAMENU_RECV = 201,
	LSSPROTO_SAMENU_SEND = 202,
#endif
#ifdef _NEWSHOP_
	LSSPROTO_SHOPOK_SEND = 208,
	LSSPROTO_SHOPOK_RECV = 209,
#endif
#ifdef _FAMILYBADGE_
	LSSPROTO_FAMILYBADGE_SEND = 210,
	LSSPROTO_FAMILYBADGE_RECV = 211,
#endif

#ifdef _CHARTITLE_
	LSSPROTO_CHARTITLE_SEND = 212,
	LSSPROTO_CHARTITLE_RECV = 213,
#endif

#ifdef _CHARTITLE_STR_
	LSSPROTO_CHARTITLE_SEND = 212,
	LSSPROTO_CHARTITLE_RECV = 213,
#endif

#ifdef _PETBLESS_
	LSSPROTO_VB_SEND = 218,
	LSSPROTO_VB_RECV = 219,
#endif

#ifdef _RIDEQUERY_//騎寵查詢,
	LSSPROTO_RIDEQUERY_SEND = 220,
#endif

#ifdef _PET_SKINS
	LSSPROTO_PETSKINS_SEND = 221,
	LSSPROTO_PETSKINS_RECV = 222,
#endif
	LSSPROTO_JOINTEAM_SEND = 239,
	LSSPROTO_ARRAGEITEM_SEND = 260,
};


#ifdef _ITEM_EQUITSPACE
typedef enum tagCHAR_EquipPlace
{
	CHAR_HEAD,
	CHAR_BODY,
	CHAR_ARM,
	CHAR_DECORATION1,
	CHAR_DECORATION2,

#ifdef _ITEM_EQUITSPACE
	CHAR_EQBELT,
	CHAR_EQSHIELD,
	CHAR_EQSHOES,
#endif

#ifdef _EQUIT_NEWGLOVE
	CHAR_EQGLOVE,
#endif
	CHAR_EQUIPPLACENUM,
#ifdef _PET_ITEM
	PET_HEAD = 0,	// 頭
	PET_WING,		// 翼
	PET_TOOTH,		// 牙
	PET_PLATE,		// 身體
	PET_BACK,		// 背
	PET_CLAW,		// 爪
	PET_FOOT,		// 腳(鰭)
	PET_EQUIPNUM
#endif
}CHAR_EquipPlace;

#ifdef _PET_ITEM
typedef enum tagITEM_CATEGORY
{
	// 寵物道具,共九種
	ITEM_PET_HEAD = 29,		// 頭
	ITEM_PET_WING,			// 翼
	ITEM_PET_TOOTH,			// 牙
	ITEM_PET_PLATE,			// 身體護甲
	ITEM_PET_BACK,			// 背部護甲
	ITEM_PET_CLAW,			// 爪
	ITEM_PET_1_FOOT,		// 腳部,雙足
	ITEM_PET_2_FOOT,		// 腳部,四足
	ITEM_PET_FIN,			// 腳部,鰭
	ITEM_CATEGORYNUM
}ITEM_CATEGORY;
constexpr int MAX_PET_ITEM = 7;
#endif


constexpr int MAX_ITEMSTART = CHAR_EQUIPPLACENUM;
constexpr int MAX_MAXHAVEITEM = 15;
#ifdef _NEW_ITEM_
constexpr int MAX_ITEM(MAX_ITEMSTART + MAX_MAXHAVEITEM * 3);
int 判斷玩家道具數量();
#else
constexpr int MAX_ITEM = (MAX_ITEMSTART + MAX_MAXHAVEITEM);
#endif
#else
constexpr int MAX_ITEMSTART = 5;
constexpr int MAX_ITEM = 20;
#endif


enum
{
	PC_ETCFLAG_GROUP = (1 << 0),	//組隊開關
	PC_ETCFLAG_PK = (1 << 2),	//決鬥開關
	PC_ETCFLAG_CARD = (1 << 4),	//名片開關
	PC_ETCFLAG_TRADE = (1 << 5),	//交易開關
	PC_ETCFLAG_WORLD = (1 << 6),	//世界頻道開關
	PC_ETCFLAG_FM = (1 << 7),	//家族頻道開關
	PC_ETCFLAG_JOB = (1 << 8),	//職業頻道開關
};

//enum
//{
//	PC_ETCFLAG_PARTY = (1 << 0),
//	PC_ETCFLAG_DUEL = (1 << 1),
//	PC_ETCFLAG_CHAT_MODE = (1 << 2),//隊伍頻道開關
//	PC_ETCFLAG_MAIL = (1 << 3),//名片頻道
//	PC_ETCFLAG_TRADE = (1 << 4)
//#ifdef _CHANNEL_MODIFY
//	, PC_ETCFLAG_CHAT_TELL = (1 << 5)//密語頻道開關
//	, PC_ETCFLAG_CHAT_FM = (1 << 6)//家族頻道開關
//#ifdef _CHAR_PROFESSION
//	, PC_ETCFLAG_CHAT_OCC = (1 << 7)//職業頻道開關
//#endif
//	, PC_ETCFLAG_CHAT_SAVE = (1 << 8)//對話儲存開關
//#ifdef _CHATROOMPROTOCOL
//	, PC_ETCFLAG_CHAT_CHAT = (1 << 9)//聊天室開關
//#endif
//#endif
//#ifdef _CHANNEL_WORLD
//	, PC_ETCFLAG_CHAT_WORLD = (1 << 10)//世界頻道開關
//#endif
//#ifdef _CHANNEL_ALL_SERV
//	, PC_ETCFLAG_ALL_SERV = (1 << 11)//星球頻道開關
//#endif
//	, PC_AI_MOD = (1 << 12)
//};

enum
{
	PC_ETCFLAG_CHAT_MODE_ID = 0

#ifdef _CHANNEL_MODIFY
	, PC_ETCFLAG_CHAT_TELL_ID		//密語頻道
	, PC_ETCFLAG_CHAT_PARTY_ID		//隊伍頻道
	, PC_ETCFLAG_CHAT_FM_ID			//家族頻道
#ifdef _CHAR_PROFESSION
	, PC_ETCFLAG_CHAT_OCC_ID			//職業頻道
#endif
#ifdef _CHATROOMPROTOCOL
	, PC_ETCFLAG_CHAT_CHAT_ID		//聊天室
#endif
#else
	, PC_ETCFLAG_CHAT_PARTY_ID		//隊伍頻道
#endif
#ifdef _CHANNEL_WORLD
	, PC_ETCFLAG_CHAT_WORLD_ID			//世界頻道
#endif
#ifdef _CHANNEL_ALL_SERV
	, PC_ETCFLAG_ALL_SERV_ID			//星球頻道開關
#endif
	, PC_ETCFLAG_CHAT_WORLD_NUM
};

enum CHR_STATUS
{
	CHR_STATUS_NONE = 0,
	CHR_STATUS_P = 0x0001,
	CHR_STATUS_N = 0x0002,
	CHR_STATUS_Q = 0x0004,
	CHR_STATUS_S = 0x0008,
	CHR_STATUS_D = 0x0010,
	CHR_STATUS_C = 0x0020,
	CHR_STATUS_W = 0x0040,
	CHR_STATUS_H = 0x0080,
	CHR_STATUS_LEADER = 0x0100,
	CHR_STATUS_PARTY = 0x0200,
	CHR_STATUS_BATTLE = 0x0400,
	CHR_STATUS_USE_MAGIC = 0x0800,
	CHR_STATUS_HELP = 0x1000,
	CHR_STATUS_FUKIDASHI = 0x2000,
	CHR_STATUS_WATCH = 0x4000,
	CHR_STATUS_TRADE = 0x8000,			// 交易中
#ifdef _ANGEL_SUMMON
	CHR_STATUS_ANGEL = 0x10000			// 使者任務中
#endif
};

enum CHAROBJ_TYPE
{
	CHAROBJ_TYPE_NONE = 0x0000,
	CHAROBJ_TYPE_NPC = 0x0001,		// NPC
	CHAROBJ_TYPE_ITEM = 0x0002,
	CHAROBJ_TYPE_MONEY = 0x0004,
	CHAROBJ_TYPE_USER_NPC = 0x0008,
	CHAROBJ_TYPE_LOOKAT = 0x0010,
	CHAROBJ_TYPE_PARTY_OK = 0x0020,
	CHAROBJ_TYPE_ALL = 0x00FF
};

enum CHAR_TYPE
{
	CHAR_TYPENONE,
	CHAR_TYPEPLAYER,
	CHAR_TYPEENEMY,
	CHAR_TYPEPET,
	CHAR_TYPEDOOR,
	CHAR_TYPEBOX,
	CHAR_TYPEMSG,
	CHAR_TYPEWARP,
	CHAR_TYPESHOP,
	CHAR_TYPEHEALER,
	CHAR_TYPEOLDMAN,
	CHAR_TYPEROOMADMIN,
	CHAR_TYPETOWNPEOPLE,
	CHAR_TYPEDENGON,
	CHAR_TYPEADM,
	CHAR_TYPETEMPLE,        // Temple master
	CHAR_TYPESTORYTELLER,
	CHAR_TYPERANKING,
	CHAR_TYPEOTHERNPC,
	CHAR_TYPEPRINTPASSMAN,
	CHAR_TYPENPCENEMY,
	CHAR_TYPEACTION,
	CHAR_TYPEWINDOWMAN,
	CHAR_TYPESAVEPOINT,
	CHAR_TYPEWINDOWHEALER,
	CHAR_TYPEITEMSHOP,
	CHAR_TYPESTONESHOP,
	CHAR_TYPEDUELRANKING,
	CHAR_TYPEWARPMAN,
	CHAR_TYPEEVENT,
	CHAR_TYPEMIC,
	CHAR_TYPELUCKYMAN,
	CHAR_TYPEBUS,
	CHAR_TYPECHARM,
	CHAR_TYPENUM
};

typedef enum
{
	LS_NOON,
	LS_EVENING,
	LS_NIGHT,
	LS_MORNING,
}LSTIME_SECTION;


#ifdef _FMVER21
enum
{
	FMMEMBER_NONE = -1,  // 未加入任何家族
	FMMEMBER_MEMBER = 1,   // 一般成員
	FMMEMBER_APPLY,        // 申請加入家族
	FMMEMBER_LEADER,       // 家族族長        
	FMMEMBER_ELDER,        // 長老
	//FMMEMBER_INVITE,     // 祭司
	//FMMEMBER_BAILEE,     // 財務長
	//FMMEMBER_VICELEADER, // 副族長
	FMMEMBER_NUMBER,
};
#endif

enum
{
	MAGIC_FIELD_ALL,
	MAGIC_FIELD_BATTLE,
	MAGIC_FIELD_MAP
};

enum
{
	MAGIC_TARGET_MYSELF,//自己
	MAGIC_TARGET_OTHER,//雙方任意
	MAGIC_TARGET_ALLMYSIDE,//我方全體
	MAGIC_TARGET_ALLOTHERSIDE,//敵方全體
	MAGIC_TARGET_ALL,//雙方全體同時
	MAGIC_TARGET_NONE,//無
	MAGIC_TARGET_OTHERWITHOUTMYSELF,//我方任意除了自己
	MAGIC_TARGET_WITHOUTMYSELFANDPET,//我方任意除了自己和寵物
	MAGIC_TARGET_WHOLEOTHERSIDE,//敵方全體 或 我方全體
#ifdef __ATTACK_MAGIC
	MAGIC_TARGET_SINGLE,				// 針對敵方某一方
	MAGIC_TARGET_ONE_ROW,				// 針對敵方某一列
	MAGIC_TARGET_ALL_ROWS,				// 針對敵方所有人
#endif
};

enum
{
	PETSKILL_FIELD_ALL,
	PETSKILL_FIELD_BATTLE,
	PETSKILL_FIELD_MAP
};

enum
{
	PETSKILL_TARGET_MYSELF,
	PETSKILL_TARGET_OTHER,
	PETSKILL_TARGET_ALLMYSIDE,
	PETSKILL_TARGET_ALLOTHERSIDE,
	PETSKILL_TARGET_ALL,
	PETSKILL_TARGET_NONE,
	PETSKILL_TARGET_OTHERWITHOUTMYSELF,
	PETSKILL_TARGET_WITHOUTMYSELFANDPET
#ifdef _BATTLESKILL				// (不可開) Syu ADD 戰鬥技能介面
	, PETSKILL_TARGET_ONE_ROW
	, PETSKILL_TARGET_ONE_LINE
	, PETSKILL_TARGER_DEATH
#endif
#ifdef _SKILL_ADDBARRIER
	, PETSKILL_TARGET_ONE_ROW_ALL //選我方的單排
#endif
};

enum
{
	ITEM_FIELD_ALL,
	ITEM_FIELD_BATTLE,
	ITEM_FIELD_MAP,
};

enum
{
	ITEM_TARGET_MYSELF,
	ITEM_TARGET_OTHER,
	ITEM_TARGET_ALLMYSIDE,
	ITEM_TARGET_ALLOTHERSIDE,
	ITEM_TARGET_ALL,
	ITEM_TARGET_NONE,
	ITEM_TARGET_OTHERWITHOUTMYSELF,
	ITEM_TARGET_WITHOUTMYSELFANDPET,
#ifdef _PET_ITEM
	ITEM_TARGET_PET
#endif
};

enum
{
	MOUSE_CURSOR_MODE_NORMAL,
	MOUSE_CURSOR_MODE_MOVE
};

enum
{
	PROC_INIT,
	PROC_ID_PASSWORD,
	PROC_TITLE_MENU,
	PROC_CHAR_SELECT,
	PROC_CHAR_MAKE,
	PROC_CHAR_LOGIN_START,
	PROC_CHAR_LOGIN,
	PROC_CHAR_LOGOUT,
	PROC_OPENNING,
	PROC_GAME,
	PROC_BATTLE,
	PROC_DISCONNECT_SERVER,

	PROC_TAKE_TEST,
	PROC_OHTA_TEST,
	PROC_DWAF_TEST,
	PROC_SPR_VIEW,
	PROC_ANIM_VIEW,
	PROC_SE_TEST,

#ifdef _80_LOGIN_PLAY
	PROC_80_LOGIN,
#endif
#ifdef _PK2007
	PROC_PKSERVER_SELECT,
#endif
	PROC_ENDING
};

enum PetState
{
	kNoneState,
	kBattle,
	kStandby,
	kMail,
	kRest,
	kRide
};

enum BUTTON_TYPE
{
	BUTTON_NOTUSED = 0,
	BUTTON_OK = 1,	   //確定
	BUTTON_CANCEL = 2, //取消
	BUTTON_YES = 4,	   //是
	BUTTON_NO = 8,	   //否
	BUTTON_CLOSE = 9,  //關閉
	BUTTON_PREVIOUS = 16,  //上一頁
	BUTTON_NEXT = 32,
};
#pragma endregion

#pragma region Structs

//typedef struct action
//{
//	struct 	action* pPrev, * pNext;			//上一個及下一個action指標
//	void 	(*func)(struct action*);	//action所執行的function的指標
//	void* pYobi;							//備用的struct指標
//	void* pOther;						//其它用途struct指標
//	UCHAR 	prio;							//action處理時的優先順序
//	UCHAR 	dispPrio;						//秀圖時的優先順序	
//	int 	x, y;							//圖的座標
//	int		hitDispNo;						//是否命中目標編號
//	BOOL	deathFlag;						//此action是否死亡旗標	
//	int 	dx, dy;							//秀圖座標位移量
//	int 	dir;							//方向
//	int 	delta;  						//合成向量
//
//	char 	name[29];						//名字
//	char 	freeName[33];					//free name
//	int 	hp;
//#ifdef _PET_ITEM
//	int		iOldHp;
//#endif
//	int 	maxHp;
//	int 	mp;
//	int 	maxMp;
//	int 	level;
//	int 	status;
//	int 	itemNameColor;				
//	int		charNameColor;				
//
//	int		bmpNo;							//圖號
//	int		bmpNo_bak;							//備份圖號
//	int		atr;							//屬性
//	int		state;							//狀態
//	int		actNo;							//行動編號
//	int		damage;
//
//	int		gx, gy;							//在目前的地圖上的座標
//	int		nextGx, nextGy;					//下一個座標
//	int		bufGx[10], bufGy[10];			//從目前座標到下一個座標之間座標的buffer
//	short	bufCount;						//設定目前要走到那一個座標
//	short	walkFlag;				
//	float	mx, my;							//地圖座標
//	float	vx, vy;							
//
//	//屬性
//	short 	earth;							
//	short 	water;						
//	short 	fire;					
//	short 	wind;					
//	//rader使用
//	int		dirCnt;					
//	//gemini使用
//	int		spd;							//移動的速度(0~63)
//	int		crs;							//方向(0~31)(正上方為0,順時鐘方向)
//	int		h_mini;							
//	int		v_mini;						
//	//pattern使用
//	int		anim_chr_no;					//人物的編號(anim_tbl.h的編號)
//	int		anim_chr_no_bak;				//上一次的人物編號
//	int		anim_no;						//人物的動作編號
//	int		anim_no_bak;					//上一次的人物編號
//	int		anim_ang;						//動作的方向(0~7)(下0)
//	int		anim_ang_bak;					//上一次的方向
//	int		anim_cnt;						//第幾張frame
//	int		anim_frame_cnt;					//這張frame停留時間
//	int		anim_x;							//X座標(Sprbin+Adrnbin)
//	int		anim_y;							//Y座標(Sprbin+Adrnbin)
//	int		anim_hit;					
//	// shan add +1
//	char    fmname[33];			            // 家族名稱
//	// Robin 0728 ride Pet
//	int		onRide;
//	char	petName[16 + 1];
//	int		petLevel;
//	int		petHp;
//	int		petMaxHp;
//	int		petDamage;
//	int		petFall;
//#ifdef _MIND_ICON
//	unsigned int sMindIcon;
//#endif
//#ifdef _SHOWFAMILYBADGE_
//	unsigned int sFamilyIcon;
//#endif
//#ifdef FAMILY_MANOR_
//	unsigned int mFamilyIcon;
//#endif
//#ifdef _CHAR_MANOR_
//	unsigned int mManorIcon;
//#endif
//#ifdef _CHARTITLE_STR_
//	TITLE_STR TitleText;
//#endif
//#ifdef _CHARTITLE_
//	unsigned int TitleIcon;
//#endif
//#ifdef _NPC_EVENT_NOTICE
//	int noticeNo;
//#endif
//
//#ifdef _SKILL_ROAR  
//	int		petRoar;		//大吼(克年獸)
//#endif 
//#ifdef _SKILL_SELFEXPLODE //自爆
//	int		petSelfExplode;
//#endif 
//#ifdef _MAGIC_DEEPPOISION   //劇毒
//	int		petDeepPoision;
//#endif 
//
//#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
//	int		profession_class;
//#endif
//	//#ifdef _BATTLESKILL				// (不可開) Syu ADD 戰鬥技能介面
//	int		warrioreffect;
//	//#endif
//#ifdef _GM_IDENTIFY		// Rog ADD GM識別
//	char gm_name[33];
//#endif
//#ifdef _STREET_VENDOR
//	char szStreetVendorTitle[64];
//#endif
//#ifdef _NPC_PICTURE
//	int picture;
//	int picturetemp;
//#endif
//#ifdef _PETSKILL_RIDE
//	int saveride;
//#endif
//#ifdef _MOUSE_DBL_CLICK
//	int index;	// 禁斷!! Server中的charaindex
//#endif
//
//#ifdef _SFUMATO
//	int sfumato;		// 二次渲染圖層色彩
//#endif
//}ACTION;

typedef struct tagLSTIME
{
	int year = 0;
	int day = 0;
	int hour = 0;
}LSTIME;

typedef struct tagITEM_BUFFER
{
	int 	x = 0, y = 0;
	int 	defX = 0, defY = 0;
	int 	bmpNo = 0;
	int 	dispPrio = 0;
	BOOL	dragFlag = FALSE;
	BOOL	mixFlag = FALSE;
}ITEM_BUFFER;

typedef struct tagMAIL_HISTORY
{
	QString 	str[MAIL_MAX_HISTORY];
	QString 	dateStr[MAIL_MAX_HISTORY];
	int 	noReadFlag[MAIL_MAX_HISTORY] = { 0 };
	int 	petLevel[MAIL_MAX_HISTORY] = { 0 };
	QString 	petName[MAIL_MAX_HISTORY];
	int 	itemGraNo[MAIL_MAX_HISTORY] = { 0 };
	int 	newHistoryNo = 0;

	void clear()
	{
		for (int i = 0; i < MAIL_MAX_HISTORY; i++)
		{
			str[i] = "";
			dateStr[i] = "";
			noReadFlag[i] = 0;
			petLevel[i] = 0;
			petName[i] = "";
			itemGraNo[i] = 0;
		}
		newHistoryNo = 0;
	}
}MAIL_HISTORY;

typedef struct tagITEM
{
	int color = 0;
	int graNo = 0;
	int level = 0;
#ifdef _ITEM_PILENUMS
	int pile = 0;
#endif
#ifdef _ALCHEMIST //#ifdef _ITEMSET7_TXT
	QString alch;
#endif
	short useFlag = 0i16;
	short field = 0i16;
	short target = 0i16;
	short deadTargetFlag = 0i16;
	short sendFlag = 0i16;
	QString name = "";
	QString name2 = "";
	QString memo = "";
	QString damage = "";
#ifdef _PET_ITEM
	char type = '\0';
#endif
#ifdef _ITEM_JIGSAW
	QString jigsaw = "";
#endif
#ifdef _NPC_ITEMUP
	int itemup = 0;
#endif
#ifdef _ITEM_COUNTDOWN
	int counttime = 0;
#endif
#ifdef _MAGIC_ITEM_
	int 道具類型 = 0;
#endif

	//custom
	int maxPile = -1;
} ITEM;

typedef struct tagPC
{
	int graNo = 0;
	int faceGraNo = 0;
	int id = 0;
	int dir = 0;
	int hp = 0, maxHp = 0, hpPercent = 0;
	int mp = 0, maxMp = 0, mpPercent = 0;
	int vital = 0;
	int str = 0, tgh = 0, dex = 0;
	int exp = 0, maxExp = 0;
	int level = 0;
	int atk = 0, def = 0;
	int quick = 0, charm = 0, luck = 0;
	int earth = 0, water = 0, fire = 0, wind = 0;
	int gold = 0;
#ifdef _NEW_MANOR_LAW
	int fame = 0;
#endif
	int titleNo = 0;
	int dp = 0;
	QString name = "";
	QString freeName = "";
	short nameColor = 0i16;
#ifdef _ANGEL_SUMMON
	unsigned status = 0u;
#else
	unsigned short status = 0ui16;
#endif
	unsigned short etcFlag = 0ui16;
	short battlePetNo = 0i16;
	short selectPetNo[MAX_PET] = { 0i16, 0i16 ,0i16 ,0i16 ,0i16 };
	short mailPetNo = 0i16;
#ifdef _STANDBYPET
	short standbyPet = 0i16;
#endif
	int battleNo = 0;
	short sideNo = 0i16;
	short helpMode = 0i16;
	ITEM item[MAX_ITEM] = { 0 };
	//ACTION* ptAct;
	int pcNameColor = 0;
	short transmigration = 0i16;
	QString chusheng = "";
	QString familyName = "";
	int familyleader = 0;
	int channel = 0;
	int quickChannel = 0;
	int personal_bankgold = 0;
	int ridePetNo = 0;//寵物形像
	int learnride = 0;//學習騎乘
	unsigned int lowsride = 0u;
	QString ridePetName = "";
	int ridePetLevel = 0;
	int familySprite = 0;
	int baseGraNo = 0;
	ITEM itempool[MAX_ITEM] = {};
	int big4fm = 0;
	int trade_confirm = 0;         // 1 -> 初始值
	// 2 -> 慬我方按下確定鍵
	// 3 -> 僅對方按下確定鍵
	// 4 -> 雙方皆按下確定鍵

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	int profession_class = 0;
	int profession_level = 0;
	//	int profession_exp;
	int profession_skill_point = 0;
	QString profession_class_name = "";
#endif	
#ifdef _ALLDOMAN // (不可開) Syu ADD 排行榜NPC
	int herofloor = 0;
#endif

#ifdef _GM_IDENTIFY		// Rog ADD GM識別
	QString gm_name = "";
#endif

#ifdef _FRIENDCHANNEL  // ROG ADD 好友頻道
	QString chatRoomNum = "";
#endif
#ifdef _STREET_VENDOR
	int iOnStreetVendor = 0;		// 擺攤模式
#endif
	int skywalker = 0; // GM天行者
#ifdef _MOVE_SCREEN
	BOOL	bMoveScreenMode = FALSE;	// 移動熒幕模式
	BOOL	bCanUseMouse = FALSE;		// 是否可以使用滑鼠移動
	int		iDestX = 0;				// 目標點 X 座標
	int		iDestY = 0;				// 目標點 Y 座標
#endif
#ifdef _THEATER
	int		iTheaterMode = 0;		// 劇場模式
	int		iSceneryNumber = 0;		// 記錄劇院背景圖號
	//ACTION* pActNPC[5];		// 記錄劇場中臨時產生出來的NPC
#endif
#ifdef _NPC_DANCE
	int     iDanceMode = 0;			// 動一動模式
#endif
#ifdef _EVIL_KILL
	int     newfame = 0; // 討伐魔軍積分
	short   ftype = 0i16;
#endif

	int debugmode = 0;
#ifdef _SFUMATO
	int sfumato = 0;		// 二次渲染圖層色彩
#endif
#ifdef _NEW_ITEM_
	int 道具欄狀態 = 0;
#endif
#ifdef _CHARSIGNADY_NO_
	int 簽到標記 = 0;
#endif
#ifdef _MAGIC_ITEM_
	int 法寶道具狀態 = 0;
	int 道具光環效果 = 0;
#endif
	//custom
	int maxload = -1;
} PC;

constexpr int DEF_PAL = 0;
typedef struct tagPALETTE_STATE
{
	int palNo = 0;
	int time = 0;
	int flag = 0;
}PALETTE_STATE;

typedef struct tagPET
{
	int index = 0;						//位置
	int graNo = 0;						//圖號
	int hp = 0, maxHp = 0, hpPercent;					//血量
	int mp = 0, maxMp = 0, mpPercent;					//魔力
	int exp = 0, maxExp = 0;				//經驗值
	int level = 0;						//等級
	int atk = 0;						//攻擊力
	int def = 0;						//防禦力
	int quick = 0;						//速度
	int ai = 0;							//AI
	int earth = 0, water = 0, fire = 0, wind = 0;
	int maxSkill = 0;
	int trn = 0;						// 寵物轉生數
#ifdef _SHOW_FUSION
	int fusion = 0;						// low word: 寵蛋旗標, hi word: 物種編碼
#endif
#ifdef _ANGEL_SUMMON
	unsigned status = 0u;
#else
	unsigned short status = 0ui16;
#endif
	QString name = "";
	QString freeName = "";
	short useFlag = 0i16;
	short changeNameFlag = 0i16;
#ifdef _PET_ITEM
	ITEM item[MAX_PET_ITEM] = {};		// 寵物道具
#endif
#ifdef _PETCOM_
	int oldlevel = 0, oldhp = 0, oldatk = 0, oldquick = 0, olddef = 0;
#endif
#ifdef _RIDEPET_
	int rideflg;
#endif
#ifdef _PETBLESS_
	int blessflg = 0;
	int blesshp = 0;
	int blessatk = 0;
	int blessquick = 0;
	int blessdef = 0;
#endif

	//custom
	PetState state = PetState::kNoneState;
} PET;


typedef struct tagMAGIC
{
	short useFlag = 0i16;
	int mp = 0;
	short field = 0i16;
	short target = 0i16;
	short deadTargetFlag = 0i16;
	QString name = "";
	QString memo = "";
} MAGIC;


typedef struct tagPARTY
{
	short useFlag = 0i16;
	int id = 0;
	int level = 0;
	int maxHp = 0;
	int hp = 0;
	int hpPercent = 0;
	int mp = 0;
	QString name = "";
	//ACTION* ptAct;
} PARTY;


typedef struct tagADDRESS_BOOK
{
	short useFlag = 0i16;
	short onlineFlag = 0i16;
	int level = 0;
	short transmigration = 0i16;
	int dp = 0;
	int graNo = 0;
	QString name = "";
#ifdef _MAILSHOWPLANET				// (可開放) Syu ADD 顯示名片星球
	QString planetname = "";
#endif
} ADDRESS_BOOK;


typedef struct tagBATTLE_RESULT_CHR
{
	short petNo = 0i16;
	short levelUp = 0i16;
	int exp = 0;
} BATTLE_RESULT_CHR;

typedef struct tagBATTLE_RESULT_MSG
{
	short useFlag = 0i16;
	BATTLE_RESULT_CHR resChr[RESULT_CHR_EXP] = {};
	QString item[RESULT_ITEM_COUNT] = {};
} BATTLE_RESULT_MSG;


typedef struct tagPET_SKILL
{
	short useFlag = 0i16;
	short skillId = 0i16;
	short field = 0i16;
	short target = 0i16;
	QString name = "";
	QString memo = "";
} PET_SKILL;

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
typedef struct tagPROFESSION_SKILL
{
	short useFlag = 0i16;
	short skillId = 0i16;
	short target = 0i16;
	short kind = 0i16;
	QString name = "";
	QString memo = "";
	int icon = 0;
	int costmp = 0;
	int skill_level = 0;
#ifdef _PRO3_ADDSKILL
	int cooltime = 0;
#endif
} PROFESSION_SKILL;
#endif


typedef struct tagCHARLISTTABLE
{
	QString name = "";
	short level = 0i16;
	int login = 0;

	int faceGraNo = 0;
	int hp = 0;
	int str = 0;
	int def = 0;
	int agi = 0;
	int app = 0;
	int attr[4] = { 0,0,0,0 };
	int dp = 0;
} CHARLISTTABLE;
#ifdef _AIDENGLU_
typedef struct
{
	int 大區 = 0;
	int 隊模 = 0;
	int 小區 = 0;
	int 人物 = 0;
	int 是否自動喊話 = 0;
	int 是否自動遇敵 = 0;
	int 人物方向 = 0;
	char 登陸人物名稱[4][32] = { 0 };
	int 登陸延時時間 = 0;
}Landed;
#endif

constexpr int MAXMISSION = 300;
typedef struct tagJOBDAILY
{
	int JobId = 0;								// 任務編號
	QString explain = "";						// 任務說明
	QString state = "";							// 狀態
}JOBDAILY;

typedef struct dialog_s
{
	int windowtype = 0;
	int buttontype = 0;
	int seqno = 0;
	int objindex = 0;
	QString data = "";
	QStringList linedatas;
}dialog_t;


typedef struct battleobject_s
{
	int pos = -1;
	QString name = "";
	QString freename = "";
	int faceid = 0;
	int level = 0;
	int hp = 0;
	int maxHp = 0;
	int hpPercent = 0;
	int status = 0;
	int rideFlag = 0;
	QString rideName = 0;
	int rideLevel = 0;
	int rideHp = 0;
	int rideMaxHp = 0;
	int rideHpPercent = 0;
} battleobject_t;

typedef struct battledata_s
{
	int fieldAttr = 0;
	battleobject_t player = {};
	battleobject_t pet = {};
	QVector<battleobject_t> objects;
	QVector<battleobject_t> allies;
	QVector<battleobject_t> enemies;

} battledata_t;


typedef struct mapunit_s
{
	CHAR_TYPE type = CHAR_TYPENONE;
	int id = 0;
	int graNo = 0;
	int x = 0;
	int y = 0;
	QPoint p;
	int dir = 0;
	int level = 0;
	int nameColor = 0;
	QString name = "";
	QString freeName = "";
	bool walkable = false;
	int height = 0;
	int charNameColor = 0;
	QString fmname = "";
	QString petname = "";
	int petlevel = 0;
	int classNo = 0;
	QString item_name = "";
	int gold = 0;
	int profession_class = 0;
	int profession_level = 0;
	int profession_skill_point = 0;
	util::ObjectType objType = util::ObjectType::OBJ_UNKNOWN;
	bool isvisible = false;
	CHR_STATUS status = CHR_STATUS::CHR_STATUS_NONE;
} mapunit_t;

#pragma endregion

static const QHash<QString, BUTTON_TYPE> buttonMap = {
	{"OK", BUTTON_OK},
	{"CANCEL", BUTTON_CANCEL},
	{"YES", BUTTON_YES},
	{"NO", BUTTON_NO},
	{"CLOSE", BUTTON_CLOSE},
	{"PREVIOUS", BUTTON_PREVIOUS},
	{"NEXT", BUTTON_NEXT},

	{"確認", BUTTON_YES},
	{"確定", BUTTON_YES},
	{"取消", BUTTON_NO},
	{"關閉", BUTTON_CLOSE},
	{"上一頁", BUTTON_PREVIOUS},
	{"上一步", BUTTON_PREVIOUS},
	{"下一頁", BUTTON_NEXT},
	{"下一步", BUTTON_NEXT},


	{"确认", BUTTON_YES},
	{"确定", BUTTON_YES},
	{"取消", BUTTON_NO},
	{"关闭", BUTTON_CLOSE},
	{"上一页", BUTTON_PREVIOUS},
	{"下一页", BUTTON_NEXT},
};

class MapAnalyzer;
class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject* parent);

	virtual ~Server();

	Q_REQUIRED_RESULT inline bool isListening() const { return  !server_.isNull() && server_->isListening(); }

	Q_REQUIRED_RESULT inline bool hasClientExist() const { return  !server_.isNull() && !clientSockets_.isEmpty(); }

	bool start(QObject* parent);

	inline void requestInterruption() { isRequestInterrupted.store(true, std::memory_order_release); }

	Q_REQUIRED_RESULT inline unsigned short getPort() const { return port_; }

signals:
	void write(QTcpSocket* clientSocket, QByteArray ba, int size);

private slots:
	void onWrite(QTcpSocket* clientSocket, QByteArray ba, int size);
	void onNewConnection();
	void onClientReadyRead();


private:
	inline bool isInterruptionRequested() const { return isRequestInterrupted.load(std::memory_order_acquire); }

	int SaDispatchMessage(char* encoded);

	void handleData(QTcpSocket* clientSocket, QByteArray data);

public://actions
	Q_REQUIRED_RESULT int getWorldStatus();

	Q_REQUIRED_RESULT int getGameStatus();

	Q_REQUIRED_RESULT int getUnloginStatus();

	bool login(int s);

	void leftCLick(int x, int y);

	void unlockSecurityCode(const QString& code);

	void clearNetBuffer();

	void logOut();

	void logBack();

	void move(const QPoint& p, const QString& dir);

	void move(const QPoint& p);

	void announce(const QString& msg, int color = 4);

	void talk(const QString& text, int color = 0);

	void EO();

	void dropItem(int index);
	void dropItem(QVector<int> index);

	void useItem(int itemIndex, int target);

	void swapItem(int from, int to);

	void useMagic(int magicIndex, int target);

	void dropPet(int petIndex);

	void setSwitcher(int flg, bool enable);

	void setSwitcher(int flg);

	void press(BUTTON_TYPE select, int seqno = -1, int objindex = -1);
	void press(int row, int seqno = -1, int objindex = -1);

	void buy(int index, int amt, int seqno = -1, int objindex = -1);
	void sell(const QVector<int>& indexs, int seqno = -1, int objindex = -1);
	void sell(int index, int seqno = -1, int objindex = -1);
	void sell(const QString& name, const QString& memo = "", int seqno = -1, int objindex = -1);
	void learn(int skillIndex, int petIndex, int spot, int seqno = -1, int objindex = -1);

	void craft(util::CraftType type, const QStringList& ingres);

	void setPetState(int petIndex, PetState state);

	void updateDatasFromMemory();

	void asyncBattleWork(bool wait = true);

	void downloadMap();
	void downloadMap(int x, int y);

	void cleanChatHistory();

	bool findUnit(const QString& name, int type, mapunit_t* unit, const QString freename = "") const
	{
		QList<mapunit_t> units = mapUnitHash.values();
		for (const mapunit_t& it : units)
		{
			if (freename.isEmpty())
			{
				if ((it.name == name) && (it.objType == type))
				{
					*unit = it;
					return true;
				}
			}
			else
			{
				if ((it.name == name) && (it.freeName == freename) && (it.objType == type))
				{
					*unit = it;
					return true;
				}
			}
		}
		return false;
	}

	void setTeamState(bool join);

	void setPlayerFaceToPoint(const QPoint& pos);
	void setPlayerFaceDirection(int dir);

	QStringList getJoinableUnitList() const;
	bool getItemIndexsByName(const QString& name, const QString& memo, QVector<int>* pv) const;
	int getItemIndexByName(const QString& name, bool isExact = true, const QString& memo = "") const;
	int getPetSkillIndexByName(int& petIndex, const QString& name) const;
	int getMagicIndexByName(const QString& name, bool isExact = true) const;

	void clear();

	bool checkPlayerMp(int cmpvalue, int* target = nullptr, bool useequal = false);
	bool checkPlayerHp(int cmpvalue, int* target = nullptr, bool useequal = false);
	bool checkPetHp(int cmpvalue, int* target = nullptr, bool useequal = false);
	bool checkPartyHp(int cmpvalue, int* target);

	bool isPetSpotEmpty() const;
	bool checkJobDailyState(const QString& missionName, const QString& state);
private:
	void setBattleEnd();
	void refreshItemInfo(int index);
	void refreshItemInfo();
	void setWorldStatus(int w);
	void setGameStatus(int g);
	void setBattleFlag(bool enable);
	void sortItem();

	void getPlayerMaxCarryingCapacity();
	inline Q_REQUIRED_RESULT constexpr bool isItemStackable(int flg) { return ((flg >> 2) & 1); }
	QString getAreaString(int target);
	Q_REQUIRED_RESULT bool matchPetNameByIndex(int index, const QString& name);

	Q_REQUIRED_RESULT int findInjuriedAllie();

	void checkAutoDropMeat(const QStringList& items);
#pragma region BattleFunctions
	int playerDoBattleWork();
	void handlePlayerBattleLogics();
	int petDoBattleWork();
	void handlePetBattleLogics();


	bool isPlayerMpEnoughForMagic(int magicIndex) const;

	void sortBattleUnit(QVector<battleobject_t>& v) const;

	Q_REQUIRED_RESULT int getBattleSelectableEnemyTarget() const;

	Q_REQUIRED_RESULT int getBattleSelectableEnemyOneRowTarget(bool front) const;

	Q_REQUIRED_RESULT int getBattleSelectableAllieTarget() const;

	Q_REQUIRED_RESULT bool matchBattleEnemyByName(const QString& name, bool isExact, QVector<battleobject_t> src, QVector<battleobject_t>* v) const;
	Q_REQUIRED_RESULT bool matchBattleEnemyByLevel(int level, QVector<battleobject_t> src, QVector<battleobject_t>* v) const;
	Q_REQUIRED_RESULT bool matchBattleEnemyByMaxHp(int maxHp, QVector<battleobject_t> src, QVector<battleobject_t>* v) const;

	Q_REQUIRED_RESULT int getGetPetSkillIndexByName(int petIndex, const QString& name) const;

	bool fixPlayerTargetByMagicIndex(int magicIndex, int oldtarget, int* target) const;
	bool fixPlayerTargetByItemIndex(int itemIndex, int oldtarget, int* target) const;
	bool fixPetTargetBySkillIndex(int skillIndex, int oldtarget, int* target) const;

	void sendBattlePlayerAttckAct(int target);
	void sendBattlePlayerMagicAct(int magicIndex, int target);
	void sendBattlePlayerJobSkillAct(int skillIndex, int target);
	void sendBattlePlayerItemAct(int itemIndex, int target);
	void sendBattlePlayerDefenseAct();
	void sendBattlePlayerEscapeAct();
	void sendBattlePlayerCatchPetAct(int petIndex);
	void sendBattlePlayerSwitchPetAct(int petIndex);
	void sendBattlePlayerDoNothing();
	void sendBattlePetSkillAct(int skillIndex, int target);
	void sendBattlePetDoNothing();

#pragma endregion

#pragma region SAClientOriginal 
	//StoneAge Client Original Functions
	bool CheckMailNoReadFlag();

	void clearPartyParam();

	void swapItemLocal(int from, int to);

	void updateMapArea(void)
	{
		mapAreaX1 = nowPoint.x() + MAP_TILE_GRID_X1;
		mapAreaY1 = nowPoint.y() + MAP_TILE_GRID_Y1;
		mapAreaX2 = nowPoint.x() + MAP_TILE_GRID_X2;
		mapAreaY2 = nowPoint.y() + MAP_TILE_GRID_Y2;

		if (mapAreaX1 < 0)
			mapAreaX1 = 0;
		if (mapAreaY1 < 0)
			mapAreaY1 = 0;
		if (mapAreaX2 > nowFloorGxSize)
			mapAreaX2 = nowFloorGxSize;
		if (mapAreaY2 > nowFloorGySize)
			mapAreaY2 = nowFloorGySize;

		mapAreaWidth = mapAreaX2 - mapAreaX1;
		mapAreaHeight = mapAreaY2 - mapAreaY1;
	}

	void resetMap(void)
	{
		//nowGx = (int)(nowX / GRID_SIZE);
		//nowGy = (int)(nowY / GRID_SIZE);
		nowPoint = QPoint(nowX / GRID_SIZE, nowY / GRID_SIZE);
		nextGx = nowPoint.x();
		nextGy = nowPoint.y();
		nowX = (float)nowPoint.x() * GRID_SIZE;
		nowY = (float)nowPoint.y() * GRID_SIZE;
		oldGx = -1;
		oldGy = -1;
		oldNextGx = -1;
		oldNextGy = -1;
		mapAreaX1 = nowPoint.x() + MAP_TILE_GRID_X1;
		mapAreaY1 = nowPoint.y() + MAP_TILE_GRID_Y1;
		mapAreaX2 = nowPoint.x() + MAP_TILE_GRID_X2;
		mapAreaY2 = nowPoint.y() + MAP_TILE_GRID_Y2;

		if (mapAreaX1 < 0)
			mapAreaX1 = 0;
		if (mapAreaY1 < 0)
			mapAreaY1 = 0;
		if (mapAreaX2 > nowFloorGxSize)
			mapAreaX2 = nowFloorGxSize;
		if (mapAreaY2 > nowFloorGySize)
			mapAreaY2 = nowFloorGySize;

		mapAreaWidth = mapAreaX2 - mapAreaX1;
		mapAreaHeight = mapAreaY2 - mapAreaY1;
		nowVx = 0;
		nowVy = 0;
		nowSpdRate = 1;
		viewPointX = nowX;
		viewPointY = nowY;
		moveRouteCnt = 0;
		moveRouteCnt2 = 0;
		moveStackFlag = false;
		mouseCursorMode = MOUSE_CURSOR_MODE_NORMAL;
		mouseLeftPushTime = 0;
		beforeMouseLeftPushTime = 0;
		//	autoMapSeeFlag = FALSE;
	}

	void PaletteChange(int palNo, int time);

	void RealTimeToSATime(LSTIME* lstime);

	bool mapCheckSum(int floor, int x1, int y1, int x2, int y2, int tileSum, int partsSum, int eventSum);

	bool writeMap(int floor, int x1, int y1, int x2, int y2, unsigned short* tile, unsigned short* parts, unsigned short* event);

	void setEventMemory(const QPoint& pos, unsigned short ev);

	inline void redrawMap(void) { oldGx = -1; oldGy = -1; }

	inline void setPcWarpPoint(const QPoint& pos) { setWarpMap(pos); }

	inline void resetPc(void) { pc.status &= (~CHR_STATUS_LEADER); }

	inline void setMap(int floor, const QPoint& pos) { nowFloor = floor; setWarpMap(pos); }


	inline unsigned long long TimeGetTime(void)
	{
#ifdef _TIME_GET_TIME
		static __int64 time;
		QueryPerformanceCounter(&CurrentTick);
		return (unsigned int)(time = CurrentTick.QuadPart / tickCount.QuadPart);
		//return GetTickCount();
#else
		return GetTickCount64();
#endif
	}

	inline void setWarpMap(const QPoint& pos)
	{
		//nowGx = gx;
		//nowGy = gy;
		nowPoint = pos;
		nowX = (float)nowPoint.x() * GRID_SIZE;
		nowY = (float)nowPoint.y() * GRID_SIZE;
		nextGx = nowPoint.x();
		nextGy = nowPoint.y();
		nowVx = 0;
		nowVy = 0;
		nowSpdRate = 1;
		oldGx = -1;
		oldGy = -1;
		oldNextGx = -1;
		oldNextGy = -1;
		viewPointX = nowX;
		viewPointY = nowY;
		wnCloseFlag = 1;
#ifdef _AniCrossFrame	   // Syu ADD 動畫層遊過畫面生物
		extern void crossAniRelease();
		crossAniRelease();
#endif
#ifdef _SURFACE_ANIM       //ROG ADD 動態場景
		extern void ReleaseSpecAnim();
		ReleaseSpecAnim();
#endif
	}

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	//    #ifdef _GM_IDENTIFY		// Rog ADD GM識別
	//  void setPcParam(char *name, char *freeName, int level, char *petname, int petlevel, int nameColor, int walk, int height, int profession_class, int profession_level, int profession_exp, int profession_skill_point , char *gm_name);
	//    void setPcParam(char *name, char *freeName, int level, char *petname, int petlevel, int nameColor, int walk, int height, int profession_class, int profession_level, int profession_skill_point , char *gm_name)   ; 
	//	#else
	//	void setPcParam(char *name, char *freeName, int level, char *petname, int petlevel, int nameColor, int walk, int height, int profession_class, int profession_level, int profession_exp, int profession_skill_point);
#ifdef _ALLDOMAN // (不可開) Syu ADD 排行榜NPC
	void setPcParam(const QString& name, const QString& freeName, int level, const QString& petname, int petlevel, int nameColor, int walk, int height, int profession_class, int profession_level, int profession_skill_point, int herofloor);
#else
	void setPcParam(const QString& name, const QString& freeName, int level, const QString& petname, int petlevel, int nameColor, int walk, int height, int profession_class, int profession_level, int profession_skill_point);
#endif
	// 	#endif
#else
	void setPcParam(const QString& name, const QString& freeName, int level, const QString& petname, int petlevel, int nameColor, int walk, int height);
#endif

#pragma endregion

private://lssproto
#pragma region lssproto
	void lssproto_W_send(const QPoint& pos, char* direction);
	void lssproto_W2_send(const QPoint& pos, char* direction);
	//Cary say 戰鬥結束後的大地圖座標
	void lssproto_XYD_recv(const QPoint& pos, int dir);
	void lssproto_EV_send(int event, int seqno, const QPoint& pos, int dir);
	void lssproto_EV_recv(int seqno, int result);
	void lssproto_EN_send(const QPoint& pos);
	void lssproto_DU_send(const QPoint& pos);
	void lssproto_EN_recv(int result, int field);
	void lssproto_EO_send(int dummy);
	void lssproto_BU_send(int dummy);
	void lssproto_JB_send(const QPoint& pos);
	void lssproto_LB_send(const QPoint& pos);
	void lssproto_RS_recv(char* data);
	void lssproto_RD_recv(char* data);
	void lssproto_B_send(char* command);
	void lssproto_B_recv(char* command);
	void lssproto_SKD_send(int dir, int index);
	void lssproto_ID_send(const QPoint& pos, int haveitemindex, int toindex);
	void lssproto_PI_send(const QPoint& pos, int dir);
	void lssproto_DI_send(const QPoint& pos, int itemindex);
	void lssproto_DG_send(const QPoint& pos, int amount);
	void lssproto_DP_send(const QPoint& pos, int petindex);
	void lssproto_I_recv(char* data);
	void lssproto_MI_send(int fromindex, int toindex);
	void lssproto_SI_recv(int fromindex, int toindex);
	void lssproto_MSG_send(int index, char* message, int color);
	//Cary say 收到普通郵件或寵物郵件
	void lssproto_MSG_recv(int aindex, char* text, int color);
	void lssproto_PMSG_send(int index, int petindex, int itemindex, char* message, int color);
	void lssproto_PME_recv(int objindex, int graphicsno, const QPoint& pos, int dir, int flg, int no, char* cdata);
	void lssproto_AB_send(int fd);
	void lssproto_AB_recv(char* data);
	void lssproto_ABI_recv(int num, char* data);
	void lssproto_DAB_send(int index);
	void lssproto_AAB_send(const QPoint& pos);
	void lssproto_L_send(int dir);
	void lssproto_TK_send(const QPoint& pos, char* message, int color, int area);
	void lssproto_TK_recv(int index, char* message, int color);
	void lssproto_MC_recv(int fl, int x1, int y1, int x2, int y2, int tilesum, int objsum, int eventsum, char* data);
	void lssproto_M_send(int fl, int x1, int y1, int x2, int y2);
	void lssproto_M_recv(int fl, int x1, int y1, int x2, int y2, char* data);
	void lssproto_C_send(int index);
	void lssproto_C_recv(char* data);
	void lssproto_CA_recv(char* data);
	void lssproto_CD_recv(char* data);
	void lssproto_R_recv(char* data);
	void lssproto_S_send(char* category);
	void lssproto_S_recv(char* data);
	void lssproto_D_recv(int category, int dx, int dy, char* data);
	void lssproto_FS_send(int flg);
	void lssproto_FS_recv(int flg);
	void lssproto_HL_send(int flg);
	//戰鬥中是否要Help
	void lssproto_HL_recv(int flg);
	void lssproto_PR_send(const QPoint& pos, int request);
	void lssproto_PR_recv(int request, int result);
	void lssproto_KS_send(int petarray);
	//Cary say 指定那一只寵物出場戰鬥
	void lssproto_KS_recv(int petarray, int result);

#ifdef _STANDBYPET
	void lssproto_SPET_send(int standbypet);
	void lssproto_SPET_recv(int standbypet, int result);
#endif

	void lssproto_AC_send(const QPoint& pos, int actionno);
	void lssproto_MU_send(const QPoint& pos, int array, int toindex);
	void lssproto_PS_send(int havepetindex, int havepetskill, int toindex, char* data);
	//Cary say 寵物合成
	void lssproto_PS_recv(int result, int havepetindex, int havepetskill, int toindex);
	void lssproto_ST_send(int titleindex);
	void lssproto_DT_send(int titleindex);
	void lssproto_FT_send(char* data);
	//Cary say 取得可加的屬性點數
	void lssproto_SKUP_recv(int point);
	void lssproto_SKUP_send(int skillid);
	void lssproto_KN_send(int havepetindex, char* data);
	void lssproto_WN_recv(int windowtype, int buttontype, int seqno, int objindex, char* data);
	void lssproto_WN_send(const QPoint& pos, int seqno, int objindex, int select, char* data);
	void lssproto_EF_recv(int effect, int level, char* option);
	void lssproto_SE_recv(const QPoint& pos, int senumber, int sw);
	void lssproto_SP_send(const QPoint& pos, int dir);
#ifdef _NEW_CLIENT_LOGIN
	void lssproto_ClientLogin_send(char* cdkey, char* passwd, char* mac, int selectServerIndex, char* ip);
#else
	void lssproto_ClientLogin_send(char* cdkey, char* passwd);
#endif
	void lssproto_ClientLogin_recv(char* result);

	void lssproto_CreateNewChar_send(int dataplacenum, char* charname, int imgno, int faceimgno, int vital, int str, int tgh, int dex, int earth, int water, int fire, int wind, int hometown);
	void lssproto_CreateNewChar_recv(char* result, char* data);
	void lssproto_CharDelete_send(char* charname);
	void lssproto_CharDelete_recv(char* result, char* data);
	void lssproto_CharLogin_send(char* charname);
	void lssproto_CharLogin_recv(char* result, char* data);
	void lssproto_CharList_send(int fd);
	void lssproto_CharList_recv(char* result, char* data);
	void lssproto_CharLogout_send(int Flg);
	void lssproto_CharLogout_recv(char* result, char* data);
	void lssproto_ProcGet_send(int fd);
	void lssproto_ProcGet_recv(char* data);
	void lssproto_PlayerNumGet_send(int fd);
	void lssproto_PlayerNumGet_recv(int logincount, int player);
	void lssproto_Echo_send(char* test);
	void lssproto_Echo_recv(char* test);
	void lssproto_Shutdown_send(char* passwd, int min);
	void lssproto_NU_recv(int AddCount);
	void lssproto_TD_send(char* data);
	void lssproto_TD_recv(char* data);
	void lssproto_FM_send(char* data);
	void lssproto_FM_recv(char* data);
	//Cary say 取得轉生的特效
	void lssproto_WO_recv(int effect);
	void lssproto_PETST_send(int nPet, int sPet);// sPet  0:休息 1:等待 4:郵件
	void lssproto_BM_send(int iindex);             // _BLACK_MARKET
#ifdef _FIX_DEL_MAP
	void lssproto_DM_send(int fd);                         // WON ADD 玩家抽地圖送監獄
#endif
#ifdef _MIND_ICON 
	void lssproto_MA_send(const QPoint& pos, int nMind);
#endif
#ifdef _ITEM_CRACKER 
	void lssproto_IC_recv(const QPoint& pos);
#endif
#ifdef _MAGIC_NOCAST//沈默
	void lssproto_NC_recv(int flg);
#endif

#ifdef _CHECK_GAMESPEED
	void lssproto_CS_send(int fd);
	void lssproto_CS_recv(int deltimes);
	int lssproto_getdelaytimes();
	void lssproto_setdelaytimes(int delays);
#endif

#ifdef _TEAM_KICKPARTY
	void lssproto_KTEAM_send(int si);
#endif

#ifdef _PETS_SELECTCON
	void lssproto_PETST_recv(int petarray, int result);
#endif
#ifdef _CHATROOMPROTOCOL			// (不可開) Syu ADD 聊天室頻道
	void lssproto_CHATROOM_send(char* data);
	void lssproto_CHATROOM_recv(char* data);
#endif
#ifdef _NEWREQUESTPROTOCOL			// (不可開) Syu ADD 新增Protocol要求細項
	void lssproto_RESIST_send(char* data);
	void lssproto_RESIST_recv(char* data);
#endif

#ifdef _ALCHEPLUS
	void lssproto_ALCHEPLUS_send(char* data);
	void lssproto_ALCHEPLUS_recv(char* data);
#endif

#ifdef _OUTOFBATTLESKILL			// (不可開) Syu ADD 非戰鬥時技能Protocol
	void lssproto_BATTLESKILL_send(int SkillNum);
	void lssproto_BATTLESKILL_recv(char* data);
#endif
	void lssproto_CHAREFFECT_recv(char* data);

#ifdef _STREET_VENDOR
	void lssproto_STREET_VENDOR_send(char* data);	// 擺攤功能
	void lssproto_STREET_VENDOR_recv(char* data);	// 擺攤功能
#endif

#ifdef _JOBDAILY
	void lssproto_JOBDAILY_send(char* data);
	void lssproto_JOBDAILY_recv(char* data);
#endif

#ifdef _FAMILYBADGE_
	void lssproto_FamilyBadge_send(int fd);
	void lssproto_FamilyBadge_recv(char* data);
#endif

#ifdef _TEACHER_SYSTEM
	void lssproto_TEACHER_SYSTEM_send(char* data);	// 導師功能
	void lssproto_TEACHER_SYSTEM_recv(char* data);
#endif

#ifdef _ADD_STATUS_2
	void lssproto_S2_send(char* data);
	void lssproto_S2_recv(char* data);
#endif

#ifdef _ITEM_FIREWORK
	void lssproto_Firework_recv(int nCharaindex, int nType, int nActionNum);	// 煙火功能
#endif
#ifdef _PET_ITEM
	void lssproto_PetItemEquip_send(int nGx, int nGy, int nPetNo, int nItemNo, int nDestNO);	// 寵物裝備功能
#endif
#ifdef _THEATER
	void lssproto_TheaterData_recv(char* pData);
#endif
#ifdef _MOVE_SCREEN
	void lssproto_MoveScreen_recv(BOOL bMoveScreenMode, int iXY);	// client 移動熒幕
#endif
#ifdef _GET_HOSTNAME
	void lssproto_HostName_send(int fd);
#endif

#ifdef _NPC_MAGICCARD
	void lssproto_MagiccardAction_recv(char* data);	//魔法牌功能
	void lssproto_MagiccardDamage_recv(int position, int damage, int offsetx, int offsety);
#endif

#ifdef  _NPC_DANCE
	void lssproto_DancemanOption_recv(int option);	//動一動狀態
#endif

#ifdef _ANNOUNCEMENT_

	void lssproto_DENGON_recv(char* data, int colors, int nums);
#endif
#ifdef _HUNDRED_KILL
	void lssproto_hundredkill_recv(int flag);
#endif
#ifdef _PK2007
	void lssproto_pkList_send(int fd);
	void lssproto_pkList_recv(int count, char* data);
#endif
#ifdef _NEW_SYSTEM_MENU
	void lssproto_SaMenu_send(int index);
#endif


#ifdef _PETBLESS_
	void lssproto_petbless_send(int petpos, int type);
#endif
#ifdef _RIDEQUERY_
	void lssproto_RideQuery_send(int fd);
#endif
#ifdef _PET_SKINS
	void lssproto_PetSkins_recv(char* data);
#endif



#ifdef _CHARSIGNDAY_
	void lssproto_SignDay_send(int fd);
#endif
#pragma endregion

public:
	//custom
	bool IS_ONLINE_FLAG = false;
	bool IS_BATTLE_FLAG = false;

	bool IS_SCRIPT_FLAG = false;

	std::atomic_bool isPacketAutoClear = false;
	bool disconnectflag = false;

	bool enablePlayerWork = false;
	bool enablePetWork = false;
	bool enemyAllReady = false;

	bool petEscapeEnableTempFlag = false;
	int tempCatchPetTargetIndex = -1;

	bool IS_WAITFOR_JOBDAILY_FLAG = false;

	QFuture<void> ayncBattleCommand;
	std::atomic_bool ayncBattleCommandFlag = false;
	QElapsedTimer loginTimer;
	QElapsedTimer battleDurationTimer;
	QElapsedTimer normalDurationTimer;
	QElapsedTimer eottlTimer;
	bool isEOTTLSend = false;

	int battle_total_time = 0;
	int battle_totol = 0;

	//client original
	int  TalkMode = 0;						//0:一般 1:密語 2: 隊伍 3:家族 4:職業 

	unsigned int ProcNo = 0u;
	unsigned int SubProcNo = 0u;
	unsigned int MenuToggleFlag = 0u;

	short prSendFlag = 0i16;

	short mailLamp = 0i16;
	short mailLampDrawFlag = 0i16;

	short mapEffectRainLevel = 0i16;
	short mapEffectSnowLevel = 0i16;
	short mapEffectKamiFubukiLevel = 0i16;

	bool DuelFlag = false;
	bool NoHelpFlag = false;
	short vsLookFlag = 0i16;
	short eventEnemyFlag = 0i16;
	int BattleMapNo = 0;

	LSTIME SaTime = { 0 };
	unsigned long long serverTime = 0ULL;
	unsigned long long FirstTime = 0ULL;
	int SaTimeZoneNo = 0;

	short charDelStatus = 0;

	bool floorChangeFlag = false;
	bool warpEffectStart = false;
	bool warpEffectOk = false;
	short eventWarpSendId = 0i16;
	short eventWarpSendFlag = 0i16;
	short eventEnemySendId = 0i16;
	short eventEnemySendFlag = 0i16;

	short sendEnFlag = 0i16;
	short duelSendFlag = 0i16;
	short jbSendFlag = 0i16;
	short helpFlag = 0i16;

	bool BattleTurnReceiveFlag = false;
	int BattleMyNo = 0;
	int BattleBpFlag = 0;
	int BattleEscFlag = 0;
	int BattleMyMp = 0;
	int BattleAnimFlag = 0;
	int BattleSvTurnNo = 0;
	int BattleCliTurnNo = 0;
	int BattlePetStMenCnt = 0;

	bool BattlePetReceiveFlag = false;
	int BattlePetReceivePetNo = -1;
	int battlePetNoBak = -2;

	int BattleCmdReadPointer = 0;
	int BattleStatusReadPointer = 0;
	int BattleCmdWritePointer = 0;
	int BattleStatusWritePointer = 0;
	QString BattleCmdBak[BATTLE_BUF_SIZE] = {};
	QString  BattleStatus[BATTLE_COMMAND_SIZE] = {};
	QString  BattleStatusBak[BATTLE_BUF_SIZE] = {};

	int StatusUpPoint = 0;

	int mailHistoryWndSelectNo = 0;
	int mailHistoryWndPageNo = 0;
	bool ItemMixRecvFlag = FALSE;

	int transmigrationEffectFlag = 0;
	int transEffectPaletteStatus = 0;

	short clientLoginStatus = 0i16;
	time_t serverAliveLongTime = 0;
	struct tm serverAliveTime = { 0 };

	QString secretName = "";

	int palNo = 0;
	int palTime = 0;

	QString nowFloorName = "";
	bool mapEmptyFlag = false;
	int nowFloor = 0;
	int nowFloorGxSize = 0, nowFloorGySize = 0;
	int oldGx = -1, oldGy = -1;
	int mapAreaX1 = 0, mapAreaY1 = 0, mapAreaX2 = 0, mapAreaY2 = 0;
	//int nowGx = 0, nowGy = 0;
	QPoint nowPoint;
	int mapAreaWidth = 0, mapAreaHeight = 0;
	float nowX = (float)0 * GRID_SIZE;
	float nowY = (float)0 * GRID_SIZE;
	int nextGx = 0, nextGy = 0;
	float nowVx = 0.0f, nowVy = 0.0f, nowSpdRate = 1.0f;
	int oldNextGx = -1, oldNextGy = -1;
	float viewPointX = 0.0f;
	float viewPointY = 0.0f;
	short wnCloseFlag = 0i16;
	short moveRouteCnt = 0i16;
	short moveRouteCnt2 = 0i16;

	bool moveStackFlag = false;
	unsigned int mouseLeftPushTime = 0u;
	unsigned int beforeMouseLeftPushTime = 0u;

	short nowEncountPercentage = 0i16;
	short minEncountPercentage = 0i16;
	short maxEncountPercentage = 0i16;
	short nowEncountExtra = 0i16;
	int MapWmdFlagBak = 0;
	unsigned short event_[MAP_X_SIZE * MAP_Y_SIZE] = {};

	short mouseCursorMode = MOUSE_CURSOR_MODE_NORMAL;

	bool TimeZonePalChangeFlag = false;
	short drawTimeAnimeFlag = 0;

	bool NoCastFlag = false;
	bool StandbyPetSendFlag = false;
	bool warpEffectFlag = false;

	short newCharStatus = 0i16;
	short charListStatus = 0i16;

	short sTeacherSystemBtn = 0i16;

	//main datas
	QMutex swapItemMutex;
	PC pc = {};

	battledata_t battleData;

	PALETTE_STATE 	PalState = {};

	MAIL_HISTORY MailHistory[MAX_ADR_BOOK] = {};
	PET pet[MAX_PET] = {};

#ifdef _CHAR_PROFESSION			// WON ADD 人物職業
	PROFESSION_SKILL profession_skill[MAX_PROFESSION_SKILL];
#endif

	MAGIC magic[MAX_MAGIC] = {};

#ifdef MAX_AIRPLANENUM
	PARTY party[MAX_AIRPLANENUM];
#else
	PARTY party[MAX_PARTY] = {};
#endif
	short partyModeFlag = 0;


	CHARLISTTABLE chartable[MAXCHARACTER] = {};

	ADDRESS_BOOK addressBook[MAX_ADR_BOOK] = {};

	BATTLE_RESULT_MSG battleResultMsg = {};

	PET_SKILL petSkill[MAX_PET][MAX_SKILL] = {};

	dialog_t currentDialog = {};

	JOBDAILY jobdaily[MAXMISSION] = {};
	int JobdailyGetMax = 0;  //是否有接收到資料

	util::SafeHash<int, mapunit_t> mapUnitHash;
	util::SafeHash<QPoint, mapunit_t> npcUnitPointHash;

	QScopedPointer<MapAnalyzer> mapAnalyzer;

	util::SafeQueue<QString> chatQueue;

	util::AfkRecorder recorder[6] = {};
	QStringList enemyNameListCache;

	//用於緩存要發送到UI的數據
	util::SafeHash<int, QVariant> playerInfoColContents;
	util::SafeHash<int, QVariant> itemInfoRowContents;
	util::SafeHash<int, QVariant> equipInfoRowContents;
	QVariant topInfoContents;
	QVariant bottomInfoContents;
	QString timeLabelContents;
	QString labelPlayerAction;
	QString labelPetAction;
private:
	QFutureSynchronizer <void> sync_;
	QMutex mutex_;
	std::atomic_bool isRequestInterrupted = false;
	//int sockfd_ = 0;
	unsigned short port_ = 0;
	QScopedPointer<QTcpServer> server_;
	QList<QTcpSocket*> clientSockets_;

};
