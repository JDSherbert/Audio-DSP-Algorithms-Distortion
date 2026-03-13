// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#include "SoftClipDistortion.h"
 
#include <cmath>
 
// ======================================================================= //
 
Sherbert::SoftClipDistortion::SoftClipDistortion(float distortionAmount)
    : Distortion(distortionAmount)
{
}
 
// ======================================================================= //
 
float Sherbert::SoftClipDistortion::ProcessSample(float input) const
{
    // ==== HOW SOFT CLIPPING WORKS ==========================================
    //
    // tanh (hyperbolic tangent) maps any input value to the range (-1, 1).
    // Its curve is gentle near zero and flattens gradually toward the limits,
    // so loud parts of the signal are compressed rather than cut abruptly.
    //
    // Multiplying input by distortionAmount before passing it to tanh
    // increases the drive — it pushes the signal further up the curve,
    // introducing more harmonic content and compression.
    //
    // At low drive:  the signal sits near the linear centre of the curve
    //                and passes through almost unchanged.
    // At high drive: the signal is pushed to the flat extremes of the curve,
    //                approaching a square wave with rounded edges.
    // =======================================================================
 
    return std::tanh(distortionAmount * input);
}
 
// ======================================================================= //
