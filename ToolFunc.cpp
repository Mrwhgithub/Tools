#include "ToolFunc.h"
#define KEY "01FD43D2A54FCE60"
#include "HNConverCode.h"
#include <regex>

namespace tools
{
	int ToolFunc::random(int start, int end)
	{
		int result = 0;
		static int count = 0;
		struct cc_timeval now;
		if (start >= end)
			return 0;
		CCTime::gettimeofdayCocos2d(&now, NULL);
		srand(now.tv_usec + count);
		count += 1;
		result = start + rand() % (end - start + 1);
		return result;
	}

	float ToolFunc::getAngle(CCPoint startPos, CCPoint endPos)
	{
		float distance = ccpDistance(endPos, startPos);
		float xDis = endPos.x - startPos.x;
		float yDis = endPos.y - startPos.y;
		float theta = atan(xDis / yDis);
		return (theta)* 57.29;
	}

	std::string ToolFunc::getFilePath(const char *pFileName)
	{
		return CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;
	}

	bool ToolFunc::getNumFromString(const char *str, vector <int> &numVec)
	{
		char c[10] = { 0 };
		int lenth = strlen(str);
		int j = 0;
		bool bEnd = false;//是否获取了一个数。

		for (int i = 0; i < lenth; i++)
		{
			//CCLOG("s::%c",str[i]);

			if (str[i] != '\0' && str[i] != ' ' && str[i] != ',')
			{
				if (bEnd)
				{//重新从数组的第一个位置开始存储
					j = 0;
					bEnd = false;
				}

				c[j] = str[i];
			}

			if (str[i] == ',' || i == lenth - 1)
			{
				int num = atoi(c);
				//CCLOG("num:%d",num);
				bEnd = true;
				memset(c, 0, sizeof(c));
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


	std::stack<BUBBLE_ITEM> Tools::parseChatMsg(const std::string &msg)
	{
		int length = msg.size();
		std::stack<char> tmp;
		std::stack<_BUBBLE_ITEM> stackMsg;
		while (1 < length--)
		{
			char c0 = msg[length];
			char c1 = msg[length - 1];
			if (c0 == ':' && c1 == '/')
			{
				length -= 1;

				//Ω‚Œˆ±Ì«È
				_BUBBLE_ITEM exp;
				if (tmp.size() > 0)
				{
					exp.t = BUBBLE_ITEM_TYPE::expression;
					for (size_t i = 0; i < 2; i++)
					{
						exp.name.push_back(tmp.top());
						tmp.pop();
					}
				}

				//Ω‚Œˆ◊÷∑˚¥Æ
				if (tmp.size() > 0)
				{
					_BUBBLE_ITEM str;
					str.t = BUBBLE_ITEM_TYPE::string;
					while (!tmp.empty())
					{
						str.name.push_back(tmp.top());
						tmp.pop();
					}

					if (!str.name.empty()) stackMsg.push(str);
				}
				if (!exp.name.empty()) stackMsg.push(exp);
			}
			else
			{
				tmp.push(c0);
			}
		}

		//¥¶¿Ìµ⁄0∏ˆ◊÷∑˚
		if (length == 0)
		{
			tmp.push(msg[length]);
		}

		//Ω‚Œˆ◊÷∑˚¥Æ
		if (tmp.size() > 0)
		{
			_BUBBLE_ITEM str;
			str.t = BUBBLE_ITEM_TYPE::string;
			while (!tmp.empty())
			{
				str.name.push_back(tmp.top());
				tmp.pop();
			}
			stackMsg.push(str);
		}

		return stackMsg;
	}

	bool Tools::verifyEmailAddress(const std::string& email)
	{
		std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
		return std::regex_match(email, pattern);
	}

	bool Tools::verifyPhone(const std::string& phone)
	{
		return true;
	}

	bool Tools::verifyChinese(const std::string& word)
	{
		std::regex pattern("^[\u4e00-\u9fa5]+$");
		return std::regex_match(word, pattern);
	}

	bool Tools::verifyNumber(const std::string& word)
	{
		std::regex pattern("^[0-9]*$");
		return std::regex_match(word, pattern);
	}

	bool Tools::verifyNumberAndEnglish(const std::string& word)
	{
		std::regex pattern("^[A-Za-z0-9]+$");
		return std::regex_match(word, pattern);
	}

	std::string Tools::base64urlencode(const std::string &str)
	{
		std::string encode = str;
		std::string::size_type pos(0);
		while ((pos = encode.find("+")) != std::string::npos)
		{
			encode.replace(pos, 1, "%2B");
		}
		pos = 0;
		while ((pos = encode.find("/")) != std::string::npos)
		{
			encode.replace(pos, 1, "%2F");
		}
		return encode;
	}

	const char* Tools::changeNumberFormat(string number)
	{
		if (number.compare("") == 0) return number.c_str();
		char str[100];
		auto num = stoll(number);
		if (num >= 100000000){
			float count = ((int)(num / 100000000.0 * 10)) / 10.0;
			sprintf(str, "%.1f亿", count);
		}
		else if (num >= 10000) {
			float count = ((int)(num / 10000.0 * 10)) / 10.0;
			sprintf(str, "%.1f万", count);
		}
		else{
			sprintf(str, "%lld", num);
		}
		return GBKToUtf8(str);
	}

	std::vector<std::string> Tools::splitString(const  std::string& s, const std::string& delim)
	{
		std::vector<std::string> elems;
		size_t pos = 0;
		size_t len = s.length();
		size_t delim_len = delim.length();
		if (delim_len == 0) return elems;
		while (pos < len)
		{
			int find_pos = s.find(delim, pos);
			if (find_pos < 0)
			{
				elems.push_back(s.substr(pos, len - pos));
				break;
			}
			elems.push_back(s.substr(pos, find_pos - pos));
			pos = find_pos + delim_len;
		}
		return elems;
	}

	bool checkKeyWords(const string &filePath, const string &scr){
		if (FileUtils::getInstance()->isFileExist(filePath))
		{
			string path = FileUtils::getInstance()->getStringFromFile(filePath);
			auto content = HN::Tools::splitString(path, ",");
			for (string str : content) {
				if (str.find(scr) >= 0 || scr.find(str) >= 0){
					return true;
				}
			}
		}
		return false;
	}
}