#include "Feedback.h"

Feedback::Feedback(string owner_username) {
	this->owner_username = owner_username;
}
void Feedback::setOwner_username(const string& username) {
	this->owner_username = username;
}

string Feedback::getOwner_username() {
	return owner_username;
}
void Feedback::updateFeedback(string username, string cmt, int score) {
	feedbacks.push_back({ username, cmt, score });
}

void Feedback::addFeedback(string username, string comment, int score){
	feedbacks.push_back({ username, comment, score });
}
vector<Comment>& Feedback::getFeedbacks() {
	return feedbacks;
}
float Feedback::getAverageRate() {
	int sum = 0;
	for (int i = 0; i < (int)feedbacks.size(); i++) sum += feedbacks[i].score;
	return (float)sum / (int)feedbacks.size();
}