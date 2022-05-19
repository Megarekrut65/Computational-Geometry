#pragma once

namespace drawer{
    class Normalizer {
    private:
        float height;
        float width;
        int zoom;
    public:
        Normalizer(float height, float width, int zoom);

        Normalizer();

        float normalize_x(float x);
        float normalize_y(float y);
        float normalize_length(float length);
    };
}


