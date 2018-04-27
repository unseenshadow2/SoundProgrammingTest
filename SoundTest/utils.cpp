#include "utils.h"
#include <iostream>

using namespace std;

float percentBetween(float min, float max, float percent)
{
	if (percent <= 0) return min;
	else if (percent >= 1) return max;
	else
	{
		float toReturn = min + ((max - min) * percent);
		return toReturn;
	}
}