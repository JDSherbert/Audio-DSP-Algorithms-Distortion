// Copyright (c) 2024 JDSherbert. All rights reserved.
 
#include "Distortion.h"
 
#include <cassert>
 
// ======================================================================= //
 
Sherbert::Distortion::Distortion(float distortionAmount)
    : distortionAmount(distortionAmount)
{
    assert(distortionAmount > 0.0f);
}
 
// ======================================================================= //
 
void Sherbert::Distortion::setDistortionAmount(float newAmount)
{
    assert(newAmount > 0.0f);
    distortionAmount = newAmount;
}
 
// ======================================================================= //
 
