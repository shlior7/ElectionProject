#pragma once
#include "CitizenMap.h"
#include "DistrictVotes.h"

enum class Type { divided = 1, unified = 2 };
class PartyArr;
class DistrictPtr;
class District {
protected:
	string name;
	int id;
	int numOfpeople;
	int numOfVotes;
	int reps;
	float votingPercent;
	Type type;
	CitizenMap citizen_map;
	DistrictVotesArr votes_arr;// an array orginzed by party
public:
	/*Init*/
	District();
	District(istream& in);
	District(string& name, int id,int reps);
	~District();
	District& operator=(const District& district) = delete;

	virtual bool save(ostream& out) const;

	void loadVotes(istream& in, PartyArr& parr);

	//***Getters***
	const string& getName() const {return name;}
	virtual const Type getType() const { return type; }
	const int getId() const { return id; }
	const int getReps() const {return reps;}
	const int getNumOfPeople() const {return numOfpeople;}
	const int getNumOfVotes() const {return numOfVotes;}
	const float getVotingPercentage()const {return votingPercent; }
	const DistrictVotesArr& getVotesArr() const { return votes_arr; }
	const CitizenMap& getCitizenMap() const { return citizen_map; }
	const int getWinner()const{ return votes_arr.getWinner(); }
	const Citizen* getCitizen(int id) const;
	const int getVotesOfParty(int party_num)const;
	const int getRepsOfParty(int party_num) const;

	//***Setters***
	bool setName(const string& name);
	bool setRepresentatives(int representatives);
	bool setID(int id);
	bool setNumOfPeople(int numOfPeople);
	bool setnumOfVoters(int numOfVoters);
	//void setVotedPrecent();

	//***Adders***
	void addCitizen(string& name, int id, int birthyear);
	void addParty(Party* partynum);
	void addRep(int party_num);
	void sort_votesArr();
	void addVote(int party_num);

	/*Calculations: */
	float calcVotingPercent();
	virtual void calculateReps(){}
	void calculateWinner();

	/*Operators: */
	friend ostream& operator<<(ostream& os, const District& dist);
	void printResults();
	virtual void printType(ostream& os) const{}
};
