#include "../headerFile/Feedback.h"

Feedback::Feedback(string owner_username) {
	this->owner_username = owner_username;
	this->avgRate = 0.0;
}
Feedback::Feedback() {
	this->avgRate = 0.0;
}
void Feedback::setOwner_username(const string& username) {
	this->owner_username = username;
}

string Feedback::getOwner_username() {
	return owner_username;
}
void Feedback::addFeedback(string username, string comment, int score){
	feedbacks.push_back({ username, comment, score });
	updateAverageRate();
}
vector<Comment>& Feedback::getComments() {
	return feedbacks;
}
void Feedback::updateAverageRate() {
	double sum = 0.0;
	for (int i = 0; i < (int)feedbacks.size(); i++) sum += (double)feedbacks[i].score;
	this->avgRate = (float)sum / feedbacks.size();
}

void Feedback::setAvgRate(float avgRate) {
	this->avgRate = avgRate;
}

float Feedback::getAvgRate() {
	return avgRate;
}