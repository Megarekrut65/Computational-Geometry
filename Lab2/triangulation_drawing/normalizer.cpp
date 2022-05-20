#include "normalizer.h"


namespace drawer {

    float Normalizer::normalize_x(float x) {
        return x * zoom + width / 2.0f;
    }

    float Normalizer::normalize_y(float y) {
        return -y * zoom + height / 2.0f;
    }

    float Normalizer::normalize_length(float length) {
        return length * zoom;
    }

    Normalizer::Normalizer(float height, float width, int zoom) : height(height), width(width), zoom(zoom) {}

    Normalizer::Normalizer() : height(0), width(0), zoom(0) {}
}
