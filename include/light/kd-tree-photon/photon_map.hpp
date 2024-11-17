#include <list>
#include "light/kd-tree-photon/kdtree.h"
#include "light/photon.hpp"

class PhotonMap
{
private:
    nn::KDTree<Photon,3,PhotonAxisPosition> _tree;

public:
    PhotonMap(std::vector<Photon> photons)
    {
        std::list<Photon> list(photons.begin(), photons.end()); 
        _tree = nn::KDTree<Photon,3,PhotonAxisPosition>(list,PhotonAxisPosition());
    }

    std::vector<const Photon*> nearest_neighbors(const Point& query_position, unsigned long nphotons_estimate, double radius_estimate)  const
    {
        return this->_tree.nearest_neighbors(query_position, nphotons_estimate, radius_estimate);
    }
};
