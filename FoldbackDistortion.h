// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#pragma once
 
#include "Distortion.h"
 
// ======================================================================= //
// FoldbackDistortion
//
// When the signal exceeds the threshold, instead of clipping it,
// the waveform is "folded back" — reflected inward. If it folds back
// past the negative threshold, it folds again, and so on until it falls
// within range.
//
// This creates complex, metallic, often dissonant harmonics not found
// in clipping-based distortion. It is commonly used in synthesis and
// industrial/noise music contexts.
//
//   Waveform shape:
//   input:   /\  /\
//   output:  /\/\/\  (peaks fold back on themselves)
//
// distortionAmount: Gain applied before folding.
//                   Range: > 0.0 (typical range: 1.0 - 5.0)
//                   Higher values cause more folds and more complex harmonics.
//
// threshold:        The fold boundary.
//                   Range: > 0.0 — defaults to 1.0.
//
// Usage:
//   Sherbert::FoldbackDistortion distortion(2.0f, 1.0f);
//   float output = distortion.ProcessSample(input);
//
// ======================================================================= //
 
namespace Sherbert
{
    class FoldbackDistortion : public Distortion
    {

    public:
 
        explicit FoldbackDistortion(float distortionAmount, float threshold = 1.0f);
 
        // Applies: folds the signal back at +/- threshold until it is in range
        [[nodiscard]] float ProcessSample(float input) const override;
 
        float getThreshold() const noexcept { return threshold; }
        void  setThreshold(float newThreshold);
 
    private:
 
        float threshold;
 
    };
 
}
 
// ======================================================================= //
 
