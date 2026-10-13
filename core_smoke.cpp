#include "../src/GrooveCore.h"
#include <cassert>
#include <cmath>
#include <iostream>
int main() {
 afrogrid::GrooveCore g;g.prepare(48000);g.setBpm(110);
 double energy=0;float peak=0;
 for(int i=0;i<48000*5;++i){float x=g.tick();assert(std::isfinite(x));energy+=double(x)*x;peak=std::max(peak,std::abs(x));}
 assert(g.samplesProcessed()==240000);assert(energy>1);assert(peak<=1);
 std::cout<<"PASS 240000 samples, energy="<<energy<<" peak="<<peak<<"\n";
}
