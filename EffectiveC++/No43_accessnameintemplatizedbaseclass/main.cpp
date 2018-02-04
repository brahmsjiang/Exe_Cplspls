/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月29日 星期一 21时52分47秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<typeinfo>

using namespace std;

class CompanyA{
public:
	void sendClrText(const std::string& str)
	{
		cout<<"compA::sendClrText==>"<<str.data()<<endl;
	}
	void sendEncrypted(const std::string& str)
	{
		cout<<"compA::sendEncrypted==>"<<str.data()<<endl;
	}

};

class CompanyB{
public:
	void sendClrText(const std::string& str)
	{
		cout<<"compB::sendClrText==>"<<str.data()<<endl;
	}
	void sendEncrypted(const std::string& str)
	{
		cout<<"compB::sendEncrypted==>"<<str.data()<<endl;
	}
};

class CompanyZ{
public:
	void sendEncrypted(const std::string& str)
	{
		cout<<"compZ::sendEncrypted==>"<<str.data()<<endl;
	}
};


class MsgInfo{
public:
	MsgInfo(const std::string& msg)
		:rmsg(msg)
	{}
	enum MSGLEVEL{	//declaration must add ";" at end, defination cannt add ";"
		NON = 0,
		ENC,
	};
	std::string createMsg(MSGLEVEL lev) const
	{
		std::string tmp;
		switch(lev)
		{
			case NON:
				tmp = rmsg;
				break;
			case ENC:
				tmp = "******"+rmsg+"******";
				break;
			default:
				break;
		}
		return tmp;
	}
	std::string rmsg;
};

template<typename Company>
class MsgSender
{
public:
	void sendClear(const MsgInfo& info){
		std::string msg;
		msg = info.createMsg(MsgInfo::NON);
		Company c;
		c.sendClrText(msg);
	}
	void sendSecret(const MsgInfo& info){
		std::string msg;
		msg = info.createMsg(MsgInfo::ENC);
		Company c;
		c.sendEncrypted(msg);
	}

};

template<>	//total template specialization
class MsgSender<CompanyZ>
{
public:
#if 0
	void sendClear(const MsgInfo& info){
		cout<<"CompanyZ don't suppprt sendclr!"<<endl;
	}
#endif
	void sendSecret(const MsgInfo& info){
		std::string msg;
		msg = info.createMsg(MsgInfo::ENC);
		CompanyZ c;
		c.sendEncrypted(msg);
	}
};

template<typename Company>
class LoggingMsgSender:public MsgSender<Company>
{
public:
	using MsgSender<Company>::sendClear; 	//2nd. tell compiler to find in base class scope
	void sendClearMsg(const MsgInfo& info){
		cout<<"logging start"<<endl;
		//sendClear(info);	//err,compiler doesnt know MsgSender<company> whether has thisfunc or not
		//this->sendClear(info);	//1st, assume sendclear will be inheritted
		sendClear(info);	//2nd
		//MsgSender<Company>::sendClear(info);//3rd,not good,if func is virtual,is will close virtual function
		cout<<"logging end"<<endl;
	}
	void sendSecretMsg(const MsgInfo& info){
		cout<<"logging start"<<endl;
		this->sendSecret(info);
		cout<<"logging end"<<endl;
	}

};

int main()
{
	MsgSender<CompanyA> senda;
	MsgInfo ma("PPPP");
	senda.sendClear(ma);
	senda.sendSecret(ma);

	MsgSender<CompanyB> sendb;
	MsgInfo mb("QQQQ");
	sendb.sendClear(mb);
	sendb.sendSecret(mb);

	MsgSender<CompanyZ> sendz;
	MsgInfo mz("RRRR");
	//sendz.sendClear(mz);	//err
	sendz.sendSecret(mz);	//ok
	
	LoggingMsgSender<CompanyA> logsenda;
	MsgInfo lma("lma");
	logsenda.sendClearMsg(lma);

	LoggingMsgSender<CompanyB> logsendz;//2nd will err, using...
	MsgInfo lmz("lmz");
	//logsendz.sendClearMsg(lmz);	//err whichever method is used
	logsendz.sendSecret(lmz);

	return 0;
}





