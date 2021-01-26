#pragma once
#include "District.h"

class UnifiedDistrict : public District
{
public:
	/*Init*/
	UnifiedDistrict(): District() { type = Type::unified; }
	UnifiedDistrict(istream& in) : District(in) { type = Type::unified; }
	UnifiedDistrict(string& _name, int _id, int _reps) :District(_name, _id, _reps){ type = Type::unified; }
	virtual ~UnifiedDistrict() {}
	/*Calculate the reps*/
	virtual void calculateReps();
	/*Prints the type*/
	virtual void printType(ostream& os) const { os << "Unified)"<<endl; }

};