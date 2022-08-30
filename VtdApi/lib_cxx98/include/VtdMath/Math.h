
#ifndef VTDFRAMEWORK_MATH_H
#define VTDFRAMEWORK_MATH_H

#include <cmath>

namespace VTD {

    const double M_PI_180 = M_PI / 180.0;
    const double M_180_PI = 180.0 / M_PI;

    /**
    * function to normalize an angle in the range [0, 2pi]
    * @param angle in radians
    * @return
    */
    template <typename T>
    T normalizeAngleRad2Pi(T angle) {
        while (angle > 2.0*M_PI) {
            angle -= 2.0*M_PI;
        }
        while (angle < 0.0) {
            angle += 2.0*M_PI;
        }
        return angle;
    }

    /**
    * function to normalize an angle in the range [-pi, pi]
    * @param angle in radians
    * @return
    */
    template <typename T>
    T normalizeAngleRad(T angle) {
        while(angle > M_PI) {
            angle -= 2.0*M_PI;
        }
        while(angle < -M_PI) {
            angle += 2.0*M_PI;
        }
        return angle;
    }

    /**
    * calculate the distance between
    * two angles normalized in the range [0, 2pi]
    * @param a
    * @param b
    * @return
    */
    template <typename T>
    T wraparoundDistance(T a, T b) {
        T min = std::min(a,b);
        T max = std::max(a,b);

        T dist1 = max - min;
        T dist2 = normalizeAngleRad(min-max);

        return std::min(dist1, dist2);
    }

    /**
    * calculate the distance between
    * two angles normalized in the range [0, 2pi]
    * @param a
    * @param b
    * @return
    */
    template <typename T>
    T wraparoundDistance2Pi(T a, T b) {
        T min = std::min(a,b);
        T max = std::max(a,b);

        T dist1 = max - min;
        T dist2 = normalizeAngleRad2Pi(min-max);

        return std::min(dist1, dist2);
    }

    /**
     * convert degrees to radians
     * @param degrees
     * @return
     */
    template<typename T>
    T deg2rad(T degrees) {
        return degrees * static_cast<T>(M_PI_180);
    }

    /**
     * convert radians to degrees
     * @param radians
     * @return
     */
    template<typename T>
    T rad2deg(T radians) {
        return radians * static_cast<T>(M_180_PI);
    }

    /**
     * convert radians to degrees
     * @param a
     * @param b
     * @param epsilon
     * @return
     */
    template<typename T>
    bool almostEqual(T a, T b, T epsilon)
    {
        return abs(a-b) < epsilon;
    }

    bool
    almostEqual(float a, float b, float epsilon = 0.0000001f)
    {
        return almostEqual<float>(a,b,epsilon);
    }

} //namespace VTD

#endif //VTDFRAMEWORK_MATH_H
