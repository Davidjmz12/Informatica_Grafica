#pragma once


#include <algorithm>
#include <limits>
#include <vector>
#include <memory>

#include "geometry/geometry.hpp"
#include "geometry/bounding_box.hpp" // Assuming a BoundingBox class with min/max coordinates for each axis
#include "global_config/global_config.hpp"

using VectorGeometries = std::vector<std::shared_ptr<Geometry>>;

class KDTreeNode
{
public:
    BoundingBox bbox;             // Bounding box for this node
    std::unique_ptr<KDTreeNode> left;  // Left child
    std::unique_ptr<KDTreeNode> right; // Right child
    VectorGeometries geometries; // Geometries in this node


    KDTreeNode(const VectorGeometries& geometries);
    void build(int depth);
    bool intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const;
};

class KDTree
{
public:
    std::unique_ptr<KDTreeNode> root;

    KDTree(const VectorGeometries& geometries);

    KDTree();

    bool intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const;

    std::string to_string() const;
};
