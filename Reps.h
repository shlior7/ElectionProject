#pragma once
#include "CitizenMap.h"

class District;
class DistrictArr;
class Citizen;
//Representative array of a single district
class Reps
{
public:
	/*Init*/
	Reps(int _log_size = 0, const District* distritct_num = nullptr);
	Reps(istream& in, District* d, DistrictArr& darr);
	~Reps();
	
	/*Adders*/
	void addCitizenToArr(const Citizen* person);

	/*Getters*/
	int size() const;
	int getDistrictNum() const;
	const District* getDistrict()const;
	const string& getNameOfRep(int idx) const;
	int getIDRep(int idx) const;
	const ConstCitizenMap& getCitizenMap() const{ return citizen_map; }

	/*Serialization*/
	bool save(ostream& out) const;

	/*Prints only Chosen rep*/
	void printChosenReps(ostream& os,int reps_num) const;

	/*Operators*/
	const Citizen* operator[](int id) { return citizen_map[id]; }
	Reps& operator=(const Reps& origin) = delete;
	friend ostream& operator<<(ostream& os, Reps& repsArr);

private:
	const District* district;
	ConstCitizenMap citizen_map;
	int log_size;
};

