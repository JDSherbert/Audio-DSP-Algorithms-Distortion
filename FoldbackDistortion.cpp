// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#include "FoldbackDistortion.h"
 
#include <cassert>
 
// ======================================================================= //
 
Sherbert::FoldbackDistortion::FoldbackDistortion(float distortionAmount, float threshold)
    : Distortion(distortionAmount)
    , threshold(threshold)
{
    assert(threshold > 0.0f);
}
 
// ======================================================================= //
 
float Sherbert::FoldbackDistortion::ProcessSample(float input) const
{
    // === HOW FOLDBACK DISTORTION WORKS =================================
    //
    // Rather than clipping the signal when it exceeds the threshold,
    // foldback reflects it back inward — like a ball bouncing off a wall.
    //
    // If the driven signal is 1.3 and the threshold is 1.0:
    //   - It exceeds +threshold by 0.3, so it folds back to 1.0 - 0.3 = 0.7
    //
    // If after folding it exceeds the opposite boundary, it folds again.
    // This can happen multiple times per sample at high drive values,
    // producing increasingly complex harmonic content with each fold.
    //
    // The result is a metallic, inharmonic distortion with a dense
    // frequency spectrum — very different in character to clipping.
    //
    // At low drive:  signal rarely exceeds threshold, subtle effect.
    // At high drive: multiple folds per sample, highly complex output.
    // ====================================================================
 
    float sample = distortionAmount * input;
 
    // Fold the signal until it falls within [-threshold, +threshold]
    while (sample > threshold || sample < -threshold)
    {
        if (sample > threshold)
            sample = 2.0f * threshold - sample;
 
        if (sample < -threshold)
            sample = -2.0f * threshold - sample;
    }
 
    return sample;
}
 
// ======================================================================= //
 
void Sherbert::FoldbackDistortion::setThreshold(float newThreshold)
{
    assert(newThreshold > 0.0f);
    threshold = newThreshold;
}
 
// ======================================================================= //
