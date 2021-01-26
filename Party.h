#pragma once	  
#include "RepsArr.h"
class District;
	class Party {
	private:
		string name;
		int id;
		const Citizen* president;
		RepsArr repsByDis;
		int votes_got;
		int RepsTotal;

	public:
		/*Init*/
		Party();
		Party(istream& in, DistrictArr& darr);
		Party(string name, int id,const Citizen* president);
		~Party(){}
		
		/*Setters*/
		bool setPartyName(string name);
		bool setPartyId(int id);
		bool setRepresentativesTotal(int representativesTotal);
		bool setChosenReps(int district_id,int reps);
		
		/*Serialization*/
		bool save(ostream& out) const;
		
		/*Getters*/
		const string& getName() const{return name;}
		const int getId() const{ return id; }
		const int getRepsTotal()const { return RepsTotal; }
		const int getVotes() const { return votes_got; }
		const Citizen& getPresident() const {return *president;}
		const RepsArr& getRepsList() const {return repsByDis;}
		const Reps* getRepsListByDis(int disNumber)const;

		/*Adders*/
		void addVotesGot(int votes);
		void addElectoralVotes();
		void addVotes(int add);
		void addReps(const Citizen* representative,int distictId);
		void addDistrict(const District* district_id);
		int addToRepsTotal(int won);

		/*Operators*/
		friend ostream& operator<<(ostream& os, Party& party);
		friend ostream& operator<<(ostream& os, const Party& party);
		friend bool operator<(Party const& a, Party const& b);
	};
	