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
	void sendNewUser(string username, int grade);	// �����û����ͱ��γɼ�
	void ConnetIntnet(HttpClient * client, HttpResponse * response);	
	void ConnecUserName(HttpClient * client, HttpResponse * response);
	string BestGradInWorld();						// �������κ����ݣ���ȡȫ���������
	string GetTheUser(string username);				// ���������û�������ȡ��ǰ�û��ĳɼ�
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
