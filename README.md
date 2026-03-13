# Audio DSP Algorithms: Distortion

<!-- Header Start -->
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Audio-Soft-Clip-Distortion?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Audio-Soft-Clip-Distortion?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Audio-Soft-Clip-Distortion?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Audio-Soft-Clip-Distortion?label=%E2%9A%A0%EF%B8%8F"/>
<img align="right" src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FJDSherbert%2FAudio-Soft-Clip-Distortion%2Fhit-counter%2FREADME&count_bg=%2379C83D&title_bg=%23555555&labelColor=0E1128&title=🔍&style=for-the-badge">
<a href="https://learn.microsoft.com/en-us/cpp/cpp-language">
  <img height="40" width="40" src="https://cdn.simpleicons.org/cplusplus">
</a>
<!-- Header End -->
 
-----------------------------------------------------------------------
 
<a href="">
  <img align="left" alt="Audio Processing" src="https://img.shields.io/badge/Audio%20Processing-black?style=for-the-badge&logo=audacity&logoColor=white&color=black&labelColor=black">
</a>
 
<a href="https://choosealicense.com/licenses/mit/">
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black">
</a>
 
<br></br>
 
-----------------------------------------------------------------------
 
## Overview
 
A family of distortion effects implemented in plain C++, intended as a learning resource for understanding how digital waveshaping works from first principles. Three algorithms are provided, each demonstrating a different approach to deforming an audio waveform and the harmonic character that results.
 
Distortion works by passing each audio sample through a non-linear function; one that does not scale the input proportionally. The shape of that function determines whether the result sounds warm and musical, harsh and aggressive, or complex and metallic.
 
This technique is also the basis of the [Sherbert Clipper VST Effect](https://jdsherbert.itch.io/sherbert-clipper).
 
-----------------------------------------------------------------------
 
## Files
 
| File | Description |
|---|---|
| `Distortion.h / .cpp` | Abstract base class — shared `distortionAmount` parameter and `ProcessSample()` interface |
| `SoftClipDistortion.h / .cpp` | Soft clipping via `tanh` — warm, musical overdrive |
| `HardClipDistortion.h / .cpp` | Hard clipping via `clamp` — harsh, aggressive fuzz |
| `FoldbackDistortion.h / .cpp` | Foldback reflection — complex, metallic harmonics |
| `main.cpp` | Example: generates a 440Hz sine wave and demonstrates all three effects |
 
-----------------------------------------------------------------------
 
## Algorithms
 
### Soft Clip - `SoftClipDistortion`
 
Uses the `tanh` (hyperbolic tangent) function to smoothly round off the peaks of the waveform. The curve is gradual, so harmonics are introduced gently. The result sounds warm and saturated, similar to a valve/tube amplifier being driven hard.
 
```
input:   /\  /\
output:  ⌒   ⌒   (peaks rounded off smoothly)
```
 
```cpp
output = tanh(distortionAmount * input)
```
 
At low drive the signal passes through almost unchanged. At high drive it approaches a square wave with rounded edges. Because the transition is always smooth, there are no abrupt discontinuities and the distortion never sounds harsh.
 
---
 
### Hard Clip - `HardClipDistortion`
 
Amplifies the signal then cuts it flat at a fixed threshold. Any part of the waveform that exceeds the threshold is simply removed. The abrupt transition introduces strong odd harmonics (3rd, 5th, 7th) — the characteristic buzz of fuzz pedals and transistor clipping circuits.
 
```
input:   /\  /\
output:  ⌐¬  ⌐¬  (peaks cut flat)
```
 
```cpp
output = clamp(distortionAmount * input, -threshold, +threshold)
```
 
The `threshold` parameter controls where clipping begins, independently of drive. A lower threshold clips earlier and more aggressively.
 
---
 
### Foldback - `FoldbackDistortion`
 
When the signal exceeds the threshold, rather than clipping it, the waveform is reflected back inward, like a ball bouncing off a wall. If it folds past the opposite boundary it folds again, and so on until it falls within range.
 
```
input:   /\  /\
output:  /\/\/\  (peaks fold back on themselves)
```
 
```cpp
while (sample > threshold || sample < -threshold)
{
    if (sample >  threshold) sample =  2 * threshold - sample;
    if (sample < -threshold) sample = -2 * threshold - sample;
}
```
 
Multiple folds per sample are possible at high drive, producing a dense and complex harmonic spectrum - metallic and dissonant in character. This is very different from clipping and is commonly used in synthesis and noise music.
 
-----------------------------------------------------------------------
 
## Soft Clip vs Hard Clip - Key Difference
 
The core distinction is the *shape of the transition*:
 
| | Soft Clip | Hard Clip |
|---|---|---|
| Transition | Gradual curve | Abrupt flat cut |
| Character | Warm, musical | Harsh, aggressive |
| Harmonics | Gentle, even | Strong odd harmonics |
| Analogy | Valve amp overdrive | Fuzz pedal |
 
Both approaches are waveshaping; the difference is entirely in the function applied to each sample.
 
-----------------------------------------------------------------------
 
## Usage
 
### Basic
 
```cpp
// Instantiate any subclass directly
Sherbert::SoftClipDistortion  softClip(2.0f);
Sherbert::HardClipDistortion  hardClip(3.0f, 0.8f);
Sherbert::FoldbackDistortion  foldback(2.0f, 1.0f);
 
// Process one sample at a time in your audio loop
float output = softClip.ProcessSample(input);
```
 
### Wet/Dry Mix
 
`ProcessSample` returns the fully wet signal. Blend with the dry input to control the mix:
 
```cpp
const float wetAmount = 0.5f; // 0.0 = fully dry, 1.0 = fully wet
 
float wet    = distortion.ProcessSample(input);
float output = (wetAmount * wet) + ((1.0f - wetAmount) * input);
```
 
### Polymorphic Usage
 
All three subclasses share the `Distortion` base interface, so you can swap algorithms without changing your audio loop:
 
```cpp
void ProcessBuffer(Sherbert::Distortion& effect, std::vector<float>& buffer)
{
    for (float& sample : buffer)
        sample = effect.ProcessSample(sample);
}
 
// Works with any subclass
ProcessBuffer(softClip, buffer);
ProcessBuffer(hardClip, buffer);
ProcessBuffer(foldback, buffer);
```
 
-----------------------------------------------------------------------
 
## API Reference
 
### `Distortion` (base)
 
| Method | Description |
|---|---|
| `ProcessSample(input)` | Pure virtual. Process one sample — override in each subclass. |
| `setDistortionAmount(value)` | Update drive amount. Must be > 0. |
| `getDistortionAmount()` | Returns current drive amount. |
 
### `SoftClipDistortion`
 
| Method | Description |
|---|---|
| `SoftClipDistortion(distortionAmount)` | Construct with drive amount (typical range: 1.0 – 10.0). |
| `ProcessSample(input)` | Applies `tanh(amount * input)`. |
 
### `HardClipDistortion`
 
| Method | Description |
|---|---|
| `HardClipDistortion(distortionAmount, threshold)` | Construct with drive and clip threshold (0.0, 1.0]. Default threshold: 1.0. |
| `ProcessSample(input)` | Applies `clamp(amount * input, -threshold, +threshold)`. |
| `setThreshold(value)` | Update clip threshold at runtime. |
| `getThreshold()` | Returns current threshold. |
 
### `FoldbackDistortion`
 
| Method | Description |
|---|---|
| `FoldbackDistortion(distortionAmount, threshold)` | Construct with drive and fold boundary. Default threshold: 1.0. |
| `ProcessSample(input)` | Folds signal back at ±threshold until in range. |
| `setThreshold(value)` | Update fold boundary at runtime. |
| `getThreshold()` | Returns current threshold. |
 
-----------------------------------------------------------------------
 
## Limitations & Next Steps
 
This implementation processes each sample independently with no internal state, which makes it simple to follow but also means it lacks some features found in real-world distortion effects:
 
**No anti-aliasing** - non-linear waveshaping introduces harmonics that can exceed the Nyquist frequency, producing aliasing artefacts. Production distortion implementations oversample the signal before processing and downsample after to avoid this.
 
**No tone control** - real distortion pedals and plugins almost always include a filter after the waveshaper (typically a low-pass or tilt EQ) to shape the resulting harmonic content. A simple `biquad` low-pass filter after `ProcessSample` would be a natural next step.
 
**No DC offset correction** - asymmetric input signals can produce a DC offset after nonlinear processing. A high-pass filter at a very low frequency (e.g. 5–10Hz) in the feedback path corrects this.
 
If you want to explore further, the natural next steps from here are:
- Oversampling (2x or 4x) before the waveshaper to reduce aliasing
- A post-distortion tone filter (low-pass biquad)
- Asymmetric waveshaping (different curves for positive and negative halves)
- Combining soft clip with hard clip for a diode-style clipping simulation
 
-----------------------------------------------------------------------
