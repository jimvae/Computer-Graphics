//============================================================
// STUDENT NAME: Jim Vincent Andes Engay
// STUDENT NO.: A0206031B
// NUS EMAIL ADDRESS: e0425954@u.nus.edu
// COMMENTS TO GRADER: 
// 
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    double a = 1;
    double b = 2 * dot(r.direction(), r.origin() - center);
    double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
    double discriminant = (b * b) - (4 * a * c);
    double t0;
    if (discriminant < 0) {
        return false;
    } else if (discriminant == 0) {
        t0 = -b / (2 * a);
    } else {
        double t1 = (-b + sqrt(discriminant)) / (2 * a);
        double t2 = (-b - sqrt(discriminant)) / (2 * a);
        if (t1 < 0 || t2 < 0) return false;
        else if (t1 > 0 && t2 < 0 ) t0 = t1; // only t1 is positive
        else if (t1 < 0 && t2 > 0 ) t0 = t2; // only t2 is positive
        else if (t1 - t2 > 0) t0 = t2; // t1 > t2
        else t0 = t1; // t1 < t2
    }
    
    if (t0 >= tmin && t0 <= tmax )
    {
        // We have a hit -- populat hit record.
        rec.t = t0;
        rec.p = r.pointAtParam(t0);
        rec.normal = rec.p - center;
        rec.mat_ptr = matp;
        return true;
    }
    return false; // You can remove/change this if needed.
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************

    double a = 1;
    double b = 2 * dot(r.direction(), r.origin() - center);
    double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
    double discriminant = (b * b) - (4 * a * c);
    double t0;

    if (discriminant < 0) {
        return false;
    } else if (discriminant == 0) {
        t0 = -b / (2 * a);
    } else {
        double t1 = (-b + sqrt(discriminant)) / (2 * a);
        double t2 = (-b - sqrt(discriminant)) / (2 * a);
        if (t1 < 0 || t2 < 0) return false;
        else if (t1 > 0 && t2 < 0 ) t0 = t1; // only t1 is positive
        else if (t1 < 0 && t2 > 0 ) t0 = t2; // only t2 is positive
        else if (t1 - t2 > 0) t0 = t2; // t1 > t2
        else t0 = t1; // t1 < t2
    }
    
    return t0 >= tmin && t0 <= tmax;
}
