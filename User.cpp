#include "User.h"

User::User(string str)
{
	name = str;
}

User::~User()
{
}

string & User::GetName()
{
	return name;
}