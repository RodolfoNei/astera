// TODO Collision Layers, GJK & SAT, Broadphase, Capsules
// Forked from RandyGaul/cute_headers/cute_c2.h

#if !defined ASTERA_COL_H
#define ASTERA_COL_H

#include <astera/linmath.h>
#include <stdint.h>

#if !defined(ASTERA_COL_SKIN_WIDTH)
#define ASTERA_COL_SKIN_WIDTH 0.001f
#endif

typedef struct {
  vec2 min, max;
} c_aabb;

typedef struct {
  vec2  center;
  float radius;
} c_circle;

// NOTE: direction vector should be normalized
typedef struct {
  vec2  center, direction;
  float distance;
} c_ray;

typedef enum {
  C_NONE,
  C_AABB,
  C_CIRCLE,
  C_RAY,
} c_types;

typedef struct {
  c_ray ray;

  float distance;
  vec2  normal, point;
} c_raycast;

typedef struct {
  vec2  point, direction;
  float distance;
} c_manifold;

/* Create a ray
 * NOTE: this will normalize the direction if the length is greater
 *       than 1
 * center - the point/center to cast from direction
 * direction - the direction of the ray
 * distance - the max distance of the ray
 * returns: ray structure, 0 length = fail */
c_ray c_ray_create(vec2 center, vec2 direction, float distance);

/* Create an AABB (Axis Aligned Bounding Box)
 * center - the center of the aabb
 * halfsize - the size / 2
 * returns: aabb structure */
c_aabb c_aabb_create(vec2 center, vec2 halfsize);

/* Move an AABB by distance
 * aabb - the AABB to move
 * distance - the distance to move the aabb */
void c_aabb_move(c_aabb* aabb, vec2 distance);

/* Move a circle by distance
 * circle - the circle to move
 * distance - the distance to move the circle*/
void c_circle_move(c_circle* circle, vec2 distance);

/* Get the size of an AABB
 * dst - the destination to store the size
 * aabb - the aabb to get size of */
void c_aabb_get_size(vec2 dst, c_aabb aabb);

/* Create a Circle
 * center - the center of the circle
 * radius - the radius of the circle
 * returns: circle structure */
c_circle c_circle_create(vec2 center, float radius);

/* Test a ray vs aabb
 * ray - the ray to test
 * b - the aabb to test
 * out - the raycast output
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_ray_vs_aabb(c_ray ray, c_aabb b, c_raycast* out);

/* Test a ray vs circle
 * ray - the ray to test
 * b - the circle to test
 * out - the raycast output
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_ray_vs_circle(c_ray ray, c_circle b, c_raycast* out);

/* Test an AABB vs AABB
 * a - the first aabb to test
 * b - the second aabb to test
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_aabb_vs_aabb(c_aabb a, c_aabb b);

/* Test an AABB vs point
 * a - the aabb to test
 * point - the point to check
 * returns: 1 = intersecting, 0 = not */
uint8_t c_aabb_vs_point(c_aabb a, vec2 point);

/* Test an aabb vs a circle
 * a - the aabb
 * b - the circle
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_aabb_vs_circle(c_aabb a, c_circle b);

/* Test a circle vs a point
 * a - the circle
 * point - the point
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_circle_vs_point(c_circle a, vec2 point);

/* Test a circle vs a circle
 * a - the first circle
 * b - the second circle
 * returns: 1 = colliding, 0 = not colliding */
uint8_t c_circle_vs_circle(c_circle a, c_circle b);

/* Test collision of AABB vs AABB
 * a - the 1st aabb
 * b - the 2nd aabb
 * returns: manifold, 0 length = fail/not colliding */
c_manifold c_aabb_vs_aabb_man(c_aabb a, c_aabb b);

/* Test collision of AABB vs Circle (aabb resolves)
 * a - the AABB
 * b - the Circle
 * returns: manifold, 0 length = fail/not colliding */
c_manifold c_aabb_vs_circle_man(c_aabb a, c_circle b);

/* Test collision of circle vs circle
 * a - the 1st circle
 * b - the 2nd circle
 * returns: manifold, 0 length = fail/not colliding */
c_manifold c_circle_vs_circle_man(c_circle a, c_circle b);

/* Test collision of circle vs aabb (circle resolves)
 * a - the circle
 * b - the aabb
 * returns: manifold, 0 length = fail/not colliding */
c_manifold c_circle_vs_aabb_man(c_circle a, c_aabb b);

// NOTE: Doesn't support rays/raycasts
/* Test 2 Collider types
 * a - 1st collider
 * a_type - the 1st collider type
 * b - 2nd collider
 * b_type - the 2nd collider type */
c_manifold c_test(void* a, c_types a_type, void* b, c_types b_type);

#endif
