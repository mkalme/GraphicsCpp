#include "../../../../Header/Scene/Surface/Uv/TexturedUvSurface.h"
#include "../../../../Header/External/stb_image.h"

TexturedUvSurface::TexturedUvSurface() = default;
TexturedUvSurface::TexturedUvSurface(ImageBuffer* buffer, double offset, SurfaceResult defaultSurface) {
    Buffer = buffer;
    Offset = offset;
    DefaultSurface = defaultSurface;
}

SurfaceResult TexturedUvSurface::GetSurface(double u, double v) {
    u = (u + 1) / 2;
    u += Offset;
    u -= (int)u;
    u = 1 - u;

    u = fmin(1, u);
    u = fmax(0, u);

    v = fmin(1, v);
    v = fmax(0, v);

    int x = u * Buffer->GetWidth(), y = v * Buffer->GetHeight();
    x = fmin(x, Buffer->GetWidth() - 1);
    y = fmin(y, Buffer->GetHeight() - 1);

    Vec3f color = Buffer->GetPixel(x, y);
    SurfaceResult output = DefaultSurface;
    output.Color = color;

    return output;
}