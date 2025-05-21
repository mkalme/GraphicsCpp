#include "../../../Header/Scene/Sky/SkyBox.h"
#include "../../../Header/External/stb_image.h"
#include "../../../Header/Math/Rotation.h"

SkyBox::SkyBox() = default;
SkyBox::SkyBox(ImageBuffer* buffer, double offset) {
    Buffer = buffer;
	Offset = offset;
}

Vec3f SkyBox::GetColor(Vec3f direction) {
    double u, v;
    GetUv(direction, u, v);

    u = (u + 1) / 2;
    u += Offset;
    u -= (int)u;

    u = fmin(1.0, u);
    u = fmax(0, u);

    v = fmin(1, v);
    v = fmax(0, v);

    int x = u * Buffer->GetWidth(), y = v * Buffer->GetHeight();
    x = fmin(x, Buffer->GetWidth() - 1);
    y = fmin(y, Buffer->GetHeight() - 1);

    Vec3f color = Buffer->GetPixel(x, y);

    if (FogEnabled && direction.Y >= 0 && direction.Y <= 0.01) {
        double intensity = 1 - direction.Y / 0.01;

        color = color * (1 - intensity) + FogColor * intensity;
    }

    return color.Clamp(0, 1);
}

void SkyBox::GetUv(Vec3f n, double& u, double& v) {
	u = atan2(n.X, -n.Z) / Rotation::PI();
	v = atan2(sqrt(n.X * n.X + n.Z * n.Z), n.Y) / Rotation::PI();
}