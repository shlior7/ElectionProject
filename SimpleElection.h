#pragma once 
#include "Election.h"
class Election;
class SimpleElection : public Election
{
public:
	SimpleElection(int reps = 0);
	SimpleElection(istream& in);
	SimpleElection(Date& date, int reps = 0);
	~SimpleElection()
	{
	}
	//add a Citizen in simple election (the disId will always be 1)
	virtual void addCitizen(string& name, int id, int birthyear,int districtid);

	//add a representative in simple election (the disId will always be 1)
	virtual void addRep(int party_num, int id, int districtId);

	//add a vote in simple election (the disId will always be 1)
	virtual void addVote(int id, int party_num);

};

