// http://www.un4seen.com/doc/#bass/BASS_Init.html

// TODO: Convert to loading files and playing them too
// ([sptS])(?:\((\d{1,2})\))?(\d+)

// Standard includes
#include <iostream>
#include <iomanip>

// Library Includes
#include "bass.h"

// Personal Includes
#include "defines.h"
#include "globals.h"
#include "waves.h"
#include "song.h"

DWORD floatable; // floating-point channel support? 0 = no, else yes
BASS_INFO info;
HSTREAM stream = 0; // the stream

// ++ DEBUG VARIABLES ++
float testBuffer[SAMPLE_RATE * 5];
float buffer2[SAMPLE_RATE * 5] = { 0 };
// -- DEBUG VARIABLES --

using namespace std;

void InitIO();
void InitBass();
void Error(const char *text);
void InitialDisplay();
void SoundTest();

int main()
{
	InitIO();

	InitBass();
	InitialDisplay();

	cout << "\nCreating stream..." << endl;
	if (stream != 0) { BASS_StreamFree(stream); }
	stream = BASS_StreamCreate(info.freq, 1, BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, NULL);

	cout << "Making the song for you..." << endl;
	MakeSong();
	cout << "Song generated. Press enter to play!" << endl;

	cin.get();
	PlaySong(stream);
	cout << "Press enter to end the program." << endl;

	cin.get();
	if (stream != 0) BASS_StreamFree(stream);
	BASS_Free();

	return 0;
}

// Setup cout and cin
void InitIO()
{
	cout << fixed;
	cout << setprecision(2);
}

// Initialize the Bass library
void InitBass()
{
	if (!BASS_Init(-1, SAMPLE_RATE, BASS_DEVICE_LATENCY, 0, NULL)) // Start the lib
		Error("Can't initialize device");

	if (BASS_GetConfig(BASS_CONFIG_FLOAT)) // Check if we can handle 32 bit floats
	{
		floatable = BASS_StreamCreate(SAMPLE_RATE, 1, BASS_SAMPLE_FLOAT, NULL, NULL); // try creating a floating-point stream
		if (floatable) BASS_StreamFree(floatable); // floating-point channels are supported (free the test stream)
	}
	else floatable = 0;

	BASS_SetConfig(BASS_CONFIG_BUFFER, 5*SECOND); // set default/maximum buffer length to 5000ms (5 seconds)
	BASS_GetInfo(&info);
	if (!info.freq) info.freq = SAMPLE_RATE; // if the device's output rate is unknown, default to 44100 Hz

	cout << "Frequency: " << info.freq << endl;
}

// display error messages
void Error(const char *text)
{
	printf("Error(%d): %s\n", BASS_ErrorGetCode(), text);
	BASS_Free();
	ExitProcess(0);
}

// Display some basic debug info
void InitialDisplay()
{
	printf("Device latency: %dms\n", info.latency);
	printf("Device minbuf: %dms\n", info.minbuf);
	printf("Ds version: %d (effects %s)\n", info.dsver, info.dsver<8 ? "disabled" : "enabled");

	if (floatable != 0) cout << "We can use float streams... HUZZAH!" << endl;
	else cout << "No float stream for you!" << endl;

	cout << "\nSize of a word: " << sizeof(WORD) 
		 << "\nSize of a double word: " << sizeof(DWORD) << endl;
}

void SoundTest()
{
#ifdef  AUDIO_DEBUG
	// Attempt to open our stream
	stream = BASS_StreamCreate(info.freq, 1, BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, NULL);
#endif //  AUDIO_DEBUG

#ifdef  AUDIO_DEBUG
	if ((stream != 0))
#else
	if (true)
#endif //  AUDIO_DEBUG
	{
#ifdef SINE_DEBUG
		SinWave(247, 0, 0.5, testBuffer, SAMPLE_RATE * 4);
		SinWave(62, 0, 0.5, testBuffer + (SAMPLE_RATE * 4), SAMPLE_RATE);
		SinWave(98, 0, 0.5, buffer2, SAMPLE_RATE / 2);
		SinWave(123, 0, 0.5, buffer2 + (SAMPLE_RATE / 2), SAMPLE_RATE / 2);
		SinWave(523, 0, 0.5, buffer2 + SAMPLE_RATE, SAMPLE_RATE);
		SinWave(131, 0, 0.5, buffer2 + (SAMPLE_RATE * 5 / 2), SAMPLE_RATE);
#elif defined(PULSE_DEBUG)
		PulseWave(247, 0, 0.5, 25, testBuffer, SAMPLE_RATE);
		PulseWave(247, 0, 0.5, 50, testBuffer + SAMPLE_RATE, SAMPLE_RATE);
		PulseWave(247, 0, 0.5, 75, testBuffer + (SAMPLE_RATE *2), SAMPLE_RATE);
#elif defined(TRI_DEBUG)
		TriangleWave(247, 0, 0.5, testBuffer, SAMPLE_RATE);
		TriangleWave(523, -0.5, 0, buffer2, SAMPLE_RATE);
#elif defined(SAW_DEBUG)
		SawtoothWave(247, 0, 0.5, testBuffer, SAMPLE_RATE);
#endif

		for (int i = 0; i < (SAMPLE_RATE * 5); i++) testBuffer[i] += buffer2[i];

#ifdef  AUDIO_DEBUG
		// Pass the data to the stream, then play
		if (BASS_StreamPutData(stream, testBuffer, SAMPLE_RATE * 5 * sizeof(float))) cout << "{1} Successfully pushed data" << endl;
		cin.get();
		if ((BASS_ChannelPlay(stream, FALSE) == TRUE)) cout << "Started playing good!" << endl;
#endif //  AUDIO_DEBUG
	}
}