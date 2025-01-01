#include "brdf/brdf.hpp"

BRDF BRDF::create_diffuse_BRDF(Color k)
{
    return BRDF(k, Color(), Color(), 0, Color());
}

BRDF BRDF::create_specular_BRDF(Color k)
{
    return BRDF(Color(), k, Color(), 0, Color());
}

BRDF BRDF::create_transmissive_BRDF(Color k, double refraction_index)
{
    return BRDF(Color(), Color(), k, refraction_index, Color());
}

BRDF BRDF::create_emisive_BRDF(Color k)
{
    return BRDF(Color(), Color(), Color(), 0, k);
}

BRDF::BRDF(Color kd, Color ks, Color kt, double refraction_index, Color ke)
    : _kd(kd), _ks(ks), _kt(kt), _refraction_index(refraction_index), _ke(ke)
{
    double sum = _kd.luminance_max() + _ks.luminance_max() + _kt.luminance_max();

    _weights[0] = _kd.luminance_max() / sum;
    _weights[1] = _ks.luminance_max() / sum;
    _weights[2] = _kt.luminance_max() / sum;
}

BRDF::BRDF(Color kd, Color ks, Color kt, double refraction_index, Color ke, std::shared_ptr<Texture> kd_texture)
    : _kd(kd), _ks(ks), _kt(kt), _refraction_index(refraction_index), _ke(ke), _kd_texture(kd_texture)
{
    double sum = _kd.luminance_max() + _ks.luminance_max() + _kt.luminance_max();

    _weights[0] = _kd.luminance_max() / sum;
    _weights[1] = _ks.luminance_max() / sum;
    _weights[2] = _kt.luminance_max() / sum;
}

BRDF::BRDF()
    : _kd(Color()), _ks(Color()), _kt(Color()), _refraction_index(0), _ke(Color())
{
    _weights[0] = 1;
    _weights[1] = 0;
    _weights[2] = 0;
}

Color BRDF::get_emission() const
{
    return _ke;
}

Color BRDF::eval(Color light, Vector w_i, Vector w_0, Point x, Vector n, double ref_coef_entry, BRDFType sampled) const
{
    if(sampled == BRDFType::DIFFUSE)
    {
        return light * this->_kd / M_PI;
    }
    else if(sampled == BRDFType::SPECULAR)
    {
        return this->_ks*light;
    }
    else if(sampled == BRDFType::TRANSMISSIVE)
    {
        return this->_kt*light;
    }
    else
    {
        throw std::invalid_argument("The BRDFType is not valid");
    }
}

bool BRDF::sample_diffuse(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const
{
    double phi = randomD(0,2*M_PI);
    double theta = randomD(0,1);
    theta = asin(theta);

    Base b = Base::complete_base_k(x, n);

    SpatialElement* base_v = new Vector(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
    Vector v = Vector(b.coord_into_canonical(base_v));
    delete base_v;
    sampled_ray = Ray(x, v, ref_coef_entry);
    return true;
}

bool BRDF::sample_specular(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const
{
    Vector projection = w_0 - n*w_0.dot(n);

    Vector final_dir = w_0 - projection * 2;
    
    sampled_ray = Ray(x, final_dir, ref_coef_entry);
    return true;
}

bool BRDF::sample_transmissive(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const
{
   if(neqD(w_0.norm(), 1) || neqD(n.norm(), 1))
        throw std::invalid_argument("The vectors must be normalized");
    
    const double theta_entry = acos(n.dot(w_0));

    const double entry_ri = is_entering ? 1 : this->_refraction_index;
    const double exit_ri = is_entering ? this->_refraction_index : 1;

    const double l = sin(theta_entry)*entry_ri/exit_ri;

    if(l>1 | l<-1)
        return false;

    const double theta_exit = asin(l);
    if(std::isnan(theta_exit))
        std::cout << "theta_exit is nan" << std::endl;
    const Vector orthogonal = ((w_0-n*w_0.dot(n))*(-1)).normalize();

    const auto base = Base(x, orthogonal, orthogonal.cross(n*(-1)) , n*(-1));
    std::unique_ptr<SpatialElement> v = std::make_unique<Vector>(sin(theta_exit),0,cos(theta_exit));
    const auto final_dir = Vector(base.coord_into_canonical(v.get()));

    sampled_ray = Ray(x, final_dir, this->_refraction_index);
    return true;
}

BRDFType BRDF::sample_ray(Vector w_0, Point x, Vector n, double ref_coef_entry, Ray& sampled_ray, bool is_entering) const
{
    double r = randomD(0,1);
    if(r < _weights[0])
    {
        sample_diffuse(w_0, x, n, ref_coef_entry, sampled_ray, is_entering);
        return BRDFType::DIFFUSE;
    }
    else if(r < _weights[0] + _weights[1])
    {
        sample_specular(w_0, x, n, ref_coef_entry, sampled_ray, is_entering);
        return BRDFType::SPECULAR;
    }
    else if(r < _weights[0] + _weights[1] + _weights[2])
    {
        sample_transmissive(w_0, x, n, ref_coef_entry, sampled_ray, is_entering);
        return BRDFType::TRANSMISSIVE;
    }
    else
    {
        return BRDFType::ABSORPTION;
    }
}

std::string BRDF::to_string() const
{
    std::string s = "BRDF: ";
    s += "Diffuse: " + _kd.to_string() + " Specular: " + _ks.to_string() + " Transmissive: " + _kt.to_string() + " Emissive: " + _ke.to_string();
    return s;
}

bool BRDF::is_delta(BRDFType t)
{
    return t == BRDFType::SPECULAR || t == BRDFType::TRANSMISSIVE;
}

std::ostream& operator<<(std::ostream& os, const BRDF& b)
{
    os << b.to_string();
    return os;
}




