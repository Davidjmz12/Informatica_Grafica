#include "geometry/kd-trees/kd-tree.hpp"

KDTree::KDTree()
{
    root = std::make_unique<KDTreeNode>(VectorGeometries());
}

KDTree::KDTree(const VectorGeometries& geometries, const size_t depth)
{
    root = std::make_unique<KDTreeNode>(geometries);
    root->build(depth);
}

bool KDTree::intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const
{
    return root->intersect_with_ray(ray, intersection);
}


std::string KDTree::to_string() const
{
    return root->to_string(0);
}

std::ostream& operator<<(std::ostream& os, const KDTree& tree)
{
    os << tree.to_string();
    return os;
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

void KDTreeNode::build(const size_t depth)
{
    if (geometries.size() <= 1 || depth == 0) return;

    size_t axis = depth % 3;
    std::sort(geometries.begin(), geometries.end(), [axis](const auto& a, const auto& b) {
        return a->get_bounding_box().center(axis) < b->get_bounding_box().center(axis);
    });

    const auto mid = geometries.size() / 2;
    VectorGeometries leftGeometries(geometries.begin(), geometries.begin() + mid);
    VectorGeometries rightGeometries(geometries.begin() + mid, geometries.end());

    left = std::make_unique<KDTreeNode>(leftGeometries);
    right = std::make_unique<KDTreeNode>(rightGeometries);

    left->build(depth - 1);
    right->build(depth - 1);
}

bool KDTreeNode::intersect_with_ray(const Ray& ray, IntersectionObject& intersection) const
{
    if (!bbox.intersect_with_ray(ray))
    {
        #ifdef METRICS
        Metrics& metrics = GlobalConf::get_instance()->get_metrics();
        metrics.increment_counter("num_bb_intersections_avoided");
        #endif
        return false;
    }
    if(!left && !right)
    {
        bool hit = false;
        IntersectionObject intersection_aux;
        for (const auto& geometry : geometries) {
            if (geometry->intersect_with_ray(ray, intersection_aux)) {
                hit = true;
                if (intersection_aux < intersection) {
                    intersection = intersection_aux;
                }
            }
        }
        return hit;
    }

    IntersectionObject intersection_left, intersection_right;
    bool hit = false;
    if (left && left->intersect_with_ray(ray, intersection_left)) hit = true;
    if (right && right->intersect_with_ray(ray, intersection_right)) hit = true;
        
    if (intersection_left < intersection_right) {
        intersection = intersection_left;
    } else {
        intersection = intersection_right;
    }
    return hit;
}

std::string KDTreeNode::to_string(const size_t offset) const
{
    const std::string offset_s(offset, '\t');
    std::string s = offset_s  + "BoundingBox " + bbox.to_string() + "\n";
    s += offset_s + "Geometries: " + std::to_string(geometries.size()) +  "\n";
    if (left) s += offset_s + "Left:\n" + left->to_string(offset + 1);
    if (right) s += offset_s + "Right:\n" + right->to_string(offset + 1);
    return s;
}

std::ostream& operator<<(std::ostream& os, const KDTreeNode& node)
{
    os << node.to_string(0);
    return os;
}