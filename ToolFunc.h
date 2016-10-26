#pragma once

#include "stdlib.h"
#include "ctime"
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "pomelo.h"
#include "MD5.h"

USING_NS_CC;
using namespace std;
namespace tools
{
	class ToolFunc
	{
	public:
		ToolFunc();
		~ToolFunc();
		static int random(int start, int end);
		static void WStrToUTF8(std::string& dest, const wstring& src);//把字符串转化成UTF_8格式
		//static int getRow(CCPoint &point,const int size);//计算点在二维表中的行数
		//static int getColumn(CCPoint &point,const int size);//计算点在二维表中的列数
		static float getAngle(CCPoint startPos, CCPoint endPos);//计算技能发射角度
		static std::string getFilePath(const char *pFileName);
		static long getCurrentTime();
		static bool getNumFromString(const char *str, vector <int> &numVec);//从字符串中提取数字()


		static bool verifyEmailAddress(const std::string& email);
		static bool verifyPhone(const std::string& phone);
		static bool verifyChinese(const std::string& word);
		static bool verifyNumber(const std::string& word);
		static bool verifyNumberAndEnglish(const std::string& word);
		static std::string base64urlencode(const std::string &str);
		static bool checkKeyWords(const string &filePath, const string &scr);
		static std::stack<BUBBLE_ITEM> parseChatMsg(const std::string &msg);
		static std::vector<std::string> splitString(const string& s, const string& delim);

		const static char* changeNumberFormat(string number);
	};
}
