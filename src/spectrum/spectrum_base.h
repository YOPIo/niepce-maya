#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_

#include "../niepce.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Spectrum utility value declarations
// ---------------------------------------------------------------------------
static constexpr Float kWavelengthSampleBegin = 360;
static constexpr Float kWavelengthSampleEnd   = 830;
static constexpr int   kSpectrumSamples       = 471;


// ---------------------------------------------------------------------------
// Spectrum utility function declarations
// ---------------------------------------------------------------------------
inline auto XYZToRGB(const std::array<Float, 3>& xyz,
                           std::array<Float, 3>* rgb) -> void
{
  (*rgb)[0] =  3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
  (*rgb)[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
  (*rgb)[2] =  0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
}

inline auto RGBToXYZ(const std::array<Float, 3>& rgb,
                           std::array<Float, 3>* xyz) -> void
{
  (*xyz)[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
  (*xyz)[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
  (*xyz)[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
}

// ---------------------------------------------------------------------------
// SpectrumBase
// ---------------------------------------------------------------------------
class SpectrumBase
{
 public:
  SpectrumBase()
  {}
  virtual ~SpectrumBase()
  {}

  SpectrumBase(const SpectrumBase& spectrum) = default;
  SpectrumBase(SpectrumBase&& spectrum)      = default;

  // ---------------------------------------------------------------------------
  // Spectrum public operators
  // ---------------------------------------------------------------------------
 public:
  auto operator = (const SpectrumBase& spectrum) -> SpectrumBase& = default;
  auto operator = (SpectrumBase&& spectrum)      -> SpectrumBase& = default;

  auto operator == (const SpectrumBase& spectrum) -> bool
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { if (spd_[i] != spectrum[i]) { return false; } }
    return true;
  }
  auto operator != (const SpectrumBase& spectrum) -> bool
  {
    return !(*this == spectrum);
  }

  auto operator [] (std::size_t idx) const -> Float  { return spd_[idx]; }
  auto operator [] (std::size_t idx)       -> Float& { return spd_[idx]; }

  auto operator + (const SpectrumBase& spectrum) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] + spectrum[i]; }
    return res;
  }
  auto operator - (const SpectrumBase& spectrum) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] - spectrum[i]; }
    return res;
  }
  auto operator * (Float v) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] * v; }
    return res;
  }
  auto operator * (const SpectrumBase& spectrum) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] * spectrum[i]; }
    return res;
  }
  auto operator / (Float v) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] / v; }
    return res;
  }
  auto operator / (const SpectrumBase& spectrum) const -> SpectrumBase
  {
    SpectrumBase res;
    for (int i = 0; i < kSpectrumSamples; ++i) { res[i] = spd_[i] / spectrum[i]; }
    return res;
  }

  auto operator += (const SpectrumBase& spectrum) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] += spectrum[i]; }
    return *this;
  }
  auto operator -= (const SpectrumBase& spectrum) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] -= spectrum[i]; }
    return *this;
  }
  auto operator *= (Float v) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] *= v; }
    return *this;
  }
  auto operator *= (const SpectrumBase& spectrum) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] *= spectrum[i]; }
    return *this;
  }
  auto operator /= (Float v) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] /= v; }
    return *this;
  }
  auto operator /= (const SpectrumBase& spectrum) -> SpectrumBase&
  {
    for (int i = 0; i < kSpectrumSamples; ++i) { (*this)[i] /= spectrum[i]; }
    return *this;
  }


  // ---------------------------------------------------------------------------
  // Spectrum Base protected data
  // ---------------------------------------------------------------------------
 private:
  std::array<Float, kSpectrumSamples> spd_;
};


}  // namespace niepce

#endif // _SPECTRUM_H_
