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
	static void WStrToUTF8(std::string& dest, const wstring& src);//���ַ���ת����UTF_8��ʽ
	//static int getRow(CCPoint &point,const int size);//������ڶ�ά���е�����
	//static int getColumn(CCPoint &point,const int size);//������ڶ�ά���е�����
	static float getAngle(CCPoint startPos,CCPoint endPos);//���㼼�ܷ���Ƕ�
	static std::string getFilePath(const char *pFileName);
	static long getCurrentTime();
	//pJson����Ϊ��������
	static bool jsonEncryptFileSave(json_t* pJson,const char* pFileName);
	//��֤ǩ����������json
	static json_t* jsonEncryptFileRead(const char* pFileName);
	static json_t* readPackageJson( const char* file ,bool doVerify = false);
	static bool getNumFromString(const char *str,vector <int> &numVec);//���ַ�������ȡ����()
};