#include "ToolFunc.h"
#define KEY "01FD43D2A54FCE60"
  
int ToolFunc::random(int start,int end)
{
	int result = 0;
	static int count = 0;
	struct cc_timeval now;
	if(start >= end)
		return 0;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	srand(now.tv_usec + count);
	count += 1;
	result = start + rand()%(end - start+1);
	return result;
}

float ToolFunc::getAngle(CCPoint startPos,CCPoint endPos)
{
	float distance = ccpDistance(endPos, startPos);
	float xDis = endPos.x - startPos.x;
	float yDis = endPos.y - startPos.y;
	float theta = atan(xDis / yDis);
	return (theta) * 57.29;
}

std::string ToolFunc::getFilePath(const char *pFileName)
{
	return CCFileUtils::sharedFileUtils()->getWritablePath()+pFileName;
}

bool ToolFunc::jsonEncryptFileSave(json_t* pJson,const char* pFileName)
{
	if(NULL == pJson)
		return false;
	//读取原文件
	string path = ToolFunc::getFilePath("temp");
	json_dump_file(pJson,path.c_str(),0);

	FILE *fp = fopen(path.c_str(), "r");
	if ( fp )
	{
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		char* buff = (char *)malloc(size+2);
		if (buff)
		{
			memset(buff,0,size+2);
			fread(buff,1,size,fp);
		}
		fclose(fp);

		////生成密文
		//std::string temp = KEY;
		//std::string file_str = buff;
		//temp.append(file_str);
		//MD5* m = new MD5(temp);
		//std::string signStr = m->toString();
		//delete m;

		//新文件
		string filePath = ToolFunc::getFilePath(pFileName);
		FILE *output = fopen(filePath.c_str(), "w");
		if (output)
		{
			//fwrite(signStr.c_str(), signStr.size(), 1, output);
			fwrite(buff,size,1,output);
			fclose(output);
		}

		if (buff)
		{
			free(buff);
			buff = NULL;
		}
	}

	return true;
}

json_t* ToolFunc::jsonEncryptFileRead(const char* pFileName)
{
	if(!pFileName)
		return NULL;
	string filePath = ToolFunc::getFilePath(pFileName);
	FILE *fp = fopen(filePath.c_str(), "r");
	if(!fp)
		return NULL;
	fseek(fp,0,SEEK_END);
	int file_len = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* buff1 = (char*)malloc(file_len+2);
	memset(buff1,0,file_len+2);
	fread(buff1,1,file_len,fp);
	fclose(fp);
	std::string tempPath = ToolFunc::getFilePath("temp");
	FILE *output = fopen(tempPath.c_str(), "w");
	fwrite(buff1,file_len,1,output);
	fclose(output);
	free(buff1);
	json_error_t error;
	json_t* pJson = json_load_file(tempPath.c_str(),0,&error);
	return pJson;
	//char* p1 = strchr(buff1,'{');
	//char* p2 = strchr(buff1,'[');
	//if(p1 && p2)
	//{
	//	if(p1 > p2)
	//		p1 = p2;
	//}
	//if(!p1 && p2)
	//{
	//	p1 = p2;
	//}
	//if(!p1 && !p2)
	//{
	//	free(buff1);
	//	return NULL;
	//}
	//int sign_len = p1-buff1;
	//int json_len = file_len - sign_len;
	////得到sign
	//char* signBuff = (char*)malloc(sign_len+2);
	//memset(signBuff,0,sign_len+2);
	//memcpy(signBuff,buff1,sign_len);
	////计算新的sign
	//char* buff2 = (char*)malloc(json_len+strlen(KEY)+2);
	//memset(buff2,0,json_len+strlen(KEY)+2);
	//strcpy(buff2,KEY);
	//memcpy(buff2+strlen(KEY),p1,json_len);
	//MD5* m = new MD5(buff2);
	//std::string newSign = m->toString();
	//delete m;
	////比较
	//if(0 == strcmp(signBuff,newSign.c_str()))
	//{
	//	std::string tempPath = ToolFunc::getFilePath("temp");
	//	FILE *output = fopen(tempPath.c_str(), "w");
	//	fwrite(p1,json_len,1,output);
	//	fclose(output);
	//	free(buff1);
	//	free(buff2);
	//	free(signBuff);
	//	json_error_t error;
	//	json_t* pJson = json_load_file(tempPath.c_str(),0,&error);
	//	return pJson;
	//}
	//else
	//{
	//	free(buff1);
	//	free(buff2);
	//	free(signBuff);
	//	return NULL;
	//}
}

json_t* ToolFunc::readPackageJson( const char* file ,bool doVerify)
{
	json_t* data_t = NULL;
	json_error_t error;
	unsigned long size = 0;
	unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(file,"rb",&size);

	if ( pBuffer )
	{
		data_t = json_loadb((const char*)pBuffer, size,0, &error);
		string data = json_dumps(data_t,0);
		MD5* md5 = new MD5(data);
		string jsonMd5 = md5->toString();
		//CCLOG("file:%s jsonMd5:%s",file,jsonMd5.c_str());
		delete(pBuffer);
		if ( doVerify )
		{
			json_t* verify_t = readPackageJson("",false);
			if ( verify_t )
			{
				json_t* key_t = json_object_get(verify_t,file);
				if ( key_t )
				{
					string key = json_string_value(key_t);
					CCLOG("verify key:%s",key.c_str());
					if ( jsonMd5 != key )//验证不通过将json置空
					{
						data_t = NULL;
					}
				}
				else
				{
					data_t = NULL;
					CCLOG("can not find key");
				}
			}
			else
			{
				data_t = NULL;
			}
		}
	}
	else
	{
		CCLOG("read file data failed");
	}
	return data_t;
}

bool ToolFunc::getNumFromString(const char *str,vector <int> &numVec)
{
	char c[10] = {0};
	int lenth = strlen(str);
	int j = 0;
	bool bEnd = false;//是否获取了一个数。

	for (int i = 0;i < lenth;i++)
	{
		//CCLOG("s::%c",str[i]);

		if (str[i] !='\0' && str[i] != ' ' && str[i] !=',')
		{
			if (bEnd)
			{//重新从数组的第一个位置开始存储
				j = 0;
				bEnd = false;
			}

			c[j] = str[i];
		}

		if(str[i] == ','|| i == lenth - 1)
		{
			int num = atoi(c);
			//CCLOG("num:%d",num);
			bEnd = true;
			memset(c,0,sizeof(c));
			numVec.push_back(num);
		}

		j++;
	 }

	return true;
}

long ToolFunc::getCurrentTime()
{
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct timeval now;
	gettimeofday(&now, NULL);
	timep = now.tv_sec;
#endif
	localtime(&timep);
	return timep;
}