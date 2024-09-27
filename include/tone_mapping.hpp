#ifndef TONE_MAPPING
#define TONE_MAPPING

class ToneMapping
{
private:
    float _gamma;
    float _slope;
    float _V;
    float _LMax;

    ToneMapping(float gamma, float slope, float V, float LMax);

public:

    static ToneMapping clamping(float LMax);
    static ToneMapping equalization(float LMax);
    static ToneMapping equalization_clamping(float V, float LMax);
    static ToneMapping gamma(float gamma, float slope, float LMax);
    static ToneMapping gamma_clamping(float gamma, float slope, float V, float LMax);


    float evaluate(float l_in);
};

#endif