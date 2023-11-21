#include "Answer.h"
#include <vector>
#include <iostream>

using namespace std;

Answer::Answer(int N)
{
	sum = 0;
	pathAnswer.reserve(N);
}
//------------------------------------------------------------------------------------------------------------------------------------
void Answer::addAnswers(Answer ans)
{
	this->sum += ans.sum;
	this->pathAnswer.insert(this->pathAnswer.end(), ans.pathAnswer.begin(), ans.pathAnswer.end());
}
