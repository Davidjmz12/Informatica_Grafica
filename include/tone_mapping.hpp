#ifndef TONE_MAPPING
#define TONE_MAPPING

class Tone_mapping
{
private:
    float _gamma;
    float _slope;
    float _V;
    float _LMax;

    Tone_mapping(float gamma, float slope, float V, float LMax);

public:

    static Tone_mapping clamping(float LMax);
    static Tone_mapping equalization(float LMax);
    static Tone_mapping equalization_clamping(float V, float LMax);
    static Tone_mapping gamma(float gamma, float slope, float LMax);
    static Tone_mapping gamma_clamping(float gamma, float slope, float V, float LMax);


    float evaluate(float l_in);
};

#endif