// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#pragma once
 
#include "Distortion.h"
 
// ======================================================================= //
// HardClipDistortion
//
// Clamps the waveform to a fixed threshold, cutting off any part of the
// signal that exceeds it. This produces a harsh, aggressive distortion
// with strong odd harmonics — characteristic of fuzz pedals and
// transistor clipping circuits.
//
// Unlike soft clipping, the transition from clean to clipped is abrupt,
// which introduces more high-frequency content and a more abrasive tone.
//
//   Waveform shape:
//   input:   /\  /\
//   output:  ⌐¬  ⌐¬  (peaks cut flat)
//
// distortionAmount: Gain applied before clipping.
//                   Range: > 0.0 (typical range: 1.0 - 10.0)
//                   Higher values push more of the signal into clipping.
//
// threshold:        The absolute value at which the signal is clamped.
//                   Range: (0.0, 1.0] — defaults to 1.0.
//                   Lower values produce earlier, more aggressive clipping.
//
// Usage:
//   Sherbert::HardClipDistortion distortion(3.0f, 0.8f);
//   float output = distortion.ProcessSample(input);
//
// ======================================================================= //
 
namespace Sherbert
{
 
    class HardClipDistortion : public Distortion
    {

    public:
 
        explicit HardClipDistortion(float distortionAmount, float threshold = 1.0f);
 
        // Applies: output = clamp(distortionAmount * input, -threshold, +threshold)
        [[nodiscard]] float ProcessSample(float input) const override;
 
        float getThreshold() const noexcept { return threshold; }
        void  setThreshold(float newThreshold);
 
    private:
 
        float threshold;
 
    };
 
}
 
// ======================================================================= //
