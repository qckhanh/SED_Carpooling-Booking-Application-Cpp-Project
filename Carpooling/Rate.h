#pragma once
#include<string>
#include<utility>
#include<vector>
using namespace std;
struct Feedback {
public:
	int userID;
	string cmt;
	int rate;
};
class Rate
{
private:
	vector<Feedback> feedbacks;
public:
	Rate(){}
	void updateFeedbac(int userID, string cmt, int rate);
	float getAverageRate();
};

