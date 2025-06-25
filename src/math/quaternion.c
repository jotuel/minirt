#include "../../include/minirt.h"

void set_quaternion(float w, t_vec3 v, t_quat *q)
{
    q->w = w;
    q->v = v;
}

float quat_norm(t_quat q)
{
    return sqrtf(q.w * q.w + q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z);
}

t_quat quat_normalize(t_quat q)
{
    const float norm = quat_norm(q);

    if (norm == 0.0f)
        return (t_quat){.w = 1.f, .v = (t_vec3){0.f, 0.f, 0.f}};
    return (t_quat){.w = q.w / norm, .v = (t_vec3){q.v.x / norm, q.v.y / norm, q.v.z / norm}};
}

t_vec3 quat_rot(t_quat q, t_vec3 v)
{
    float const ww = powf(q.w, 2);
    float const xx = powf(q.v.x, 2);
    float const yy = powf(q.v.y, 2);
    float const zz = powf(q.v.z, 2);
    float const wx = q.w * q.v.x;
    float const wy = q.w * q.v.y;
    float const wz = q.w * q.v.z;
    float const xy = q.v.x * q.v.y;
    float const xz = q.v.x * q.v.z;
    float const yz = q.v.y * q.v.z;

    return ((t_vec3){.x = ww * v.x + 2 * wy * v.z - 2 * wz * v.y +
        xx * v.x + 2 * wx * v.y + 2 * xy * v.z,
        .y = 2 * wz * v.x - ww * v.y + 2 * wy * v.z +
        yy * v.y + 2 * wy * v.x + 2 * yz * v.z,
        .z = 2 * wy * v.x - 2 * wz * v.y + ww * v.z +
        zz * v.z + 2 * xz * v.x + 2 * yz * v.y});
}

t_quat to_quaternion(t_vec3 v)
{
    const float cy = cosf(v.x * .5f);
    const float sy = sinf(v.x * .5f);
    const float cz = cosf(v.y * .5f);
    const float sz = sinf(v.y * .5f);
    const float cw = cosf(v.z * .5f);
    const float sw = sinf(v.z * .5f);
    const float x = sy * cz * sw - cy * sz * cw;
    const float y = cy * sz * sw + sy * cz * cw;
    const float z = cy * cz * sw - sy * sz * cw;
    const float w = cy * cz * cw + sy * sz * sw;

    return (t_quat){.w = w, .v = (t_vec3){x, y, z}};
}
