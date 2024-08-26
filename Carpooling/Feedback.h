#include<string>
#pragma once

#include<utility>
#include<vector>
using namespace std;
struct Comment {
public:
	string username;
	string comment;
	int score;
};

class Feedback
{
private:
	string owner_username;
	vector<Comment> feedbacks;
public:
	Feedback(string owner_username);
	Feedback(){}
	
	void setOwner_username(const string& username);
	string getOwner_username();
	void addFeedback(string username, string comment, int score);
	vector<Comment>& getFeedbacks();
	void updateFeedback(string username, string cmt, int score);
	float getAverageRate();
};

