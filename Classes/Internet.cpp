#include "Internet.h"

Internet * Internet::internet = NULL;

Internet * Internet::getInstance()
{
	if (internet == NULL) {
		internet = new Internet();
	}
	return internet;
}



void Internet::sendNewUser(string username, int grade)
{
	// 获取HttpRequest对象
	auto request = new HttpRequest();
	// 设置请求连接
	request->setUrl("http://120.79.249.199:8080/Test/BestGrade");
	// 设置请求方式
	request->setRequestType(HttpRequest::Type::POST);
	// 设置发送数据
	char data[50];
	sprintf(data, "username=%s&grade=%d", username.c_str(), grade);
	CCLOG("send message is %s ", data);
	request->setRequestData(data, strlen(data));

	// 获取唯一的clien实例
	auto client = HttpClient::getInstance();
	// 设置超时时间
	client->setTimeoutForConnect(60);
	// 设置读取时间
	client->setTimeoutForRead(100);
	// 发送请求
	client->send(request);
	request->release();

}

string Internet::BestGradInWorld()
{
	auto request = new HttpRequest();
	// 设置请求连接
	request->setUrl("http://120.79.249.199:8080/Test/BestGrade");
	// 设置请求方式
	request->setRequestType(HttpRequest::Type::POST);
	// 设置发送数据
	char data[50];
	sprintf(data, "username=&grade=");
	CCLOG("send message is %s ", data);
	request->setRequestData(data, strlen(data));

	// 获取唯一的clien实例
	auto client = HttpClient::getInstance();
	// 设置超时时间
	client->setTimeoutForConnect(60);
	// 设置读取时间
	client->setTimeoutForRead(100);
	// 发送请求
	client->send(request);
	request->release();

	return BeatGrade;

}

string Internet::GetTheUser(string username)
{
	TheUserName = username;

	auto request = new HttpRequest();
	// 设置请求连接
	request->setUrl("http://120.79.249.199:8080/Test/BestGrade");
	// 设置请求方式
	request->setRequestType(HttpRequest::Type::POST);
	// 设置发送数据
	char data[50];
	sprintf(data, "username=%s&grade=", username.c_str());
	CCLOG("send message is %s ", data);
	request->setRequestData(data, strlen(data));

	request->setResponseCallback(CC_CALLBACK_2(Internet::ConnecUserName, this));

	// 获取唯一的clien实例
	auto client = HttpClient::getInstance();
	// 设置超时时间
	client->setTimeoutForConnect(60);
	// 设置读取时间
	client->setTimeoutForRead(100);
	// 发送请求
	client->send(request);

	request->release();

	CCLOG("in the internet, the TheUserName is %s", TheUserName.c_str());

	return TheUserName;
}

Internet::Internet()
{
}

Internet::~Internet()
{
	delete internet;
}

string Internet::getBestGrade()
{
	return BeatGrade;
}

string Internet::getTheUserName()
{
	return TheUserName;
}

void Internet::ConnetIntnet(HttpClient * client, HttpResponse * response)
{
	CCLOG("response code = %d", response->getResponseCode());
	if (response->isSucceed()) {
		std::vector<char> *data = response->getResponseData();
		std::stringstream oss;
		for (int i = 0; i < data->size(); i++) {
			oss << (*data)[i];
		}
		BeatGrade = oss.str().c_str();
		CCLOG("TheBestGrade response data is %s", oss.str().c_str());
	}
	else {
		BeatGrade = "error";
		CCLOG("error msg is : %s", response->getErrorBuffer());
	}
}

void Internet::ConnecUserName(HttpClient * client, HttpResponse * response)
{
	CCLOG("response code = %d", response->getResponseCode());
	if (response->isSucceed()) {
		std::vector<char> *data = response->getResponseData();
		std::stringstream oss;
		for (int i = 0; i < data->size(); i++) {
			oss << (*data)[i];
		}
		BeatGrade = oss.str().c_str();
		CCLOG("TheUserName response data is %s", oss.str().c_str());
	}
	else {
		BeatGrade = "error";
		CCLOG("error msg is : %s", response->getErrorBuffer());
	}
}
