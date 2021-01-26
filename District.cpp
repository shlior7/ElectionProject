#include "District.h"

District::District() {
	name = "";
	reps = 0;
	id = 0;
	numOfpeople = 0;
	numOfVotes = 0;
	votingPercent = 0;
}

 District::District(istream& in)
{	
	int DisId, numOfp, numOfv, rep;
	float perc;
	getline(in, name, '\0');
	in.read(rcastc(&DisId), sizeof(DisId));
	in.read(rcastc(&numOfp), sizeof(numOfp));
	in.read(rcastc(&numOfv), sizeof(numOfv));
	in.read(rcastc(&rep), sizeof(rep));
	in.read(rcastc(&perc), sizeof(perc));
	if (!in.good())
		throw Except("Loading Error");
	id = DisId; numOfpeople = numOfp; numOfVotes = numOfv; reps = rep; votingPercent = perc;
	citizen_map.load(in, this);
}
District::District(string& _name, int _id, int _reps)
{
	id = _id;
	reps = _reps;
	name = _name;
	numOfpeople = 0;;
	votingPercent = 0;
	numOfVotes = 0;

}

District::~District() {
}

bool District::setName(const string& _name)
{
	name = _name;
	return true;
}

bool District::setRepresentatives(int _reps) {
	reps = _reps;
	return true;
}

bool District::setID(int _id) {
	id = _id;
	return true;
}

bool District::setNumOfPeople(int _numOfPeople) {
	numOfpeople = _numOfPeople;
	return true;
}

bool District::setnumOfVoters(int _numOfVoters) {
	numOfVotes = _numOfVoters;
	return true;
}


void District::addVote(int party_num)
{
	votes_arr.addVote(party_num);
	numOfVotes++;
}

const Citizen* District::getCitizen(int id) const
{
	return citizen_map.getCitizenByID(id);
	//return citizen_arr.getCitizenByID(id);

}
const int District::getVotesOfParty(int party_num) const
{
	return votes_arr.getVotes(party_num);
}

const int District::getRepsOfParty(int party_num) const
{
	return votes_arr.getReps(party_num);
}
float District::calcVotingPercent()
{
	votingPercent = ((float)numOfVotes / (float)(citizen_map.getSize()) * 100.f);
	return votingPercent;
}

void District::addCitizen(string& name, int id, int birthyear)
{
	citizen_map.addCitizen(name, id, birthyear, this);
}

void District::addParty(Party* partynum)
{
	votes_arr.addParty(partynum);
}

void District::addRep(int party_num)
{
	votes_arr.addRep(party_num);
}

void District::sort_votesArr(){
	votes_arr.sortPartyVotes();
}
void District::calculateWinner()
{
	int winner = 0;
	int winner_votes = 0;

	for (int i = 0; i < votes_arr.size(); i++)
	{
		if (winner_votes < votes_arr[i].votes) {
			winner_votes = votes_arr[i].votes;
			winner = i;
		}
		if (winner_votes == votes_arr[i].votes) {
			if (votes_arr[i].party->getId() < votes_arr[winner].party->getId())
				winner = i;
		}
	}
	votes_arr.setWinner(votes_arr[winner].party->getId());
}

ostream& operator<<(ostream& os, const District& dist)
{
	using namespace std;
	os << "***********************************" << endl <<
		"District Number: (" << dist.getId() <<
		") |||  District Name: (" << dist.getName() <<
		") |||  Number of representatives: (" << dist.getReps() <<
		") |||  District Type: (";
	dist.printType(os);
	os <<"***********************************" << endl;
	return os;
}

void District::printResults() {
	std::cout << votes_arr;
}


bool District::save(ostream& out) const
{
	out.write(name.c_str(), name.size());
	out.write("\0", sizeof(char));
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&numOfpeople), sizeof(numOfpeople));
	out.write(rcastcc(&numOfVotes), sizeof(numOfVotes));
	out.write(rcastcc(&reps), sizeof(reps));
	out.write(rcastcc(&votingPercent), sizeof(votingPercent));
	citizen_map.save(out);
	return out.good();
}

void District::loadVotes(istream& in,PartyArr& parr)
{
	votes_arr.load(in, parr);
}