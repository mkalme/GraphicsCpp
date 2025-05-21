#include "../../Header/Math/Ray.h"

Ray::Ray(Vec3f origin, Vec3f direction) {
	Origin = origin;
	Direction = direction;
}

Ray::Ray() = default;