#include "PartyArr.h"
#include "District.h"

PartyArr::PartyArr(int _size)
{
	
}
PartyArr::~PartyArr()
{
	for (int i = 0; i < size(); i++)
		delete arr[i];
}


const Party* PartyArr::getParty(string& name) const
{	
	for (int i = 0; i < size(); i++)
	{
		if (arr[i]->getName() == name)
			return arr[i];
	}
	return nullptr;
}
Party* PartyArr::addParty(string& name, int _partyNum, const Citizen* leader)
{
	Party* new_party = new Party(name, _partyNum, leader);
	push_back(new_party);
	return new_party;
}

void PartyArr::addDistrict(District* district_id)
{
	for (int i = 0; i < size(); i++)
	{
		arr[i]->addDistrict(district_id);
	}
}

void PartyArr::push_back(Party* value) {

	arr.push_back(value);
}

void PartyArr::party_sort()
{
	merge_sort(0, size() - 1);
}

void PartyArr::merge_sort(int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort( start, mid); // merge sort the elements between [start, mid]
		merge_sort( mid + 1, end); // merge sort the elements between [mid+1, end]
		Merge(start, end);   // merge both
	}
}

// template function to merge two sorted arrays
void PartyArr::Merge(int start, int end)
{
	int z, x, y, mid;

	vector<Party*> temp(end - start + 1);
	mid = (start + end) / 2;
	z = 0;
	x = start;
	y = mid + 1;
	while (x <= mid && y <= end) {
		if (*(arr[x]) < *(arr[y])) {
			temp[z] = arr[x];
			++x, ++z;
		}
		else {
			temp[z] = arr[y];
			++y, ++z;
		}
	}
	while (x <= mid) {
		temp[z] = arr[x];
		++x, ++z;
	}

	while (y <= end) {
		temp[z] = arr[y];
		++y, ++z;
	}
	for (int i = start; i <= end; ++i) {
		arr[i] = temp[i - start];
	}
}
void PartyArr::CheckIfRep(int repId)const { 
	const Citizen* rep;
	for (int i = 0; i < size(); i++)
	{
		rep = arr[i]->getRepsList().getRepbyId(repId);
		if (rep != nullptr)
		{
			throw Already_Exists(rep->getName() + " as a Representative");
		}
		if (arr[i]->getPresident().getID() == repId)
			throw Already_Exists(arr[i]->getPresident().getName()+" as the president");
	}
	
}

void PartyArr::addRep(int party_num, int district_num, const Citizen* newrep)
{
	CheckIfRep(newrep->getID());
	arr[party_num]->addReps(newrep, district_num);
}

ostream& operator<<(ostream& os, const PartyArr& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		os << *(arr[i]);
	}
	return os;
}

ostream& operator<<(ostream& os, PartyArr& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		os << *(arr[i]);
	}
	return os;
}


void PartyArr::save(ostream& out) const
{
	int lSize = size();
	out.write(rcastcc(&lSize), sizeof(lSize));
	for (int i = 0; i < lSize; i++)
	{
		arr[i]->save(out);
	}
	if (!out.good())
		throw Except("Saving Error");
}


void PartyArr::load(istream& in, DistrictArr& darr)
{
	Party* p;
	int lsize;
	in.read(rcastc(&lsize), sizeof(lsize));
	if (!in.good())
		throw Except("Loading Error");
	for (int i = 0; i < lsize; i++)
	{
		p = new Party(in, darr);
		push_back(p);
	}
}