#include "EnvelopeFilter.hpp"
#include <iostream>

void EnvelopeFilter::doFilterings(){

    float y = 0;

    for (unsigned int n = 0; n < frame_length; n++){

        switch (envelope_phase){
        case(ATTACK):

            y = (1 / (float) adsr.attack) * phase;
            //std::cerr << "A @ " << phase << " : " << y << std::endl;
            if (phase >= adsr.attack) {envelope_phase = DECAY; phase = 0;}
            break;

        case(DECAY):

            y = -((1 - adsr.sustain)  / (float) adsr.decay) * phase + 1;
            //y = 1;
            //std::cerr << "D @ " << phase << " : " << y << std::endl;
            if (phase > adsr.decay) envelope_phase = SUSTAIN;
            break;

        case(SUSTAIN):

            phase = 0;
            // std::cerr << "S" << std::endl;
            y = adsr.sustain;
            break;

        case(RELEASE):
            y = adsr.sustain - (adsr.release * phase);
            break;
        }

        buffer[n] = buffer[n] * y;
        phase++;
    }

}
