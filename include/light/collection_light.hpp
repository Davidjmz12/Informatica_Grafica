
#include "light/punctual_light.hpp"
#include "global_config/constants.hpp"

using VectorPunctualLight = std::vector<std::shared_ptr<PunctualLight>>;

class CollectionLight final
{
private:
    VectorPunctualLight _lights;
    std::vector<double> _weights;
public:

    CollectionLight(const VectorPunctualLight& lights);

    [[nodiscard]] double sample_light(PunctualLight& light);
};
