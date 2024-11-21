/**
 * @file scene_file.hpp
 * @brief This file contains the definition of SceneFile class, which
 *  represents a scene.
 * @authors Davidjmz12 DavidTizne
 * @date 03/11/2024
*/
#pragma once
#include <string>
#include <unordered_map>

#include "properties/brdf/all_brdf.hpp"
#include "files/ppm_file.hpp"
#include "files/ply_file.hpp"
#include "light/area_light/area_light.hpp"

#include "render/ray_tracing.hpp"
#include "render/photon_mapping.hpp"

using PropertyHash = std::unordered_map<std::string, Property>;

/**
 * Class for represent a scene
 */
class SceneFile {

private:
    std::string _ply_dir;
    mutable std::ifstream _file;
    PropertyHash _ch;

    /**
     * @brief Method for reading a not-commented line of the file
     * @return The next line of the file that is not commented
     */
    std::string read_line() const;

    /**
     * @brief Method for reading a point
     * @return The point
     */
    Point read_point() const;

    /**
     * @brief Method for reading a vector
     * @return The vector
     */
    Vector read_vector() const;

    /**
     * @brief Method for reading a camera
     * @return The camera
     */
    Camera read_camera() const;

    /**
     * @brief Method for reading the properties
     *  and store them in the object
     */
    void read_properties();

    /**
     * @brief Method for reading a geometry
     * @return A pointer to the geometry
     */
    std::shared_ptr<Geometry> read_geometry() const;

    /**
     * @brief Method for reading all the geometries
     * @return A vector with pointers to all geometries
     */
    VectorGeometries read_geometries() const;

    /**
     * @brief Method for reading all the lights
     * @param pl[out] The punctual lights
     * @param al[out] The area lights
     */
    void read_lights(VectorPunctualLight& pl, VectorAreaLight& al) const;

    /**
     * @brief Method for reading the tone mapping
     * @return A pointer to the tone mapping
     */
    std::unique_ptr<ToneMapping> read_tone_mapping(double max) const;

    /**
     * @brief Method for reading the resolution of the
     *  image
     * @return An array of size 2 with the dimensions of
     *  the image
     */
    std::array<int,2> read_resolution() const;

    /**
     * @brief Method for reading the headers
     * @param expected The expected string to have in
     *  the header
     * @return The number of elements in the section
     */
    int read_header(const std::string& expected) const;

    /**
     * @brief Method for reading a color
     * @return The color
     */
    Color read_color() const;

    /**
     * @brief Method for reading a BRDF object
     * @return The color of the object
     */
    std::shared_ptr<BRDF> read_brdf() const;

    /**
     * @brief Method for reading a bounding box
     * @return An array of size 6 with all the necessary
     *  parameters for create a bounding box
     */
    std::array<double,6> read_bounding_box() const;

    /**
     * @brief Method for reading a property
     * @param key The name of one property that has been
     *  defined previously in the properties section
     * @return The property
     */
    Property read_property(const std::string& key) const;

    /**
     * @brief Method for reading a punctual light
     * @return A pointer to the punctual light
     */
    std::shared_ptr<PunctualLight> read_punctual_light() const;

    /**
     * @brief Method for reading an area light
     * @return A pointer to the AreaLight object
     */
    std::shared_ptr<AreaLight> read_area_light() const;

    /**
     * @brief Method for reading a plane
     * @param p The property of the plane
     * @brief The plane
     */
    std::shared_ptr<Geometry> read_plane(const Property& p) const;

    /**
     * @brief Method for reading a sphere
     * @param p The property of the sphere
     * @brief The sphere
     */
    std::shared_ptr<Geometry> read_sphere(const Property& p) const;

    /**
     * @brief Method for reading a cylinder
     * @param p The property of the cylinder
     * @brief The cylinder
     */
    std::shared_ptr<Geometry> read_cylinder(const Property& p) const;

    /**
     * @brief Method for reading a mesh
     * @param p The property of the mesh
     * @brief The mesh
     */
    std::shared_ptr<Geometry> read_mesh(const Property& p) const;

    /**
     * @brief Method for reading a box
     * @param p The property of the box
     * @brief The box
     */
    std::shared_ptr<Geometry> read_box(const Property& p) const;

    /**
     * @brief Method for reading a face
     * @param p The property of the face
     * @brief The face
     */
    std::shared_ptr<Geometry> read_face(const Property& p) const;

    /**
     * @brief Method for reading a cone
     * @param p The property of the cone
     * @brief The cone
     */
    std::shared_ptr<Geometry> read_cone(const Property& p) const;

    /**
     * @brief Method for reading a disk
     * @param p The property of the disk
     * @brief The disk
     */
    std::shared_ptr<Geometry> read_disk(const Property& p) const;

    /**
     * @brief Method for reading an ellipsoid
     * @param p The property of the ellipsoid
     * @brief The ellipsoid
     */
    std::shared_ptr<Geometry> read_ellipsoid(const Property& p) const;

    /**
     * @brief Method for reading a triangle
     * @param p The property of the triangle
     * @brief The triangle
     */
    std::shared_ptr<Geometry> read_triangle(const Property& p) const;

    /**
     * @brief Method for reading a gamma tone mapping
     * @param max The maximum of luminance
     * @brief A pointer to the gamma tone mapping
     */
    std::unique_ptr<ToneMapping> read_gamma_tm(double max) const;

public:
    /**
     * @brief Constructor of the SceneFile class
     * @param file The scene file
     * @param ply_dir The path to the dir with the ply files
     */
    SceneFile(const std::string& file, std::string ply_dir);

    /**
     * @brief Method for reading the file and create the image
     * @param path The path to the directory in which the image
     *  is going to be stored
     * @param file_save The name for the created file
     */
    void read_scene(const std::string& path, const std::string& file_save);
};
