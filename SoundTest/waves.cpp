#include <cmath>
#include "waves.h"
#include "defines.h"
#include "globals.h"
#include "utils.h"

#if defined(WAVE_DEBUG)
#include <iostream>
using namespace std;
#endif

/*
* Frequency/Pitch/Period/Width (Hertz or waves per second)
* -- The number of times a wave repeats in one second
* -- sin(a * x) -- Alters the period of the wave
*
* Volume/Amplitude/Height
* -- The distance between the center line and the top/bottom of the wave
* -- sin(x) + a -- Shifts center line up/down
* -- a * sin(x) -- Alter distance of extremes from the center line
*
* X Offset
* -- The deviation on the x axis from a standard sin wave
* -- sin(x + a) -- Shift the starting point on the x axis
*/

void SinWave(DWORD freq, float min, float max, float* buffer, size_t size)
{
	// All of our math
	double a = (max - min) / 2;
	double d = min + a;

	double phase = (double)freq / SAMPLE_RATE;
	double x;

#ifdef WAVE_DEBUG
	cout << "A: " << a << "\n"
		<< "C: " << c << "\n"
		<< "D: " << d << "\n"
		<< "Phase: " << phase << endl;
#endif

	// Write data to the buffer
	for (int i = 0; i < size; i++)
	{
		x = phase * i * TWO_PI;
		buffer[i] = (a * sin(x) + d);

#ifdef WAVE_DEBUG
		cout << "x[" << i << "]: " << x << "\n" <<
			"sin(x): " << sin(x) << endl;
#endif
	}
}

void PulseWave(DWORD freq, float min, float max, int pulsePercent, float* buffer, size_t size)
{
	int pulseWidth = SAMPLE_RATE / freq; // How many samples a single pulse takes
	int activeWidth = (pulseWidth * pulsePercent) / 100; // How many samples the pulse remains active
	int inactiveWidth = pulseWidth - activeWidth; // How many samples the pulse remains inactive
	int cycleStop; // When does a stage of the pulse stop

#ifdef WAVE_DEBUG
	cout << "Pulse Width: " << pulseWidth << "\n"
		<< "Active Width: " << activeWidth << "\n"
		<< "Inactive Width: " << inactiveWidth << endl;
#endif

	// Build the data
	for (int i = 0; i < size; i+=pulseWidth)
	{
		// Active cycle
		cycleStop = i + activeWidth;
		for (int j = i; (j < size) && (j < cycleStop); j++)
		{
			buffer[j] = max;
		}

		// Inactive cycle
		cycleStop = i + pulseWidth;
		for (int j = i + activeWidth; (j < size) && (j < cycleStop); j++)
		{
			buffer[j] = min;
		}
	}

#ifdef WAVE_DEBUG
	for (int i = 0; i < size; i++)
	{
		cout << "[" << i << ", " << buffer[i] << "], ";
		if (((i + 1) % 5) == 0) cout << "\n";
	}

	cout << endl;
#endif
}

void TriangleWave(DWORD freq, float min, float max, float* buffer, size_t size)
{
	int phase = SAMPLE_RATE / freq; // The length of a single "pulse"
	int crest = phase / 2;
	bool isGoingUp = true;

#ifdef WAVE_DEBUG
	cout << "Phase: " << phase <<
		"\nCrest: " << crest << endl;
#endif

	for (int i = 0, j = 0; i < size; i++)
	{
		buffer[i] = percentBetween(min, max, (float)j / crest);

		if (isGoingUp)
		{
			if (j < crest) ++j;
			else
			{
				isGoingUp = false;
				--j;
			}
		}
		else
		{
			if (j > 0) --j;
			else
			{
				isGoingUp = true;
				++j;
			}
		}
	}

#ifdef WAVE_DEBUG
	for (int i = 0; i < size; i++)
	{
		cout << "[" << i << ", " << buffer[i] << "], ";
		if (((i + 1) % 5) == 0) cout << "\n";
	}

	cout << endl;
#endif
}

void SawtoothWave(DWORD freq, float min, float max, float* buffer, size_t size)
{
	int phase = SAMPLE_RATE / freq; // The length of a single "pulse"

	for (int i = 0, j = 0; i < size; i++)
	{
		buffer[i] = percentBetween(min, max, (float)j / phase);

		if (j < phase) ++j;
		else j = 0;
	}


#ifdef WAVE_DEBUG
	for (int i = 0; i < size; i++)
	{
		cout << "[" << i << ", " << buffer[i] << "], ";
		if (((i + 1) % 5) == 0) cout << "\n";
	}

	cout << endl;
#endif
}