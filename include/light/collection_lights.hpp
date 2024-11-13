
#include "light/light.hpp"
#include "global_config/constants.hpp"

using LightVector = std::vector<std::shared_ptr<PunctualLight>>;

class CollectionLight final
{
private:
    LightVector _lights;
    std::vector<double> _weights;
public:

    CollectionLight(const LightVector& lights);

    [[nodiscard]] double sample_light(PunctualLight& light);
};
