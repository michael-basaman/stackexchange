#include <iostream>

using namespace std;

class FirstOrderFilterData;

class FirstOrderFilter {
public:
	FirstOrderFilter(double tau);
	virtual ~FirstOrderFilter();

	FirstOrderFilter& operator=(const FirstOrderFilter& other);

	double Step(double in);
	void Reset(double in);
	void Print();
private:
	FirstOrderFilterData *data;
};

class FirstOrderFilterData {
public:
	FirstOrderFilterData(double tau);

	double Step(double in);
	void Reset(double in);
	void Print();
private:
	friend FirstOrderFilter& FirstOrderFilter::operator=(const FirstOrderFilter& other);

	const double tau;
	double in_prev;
	double in_current;
};

FirstOrderFilter::FirstOrderFilter(double tau) {
	data = new FirstOrderFilterData(tau);
}

FirstOrderFilter::~FirstOrderFilter() {
	delete data;
}

FirstOrderFilter& FirstOrderFilter::operator=(const FirstOrderFilter& other) {
	delete data;
	data = new FirstOrderFilterData(other.data->tau);

	return *this;
}

double FirstOrderFilter::Step(double in = 0) {
	return data->Step(in);
}

void FirstOrderFilter::Reset(double in = 0) {
	data->Reset(in);
}

void FirstOrderFilter::Print() {
	data->Print();
}

FirstOrderFilterData::FirstOrderFilterData(double tau) : tau(tau), in_prev(0.0), in_current(0.0) {
}

double FirstOrderFilterData::Step(double in) {
	in_prev = in_current;
	in_current += in;
	return in_current;
}

void FirstOrderFilterData::Reset(double in = 0) {
	in_prev = in;
	in_current = in;
}

void FirstOrderFilterData::Print() {
	cout << "tau: " << tau << ", in_current: " << in_current << ", in_prev: " << in_prev << endl;
}

int main() {
	FirstOrderFilter a(10.0);
	a.Print();
	a.Step(2.0);
	a.Print();
	a.Step(2.0);
	a.Print();
	a.Reset();
	a.Print();
	a.Step(3.0);
	a.Print();

	a = FirstOrderFilter(20.0);
	a.Print();
	a.Step(2.0);
	a.Print();
	a.Step(2.0);
	a.Print();

	return(0);
}
