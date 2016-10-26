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
		static void WStrToUTF8(std::string& dest, const wstring& src);//���ַ���ת����UTF_8��ʽ
		//static int getRow(CCPoint &point,const int size);//������ڶ�ά���е�����
		//static int getColumn(CCPoint &point,const int size);//������ڶ�ά���е�����
		static float getAngle(CCPoint startPos, CCPoint endPos);//���㼼�ܷ���Ƕ�
		static std::string getFilePath(const char *pFileName);
		static long getCurrentTime();
		static bool getNumFromString(const char *str, vector <int> &numVec);//���ַ�������ȡ����()


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
