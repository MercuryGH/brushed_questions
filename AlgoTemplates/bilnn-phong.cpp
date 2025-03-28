#include <vector>
#include <algorithm>
using std::vector;

struct Vector3
{
    float x, y, z;
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() : x(0), y(0), z(0) {}

    Vector3 operator-(const Vector3 &v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    Vector3 operator+(const Vector3 &v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    Vector3 operator*(const float k) const // 标量乘
    {
        return Vector3(x * k, y * k, z * k);
    }
    Vector3 operator/(const float k) const // 标量除
    {
        return Vector3(x / k, y / k, z / k);
    }
    Vector3 operator+=(const Vector3 &v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    friend Vector3 operator*(const float k, const Vector3 &v) // 还是标量乘
    {
        return Vector3(v.x * k, v.y * k, v.z * k);
    }
    float dot(const Vector3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    float sqrDis() const
    {
        return this->dot(*this);
    }
    Vector3 cwiseProduct(const Vector3 &v) const // 标量乘
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }
    float normalizedDot(const Vector3 &v) const // 单位化后点积（懒得实现）
    {
        return 0;
    }
    Vector3 normalized() const // 单位化
    {
        return Vector3(0, 0, 0);
    }
};

struct FSPayload
{
    Vector3 color;  // 被着色的点的颜色向量（用于漫反射）
    Vector3 point;  // 被着色的点的坐标
    Vector3 normal; // 法线方向
};

struct Light
{
    Vector3 position;
    Vector3 intensity;
};

Vector3 blinnPhongShader(FSPayload payload)
{
    // Vector3 ka(0.005, 0.005, 0.005); // 环境光
    const float ka = 0.005;
    Vector3 kd = payload.color; // 漫反射
    // Vector3 ks(0.8, 0.8, 0.8); // 镜面反射
    const float ks = 0.8;

    Light l1 = Light{{20, 20, 20}, {500, 500, 500}};
    Light l2 = Light{{-20, 20, 20}, {500, 500, 500}};
    vector<Light> lights = {l1, l2};

    Vector3 viewPos(0, 0, 10); // 摄像机的坐标

    Vector3 ambientLightIntensity(10, 10, 10); // L_a

    const float p = 150;

    Vector3 result;
    for (const auto &light : lights)
    {
        const Vector3 lightVec = light.position - payload.point; // 入射光线
        const Vector3 viewVec = viewPos - payload.point;         // 相机-反射点向量
        const float rSquare = lightVec.sqrDis();                 // 入射光线的长度的平方

        // ambient
        const Vector3 la = ka * ambientLightIntensity;
        // diffuse
        const Vector3 ld = kd.cwiseProduct(light.intensity / rSquare) * std::max(0.0f, payload.normal.normalizedDot(lightVec));
        // specular
        const Vector3 h = (lightVec + viewVec).normalized();
        const Vector3 ls = ks * (light.intensity / rSquare) * std::pow(std::max(0.0f, payload.normal.normalizedDot(h)), p);

        result += (la + ld + ls);
    }
    return result;
}