#include "Rate.h"

void Rate::updateFeedbac(int userID, string cmt, int rate) {
	feedbacks.push_back({ userID, cmt, rate });
}

float Rate::getAverageRate() {
	int sum = 0;
	for (int i = 0; i < (int)feedbacks.size(); i++) sum += feedbacks[i].rate;
	return (float)sum / (int)feedbacks.size();
}