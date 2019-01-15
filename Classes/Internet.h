#ifndef __INTERNET_SCENE_H__
#define __INTERNET_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

USING_NS_CC;
using namespace cocos2d::network;
using namespace std;


class Internet
{
public:
	static Internet* getInstance();
	void sendNewUser(string username, int grade);	// 发送用户名和本次成绩
	void ConnetIntnet(HttpClient * client, HttpResponse * response);	
	void ConnecUserName(HttpClient * client, HttpResponse * response);
	string BestGradInWorld();						// 不发送任何数据，获取全服最佳数据
	string GetTheUser(string username);				// 单个发送用户名，获取当前用户的成绩
	string BeatGrade;
	string TheUserName;
	Internet();
	~Internet();
	string getBestGrade();
	string getTheUserName();

private:
	static Internet* internet;

};

#endif // __HELLOWORLD_SCENE_H__
