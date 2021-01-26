#include"Party.h"
#include "DistrictArr.h"

Party::Party() {
	name = "";
	id = -1;
	RepsTotal = -1;
	votes_got = -1;
}

Party::Party(istream& in, DistrictArr& darr)
{
	int PresId;
	getline(in, name, '\0');
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&votes_got), sizeof(votes_got));
	in.read(rcastc(&RepsTotal), sizeof(RepsTotal));
	in.read(rcastc(&PresId), sizeof(PresId));
	if (!in.good())
		throw Except("Loading Error");
	president = darr.getCitizenFrom(PresId);
	if(president == nullptr)
		throw Except("Loading Error");
	repsByDis.load(in, darr);

}
Party::Party(string _partyName, int _partyId, const Citizen* _president) {
	name = _partyName;
	id = _partyId;
	president = _president;
	RepsTotal = 0;
	votes_got = 0;
	
}

void Party::addVotes(int add) {
	votes_got += add;
}


bool Party::setPartyName(string _name) {
	name = _name;
	return true;
}
bool Party::setRepresentativesTotal(int num) {
	RepsTotal = num;
	return true;
}
bool Party::setPartyId(int id)
{
	id = id;
	return true;
}
void Party::addVotesGot(int votes)
{
	votes_got += votes;
}
const Reps* Party::getRepsListByDis(int disNumber) const {
	return repsByDis[disNumber];
}

void Party::addReps(const Citizen* representative,int distictId) {
	repsByDis.addRep(representative, distictId);
}

void Party::addDistrict(const District* district_id)
{
	repsByDis.addDistrict(district_id);
}


void Party::addElectoralVotes()
{
	const District* d;
	int party_votes;
	votes_got = 0;
	RepsTotal = 0;
	for (int i = 0; i < repsByDis.size(); i++)
	{
		 d = repsByDis[i]->getDistrict();
		 addToRepsTotal(d->getRepsOfParty(id));
		 party_votes = d->getVotesOfParty(id);
		 addVotesGot(party_votes);
	}
	
}
int Party::addToRepsTotal(int won)
{
	RepsTotal += won;
	return OK;
}
ostream& operator<<(ostream& os,Party& party){
	os << "*************************************************" << endl;
	os << "Party Name:" << party.getName() << endl<<
	"Party Number: " << party.getId() << endl <<
	"Candidate for Head of State: " << party.getPresident().getName() << endl;
	if (party.getRepsList().size()) os << "List of Representatives: " << endl; 
	os << "**********************************" << endl
	<< party.getRepsList()
	<< "******************************" << endl << endl;
	return os;
}

ostream& operator<<(ostream& os, const Party& party) {
	os << "*************************************************" << endl;
	os << "Party Name:" << party.getName() << endl <<
		"Party Number: " << party.getId() << endl <<
		"Candidate for Head of State: " << party.getPresident().getName() << endl;
	if (party.getRepsList().size()) os << "List of Representatives: " << endl;
	os << "**********************************" << endl
		<< party.getRepsList()
		<< "******************************" << endl << endl;
	return os;
}
bool operator<(Party const& a, Party const& b)
{
	return a.RepsTotal > b.RepsTotal;
}
bool Party::save(ostream& out) const
{
	int presid = president->getID();
	out.write(name.c_str(), name.size());
	out.write("\0", sizeof(char));
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&votes_got), sizeof(votes_got));
	out.write(rcastcc(&RepsTotal), sizeof(RepsTotal));
	out.write(rcastcc(&presid), sizeof(int));
	repsByDis.save(out);
	return out.good();
}
