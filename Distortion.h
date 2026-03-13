// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#pragma once
 
// ======================================================================= //
// Distortion (Base Class)
//
// A family of distortion effects implemented as a base class with separate
// subclasses for each algorithm. Each subclass overrides ProcessSample()
// with its own waveshaping function.
//
// Distortion works by intentionally deforming the shape of an audio
// waveform. The nature of that deformation determines the character of
// the effect — soft and musical, harsh and aggressive, or complex and
// metallic.
//
// All algorithms share a single parameter: distortionAmount, which
// controls the intensity of the effect. The valid range and behaviour
// of this parameter varies per algorithm and is documented on each subclass.
//
// Do not instantiate this class directly — use one of the subclasses:
//   - SoftClipDistortion  (SoftClipDistortion.h)
//   - HardClipDistortion  (HardClipDistortion.h)
//   - FoldbackDistortion  (FoldbackDistortion.h)
//
// ======================================================================= //
 
namespace Sherbert
{
 
    class Distortion
    {

    public:
 
        // ------------------------------------------------------------------
        // Constructor
        //
        // distortionAmount - Controls the intensity of the effect.
        //                    See each subclass for its specific range and behaviour.
        //                    Must be greater than 0.
        // ------------------------------------------------------------------
 
        explicit Distortion(float distortionAmount);
        virtual ~Distortion() = default;
 
        // ------------------------------------------------------------------
        // ProcessSample
        //
        // Apply the distortion effect to a single input sample.
        // Call this once per sample in your audio callback loop.
        // Input is expected to be in the range [-1.0, 1.0].
        // ------------------------------------------------------------------
 
        [[nodiscard]] virtual float ProcessSample(float input) const = 0;
 
        // ------------------------------------------------------------------
        // Getters / Setters
        // ------------------------------------------------------------------
 
        float getDistortionAmount() const noexcept { return distortionAmount; }
        void  setDistortionAmount(float newAmount);
 
    protected:
 
        float distortionAmount;
 
    };
 
}
 
// ======================================================================= //
 
