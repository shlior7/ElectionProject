#include "RepsArr.h"
#include "DistrictArr.h"

RepsArr::RepsArr(int size)
{
}
RepsArr::~RepsArr()
{
	for (int i = 0; i < size(); i++)
		delete arr[i];
}

void RepsArr::addDistrict(const District* district_id)
{
	push_back(new Reps(0, district_id));
}

void RepsArr::addRep(const Citizen* rep, int district_id)
{
	if (district_id >= size())
		throw Not_Found("No District with this ID!");
	arr[district_id]->addCitizenToArr(rep);
}

void RepsArr::push_back(Reps* reps)
{
	arr.push_back(reps);
}

const Reps* RepsArr::getRepsOfDistrict(int district_num) const
{
	if (district_num >= size())
		throw Not_Found("District");
	return arr[district_num];
}

const Citizen* RepsArr::getRepbyId(int repId)const {
	const Citizen* cit = nullptr;
	for (int i=0;i< size() ||cit!= nullptr;i++)
	{
		Reps* r = arr[i];
		cit = (*r)[repId];
	}
	return cit;
}


bool RepsArr::save(ostream& out) const
{
	int lSize = size();
	out.write(rcastcc(&lSize), sizeof(lSize));
	for (int i = 0; i < lSize; i++)
	{
		(*arr[i]).save(out);
	}
	return out.good();
}

void RepsArr::load(istream& in, DistrictArr& darr)
{
	int lSize;
	in.read(rcastc(&lSize), sizeof(lSize));
	if (!in.good())
		throw Except("Loading Error");
	for (int i = 0; i < lSize; i++)
	{
		arr.push_back(new Reps(in, darr[i], darr));
	}
}

ostream& operator<<(ostream& os, const RepsArr& repArr) {
	for (int i = 0; i < repArr.size(); i++)
	{
		os << *(repArr[i]);
	}
	return os;
}