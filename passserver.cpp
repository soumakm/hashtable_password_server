#include "passserver.h"
//check
PassServer::PassServer(size_t size) : currentSize{ 0 }
{
	
	table = cop4530::HashTable<string, string>(size);

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
	pair<string, string> q = make_pair(p.first, encrypt(p.second));

	if(!table.contains(q.first))
		return false;
	else if (!table.match(q))
		return false;
	else if(q.second == newpassword)
		return false;
	else
	{
		removeUser(q.first);
		table.insert(q);
		currentSize++;
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
	char salt[] = "$1$########";
	char * password = new char [100];
   // string password_str;

	strcpy ( password, crypt(str.c_str(), salt));	
	string password_str(password);
	return password_str.substr(12);
}