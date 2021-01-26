#pragma once
#include "Party.h"
class Party;
class PartyPtr
{
public:
	PartyPtr();
	PartyPtr(Party* p);
	~PartyPtr();
	void setPtr(Party* new_ptr);
	Party* getPtr() {return ptr;}
	Party* operator->() { return ptr; }
	Party* operator->() const{ return ptr; }
	Party& operator*() { return *ptr; }
	Party& operator*() const{ return *ptr; }
	void operator=(const PartyPtr& other);
private:
	Party* ptr;
};

