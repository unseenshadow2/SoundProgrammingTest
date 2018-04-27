#include "song.h"
#include "waves.h"

#define CHANNEL_MAX 0.25f
#define CHANNEL_MIN -0.25f

const size_t songLength = 5;
const size_t songBuffLen = songLength * SAMPLE_RATE;
float song[songBuffLen] = { 0 };

void MakeChannel1(float* channel);
void MakeChannel2(float* channel);
void MakeChannel3(float* channel);
void MakeChannel4(float* channel);

void MakeSong()
{
	float* channel1 = new float[songBuffLen];
	float* channel2 = new float[songBuffLen];
	float* channel3 = new float[songBuffLen];
	float* channel4 = new float[songBuffLen];

	MakeChannel1(channel1);
	MakeChannel2(channel2);
	MakeChannel3(channel3);
	MakeChannel4(channel4);

	for (int i = 0; i < songBuffLen; i++)
		song[i] = channel1[i] + channel2[i] + channel3[i] + channel4[i];

	delete[] channel1;
	delete[] channel2;
	delete[] channel3;
	delete[] channel4;
}

void PlaySong(HSTREAM stream)
{
	if (BASS_StreamPutData(stream, song, songBuffLen * sizeof(float))) 
		BASS_ChannelPlay(stream, FALSE);
}

// *******************************
// **** Song Making Goes Here ****
// *******************************

// Sin
void MakeChannel1(float* channel)
{
	size_t delta = 0;

	// 0 - 1
	delta = SAMPLE_RATE;
	SinWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, SAMPLE_RATE);

	// 1 - 2.5
	channel += delta;
	delta = SAMPLE_RATE + (SAMPLE_RATE / 2);
	SinWave(175, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 2.5 - 3
	channel += delta;
	delta = SAMPLE_RATE / 2;
	SinWave(1047, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 3 - 5
	channel += delta;
	delta = SAMPLE_RATE * 2;
	SinWave(165, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
}

// Pulse
void MakeChannel2(float* channel)
{
	size_t delta = 0;

	// 0 - 0.25
	delta = SAMPLE_RATE / 4;
	PulseWave(350, CHANNEL_MIN, CHANNEL_MAX, 40, channel, delta);

	// 0.25 - 1
	channel += delta;
	delta = (SAMPLE_RATE * 3) / 4;
	PulseWave(73, CHANNEL_MIN, CHANNEL_MAX, 50, channel, delta);

	// 1 - 1.5
	channel += delta;
	delta = SAMPLE_RATE / 2;
	PulseWave(3322, CHANNEL_MIN, CHANNEL_MAX, 30, channel, delta);

	// 1.5 - 1.75
	channel += delta;
	delta = SAMPLE_RATE / 4;
	for (int i = 0; i < delta; i++) channel[i] = 0;
	
	// 1.75 - 2
	channel += delta;
	PulseWave(784, CHANNEL_MIN, CHANNEL_MAX, 50, channel, delta);
	
	// 2 - 2.5
	channel += delta;
	delta = SAMPLE_RATE / 2;
	PulseWave(392, CHANNEL_MIN, CHANNEL_MAX, 40, channel, delta);

	// 2.5 - 3
	channel += delta;
	PulseWave(175, CHANNEL_MIN, CHANNEL_MAX, 25, channel, delta);

	// 3 - 4
	channel += delta;
	delta = SAMPLE_RATE;
	PulseWave(392, CHANNEL_MIN, CHANNEL_MAX, 50, channel, delta);

	// 4 - 4.5
	channel += delta;
	delta = SAMPLE_RATE / 2;
	PulseWave(175, CHANNEL_MIN, CHANNEL_MAX, 25, channel, delta);

	// 4.5 - 4.75
	channel += delta;
	delta = SAMPLE_RATE / 4;
	PulseWave(784, CHANNEL_MIN, CHANNEL_MAX, 50, channel, delta);

	// 4.75 - 5
	channel += delta;
	PulseWave(175, CHANNEL_MIN, CHANNEL_MAX, 25, channel, delta);
}

// Triangle
void MakeChannel3(float* channel)
{
	size_t delta = 0;

	// 0 - 3
	delta = SAMPLE_RATE * 3;
	TriangleWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 3 - 5
	channel += delta;
	delta = SAMPLE_RATE * 2;
	TriangleWave(523, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
}

// Sawtooth
void MakeChannel4(float* channel)
{
	size_t delta = SAMPLE_RATE / 4;

	// 0 - 1
	SawtoothWave(294, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(349, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 1 - 2
	channel += delta;
	SawtoothWave(294, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(349, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 2 - 3
	channel += delta;
	SawtoothWave(294, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(349, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 3 - 4
	channel += delta;
	SawtoothWave(294, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(349, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);

	// 4 - 5
	channel += delta;
	SawtoothWave(294, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(330, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(349, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
	channel += delta;
	SawtoothWave(131, CHANNEL_MIN, CHANNEL_MAX, channel, delta);
}