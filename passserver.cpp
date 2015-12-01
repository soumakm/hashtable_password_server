#include "passserver.h"

PassServer::PassServer(size_t size = 101)
{
	table = new HashTable(size);

}
PassServer::~PassServer()
{
	delete table;
}
bool PassServer::load(const char *filename)
{
	table.load(filename);
}

bool PassServer::addUser(std::pair<string,  string> & kv)
{
	table.insert(kv);
	currentSize++;
}

bool PassServer::addUser(std::pair<string, string> && kv)
{
	table.insert(kv);
	currentSize++;
}

bool PassServer::removeUser(const string & k)
{
	table.remove(k);
}
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{

}

bool PassServer::find(const string & user)
{
	return table.contains(user);
}

void PassServer::dump()
{
	table.dump();
}

size_t PassServer::size()
{
	return currentSize;
}

bool PassServer::write_to_file(const char *filename)
{
	table.write_to_file();
}

string ePassServer::ncrypt(const string & str);	