#include "Election.h" 

Election::Election()
{
	new_district_id = 0;
	new_party_id = 0;
}
Election::Election(Date& date) : date_Of_Election(date)
{
	new_district_id = 0;
	new_party_id = 0;
	type = election_type::regular_election;
}

Election::Election(istream& in)
{
	type = election_type::regular_election;
	date_Of_Election.load(in);
	districtList.load(in);
	partyList.load(in, districtList);
	districtList.loadVotes(in, partyList);
	in.read(rcastc(&new_district_id), sizeof(new_district_id));
	in.read(rcastc(&new_party_id), sizeof(new_party_id));
}


void Election::addDistrict(string& name,const int reps,Type type)
{
	if (districtList.getDistrict(name) != nullptr)
		throw (Already_Exists("District"));
	int district_id = new_district_id;

	partyList.addDistrict(districtList.addDistrict(name, district_id, reps, type));
	new_district_id++;
}

void Election::addParty(string& name, int candidate_id)
{
	int party_id = new_party_id;
	if (partyList.getParty(name) != nullptr)  throw Already_Exists("Party");

	const Citizen* president = districtList.getCitizenFrom(candidate_id);
	if (president == nullptr)
		throw Not_Found("Citizen");
	partyList.CheckIfRep(candidate_id);//checks if he is already a rep
	Party* new_party = partyList.addParty(name, party_id, president);
	districtList.addParty(new_party);
	for (int i = 0; i < districtList.size(); i++)
	{
		new_party->addDistrict(districtList[i]);
	}
	new_party_id++;
	throw Added("Party");
}

void Election::addCitizen(string& name, int id, int birthyear, int district_num)
{
	districtList.addCitizen(name, id, birthyear, district_num);
	throw Added("Citizen");
}

void Election::addRep(int party_num, int rep_id, int district_num)
{
	const Citizen* rep_ptr = districtList.getCitizenFrom(rep_id);
	if (rep_ptr == nullptr) 
		throw Not_Found("Citizen in District");
	partyList.addRep(party_num, district_num, rep_ptr);
	throw Added("Rep");
}

void Election::addVote(int id, int district_num,int party_num)	{
	Citizen* citizen = districtList[district_num]->getCitizenMap().getCitizenByID(id);
	if (citizen == nullptr)
		throw Not_Found("Citizen");
	if (citizen->getVotedFor() != -1)
		throw Already_Exists("Already Voted");
	if (date_Of_Election.getYear() - citizen->getYearOfBirth() < 18)
		throw Except("Too young to vote");
	citizen->SetVotedFor(party_num);

	districtList.addVote(party_num, district_num);
	throw Added("Vote");
}

bool Election::SetDate(int day, int month, int year) {
	date_Of_Election.setDay(day);
	date_Of_Election.setMonth(month);
	date_Of_Election.setYear(year);
	return true;
}

void Election::sumResults()
{
	if (!districtList.getTotalVotes())
		throw Except("No Votes in this Election yet");
	for (int i = 0; i < districtList.size(); i++){
		districtList[i]->calcVotingPercent();
		districtList[i]->calculateReps();
	}
	for (int j = 0; j < partyList.size(); j++)
	{
		partyList[j]->addElectoralVotes();
	}
}

void Election::checkReps()
{
	for (int i = 0; i < districtList.size(); i++)
	{
		for (int n = 0; n < districtList[i]->getVotesArr().size(); n++)
		{
			if (districtList[i]->getVotesArr()[n].reps_num > districtList[i]->getVotesArr()[n].party->getRepsList().getRepsOfDistrict(districtList[i]->getId())->size()) {
				cout << "Not enough representative in District: " << districtList[i]->getName() <<
					" for Party: " << districtList[i]->getVotesArr()[n].party->getName() <<
					"(id: " << districtList[i]->getVotesArr()[n].party->getId() << ") " << endl <<
					"Needed: " << districtList[i]->getVotesArr()[n].reps_num << " Currently has: " << districtList[i]->getVotesArr()[n].party->getRepsList().
					getRepsOfDistrict(districtList[i]->getId())->size() << endl;
				throw Except("Not Enough Reps in the Party");
				//we can't have more reps_num than the available reps in party
			}
		}
	}

}
///
ostream& operator<<(ostream& os, Election& election)
{
	election.checkReps();
	for (int i = 0; i < election.districtList.size(); i++)
	{
		os << "***********************************" << endl <<
			*(election.districtList[i]) <<
			"District winner: " << election.partyList[election.districtList[i]->getWinner()]->getPresident().getName() << endl <<
			"Total votes in district:" << election.districtList[i]->getNumOfVotes() << endl <<
			"Voting percentage in district: " << election.districtList[i]->getVotingPercentage() << "%" << endl <<
			"Elected representatives per party: " << endl;
		election.districtList[i]->sort_votesArr();
		for (int j = 0; j < election.districtList[i]->getVotesArr().size(); j++)
		{
			os << "**********************" << endl
				<< "Party Name: " << election.districtList[i]->getVotesArr()[j].party->getName() << endl <<
				"Number of representatives: " << election.districtList[i]->getVotesArr()[j].reps_num << endl <<
				"List of chosen representatives: " << endl;
			election.districtList[i]->getVotesArr()[j].party->getRepsList()[i]->printChosenReps(os, election.districtList[i]->getVotesArr()[j].reps_num);
			os << endl << "Number of votes: " << election.districtList[i]->getVotesArr()[j].votes << endl <<
				"Percentage from total votes: " <<
				election.districtList[i]->getVotesArr()[j].votedPrecent << "%" << endl << endl;
		}
	}
	election.partyList.party_sort();
	for (int i = 0; i < election.partyList.size(); i++)
	{
		os << "******************************" << endl;
		os << "Party Name: " << election.partyList[i]->getName() << endl <<
			"Party Leader: " << election.partyList[i]->getPresident().getName() << endl <<
			"Total number of chosen electors: " << election.partyList[i]->getRepsTotal() << endl <<
			"Total number of votes: " << election.partyList[i]->getVotes() << endl;
		os << "******************************" << endl;
	}

	return os;
}

void Election::save(ostream& out) const
{
	 date_Of_Election.save(out);
	 districtList.save(out);
	 partyList.save(out);
	 districtList.saveVotes(out);
	 out.write(rcastcc(&new_district_id), sizeof(new_district_id));
	 out.write(rcastcc(&new_party_id), sizeof(new_party_id));
	 if(!out.good())
		 throw (Except("Saving Error"));
}