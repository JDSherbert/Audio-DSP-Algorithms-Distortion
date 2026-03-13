// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#pragma once
 
#include "Distortion.h"
 
// ======================================================================= //
// SoftClipDistortion
//
// Uses a tanh (hyperbolic tangent) function to smoothly compress the
// waveform as it approaches the clipping threshold. This produces warm,
// musical overdrive — the same principle used in valve/tube amplifiers.
//
// Because tanh is a smooth curve, harmonics are introduced gradually,
// resulting in a natural, rounded sound. At low amounts it acts like
// gentle saturation; at high amounts it approaches hard clipping.
//
//   Waveform shape:
//   input:   /\  /\
//   output:  ⌒   ⌒   (peaks rounded off smoothly)
//
// distortionAmount: Drive applied before the tanh function.
//                   Range: > 0.0 (typical range: 1.0 - 10.0)
//                   At 1.0 the effect is subtle; at 10.0 it is very driven.
//
// Usage:
//   Sherbert::SoftClipDistortion distortion(2.0f);
//   float output = distortion.ProcessSample(input);
//
// ======================================================================= //
 
namespace Sherbert
{
 
    class SoftClipDistortion : public Distortion
    {
    public:
 
        explicit SoftClipDistortion(float distortionAmount);
 
        // Applies: output = tanh(distortionAmount * input)
        [[nodiscard]] float ProcessSample(float input) const override;
 
    };
 
}
 
// ======================================================================= //
