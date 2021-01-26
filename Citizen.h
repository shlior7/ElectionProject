#pragma once
#include "General.h"

class District;
	class Citizen
	{
	public:
		/**Init**/
		Citizen();//default init
		Citizen(istream& in, District* dis);//initialize from file
		Citizen(string& _name, int _id, int _yearOfBirth, District* _district);//initialize from citizen info
		~Citizen();
		Citizen(const Citizen& citizen);
		Citizen& operator=(const Citizen& citizen) = delete;

		/**Setters**/
		bool SetName(string name);
		bool SetId(int id);
		bool SetYearOfBirth(int yearOfBirth);
		bool SetDistrictNumber(int districtNumber);
		bool SetVotedFor(int vote);

		/**Getters**/
		int getID()const { return id; }
		const string getName()const {return name;}
		const int getYearOfBirth()const {return this->yearOfBirth;}
		const int getVotedFor()const {return votedfor;}
		const District* getDistrict()const { return district; }

		/**Operators**/
		friend ostream& operator<<(ostream& os, const Citizen& citizen);//prints const Citizen
		friend ostream& operator<<(ostream& os, Citizen& citizen);//prints Citizen

		/**Serialization**/
		bool save(ostream& out) const;//saves
	
	private:
		string name;
		int id;
		int yearOfBirth;
		const District* district;
		int votedfor;
	};
