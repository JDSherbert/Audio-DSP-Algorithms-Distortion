// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#include "HardClipDistortion.h"
 
#include <algorithm>
#include <cassert>
 
// ======================================================================= //
 
Sherbert::HardClipDistortion::HardClipDistortion(float distortionAmount, float threshold)
    : Distortion(distortionAmount)
    , threshold(threshold)
{
    assert(threshold > 0.0f && threshold <= 1.0f);
}
 
// ======================================================================= //
 
float Sherbert::HardClipDistortion::ProcessSample(float input) const
{
    // ==== HOW HARD CLIPPING WORKS ========================================
    //
    // The input is first amplified by distortionAmount (increasing drive),
    // then clamped hard to the range [-threshold, +threshold].
    //
    // Any part of the signal that exceeds the threshold is simply cut flat.
    // This abrupt transition introduces strong odd harmonics (3rd, 5th, 7th)
    // which give hard clipping its characteristic harsh, buzzy character.
    //
    // At low drive:  only the loudest peaks are clipped — subtle effect.
    // At high drive: most of the waveform is clamped, approaching a square
    //                wave with hard edges — very aggressive.
    //
    // Lowering the threshold clips earlier, increasing aggression
    // independently of the drive amount.
    // =====================================================================
 
    const float driven = distortionAmount * input;
    return std::clamp(driven, -threshold, threshold);
}
 
// ======================================================================= //
 
void Sherbert::HardClipDistortion::setThreshold(float newThreshold)
{
    assert(newThreshold > 0.0f && newThreshold <= 1.0f);
    threshold = newThreshold;
}
 
// ======================================================================= //
