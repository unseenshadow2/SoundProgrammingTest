#pragma once
#include "defines.h"
#include "bass.h"

extern const size_t songLength;
extern const size_t songBuffLen;

void MakeSong();
void PlaySong(HSTREAM stream);