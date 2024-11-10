#include "geometry/kd-trees/kd-tree.hpp"

KDTree::KDTree()
{
    root = std::make_unique<KDTreeNode>(VectorGeometries());
}

KDTree::KDTree(const VectorGeometries& geometries)
{
    size_t depth = GlobalConf::get_instance()->get_max_depth();
    root = std::make_unique<KDTreeNode>(geometries);
    root->build(depth);
}

bool KDTree::intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const
{
    return root->intersect_with_ray(ray, intersection);
}


std::string KDTree::to_string() const
{
    return "NOT IMPLEMENTED YET";
}

KDTreeNode::KDTreeNode(const VectorGeometries& geometries)
    : geometries(geometries)
{
    // Initialize bbox by encompassing all geometries' bounding boxes
    std::vector<BoundingBox> bounding_boxes;
    for (const auto& geometry : geometries) {
        bounding_boxes.push_back(geometry->get_bounding_box());
    }
    bbox = BoundingBox::combine_all(bounding_boxes);
}

void KDTreeNode::build(int depth)
{
    if (geometries.size() <= 1 || depth > 0) return;

    int axis = depth % 3;
    std::sort(geometries.begin(), geometries.end(), [axis](const auto& a, const auto& b) {
        return a->get_bounding_box().center(axis) < b->get_bounding_box().center(axis);
    });

    auto mid = geometries.size() / 2;
    VectorGeometries leftGeometries(geometries.begin(), geometries.begin() + mid);
    VectorGeometries rightGeometries(geometries.begin() + mid, geometries.end());

    left = std::make_unique<KDTreeNode>(leftGeometries);
    right = std::make_unique<KDTreeNode>(rightGeometries);

    left->build(depth - 1);
    right->build(depth - 1);
}

bool KDTreeNode::intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const
{
    if (!bbox.intersect_with_ray(ray)) return false;


    if(!left && !right)
    {
        bool hit = false;
        for (const auto& geometry : geometries) {
            if (geometry->intersect_with_ray(ray, intersection)) {
                hit = true;
            }
        }
        return hit;
    } else 
    {
        IntersectionObject intersection_left, intersection_right;
        bool hit;
        if (left && left->intersect_with_ray(ray, intersection_left)) hit = true;
        if (right && right->intersect_with_ray(ray, intersection_right)) hit = true;
        
        if (intersection_left < intersection_right) {
            intersection = intersection_left;
        } else {
            intersection = intersection_right;
        }
        return hit;
    }

}