#include "Matrix4x4.hpp"
#include "Math.hpp"

namespace wfe {
	Matrix4x4::Matrix4x4() : m00(1.f), m01(0.f), m02(0.f), m03(0.f),
	                         m10(0.f), m11(1.f), m12(0.f), m13(0.f),
	                         m20(0.f), m21(0.f), m22(1.f), m23(0.f),
	                         m30(0.f), m31(0.f), m32(0.f), m33(1.f)  { }
	Matrix4x4::Matrix4x4(float32_t m00, float32_t m01, float32_t m02, float32_t m03, 
	                     float32_t m10, float32_t m11, float32_t m12, float32_t m13, 
	                     float32_t m20, float32_t m21, float32_t m22, float32_t m23,
	                     float32_t m30, float32_t m31, float32_t m32, float32_t m33) : m00(m00), m01(m01), m02(m02), m03(m03),
	                                                                                   m10(m10), m11(m11), m12(m12), m13(m13),
	                                                                                   m20(m20), m21(m21), m22(m22), m23(m23),
	                                                                                   m30(m30), m31(m31), m32(m32), m33(m33)  { }
	Matrix4x4::Matrix4x4(float32_t m00, float32_t m01, float32_t m02, 
	                     float32_t m10, float32_t m11, float32_t m12, 
	                     float32_t m20, float32_t m21, float32_t m22) : m00(m00), m01(m01), m02(m02), m03(0.f),
	                                                                    m10(m10), m11(m11), m12(m12), m13(0.f),
	                                                                    m20(m20), m21(m21), m22(m22), m23(0.f),
	                                                                    m30(0.f), m31(0.f), m32(0.f), m33(1.f)  { }
	Matrix4x4::Matrix4x4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4) : rows{ row1, row2, row3, row4 } { }
	Matrix4x4::Matrix4x4(const Vector3& row1, const Vector3& row2, const Vector3& row3) : rows{ row1, row2, row3, { 0.f, 0.f, 0.f, 1.f } } { }
	Matrix4x4::Matrix4x4(const float32_t data[16]) : m00(data[ 0]), m01(data[ 1]), m02(data[ 2]), m03(data[ 3]),
	                                                 m10(data[ 4]), m11(data[ 5]), m12(data[ 6]), m13(data[ 7]),
	                                                 m20(data[ 8]), m21(data[ 9]), m22(data[10]), m23(data[11]),
	                                                 m30(data[12]), m31(data[13]), m32(data[14]), m33(data[15])  { }
	Matrix4x4::Matrix4x4(const float32_t mat[4][4]) : m00(mat[0][0]), m01(mat[0][1]), m02(mat[0][2]), m03(mat[0][3]),
	                                                  m10(mat[1][0]), m11(mat[1][1]), m12(mat[1][2]), m13(mat[1][3]),
	                                                  m20(mat[2][0]), m21(mat[2][1]), m22(mat[2][2]), m23(mat[2][3]),
	                                                  m30(mat[3][0]), m31(mat[3][1]), m32(mat[3][2]), m33(mat[3][3])  { }
											
	float32_t* Matrix4x4::operator[](size_t index) {
		// Calculate the row's position
		return data + index * 4;
	}
	const float32_t* Matrix4x4::operator[](size_t index) const {
		// Calculate the row's position
		return data + index * 4;
	}

	bool8_t Matrix4x4::operator==(const Matrix4x4& other) const {
		// Compare all of the matrices' values
		return m00 == other.m00 && m01 == other.m01 && m02 == other.m02 && m03 == other.m03 &&
		       m10 == other.m10 && m11 == other.m11 && m12 == other.m12 && m13 == other.m13 &&
		       m20 == other.m20 && m21 == other.m21 && m22 == other.m22 && m23 == other.m23 &&
		       m30 == other.m30 && m31 == other.m31 && m32 == other.m32 && m33 == other.m33;
	}
	bool8_t Matrix4x4::operator!=(const Matrix4x4& other) const {
		// Compare all of the matrices' values
		return m00 != other.m00 || m01 != other.m01 || m02 != other.m02 || m03 != other.m03 ||
		       m10 != other.m10 || m11 != other.m11 || m12 != other.m12 || m13 != other.m13 ||
		       m20 != other.m20 || m21 != other.m21 || m22 != other.m22 || m23 != other.m23 ||
		       m30 != other.m30 || m31 != other.m31 || m32 != other.m32 || m33 != other.m33;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
		// Create an array containing the resulting matrix's data
		float32_t outData[16];

		// Multiply the two matrices
		const float32_t* thisData = data;
		float32_t* outPtr = outData;

		for(size_t i = 0; i != 4; ++i) {
			for(size_t j = 0; j != 4; ++j) {
				// Calculate the current value
				*outPtr = thisData[0] * other.data[j] + thisData[1] * other.data[4 + j] + thisData[2] * other.data[8 + j] + thisData[3] * other.data[12 + j];

				// Increment the out pointer
				++outPtr;
			}

			// Increment this vector's pointer by 4
			thisData += 4;
		}

		return outData;
	}
	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
		// Create an array containing the resulting matrix's new data
		float32_t newData[16];

		// Multiply the two matrices
		const float32_t* thisData = data;
		float32_t* outPtr = newData;

		for(size_t i = 0; i != 4; ++i) {
			for(size_t j = 0; j != 4; ++j) {
				// Calculate the current value
				*outPtr = thisData[0] * other.data[j] + thisData[1] * other.data[4 + j] + thisData[2] * other.data[8 + j] + thisData[3] * other.data[12 + j];

				// Increment the out pointer
				++outPtr;
			}

			// Increment this vector's pointer by 4
			thisData += 4;
		}

		// Set the matrix's new values
		for(size_t i = 0; i != 16; ++i)
			data[i] = newData[i];

		return *this;
	}

	Matrix4x4& Matrix4x4::Invert() {
		// Save the matrix's old data
		float32_t m[16];

		for(size_t i = 0; i != 16; ++i)
			m[i] = data[i];

		// No idea
		float32_t t0 = m[10] * m[15];
		float32_t t1 = m[14] * m[11];
		float32_t t2 = m[6] * m[15];
		float32_t t3 = m[14] * m[7];
		float32_t t4 = m[6] * m[11];
		float32_t t5 = m[10] * m[7];
		float32_t t6 = m[2] * m[15];
		float32_t t7 = m[14] * m[3];
		float32_t t8 = m[2] * m[11];
		float32_t t9 = m[10] * m[3];
		float32_t t10 = m[2] * m[7];
		float32_t t11 = m[6] * m[3];
		float32_t t12 = m[8] * m[13];
		float32_t t13 = m[12] * m[9];
		float32_t t14 = m[4] * m[13];
		float32_t t15 = m[12] * m[5];
		float32_t t16 = m[4] * m[9];
		float32_t t17 = m[8] * m[5];
		float32_t t18 = m[0] * m[13];
		float32_t t19 = m[12] * m[1];
		float32_t t20 = m[0] * m[9];
		float32_t t21 = m[8] * m[1];
		float32_t t22 = m[0] * m[5];
		float32_t t23 = m[4] * m[1];

		float32_t* o = data;

		o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
		o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
		o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
		o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

		float32_t d = 1.f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

		o[0] = d * o[0];
		o[1] = d * o[1];
		o[2] = d * o[2];
		o[3] = d * o[3];
		o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
		o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
		o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
		o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
		o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
		o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
		o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
		o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
		o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
		o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
		o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
		o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

		return *this;
	}
	Matrix4x4 Matrix4x4::Inverse() const {
		// Create the resulting matrix's data
		float32_t o[16];

		// No idea
		const float32_t* m = data;

		float32_t t0 = m[10] * m[15];
		float32_t t1 = m[14] * m[11];
		float32_t t2 = m[6] * m[15];
		float32_t t3 = m[14] * m[7];
		float32_t t4 = m[6] * m[11];
		float32_t t5 = m[10] * m[7];
		float32_t t6 = m[2] * m[15];
		float32_t t7 = m[14] * m[3];
		float32_t t8 = m[2] * m[11];
		float32_t t9 = m[10] * m[3];
		float32_t t10 = m[2] * m[7];
		float32_t t11 = m[6] * m[3];
		float32_t t12 = m[8] * m[13];
		float32_t t13 = m[12] * m[9];
		float32_t t14 = m[4] * m[13];
		float32_t t15 = m[12] * m[5];
		float32_t t16 = m[4] * m[9];
		float32_t t17 = m[8] * m[5];
		float32_t t18 = m[0] * m[13];
		float32_t t19 = m[12] * m[1];
		float32_t t20 = m[0] * m[9];
		float32_t t21 = m[8] * m[1];
		float32_t t22 = m[0] * m[5];
		float32_t t23 = m[4] * m[1];


		o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
		o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
		o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
		o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

		float32_t d = 1.f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

		o[0] = d * o[0];
		o[1] = d * o[1];
		o[2] = d * o[2];
		o[3] = d * o[3];
		o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
		o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
		o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
		o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
		o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
		o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
		o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
		o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
		o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
		o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
		o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
		o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

		return o;
	}
	Matrix4x4& Matrix4x4::Transpose() {
		// Swap every value with its transposed equivalent
		float32_t val = m01;
		m01 = m10;
		m10 = val;

		val = m02;
		m02 = m20;
		m20 = val;

		val = m03;
		m03 = m30;
		m30 = val;

		val = m12;
		m12 = m21;
		m21 = val;

		val = m13;
		m13 = m31;
		m31 = val;

		val = m23;
		m23 = m32;
		m32 = val;

		return *this;
	}
	Matrix4x4 Matrix4x4::Transposed() const {
		// Set the resulting matrix's values
		return { m00, m10, m20, m30,
		         m01, m11, m21, m31,
		         m02, m12, m22, m32,
		         m03, m13, m23, m33 };
	}

	Vector3 Matrix4x4::Forward() const {
		// Set the resulting vector's elements
		Vector3 result{ -m02, -m12, -m22 };

		// Normalize and return the vector
		return result.Normalize();
	}
	Vector3 Matrix4x4::Backward() const {
		// Set the resulting vector's elements
		Vector3 result{ m02, m12, m22 };

		// Normalize and return the vector
		return result.Normalize();
	}
	Vector3 Matrix4x4::Up() const {
		// Set the resulting vector's elements
		Vector3 result{ m01, m11, m21 };

		// Normalize and return the vector
		return result.Normalize();
	}
	Vector3 Matrix4x4::Down() const {
		// Set the resulting vector's elements
		Vector3 result{ -m01, -m11, -m21 };

		// Normalize and return the vector
		return result.Normalize();
	}
	Vector3 Matrix4x4::Left() const {
		// Set the resulting vector's elements
		Vector3 result{ -m00, -m10, -m20 };

		// Normalize and return the vector
		return result.Normalize();
	}
	Vector3 Matrix4x4::Right() const {
		// Set the resulting vector's elements
		Vector3 result{ m00, m10, m20 };

		// Normalize and return the vector
		return result.Normalize();
	}

	Matrix4x4 Matrix4x4::PerspectiveProjection(float32_t fov, float32_t aspectRatio, float32_t nearPlane, float32_t farPlane) {
		// Calculate some values to save processing
		float32_t halfTanFov = Tan(fov * .5f);
		float32_t invFarNear = 1.f / (farPlane - nearPlane);

		// Calculate the resulting matrix's values
		return { 1.f / (aspectRatio * halfTanFov), 0.f,               0.f,                                  0.f,
		         0.f,                              1.f / halfTanFov,  0.f,                                  0.f,
		         0.f,                              0.f,              -farPlane * invFarNear,               -1.f,
		         0.f,                              0.f,              -(nearPlane * farPlane) * invFarNear,  0.f };
	}
	Matrix4x4 Matrix4x4::OrtographicProjection(float32_t left, float32_t right, float32_t bottom, float32_t top, float32_t nearPlane, float32_t farPlane) {
		// Calculate some values to save processing
		float32_t invLeftRight = 1.f / (left - right);
		float32_t invBottomTop = 1.f / (bottom - top);
		float32_t invNearFar = 1.f / (nearPlane - farPlane);

		// Calculate the resulting matrix's values
		return { -2.f * invLeftRight,             0.f,                           0.f,                                 0.f,
		          0.f,                           -2.f * invBottomTop,            0.f,                                 0.f,
		          0.f,                            0.f,                           2.f * invNearFar,                    0.f,
		          (left + right) * invLeftRight,  (top + bottom) * invBottomTop, (farPlane + nearPlane) * invNearFar, 1.f };
	}
	Matrix4x4 Matrix4x4::LookAt(Vector3 position, Vector3 target, Vector3 up) {
		// Calculate all axes using the given vectors
		Vector3 zAxis = target - position;
		zAxis.Normalize();

		Vector3 xAxis = zAxis.Cross(up);
		Vector3 yAxis = xAxis.Cross(zAxis);

		// Calculate the resulting matrix's values
		return {  xAxis.x,              yAxis.x,             -zAxis.x,             0.f,
		          xAxis.y,              yAxis.y,             -zAxis.y,             0.f,
				  xAxis.z,              yAxis.z,             -zAxis.z,             0.f,
		         -xAxis.Dot(position), -yAxis.Dot(position),  zAxis.Dot(position), 1.f };
	}
	Matrix4x4 Matrix4x4::Translation(Vector3 position) {
		// Set the resulting matrix's values
		return { 1.f,        0.f,        0.f,        0.f,
		         0.f,        1.f,        0.f,        0.f,
		         0.f,        0.f,        1.f,        0.f,
		         position.x, position.y, position.z, 1.f };
	}
	Matrix4x4 Matrix4x4::EulerX(float32_t angle) {
		// Calculate the sine and cosine of the given angle
		float32_t sin = Sin(angle), cos = Cos(angle);

		// Calculate the resulting matrix's values
		return { 1.f,  0.f, 0.f,
		         0.f,  cos, sin,
		         0.f, -sin, cos };
	}
	Matrix4x4 Matrix4x4::EulerY(float32_t angle) {
		// Calculate the sine and cosine of the given angle
		float32_t sin = Sin(angle), cos = Cos(angle);

		// Calculate the resulting matrix's values
		return { cos, 0.f, -sin,
		         0.f, 1.f,  0.f,
		         sin, 0.f,  cos };
	}
	Matrix4x4 Matrix4x4::EulerZ(float32_t angle) {
		// Calculate the sine and cosine of the given angle
		float32_t sin = Sin(angle), cos = Cos(angle);

		// Calculate the resulting matrix's values
		return {  cos, sin, 0.f,
		         -sin, cos, 0.f,
		          0.f, 0.f, 1.f };
	}
	Matrix4x4 Matrix4x4::Rotation(Quaternion rotation) {
		// Save the quaternion's elements for convenience
		float32_t x = rotation.x, y = rotation.y, z = rotation.z, w = rotation.w;
		
		// Calculate the resulting matrix's values
		return { 1.f - 2.f * y * y - 2.f * z * z,       2.f * x * y - 2.f * z * w,       2.f * x * z + 2.f * y * w,
		               2.f * x * y + 2.f * z * w, 1.f - 2.f * x * x - 2.f * z * z,       2.f * y * z - 2.f * x * w,
		               2.f * x * z - 2.f * y * w,       2.f * y * z + 2.f * x * w, 1.f - 2.f * x * x - 2.f * y * y };
	}
	Matrix4x4 Matrix4x4::Scaling(Vector3 scale) {
		// Calculate the resulting matrix's values
		return { scale.x, 0.f,     0.f,
		         0.f,     scale.y, 0.f,
		         0.f,     0.f,     scale.z };
	}
	Matrix4x4 Matrix4x4::Transform(Vector3 position, Quaternion rotation, Vector3 scale) {
		// Multiply the matrices of each transform
		return Scaling(scale) * Rotation(rotation) * Translation(position);
	}

	Vector2 operator*(const Matrix4x4& mat, const Vector2& vec) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 + mat.m30, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 + mat.m31 };
	}
	Vector2 operator*(const Vector2& vec, const Matrix4x4& mat) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 + mat.m30, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 + mat.m31 };
	}
	Vector3 operator*(const Matrix4x4& mat, const Vector3& vec) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 * vec.z + mat.m30, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 * vec.z + mat.m31,
		         mat.m02 * vec.x + mat.m12 * vec.y + mat.m22 * vec.z + mat.m32 };
	}
	Vector3 operator*(const Vector3& vec, const Matrix4x4& mat) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 * vec.z + mat.m30, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 * vec.z + mat.m31,
		         mat.m02 * vec.x + mat.m12 * vec.y + mat.m22 * vec.z + mat.m32 };
	}
	Vector4 operator*(const Matrix4x4& mat, const Vector4& vec) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 * vec.z + mat.m30 * vec.w, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 * vec.z + mat.m31 * vec.w,
		         mat.m02 * vec.x + mat.m12 * vec.y + mat.m22 * vec.z + mat.m32 * vec.w,
		         mat.m03 * vec.x + mat.m13 * vec.y + mat.m23 * vec.z + mat.m33 * vec.w };
	}
	Vector4 operator*(const Vector4& vec, const Matrix4x4& mat) {
		// Calculate the resulting vector's elements
		return { mat.m00 * vec.x + mat.m10 * vec.y + mat.m20 * vec.z + mat.m30 * vec.w, 
		         mat.m01 * vec.x + mat.m11 * vec.y + mat.m21 * vec.z + mat.m31 * vec.w,
		         mat.m02 * vec.x + mat.m12 * vec.y + mat.m22 * vec.z + mat.m32 * vec.w,
		         mat.m03 * vec.x + mat.m13 * vec.y + mat.m23 * vec.z + mat.m33 * vec.w };
	}
}