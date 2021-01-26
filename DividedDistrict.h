#pragma once
#include "District.h"

class DividedDistrict : public District
{
	
public:
	/*Init*/
	DividedDistrict() :District() { type = Type::divided; }
	DividedDistrict(istream& in) :District(in) { type = Type::divided; }
	DividedDistrict(string& name, int id, int reps) :District( name,  id,  reps) { type = Type::divided; }
	virtual ~DividedDistrict(){}
	
	/*Calculate the reps*/
	virtual void calculateReps();
	
	/*Prints the type*/
	virtual void printType(ostream& os) const { os << "Divided)"<<endl; }

};