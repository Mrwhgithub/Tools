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

class ToolFunc
{
public:
	ToolFunc();
	~ToolFunc();
	static int random(int start,int end);
	static void WStrToUTF8(std::string& dest, const wstring& src);//把字符串转化成UTF_8格式
	//static int getRow(CCPoint &point,const int size);//计算点在二维表中的行数
	//static int getColumn(CCPoint &point,const int size);//计算点在二维表中的列数
	static float getAngle(CCPoint startPos,CCPoint endPos);//计算技能发射角度
	static std::string getFilePath(const char *pFileName);
	static long getCurrentTime();
	//pJson必须为匿名对象
	static bool jsonEncryptFileSave(json_t* pJson,const char* pFileName);
	//验证签名，并返回json
	static json_t* jsonEncryptFileRead(const char* pFileName);
	static json_t* readPackageJson( const char* file ,bool doVerify = false);
	static bool getNumFromString(const char *str,vector <int> &numVec);//从字符串中提取数字()
};