#ifndef VTD_FRAMEWORK_VECTOR_H
#define VTD_FRAMEWORK_VECTOR_H

#include <VtdCore/BasicTypes.h>

namespace VTD {

class Vector3lf
{
public:

    static const Vector3lf zero;
    static const Vector3lf x_axis;
    static const Vector3lf y_axis;
    static const Vector3lf z_axis;

    Vector3lf(void);
    Vector3lf(double x, double y, double z);
    explicit Vector3lf(const double* xyz);
    Vector3lf(const Vector3lf &other);

    ~Vector3lf(void);

    Vector3lf& operator+=(const Vector3lf &other);
    Vector3lf operator+(const Vector3lf &other) const;
    Vector3lf& operator-=(const Vector3lf &other);
    Vector3lf operator-(const Vector3lf &other) const;
    Vector3lf& operator*=(const double &other);
    Vector3lf operator*(const double &other) const;

    Vector3lf cross(const Vector3lf &other) const;
    double dot(const Vector3lf &other) const;

    void normalize();
    static Vector3lf normalize(const Vector3lf& v);

    double length() const;
    double lengthSquared() const;

    Vector3lf& rotate(const Vector3lf& origin, double radians);
    double cosA(const Vector3lf& other) const;
    double angle(const Vector3lf& other) const;

    const double& x() const { return data_[0]; }
    const double& y() const { return data_[1]; }
    const double& z() const { return data_[2]; }

    const double& h() const { return data_[0]; }
    const double& p() const { return data_[1]; }
    const double& r() const { return data_[2]; }

    double& operator[](SizeType dimension) { return data_[dimension]; }
    const double& operator[](SizeType dimension) const { return data_[dimension]; }

private:
    double data_[3];
};

typedef Vector3lf Vector3;
typedef Vector3lf Vec3;
}

#endif //VTD_FRAMEWORK_VECTOR_H

