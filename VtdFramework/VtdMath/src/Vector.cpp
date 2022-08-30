#include <VtdMath/Vector.h>

#include <cmath>
#include <cstring>

namespace VTD {

const Vector3lf Vector3lf::zero = Vector3lf(0.0f,0.0f,0.0f);
const Vector3lf Vector3lf::x_axis = Vector3lf(1.0f,0.0f,0.0f);
const Vector3lf Vector3lf::y_axis = Vector3lf(0.0f,1.0f,0.0f);
const Vector3lf Vector3lf::z_axis = Vector3lf(0.0f,0.0f,1.0f);

Vector3lf::Vector3lf(void) :
    data_()
{ /**/ }

Vector3lf::Vector3lf(double x, double y, double z)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}

Vector3lf::Vector3lf(const double* xyz)
{
    memcpy(data_, xyz, sizeof(data_));
}

Vector3lf::Vector3lf(const Vector3lf &other)
{
    memcpy(data_, other.data_, sizeof(data_));
}

Vector3lf::~Vector3lf(void)
{ /**/ }

Vector3lf& Vector3lf::operator+=(const Vector3lf &other)
{
    data_[0] += other[0];
    data_[1] += other[1];
    data_[2] += other[2];
    return *this;
}

Vector3lf Vector3lf::operator+(const Vector3lf &other) const
{
    Vector3lf result(*this);
    result += other;
    return result;
}

Vector3lf& Vector3lf::operator-=(const Vector3lf &other)
{
    data_[0] -= other[0];
    data_[1] -= other[1];
    data_[2] -= other[2];
    return *this;
}

Vector3lf Vector3lf::operator-(const Vector3lf &other) const
{
    Vector3lf result(*this);
    result -= other;
    return result;
}

Vector3lf& Vector3lf::operator*=(const double &other)
{
    data_[0] *= other;
    data_[1] *= other;
    data_[2] *= other;
    return *this;
}

Vector3lf Vector3lf::operator*(const double &other) const
{
    Vector3lf result(*this);
    result *= other;
    return result;
}

Vector3lf Vector3lf::cross(const Vector3lf &other) const
{
    Vector3lf result(
        data_[1]*other[2] - data_[2]*other[1],
        data_[2]*other[0] - data_[0]*other[2],
        data_[0]*other[1] - data_[1]*other[0]);
    return result;
}

double Vector3lf::dot(const Vector3lf &other) const
{
    return data_[0]*other[0] + data_[1]*other[1] + data_[2]*other[2];
}

void Vector3lf::normalize()
{
    double l = length();
    data_[0] /= l;
    data_[1] /= l;
    data_[2] /= l;
}

Vector3lf Vector3lf::normalize(const Vector3lf& other)
{
    Vector3lf n(other);
    n.normalize();
    return n;
}

double Vector3lf::length() const
{
    return sqrt(lengthSquared());
}

double Vector3lf::lengthSquared() const
{
    return data_[0]*data_[0] + data_[1]*data_[1] + data_[2]*data_[2];
}

double Vector3lf::cosA(const Vector3lf& other) const
{
    double num = dot(other);
    double den = length()*other.length();
    return num/den;
}

double Vector3lf::angle(const Vector3lf& other) const
{
    return acos( cosA(other) );
}

Vector3lf& Vector3lf::rotate(const Vector3lf& a, double radians)
{
    double s = sin(radians);
    double c = cos(radians);
    Vector3lf tmp;

    tmp[0] = (data_[0]*(a[0]*a[0]*(1-c)+c) + data_[1]*(a[0]*a[1]*(1-c)-a[2]*s) + data_[2]*(a[0]*a[2]*(1-c)+a[1]*s));
    tmp[1] = (data_[0]*(a[1]*a[0]*(1-c)+a[2]*s) + data_[1]*(a[1]*a[1]*(1-c)+c) + data_[2]*(a[1]*a[2]*(1-c)-a[0]*s));
    tmp[2] = (data_[0]*(a[0]*a[2]*(1-c)-a[1]*s) + data_[1]*(a[1]*a[2]*(1-c)+a[0]*s) + data_[2]*(a[2]*a[2]*(1-c)+c));
    *this = tmp;
    return *this;
}

}
