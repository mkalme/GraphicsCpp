#pragma once
#include <corecrt_math.h>

class MathUtilities
{
public:
	static double NegMod(double a, double b) {
		double r = a - (int)(a / b) * b;
		return r < 0 ? r + b : r;
	}

    static double DivideNeg(double a, double b) {
        double n = (int)(a / b);
        return a < 0 ? n - 1 : n;
    }

    static bool DetermineRoot(double a, double b, double c, double& t) {
        t = -1;

        double d = b * b - 4 * a * c;
        if (d < 0) return false;

        double sqrtD = sqrt(d);

        double t0 = (-b + sqrtD) / (2 * a);
        double t1 = (-b - sqrtD) / (2 * a);

        if (t1 < 0) t = t0;
        else if (t0 < 0) t = t1;
        else t = t1 < t0 ? t1 : t0;

        return true;
    }
    static bool DetermineRoot(double a, double b, double c, double& t0, double& t1) {
        t0 = -1;
        t1 = -1;

        double d = b * b - 4 * a * c;
        if (d < 0) return false;

        double sqrtD = sqrt(d);

        t0 = (-b + sqrtD) / (2 * a);
        t1 = (-b - sqrtD) / (2 * a);

        return true;
    }
};