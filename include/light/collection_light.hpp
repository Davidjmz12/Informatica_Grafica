
#include "light/punctual_light.hpp"
#include "light/area_light.hpp"
#include "global_config/constants.hpp"

using VectorPunctualLight = std::vector<std::shared_ptr<PunctualLight>>;
using VectorAreaLight = std::vector<std::shared_ptr<AreaLight>>;

class CollectionLight final
{
private:
    VectorPunctualLight _lights;
    VectorAreaLight _area_lights;
    std::vector<double> _weights;
public:

    CollectionLight(const VectorPunctualLight& lights, const VectorAreaLight& area_lights);

    [[nodiscard]] double sample_light(std::shared_ptr<AbstractLight>& light);
};
