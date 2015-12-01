#include "passserver.h"
//check
PassServer::PassServer(size_t size) : currentSize{ 0 }
{
	cop4530::HashTable<string, string> table(size);

}
PassServer::~PassServer()
{
	table.clear();
	currentSize = 0;
}
bool PassServer::load(const char *filename)
{
	return table.load(filename);
}

bool PassServer::addUser(std::pair<string,  string> & kv)
{
	if(table.insert(make_pair(kv.first, encrypt(kv.second))))
	{
		currentSize++;
		return true;
	}
	else
		return false;
}

bool PassServer::addUser(std::pair<string, string> && kv)
{
	
	if(table.insert(make_pair(kv.first, encrypt(kv.second))))
	{
		currentSize++;
	    return true;
	}
	else
		return false;
}

bool PassServer::removeUser(const string & k)
{
	if(table.remove(k))
	{
		currentSize--;
		return true;
	}
	else
		return false;
}

bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	if(!table.contains(p.first))
		return false;
	else if (!table.match(p))
		return false;
	else if(p.second == newpassword)
		return false;
	else
	{
		removeUser(p.first);
		table.insert(make_pair(p.first, encrypt(newpassword)));
		return true;
	}
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
	return table.write_to_file(filename);
}

//change
string PassServer::encrypt(const string & str)
{
	return str;
}