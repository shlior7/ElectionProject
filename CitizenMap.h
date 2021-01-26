#include <limits>
#include <map>
#include "Citizen.h"
#pragma once

class CitizenMap {
private:
	map<int, Citizen*> citizen_map;
public:
	/*Init*/
	CitizenMap(){}
	~CitizenMap();
	CitizenMap& operator=(const CitizenMap& other) = delete;

	/*Getters*/
	map<int, Citizen*>& getMap() { return citizen_map; }
	int getSize() const{ return citizen_map.size(); }
	Citizen* getCitizenByID(const int id) const;

	/*Adders*/
	void addCitizen(string& _name, int _id, int _birth_year, District* district);
	
	/*Serialization*/
	void load(istream& in, District* dis);
	bool save(ostream& out) const;

	/*Operators*/
	friend ostream& operator<<(ostream& os, const CitizenMap& arr);
	Citizen* operator[](int id) { return getCitizenByID(id); }
	
};

/*********************************************************************************************************/

class ConstCitizenMap // for the const pointers in Reps
{
private:
	map<int, const Citizen*> citizen_map;
public:
	/*Init*/
	ConstCitizenMap() {}
	~ConstCitizenMap();
	ConstCitizenMap& operator=(const ConstCitizenMap& other) = delete;
	
	/*Getters*/
	const map<int, const Citizen*>& getMap() const { return citizen_map; }
	int getSize() const { return citizen_map.size(); }
	const Citizen* getCitizenByID(const int id) const;

	/*Adders*/
	void addCitizen(const Citizen* cit);

	/*Serialization*/
	bool save(ostream& out) const;

	/*Operators*/
	friend ostream& operator<<(ostream& os, const ConstCitizenMap& arr);
	const Citizen* operator[](int id) const{ return getCitizenByID(id); }
};