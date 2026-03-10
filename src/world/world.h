#include "../math/vec3.h"

const Vec3 EARTH_POSITION = Vec3(0, 0, 0),
           MOON_POSITION = Vec3(10.0f, 0, 0),
           SHIP_POSITION = Vec3(-10.0, 0, 0);

const float EARTH_RADIUS = 5.0f, EARTH_GRAVITY = 50.0f,
            MOON_RADIUS = 3.0f, MOON_GRAVITY = 8.0f;

const Vec3 SHIP_CAMERA_OFFSET = Vec3(0.0f, 3.0f, 8.0f);

const float SHIP_THRUST_POWER = 20.0f,
            SHIP_MASS = 1.0f;

const Vec3 CAMERA_POSITION = Vec3(0, 0, 30),
           CAMERA_TARGET = Vec3(0, 0, 0),
           CAMERA_UP = Vec3(0, 1, 0);
