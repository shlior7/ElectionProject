#include "SimpleElection.h"

SimpleElection::SimpleElection(int reps):Election()
{
	string name = "Simple";
	type = election_type::simple_election;
	addDistrict(name, reps,Type::divided);
}

SimpleElection::SimpleElection(istream& in):Election(in)
{
	type = election_type::simple_election;
}
SimpleElection::SimpleElection(Date& date, const int reps):Election(date)
{
	string name;
	type = election_type::simple_election;
	Election::addDistrict(name, reps, Type::divided);
}

void SimpleElection::addCitizen(string& name, int id, int birth_year,int district_Id)
{
	Election::addCitizen(name, id, birth_year, 0);
	 
}

void SimpleElection::addRep(int party_num, int id,int districtId)
{
	districtList[0]->setRepresentatives(districtList[0]->getReps() + 1);
	Election::addRep(party_num, id, 0);
	
}

void  SimpleElection::addVote(int id, int party_num)
{
	Election::addVote(id,0, party_num);
}