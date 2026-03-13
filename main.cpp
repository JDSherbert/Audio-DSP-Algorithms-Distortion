// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
 
#include "SoftClipDistortion.h"
#include "HardClipDistortion.h"
#include "FoldbackDistortion.h"
 
// ======================================================================= //
 
// Generates a single sample of a sine wave at the given frequency and time.
// frequency - Hz (e.g. 440.0 = concert A)
// time      - position in seconds (e.g. sampleIndex / sampleRate)
float GenerateInputSignal(float frequency, float time)
{
    return std::sin(2.0f * static_cast<float>(M_PI) * frequency * time);
}
 
// ======================================================================= //
 
// Prints a labelled sample value to stdout.
void PrintSample(const std::string& label, float value)
{
    std::cout << label << " : " << value << "\n";
}
 
// ======================================================================= //
 
// Runs a distortion effect over a buffer and prints before/after values
// for the first printCount samples so the effect is clearly visible.
void DemonstrateDistortion
(
    Sherbert::Distortion& effect,
    const std::vector<float>& inputBuffer,
    const std::string& label,
    int printCount = 10
)
{
    std::cout << "\n--- " << label << " ---\n";
 
    for (int i = 0; i < printCount; ++i)
    {
        const float input  = inputBuffer[i];
        const float output = effect.ProcessSample(input);
        PrintSample("  Input ", input);
        PrintSample("  Output", output);
        std::cout << "\n";
    }
}
 
// ======================================================================= //
 
int main()
{
    // == Signal Parameters ==============================================
    const int   sampleRate  = 44100;   // 44.1 kHz
    const float frequency   = 440.0f;  // Concert A
    const float duration    = 0.1f;    // 0.1 seconds — enough to see the effect
 
    const int numSamples = static_cast<int>(sampleRate * duration);
 
    // == Generate Sine Wave ==============================================
    // Each sample index is divided by sampleRate to convert it to seconds.
    // This is then passed to the sine function as the time argument:
    //   sample = sin(2π * frequency * time)
    std::vector<float> sineWave(numSamples);
    for (int i = 0; i < numSamples; ++i)
    {
        sineWave[i] = GenerateInputSignal(frequency, i / static_cast<float>(sampleRate));
    }
 
    // == Demonstrate Each Distortion Type ================================
    // Each distortion type is demonstrated independently on the same
    // input buffer so the differences in character are easy to compare.
 
    Sherbert::SoftClipDistortion  softClip (2.0f);
    Sherbert::HardClipDistortion  hardClip (3.0f, 0.8f);
    Sherbert::FoldbackDistortion  foldback (2.0f, 1.0f);
 
    DemonstrateDistortion(softClip, sineWave, "Soft Clip  (amount: 2.0)");
    DemonstrateDistortion(hardClip, sineWave, "Hard Clip  (amount: 3.0, threshold: 0.8)");
    DemonstrateDistortion(foldback, sineWave, "Foldback   (amount: 2.0, threshold: 1.0)");
 
    return 0;
}
 
// ======================================================================= //
 
