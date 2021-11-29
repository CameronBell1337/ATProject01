#include <math.h>



constexpr float _pi = 3.14159265358979f;
constexpr double PI_D = 3.1415926535897932;


/// <summary>
/// Multiplies x by x
/// </summary>
/// <param name="x"> The value to be multiplied.</param>
/// <returns> the square of x.</returns>
template <typename T>
constexpr auto sqr(const T& x)
{
	return x * x;
}

/// <summary>
/// Linearly interpolates between a and b by t
/// </summary>
/// <param name="a">Is the start value.</param>
/// <param name="b">Is the end Value.</param>
/// <param name="t">Is the interpolation value between the two floats.</param>
/// <returns> The interpolated float result between the two float values.</returns>
template <typename T>
constexpr T lerp(const T& a, const T& b, float t)
{
	//https://lunarlabs.pt/blog/post/the_art_of_lerp
	return a + (b - a) * t;
}


template<typename T>
T wrap_angle(T theta)
{
	const T modded = fmod(theta, (T)2.0 * (T)PI_D);
	return (modded > (T)PI_D) ?
		(modded - (T)2.0 * (T)PI_D) :
		modded;
}

/// <summary>
/// degree to radians conversion
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="a">degree value</param>
/// <returns>returns the value of radians from specififed degree</returns>
template <typename T>
constexpr T deg2Rad(T a)
{
	return a * _pi / (T)180.0;
}

