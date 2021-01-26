#include "PartyPtr.h"
PartyPtr::PartyPtr()
{
	ptr = nullptr;
}

PartyPtr::PartyPtr(Party* p)
{
	ptr = p;
}

PartyPtr::~PartyPtr()
{
	delete ptr;
}

void PartyPtr::setPtr(Party* _party)
{
	ptr = _party;
}

void PartyPtr::operator=(const PartyPtr& other)
{
	ptr = other.ptr;
}
