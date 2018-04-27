#pragma once
#include <windows.h>
//#include <iostream>

// https://www.geogebra.org/m/uvjr5m4K - Sine wave generator

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

void SinWave(DWORD freq, float min, float max, float* buffer, size_t size);
void PulseWave(DWORD freq, float min, float max, int pulsePercent, float* buffer, size_t size);
void TriangleWave(DWORD freq, float min, float max, float* buffer, size_t size);
void SawtoothWave(DWORD freq, float min, float max, float* buffer, size_t size);