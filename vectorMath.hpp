#pragma once
#define VECTORMATH_H

#include "raylib.h"
#include "math.h"

inline float distanceBetween(Vector2& a, Vector2& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

inline Vector2 subtract(Vector2& a, Vector2& b) {
    return Vector2{a.x - b.x, a.y - b.y};
}

inline float getLength(Vector2& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

inline Vector2 normalize(Vector2& vec) {
    float length = getLength(vec);
    return Vector2{vec.x / length, vec.y / length};
}