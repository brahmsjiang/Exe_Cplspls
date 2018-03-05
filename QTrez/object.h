/*************************************************************************
    > File Name: object.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月26日 星期一 12时21分21秒
 ************************************************************************/


#ifdef DB_OBJECT
#define DB_OBJECT
#include<iostream>
#include <map>
#define db_slots
#define db_signals protected
#define db_emit

class Object;
struct MetaObject
{
	const char *sig_names;
	const char *slts_names;
	static void active(Object *sender, int idx);
};

struct Connection
{
	Object *receiver;
	int method;
};

typedef std::multimap<int, Connection> ConnectionMap;
typedef std::multimap<int, Connection>::iterator ConnectionMapIt;

class Object
{
	static MetaObject meta;
	void metacall(int idx);
public:
	Object();
	virtual ~Object();
	static void db_connect(Object*, const char*, const char*);
	void testSignal();
db_signals:
	void sigl();
public db_slots:
	void slotl();
friend class MetaObject;
private:
	ConnectionMap connections;
};

#endif

