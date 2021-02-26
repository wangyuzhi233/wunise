#pragma once
#ifndef __WUNISE__H__
#define __WUNISE__H__


//#define __my_max(a,b)            (((a) > (b)) ? (a) : (b))
//#define __my_min(a,b)            (((a) < (b)) ? (a) : (b))
namespace wunise {
	
	////Vector4
	//class Vector4 {
	//public:
	//	Vector4(const float &_x = 0.f, const float& _y = 0.f, const float& _z = 0.f, const float& _w = 0.f) 
	//	{
	//		m128 = _mm_set_ps(_w, _z, _y, _x);
	//	}
	//	Vector4(const Vector4& other) { m128 = other.m128; }
	//	Vector4& operator =(const Vector4& other) { m128 = other.m128; return *this; }
	//	Vector4(Vector4&& other) noexcept { m128 = other.m128; other.m128 = _mm_set_ps(0.f, 0.f, 0.f, 0.f); }
	//	Vector4& operator =(Vector4&& other) noexcept { m128 = other.m128; other.m128 = _mm_set_ps(0.f, 0.f, 0.f, 0.f); return *this; }


	//	void Set(float newX, float newY, float newZ, float newW) {
	//		m128 = _mm_set_ps(newW, newZ, newY, newX);
	//	}

	//	bool Equals(const Vector4&other) const {
	//		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	//	}

	//	std::string ToString() const {
	//		return std::string("(") +
	//			std::to_string(x) + std::string(", ") +
	//			std::to_string(y) + std::string(", ") +
	//			std::to_string(z) + std::string(", ") +
	//			std::to_string(w) + std::string(")");
	//	}
	//	static Vector4 Min(const Vector4& a, const Vector4& b) {	
	//		return Vector4(__my_min(a.x, b.x), __my_min(a.y, b.y), __my_min(a.z, b.z), __my_min(a.w, b.w));
	//	}
	//	static Vector4 Max(const Vector4& a, const Vector4& b) {
	//		return Vector4(__my_max(a.x, b.x), __my_max(a.y, b.y), __my_max(a.z, b.z), __my_max(a.w, b.w));
	//	}
	//	
	//	union {
	//		__m128 m128;
	//		struct { float x, y, z, w; };
	//	};
	//};
	//inline Vector4 operator +(const Vector4& a, const Vector4& b) { return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	//inline Vector4 operator -(const Vector4& a, const Vector4& b) { return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	//inline Vector4 operator *(const float& a, const Vector4& b) { return Vector4(a * b.x, a * b.y, a * b.z, a * b.w); }
	//inline Vector4 operator *(const Vector4& a, const float& b) { return Vector4(a.x * b, a.y * b, a.z * b, a.w * b); }
	//inline Vector4 operator /(const Vector4& a, const float& b) { return Vector4(a.x / b, a.y / b, a.z / b, a.w / b); }
	//inline bool operator ==(const Vector4& lhs, const Vector4& rhs) { return lhs.Equals(rhs); }
	//inline bool operator !=(const Vector4& lhs, const Vector4& rhs) { return !lhs.Equals(rhs); }
	////Color
	//class Color {
	//public:

	//};
	//
	////Mesh
	//class Mesh {

	//};
}

#endif // !__WUNISE__H__
