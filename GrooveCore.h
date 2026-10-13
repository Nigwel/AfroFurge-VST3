#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
namespace afrogrid {
constexpr double pi=3.14159265358979323846;
struct Hit {double beat; int voice; double velocity;};
// Two-bar foundation, deliberately sparse. Rim voices are displaced; bass answers kick gaps.
constexpr std::array<Hit,19> phrase{{
 {0,0,1.0},{1.75,0,.64},{3.5,0,.77},{4,0,.92},{6.75,0,.75},
 {1.25,1,.89},{2.75,1,.54},{5.25,1,.85},{7.0,1,.87},
 {.50,2,.35},{1.50,2,.48},{2.50,2,.35},{3.50,2,.46},
 {4.50,2,.39},{5.50,2,.48},{6.50,2,.34},{7.50,2,.43},
 {2.25,3,.70},{6.25,3,.75}
}};
struct Voice {double phase=0, env=0, frequency=100;};
class GrooveCore {
public:
 void prepare(double sampleRate) {sr=std::max(8000.0,sampleRate); reset();}
 void reset() {sample=0; voices={};}
 void setBpm(double v) {bpm=std::clamp(v,60.0,180.0);}
 void setGain(double v) {gain=std::clamp(v,0.0,1.0);}
 void setEnabled(bool v) {enabled=v;}
 float tick() {
  const double beat=double(sample)*bpm/(60.0*sr);
  const double prev=double(sample==0?0:sample-1)*bpm/(60.0*sr);
  const auto within=[](double b){double p=std::fmod(b,8.0);return p<0?p+8:p;};
  const double pos=within(beat), old=within(prev);
  if(enabled) for(const auto& hit:phrase) {
   // Rim deliberately late 14 ms; shaker swung in alternate eighths.
   const double offset=hit.voice==1 ? .014*bpm/60.0 : (hit.voice==2 && (int(hit.beat*2)%2) ? .035 : 0.0);
   const double target=hit.beat+offset;
   if((sample==0 && target==0) || (old<=pos ? (old<target && pos>=target) : (target>old || target<=pos))) trigger(hit);
  }
  ++sample;
  double sum=0;
  for(int r=0;r<4;++r) {
   auto& v=voices[size_t(r)];
   const double tau=(r==0?.090:r==1?.038:r==2?.023:.18);
   v.env*=std::exp(-1.0/(tau*sr));
   const double frequency=v.frequency*(r==0?(.65+.35*v.env):1.0);
   v.phase+=2*pi*frequency/sr;
   if(v.phase>2*pi) v.phase=std::fmod(v.phase,2*pi);
   const double wave=r==1 ? std::sin(v.phase)+.26*std::sin(v.phase*2) :
       r==2 ? std::sin(v.phase)*std::sin(v.phase*1.83) : std::sin(v.phase);
   sum+=wave*v.env*(r==0?.40:r==1?.16:r==2?.06:.21);
  }
  return float(std::tanh(sum*gain));
 }
 uint64_t samplesProcessed() const {return sample;}
private:
 void trigger(const Hit& hit) {
  auto& v=voices[size_t(hit.voice)]; v.env=hit.velocity; v.phase=0;
  v.frequency=hit.voice==0?95:hit.voice==1?790:hit.voice==2?1600:88;
 }
 double sr=48000,bpm=110,gain=.75; bool enabled=true;
 uint64_t sample=0; std::array<Voice,4> voices{};
};
}
