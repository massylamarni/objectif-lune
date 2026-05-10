#include "../math/vec2.h"
#include "../math/vec3.h"

#define EARTH_ID 0
#define MOON_ID 1
#define SUN_ID 2
#define RIGID_BODY_ID 3
#define EARTH_ID_RES "earth"
#define MOON_ID_RES "moon"
#define SUN_ID_RES "sun"
#define RIGIDBODY_ID_RES "rigidbody"

#define EARTH_POSITION Vec3(-9500.0f, 0, 0)
#define EARTH_RADIUS 300.0f
#define EARTH_MASS 1.0f

#define MOON_POSITION Vec3(0, 0, 0)
#define MOON_RADIUS 300.0f
#define MOON_MASS 100000.0f

#define SUN_POSITION Vec3(-4000.0f, 1000, 7500.0f)
#define SUN_RADIUS 100.0f
#define SUN_MASS 1.0f
#define ALT_SUN_POSITION Vec3(-4000.0f, 3000, 7500.0f)

#define SHIP_POSITION Vec3(0, 0, 1000.0f)
#define SHIP_CAMERA_OFFSET Vec3(0.0f, 3.0f, 8.0f)
#define SHIP_THRUST_POWER 15.0f
#define SHIP_MASS 1.0f
#define SHIP_RADIUS 0.5f
#define SHIP_MAX_SPEED 50.0f

#define CAMERA_POSITION Vec3(0, 0, 30)
#define CAMERA_TARGET Vec3(0, 0, 0)
#define CAMERA_UP Vec3(0, 1, 0)

static const char ID_MAPPING[8][32] = {
  "earth", "moon", "sun", "rigidbody"
};

#define INPUT_VEC3_UPDATE_VALUE 0.1
#define MOUSE_SENSITIVITY 0.005f // radians per pixel

