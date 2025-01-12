#include "types.h"
#include "math.h"
#include "Plane.h"
#include "Camera.h"
#include "Matrix3f.h"
#include "stl/math.h"
#include "Collision.h"
#include "BoundBox.h"
#include "KMath.h"

/*
 * --INFO--
 * Address: ........
 * Size:    00009C
 */
static void _Error(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    0000F0
 */
static void _Print(char*, ...)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    0000C0
 */
bool Plane::equal(Plane&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    000148
 */
void Plane::calcRadScale()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    000074
 */
void Plane::reflect(Vector3f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    00006C
 */
void Plane::reflectVector(Vector3f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    000078
 */
void Plane::bounceVector(Vector3f&, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    000084
 */
void Plane::frictionVector(Vector3f&, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: 8003756C
 * Size:    0000A0
 */
void CullingPlane::CheckMinMaxDir()
{
	if (mPlane.mNormal.x < 0.0f) {
		_10 = 3;
		_1C = 0;
	} else {
		_10 = 0;
		_1C = 3;
	}

	if (mPlane.mNormal.y < 0.0f) {
		_14 = 4;
		_20 = 1;
	} else {
		_14 = 1;
		_20 = 4;
	}

	if (mPlane.mNormal.z < 0.0f) {
		_18 = 5;
		_24 = 2;
	} else {
		_18 = 2;
		_24 = 5;
	}
}

/*
 * --INFO--
 * Address: ........
 * Size:    0000AC
 */
void Vector3f::rotateTranspose(Matrix4f&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: 8003760C
 * Size:    0000AC
 */
void Vector3f::rotate(Matrix4f& mtx)
{
	Vector3f vec;
	vec.x = mtx.mMtx[0][0] * x + mtx.mMtx[0][1] * y + mtx.mMtx[0][2] * z;
	vec.y = mtx.mMtx[1][0] * x + mtx.mMtx[1][1] * y + mtx.mMtx[1][2] * z;
	vec.z = mtx.mMtx[2][0] * x + mtx.mMtx[2][1] * y + mtx.mMtx[2][2] * z;

	*this = vec;
}

/*
 * --INFO--
 * Address: 800376B8
 * Size:    000094
 */
void Vector3f::rotateTo(Matrix4f& mtx, Vector3f& outVec)
{
	outVec.x = mtx.mMtx[0][0] * x + mtx.mMtx[0][1] * y + mtx.mMtx[0][2] * z;
	outVec.y = mtx.mMtx[1][0] * x + mtx.mMtx[1][1] * y + mtx.mMtx[1][2] * z;
	outVec.z = mtx.mMtx[2][0] * x + mtx.mMtx[2][1] * y + mtx.mMtx[2][2] * z;
}

/*
 * --INFO--
 * Address: 8003774C
 * Size:    0000C4
 */
void Vector3f::multMatrix(Matrix4f& mtx)
{
	Vector3f vec;
	vec.x = mtx.mMtx[0][0] * x + mtx.mMtx[0][1] * y + mtx.mMtx[0][2] * z + mtx.mMtx[0][3];
	vec.y = mtx.mMtx[1][0] * x + mtx.mMtx[1][1] * y + mtx.mMtx[1][2] * z + mtx.mMtx[1][3];
	vec.z = mtx.mMtx[2][0] * x + mtx.mMtx[2][1] * y + mtx.mMtx[2][2] * z + mtx.mMtx[2][3];
	*this = vec;
}

/*
 * --INFO--
 * Address: 80037810
 * Size:    0000AC
 */
void Vector3f::multMatrixTo(Matrix4f& mtx, Vector3f& outVec)
{
	outVec.x = mtx.mMtx[0][0] * x + mtx.mMtx[0][1] * y + mtx.mMtx[0][2] * z + mtx.mMtx[0][3];
	outVec.y = mtx.mMtx[1][0] * x + mtx.mMtx[1][1] * y + mtx.mMtx[1][2] * z + mtx.mMtx[1][3];
	outVec.z = mtx.mMtx[2][0] * x + mtx.mMtx[2][1] * y + mtx.mMtx[2][2] * z + mtx.mMtx[2][3];
}

/*
 * --INFO--
 * Address: ........
 * Size:    000110
 */
void Vector3f::rotate(Quat&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: ........
 * Size:    000104
 */
void Vector3f::rotateInverse(Quat&)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: 800378BC
 * Size:    0004E4
 */
void Quat::fromMat3f(Matrix3f& mtx)
{
	f32 diag = mtx.mMtx[0] + mtx.mMtx[4] + mtx.mMtx[8];
	f32 a    = 0.25f * (1.0f + diag);                  // f4
	f32 b    = a - 0.5f * (mtx.mMtx[4] + mtx.mMtx[8]); // f2, f5
	f32 c    = a - 0.5f * (mtx.mMtx[8] + mtx.mMtx[0]); // f6
	f32 d    = a - 0.5f * (mtx.mMtx[0] + mtx.mMtx[4]); // f7

	int type;
	if (a > b) {
		if (a > c) {
			if (a > d) {
				type = 0;
			} else {
				type = 3;
			}
		} else if (c > d) {
			type = 2;
		} else {
			type = 3;
		}
	} else if (b > c) {
		if (b > d) {
			type = 1;
		} else {
			type = 3;
		}
	} else if (c > d) {
		type = 2;
	} else {
		type = 3;
	}

	switch (type) {
	case 0: {
		s     = std::sqrtf(a);
		f32 t = 1.0f / s;
		v.x   = t * (mtx.mMtx[7] - mtx.mMtx[5]);
		v.y   = t * (mtx.mMtx[2] - mtx.mMtx[6]);
		v.z   = t * (mtx.mMtx[3] - mtx.mMtx[1]);
	} break;
	case 1: {
		v.x   = std::sqrtf(b);
		f32 t = 1.0f / v.x;
		s     = t * (mtx.mMtx[7] - mtx.mMtx[5]);
		v.y   = t * (mtx.mMtx[1] + mtx.mMtx[3]);
		v.z   = t * (mtx.mMtx[2] + mtx.mMtx[6]);
	} break;
	case 2: {
		v.y   = std::sqrtf(c);
		f32 t = 1.0f / v.y;
		s     = t * (mtx.mMtx[2] - mtx.mMtx[6]);
		v.z   = t * (mtx.mMtx[5] + mtx.mMtx[7]);
		v.x   = t * (mtx.mMtx[3] + mtx.mMtx[1]);
	} break;
	case 3: {
		v.z   = std::sqrtf(d);
		f32 t = 1.0f / v.z;
		s     = t * (mtx.mMtx[3] - mtx.mMtx[1]);
		v.x   = t * (mtx.mMtx[6] + mtx.mMtx[2]);
		v.y   = t * (mtx.mMtx[7] + mtx.mMtx[5]);
	} break;
	}

	if (s < 0.0f) {
		s   = -s;
		v.x = -v.x;
		v.y = -v.y;
		v.z = -v.z;
	}

	f32 n = 1.0f / std::sqrtf(SQUARE(s) + SQUARE(v.x) + SQUARE(v.y) + SQUARE(v.z));

	s *= n;
	v.x *= n;
	v.y *= n;
	v.z *= n;
}

/*
 * --INFO--
 * Address: 80037DA0
 * Size:    0000A4
 */
void Quat::rotate(Vector3f& axis, f32 angle)
{
	f32 theta  = 0.5f * angle;
	f32 sinVal = sinf(theta);
	f32 cosVal = cosf(theta);

	Quat quat(axis.x * sinVal, axis.y * sinVal, axis.z * sinVal, cosVal);

	multiply(quat);
}

/*
 * --INFO--
 * Address: 80037E44
 * Size:    0000EC
 */
void Quat::multiply(Quat& other)
{
	Quat tmp;
	tmp.s   = other.s * s - other.v.x * v.x - other.v.y * v.y - other.v.z * v.z;
	tmp.v.x = (other.v.y * v.z + (other.s * v.x + other.v.x * s)) - other.v.z * v.y;
	tmp.v.y = (other.v.z * v.x + (other.s * v.y + other.v.y * s)) - other.v.x * v.z;
	tmp.v.z = (other.v.x * v.y + (other.s * v.z + other.v.z * s)) - other.v.y * v.x;
	*this   = tmp;
}

/*
 * --INFO--
 * Address: ........
 * Size:    000104
 */
void Quat::multiplyTo(Quat& other, Quat& outQuat)
{
	outQuat.s   = other.s * s - other.v.x * v.x - other.v.y * v.y - other.v.z * v.z;
	outQuat.v.x = (other.v.y * v.z + (other.s * v.x + other.v.x * s)) - other.v.z * v.y;
	outQuat.v.y = (other.v.z * v.x + (other.s * v.y + other.v.y * s)) - other.v.x * v.z;
	outQuat.v.z = (other.v.x * v.y + (other.s * v.z + other.v.z * s)) - other.v.y * v.x;
}

/*
 * --INFO--
 * Address: 80037F30
 * Size:    0000D4
 */
void Quat::normalise()
{
	f32 factor = 1.0f / std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + s * s);
	v.x *= factor;
	v.y *= factor;
	v.z *= factor;
	s *= factor;
}

/*
 * --INFO--
 * Address: 80038004
 * Size:    000080
 */
void Quat::genVectorX(Vector3f& outVec)
{
	f32 yy   = v.y * v.y;
	f32 zz   = v.z * v.z;
	outVec.x = (1.0f - 2.0f * yy) - (2.0f * zz);

	f32 xy   = v.x * v.y;
	f32 sz   = s * v.z;
	outVec.y = 2.0f * xy + 2.0f * sz;

	f32 xz   = v.x * v.z;
	f32 sy   = s * v.y;
	outVec.z = 2.0f * xz - 2.0f * sy;
}

/*
 * --INFO--
 * Address: 80038084
 * Size:    000080
 */
void Quat::genVectorY(Vector3f& outVec)
{
	f32 xy   = v.x * v.y;
	f32 sz   = s * v.z;
	outVec.x = 2.0f * xy - 2.0f * sz;

	f32 xx   = v.x * v.x;
	f32 zz   = v.z * v.z;
	outVec.y = (1.0f - 2.0f * xx) - (2.0f * zz);

	f32 yz   = v.y * v.z;
	f32 sx   = s * v.x;
	outVec.z = 2.0f * yz + 2.0f * sx;
}

/*
 * --INFO--
 * Address: 80038104
 * Size:    000080
 */
void Quat::genVectorZ(Vector3f& outVec)
{
	f32 xz   = v.x * v.z;
	f32 sy   = s * v.y;
	outVec.x = 2.0f * xz + 2.0f * sy;

	f32 yz   = v.y * v.z;
	f32 sx   = s * v.x;
	outVec.y = 2.0f * yz - 2.0f * sx;

	f32 xx   = v.x * v.x;
	f32 yy   = v.y * v.y;
	outVec.z = (1.0f - 2.0f * xx) - (2.0f * yy);
}

/*
 * --INFO--
 * Address: 80038184
 * Size:    000164
 */
void Quat::slerp(Quat& other, f32 t, int)
{
	f32 dot = v.x * other.v.x + v.y * other.v.y + v.z * other.v.z + s * other.s;
	BOOL isNegative;
	if (dot < 0.0) {
		dot        = -dot;
		isNegative = TRUE;
	} else {
		isNegative = FALSE;
	}

	f32 tComp;
	if (1.0f - dot < 0.000001) {
		tComp = 1.0f - t;
	} else {
		f32 acosVal = acosf(dot);
		f32 sinVal  = sinf(acosVal);
		f32 ang     = t * acosVal;
		tComp       = sinf(acosVal - ang) / sinVal;
		t           = sinf(ang) / sinVal;
	}

	if (isNegative) {
		t = -t;
	}

	v.x = tComp * v.x + t * other.v.x;
	v.y = tComp * v.y + t * other.v.y;
	v.z = tComp * v.z + t * other.v.z;
	s   = tComp * s + t * other.s;
}

/*
 * --INFO--
 * Address: 800382E8
 * Size:    0002A0
 */
void Quat::fromEuler(Vector3f& angles)
{
	Quat psiQ;
	Quat thetaQ;
	Quat phiQ;
	f32 psi   = 0.5f * angles.x;
	f32 theta = 0.5f * angles.y;
	f32 phi   = 0.5f * angles.z;

	f32 sinPsi = sinf(psi);
	f32 cosPsi = cosf(psi);

	f32 sinTheta = sinf(theta);
	f32 cosTheta = cosf(theta);

	f32 sinPhi = sinf(phi);
	f32 cosPhi = cosf(phi);

	psiQ.set(sinPsi, 0.0f, 0.00, cosPsi);
	thetaQ.set(0.0f, sinTheta, 0.0f, cosTheta);
	phiQ.set(0.0f, 0.0f, sinPhi, cosPhi);

	psiQ.multiplyTo(thetaQ, *this);
	multiplyTo(phiQ, *this);
	normalise();
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0xA0(r1)
	  stfd      f31, 0x98(r1)
	  stfd      f30, 0x90(r1)
	  stfd      f29, 0x88(r1)
	  stfd      f28, 0x80(r1)
	  stfd      f27, 0x78(r1)
	  stfd      f26, 0x70(r1)
	  stw       r31, 0x6C(r1)
	  mr        r31, r3
	  lfs       f2, -0x7C50(r2)
	  lfs       f0, 0x0(r4)
	  lfs       f1, 0x4(r4)
	  fmuls     f27, f2, f0
	  lfs       f0, 0x8(r4)
	  fmuls     f29, f2, f1
	  fmuls     f26, f2, f0
	  fmr       f1, f27
	  bl        0x1E39B4
	  fmr       f30, f1
	  fmr       f1, f27
	  bl        0x1E3814
	  fmr       f27, f1
	  fmr       f1, f29
	  bl        0x1E399C
	  fmr       f28, f1
	  fmr       f1, f29
	  bl        0x1E37FC
	  fmr       f29, f1
	  fmr       f1, f26
	  bl        0x1E3984
	  fmr       f31, f1
	  fmr       f1, f26
	  bl        0x1E37E4
	  lfs       f0, -0x7C60(r2)
	  fmuls     f2, f29, f27
	  fmuls     f3, f29, f30
	  fmuls     f8, f0, f30
	  fmuls     f9, f0, f27
	  fmuls     f7, f28, f0
	  fsubs     f5, f2, f8
	  fmuls     f10, f29, f0
	  fmuls     f2, f28, f27
	  fadds     f4, f3, f9
	  fsubs     f6, f5, f7
	  fadds     f3, f10, f2
	  fadds     f5, f7, f4
	  fsubs     f6, f6, f0
	  fadds     f4, f8, f3
	  fadds     f2, f10, f9
	  fsubs     f5, f5, f0
	  stfs      f6, 0xC(r31)
	  fsubs     f4, f4, f0
	  fadds     f3, f0, f2
	  fmuls     f2, f28, f30
	  stfs      f5, 0x0(r31)
	  fsubs     f2, f3, f2
	  stfs      f4, 0x4(r31)
	  stfs      f2, 0x8(r31)
	  lfs       f4, 0xC(r31)
	  lfs       f3, 0x4(r31)
	  lfs       f2, 0x0(r31)
	  fmuls     f5, f1, f4
	  fmuls     f3, f0, f3
	  fmuls     f4, f0, f2
	  lfs       f2, 0x8(r31)
	  fmuls     f2, f31, f2
	  fsubs     f4, f5, f4
	  fsubs     f3, f4, f3
	  fsubs     f2, f3, f2
	  stfs      f2, 0xC(r31)
	  lfs       f3, 0x0(r31)
	  lfs       f5, 0x8(r31)
	  lfs       f2, 0xC(r31)
	  fmuls     f4, f1, f3
	  fmuls     f5, f0, f5
	  fmuls     f3, f0, f2
	  lfs       f2, 0x4(r31)
	  fmuls     f2, f31, f2
	  fadds     f3, f4, f3
	  fadds     f3, f5, f3
	  fsubs     f2, f3, f2
	  stfs      f2, 0x0(r31)
	  lfs       f3, 0x4(r31)
	  lfs       f5, 0x0(r31)
	  lfs       f2, 0xC(r31)
	  fmuls     f4, f1, f3
	  fmuls     f5, f31, f5
	  fmuls     f3, f0, f2
	  lfs       f2, 0x8(r31)
	  fmuls     f2, f0, f2
	  fadds     f3, f4, f3
	  fadds     f3, f5, f3
	  fsubs     f2, f3, f2
	  stfs      f2, 0x4(r31)
	  lfs       f3, 0x8(r31)
	  lfs       f2, 0xC(r31)
	  fmuls     f3, f1, f3
	  lfs       f4, 0x4(r31)
	  fmuls     f2, f31, f2
	  lfs       f1, 0x0(r31)
	  fmuls     f4, f0, f4
	  fadds     f2, f3, f2
	  fmuls     f1, f0, f1
	  fadds     f2, f4, f2
	  fsubs     f1, f2, f1
	  stfs      f1, 0x8(r31)
	  lfs       f2, 0x0(r31)
	  lfs       f1, 0x4(r31)
	  lfs       f3, 0x8(r31)
	  fmuls     f2, f2, f2
	  fmuls     f1, f1, f1
	  lfs       f4, 0xC(r31)
	  fmuls     f3, f3, f3
	  fmuls     f4, f4, f4
	  fadds     f1, f2, f1
	  fadds     f1, f3, f1
	  fadds     f4, f4, f1
	  fcmpo     cr0, f4, f0
	  ble-      .loc_0x23C
	  fsqrte    f1, f4
	  lfd       f3, -0x7C48(r2)
	  lfd       f2, -0x7C40(r2)
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f4, f0
	  fsub      f0, f2, f0
	  fmul      f0, f1, f0
	  fmul      f0, f4, f0
	  frsp      f0, f0
	  stfs      f0, 0x28(r1)
	  lfs       f4, 0x28(r1)

	.loc_0x23C:
	  lfs       f1, -0x7C5C(r2)
	  lfs       f0, 0x0(r31)
	  fdivs     f1, f1, f4
	  fmuls     f0, f0, f1
	  stfs      f0, 0x0(r31)
	  lfs       f0, 0x4(r31)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x4(r31)
	  lfs       f0, 0x8(r31)
	  fmuls     f0, f0, f1
	  stfs      f0, 0x8(r31)
	  lfs       f0, 0xC(r31)
	  fmuls     f0, f0, f1
	  stfs      f0, 0xC(r31)
	  lwz       r0, 0xA4(r1)
	  lfd       f31, 0x98(r1)
	  lfd       f30, 0x90(r1)
	  lfd       f29, 0x88(r1)
	  lfd       f28, 0x80(r1)
	  lfd       f27, 0x78(r1)
	  lfd       f26, 0x70(r1)
	  lwz       r31, 0x6C(r1)
	  addi      r1, r1, 0xA0
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 80038588
 * Size:    00002C
 */
f32 roundAng(f32 x)
{
	if (x < 0.0f) {
		x += TAU;
	}

	if (x >= TAU) {
		x -= TAU;
	}

	return x;
}

/*
 * --INFO--
 * Address: 800385B4
 * Size:    000074
 */
f32 angDist(f32 angle1, f32 angle2)
{
	f32 angle = roundAng(angle1 - angle2);

	if (angle >= PI) {
		angle = -roundAng(TAU - angle);
	}
	return angle;
}

/*
 * --INFO--
 * Address: 80038628
 * Size:    000050
 */
f32 qdist2(f32 x0, f32 y0, f32 x1, f32 y1)
{
	x1 -= x0;
	if (x1 < 0.0f) {
		x1 = -x1;
	}

	y1 -= y0;
	if (y1 < 0.0f) {
		y1 = -y1;
	}

	f32 min = (x1 > y1) ? y1 : x1;

	return (x1 + y1) - (0.5f * min);
}

/*
 * --INFO--
 * Address: ........
 * Size:    000080
 */
f32 qdist3(f32, f32, f32, f32, f32, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address: 80038678
 * Size:    0001BC
 */
void CollTriInfo::init(RoomInfo* info, Vector3f* pos)
{
	for (int i = 0; i < 3; ++i) {
		// Vector3f* pos1;
		// Vector3f* pos2;
		// pos2 = &pos[this->_04[(i + 1) % 3]];
		// pos1 = &pos[this->_04[i % 3]];

		// Vector3f tempVector;
		// tempVector.sub2(pos2, pos1);
		// tempVector.normalise();
		// tempVector.CP(&this->field_18);
		// this->field_28[i] = tempVector;
		// f64 dpResult      = tempVector.DP(pos2);
		// this->field_34[i] = dpResult;
	}
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x78(r1)
	  stfd      f31, 0x70(r1)
	  stmw      r26, 0x58(r1)
	  mr        r27, r3
	  lis       r3, 0x5555
	  addi      r28, r5, 0
	  addi      r30, r27, 0
	  addi      r31, r3, 0x5556
	  li        r29, 0
	  lfs       f31, -0x7C60(r2)

	.loc_0x30:
	  addi      r6, r29, 0x1
	  mulhw     r5, r31, r6
	  mulhw     r3, r31, r29
	  rlwinm    r4,r5,1,31,31
	  rlwinm    r0,r3,1,31,31
	  add       r4, r5, r4
	  add       r0, r3, r0
	  mulli     r3, r4, 0x3
	  mulli     r0, r0, 0x3
	  sub       r3, r6, r3
	  sub       r0, r29, r0
	  rlwinm    r4,r3,2,0,29
	  rlwinm    r3,r0,2,0,29
	  addi      r4, r4, 0x4
	  addi      r0, r3, 0x4
	  lwzx      r3, r27, r4
	  lwzx      r0, r27, r0
	  mulli     r3, r3, 0xC
	  add       r26, r28, r3
	  mulli     r0, r0, 0xC
	  lfs       f1, 0x0(r26)
	  lfs       f3, 0x4(r26)
	  lfs       f5, 0x8(r26)
	  add       r3, r28, r0
	  lfs       f0, 0x0(r3)
	  lfs       f2, 0x4(r3)
	  lfs       f4, 0x8(r3)
	  fsubs     f0, f1, f0
	  fsubs     f2, f3, f2
	  fsubs     f1, f5, f4
	  stfs      f0, 0x4C(r1)
	  stfs      f2, 0x50(r1)
	  stfs      f1, 0x54(r1)
	  lfs       f1, 0x4C(r1)
	  lfs       f0, 0x50(r1)
	  lfs       f2, 0x54(r1)
	  fmuls     f1, f1, f1
	  fmuls     f0, f0, f0
	  fmuls     f2, f2, f2
	  fadds     f0, f1, f0
	  fadds     f1, f2, f0
	  bl        -0x2AB0C
	  fcmpu     cr0, f31, f1
	  beq-      .loc_0x104
	  lfs       f0, 0x4C(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x4C(r1)
	  lfs       f0, 0x50(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x50(r1)
	  lfs       f0, 0x54(r1)
	  fdivs     f0, f0, f1
	  stfs      f0, 0x54(r1)

	.loc_0x104:
	  lfs       f1, 0x54(r1)
	  addi      r29, r29, 0x1
	  lfs       f2, 0x1C(r27)
	  cmpwi     r29, 0x3
	  lfs       f5, 0x18(r27)
	  lfs       f6, 0x50(r1)
	  fmuls     f0, f1, f2
	  lfs       f7, 0x4C(r1)
	  fmuls     f4, f1, f5
	  lfs       f3, 0x20(r27)
	  fmuls     f2, f7, f2
	  fmuls     f1, f6, f3
	  fmuls     f3, f7, f3
	  fsubs     f0, f1, f0
	  fmuls     f1, f6, f5
	  fsubs     f3, f4, f3
	  stfs      f0, 0x4C(r1)
	  fsubs     f0, f2, f1
	  stfs      f3, 0x50(r1)
	  stfs      f0, 0x54(r1)
	  lwz       r3, 0x4C(r1)
	  lwz       r0, 0x50(r1)
	  stw       r3, 0x28(r30)
	  stw       r0, 0x2C(r30)
	  lwz       r0, 0x54(r1)
	  stw       r0, 0x30(r30)
	  lfs       f3, 0x4C(r1)
	  lfs       f2, 0x0(r26)
	  lfs       f1, 0x50(r1)
	  lfs       f0, 0x4(r26)
	  fmuls     f2, f3, f2
	  lfs       f3, 0x54(r1)
	  fmuls     f0, f1, f0
	  lfs       f1, 0x8(r26)
	  fmuls     f1, f3, f1
	  fadds     f0, f2, f0
	  fadds     f0, f1, f0
	  stfs      f0, 0x34(r30)
	  addi      r30, r30, 0x10
	  blt+      .loc_0x30
	  lmw       r26, 0x58(r1)
	  lwz       r0, 0x7C(r1)
	  lfd       f31, 0x70(r1)
	  addi      r1, r1, 0x78
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 80038834
 * Size:    0000C4
 */
void CollTriInfo::behindEdge(Vector3f&)
{
	/*
	.loc_0x0:
	  lfs       f2, 0x28(r3)
	  lfs       f5, 0x0(r4)
	  lfs       f1, 0x2C(r3)
	  lfs       f3, 0x4(r4)
	  fmuls     f4, f2, f5
	  lfs       f6, 0x30(r3)
	  fmuls     f2, f1, f3
	  lfs       f7, 0x8(r4)
	  lfs       f1, 0x34(r3)
	  fmuls     f6, f6, f7
	  lfs       f0, -0x7C60(r2)
	  fadds     f2, f4, f2
	  fadds     f2, f6, f2
	  fsubs     f1, f2, f1
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x48
	  li        r3, 0
	  blr

	.loc_0x48:
	  addi      r3, r3, 0x10
	  lfs       f2, 0x28(r3)
	  lfs       f1, 0x2C(r3)
	  fmuls     f4, f2, f5
	  lfs       f6, 0x30(r3)
	  fmuls     f2, f1, f3
	  lfs       f1, 0x34(r3)
	  fmuls     f6, f6, f7
	  fadds     f2, f4, f2
	  fadds     f2, f6, f2
	  fsubs     f1, f2, f1
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0x84
	  li        r3, 0x1
	  blr

	.loc_0x84:
	  lfs       f2, 0x38(r3)
	  lfs       f1, 0x3C(r3)
	  fmuls     f4, f2, f5
	  lfs       f6, 0x40(r3)
	  fmuls     f2, f1, f3
	  lfs       f1, 0x44(r3)
	  fmuls     f6, f6, f7
	  fadds     f2, f4, f2
	  fadds     f2, f6, f2
	  fsubs     f1, f2, f1
	  fcmpo     cr0, f1, f0
	  bge-      .loc_0xBC
	  li        r3, 0x2
	  blr

	.loc_0xBC:
	  li        r3, -0x1
	  blr
	*/
}

/*
 * --INFO--
 * Address: 800388F8
 * Size:    000644
 */
void BoundBox::draw(Graphics&)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x190(r1)
	  stw       r31, 0x18C(r1)
	  mr        r31, r3
	  addi      r5, r1, 0x120
	  stw       r30, 0x188(r1)
	  addi      r30, r4, 0
	  addi      r4, r1, 0x12C
	  lfs       f0, 0xC(r3)
	  addi      r3, r30, 0
	  stfs      f0, 0x120(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x124(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x128(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x12C(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x130(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x134(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r5, r1, 0x108
	  addi      r4, r1, 0x114
	  stfs      f0, 0x108(r1)
	  mr        r3, r30
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x10C(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x110(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x114(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x118(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x11C(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0xF0
	  addi      r4, r1, 0xFC
	  stfs      f0, 0xF0(r1)
	  mr        r3, r30
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0xF4(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0xF8(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0xFC(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x100(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x104(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0xD8
	  addi      r4, r1, 0xE4
	  stfs      f0, 0xD8(r1)
	  mr        r3, r30
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0xDC(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0xE0(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0xE4(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0xE8(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0xEC(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r5, r1, 0xC0
	  addi      r4, r1, 0xCC
	  stfs      f0, 0xC0(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0xC4(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0xC8(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0xCC(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0xD0(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0xD4(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r5, r1, 0xA8
	  addi      r4, r1, 0xB4
	  stfs      f0, 0xA8(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0xAC(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0xB0(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0xB4(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0xB8(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0xBC(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0x90
	  addi      r4, r1, 0x9C
	  stfs      f0, 0x90(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x94(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x98(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x9C(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0xA0(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0xA4(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0x78
	  addi      r4, r1, 0x84
	  stfs      f0, 0x78(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x7C(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x80(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x84(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x88(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x8C(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0x60
	  addi      r4, r1, 0x6C
	  stfs      f0, 0x60(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x64(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x68(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x6C(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x70(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x74(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r5, r1, 0x48
	  addi      r4, r1, 0x54
	  stfs      f0, 0x48(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x4C(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x50(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x54(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x58(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x5C(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r5, r1, 0x30
	  addi      r4, r1, 0x3C
	  stfs      f0, 0x30(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x34(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x38(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x3C(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x40(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x44(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r5, r1, 0x18
	  addi      r4, r1, 0x24
	  stfs      f0, 0x18(r1)
	  mr        r3, r30
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x1C(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x20(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x24(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x28(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x2C(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0x98(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, -0x7C60(r2)
	  li        r0, 0x20
	  addi      r4, r1, 0x14
	  stfs      f0, 0x160(r1)
	  mr        r3, r30
	  li        r5, 0x1
	  stfs      f0, 0x15C(r1)
	  stfs      f0, 0x158(r1)
	  stfs      f0, 0x16C(r1)
	  stfs      f0, 0x168(r1)
	  stfs      f0, 0x164(r1)
	  stfs      f0, 0x178(r1)
	  stfs      f0, 0x174(r1)
	  stfs      f0, 0x170(r1)
	  stfs      f0, 0x184(r1)
	  stfs      f0, 0x180(r1)
	  stfs      f0, 0x17C(r1)
	  lbz       r8, 0x31A(r30)
	  lbz       r7, 0x319(r30)
	  lbz       r6, 0x318(r30)
	  stb       r6, 0x14(r1)
	  stb       r7, 0x15(r1)
	  stb       r8, 0x16(r1)
	  stb       r0, 0x17(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xA8(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  mr        r3, r30
	  addi      r4, r1, 0x158
	  stfs      f0, 0x158(r1)
	  addi      r6, r1, 0x138
	  li        r5, 0
	  lfs       f0, 0x4(r31)
	  li        r7, 0x4
	  stfs      f0, 0x15C(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x160(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x164(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x168(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x174(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x178(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x17C(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x180(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x184(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r3, r30, 0
	  addi      r4, r1, 0x158
	  stfs      f0, 0x158(r1)
	  addi      r6, r1, 0x138
	  li        r5, 0
	  lfs       f0, 0x10(r31)
	  li        r7, 0x4
	  stfs      f0, 0x15C(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x160(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x164(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x168(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x174(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x178(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x17C(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x180(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x184(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0xC(r31)
	  addi      r3, r30, 0
	  addi      r4, r1, 0x158
	  stfs      f0, 0x158(r1)
	  addi      r6, r1, 0x138
	  li        r5, 0
	  lfs       f0, 0x4(r31)
	  li        r7, 0x4
	  stfs      f0, 0x15C(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x160(r1)
	  lfs       f0, 0xC(r31)
	  stfs      f0, 0x164(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x168(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x174(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x178(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x17C(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x180(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x184(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  lfs       f0, 0x0(r31)
	  addi      r3, r30, 0
	  addi      r4, r1, 0x158
	  stfs      f0, 0x158(r1)
	  addi      r6, r1, 0x138
	  li        r5, 0
	  lfs       f0, 0x10(r31)
	  li        r7, 0x4
	  stfs      f0, 0x15C(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x160(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x164(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x168(r1)
	  lfs       f0, 0x14(r31)
	  stfs      f0, 0x16C(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x170(r1)
	  lfs       f0, 0x4(r31)
	  stfs      f0, 0x174(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x178(r1)
	  lfs       f0, 0x0(r31)
	  stfs      f0, 0x17C(r1)
	  lfs       f0, 0x10(r31)
	  stfs      f0, 0x180(r1)
	  lfs       f0, 0x8(r31)
	  stfs      f0, 0x184(r1)
	  lwz       r12, 0x3B4(r30)
	  lwz       r12, 0xA0(r12)
	  mtlr      r12
	  blrl
	  lwz       r0, 0x194(r1)
	  lwz       r31, 0x18C(r1)
	  lwz       r30, 0x188(r1)
	  addi      r1, r1, 0x190
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 80038F3C
 * Size:    0000E8
 */
bool pointInsideTri(KTri& tri, Vector3f& point)
{
	Vector3f A;
	A           = tri.mVertA;
	Vector3f AB = A + tri.mSideAB;
	Vector3f AC = A + tri.mSideAC;

	Vector3f B = AB - A;
	Vector3f C = AC - AB;
	Vector3f D = A - AC;

	if (B.z * (point.x - A.x) - B.x * (point.z - A.z) > 0.0f) {
		return false;
	}

	if (C.z * (point.x - AB.x) - C.x * (point.z - AB.z) > 0.0f) {
		return false;
	}

	if (D.z * (point.x - AC.x) - D.x * (point.z - AC.z) > 0.0f) {
		return false;
	}

	FORCE_DONT_INLINE;

	return true;
	/*
	.loc_0x0:
	  stwu      r1, -0x200(r1)
	  lfs       f4, -0x7C60(r2)
	  stfs      f4, 0x1FC(r1)
	  stfs      f4, 0x1F8(r1)
	  lwz       r5, 0x0(r3)
	  lwz       r0, 0x4(r3)
	  stw       r5, 0x1F4(r1)
	  stw       r0, 0x1F8(r1)
	  lwz       r0, 0x8(r3)
	  stw       r0, 0x1FC(r1)
	  lfs       f9, 0x1FC(r1)
	  lfs       f0, 0x14(r3)
	  lfs       f10, 0x1F4(r1)
	  fadds     f5, f9, f0
	  lfs       f0, 0xC(r3)
	  lfs       f11, 0x8(r4)
	  fadds     f6, f10, f0
	  lfs       f12, 0x0(r4)
	  fsubs     f7, f11, f9
	  lfs       f3, 0x20(r3)
	  fsubs     f0, f6, f10
	  fsubs     f8, f12, f10
	  lfs       f2, 0x18(r3)
	  fsubs     f1, f5, f9
	  fmuls     f0, f0, f7
	  fadds     f3, f9, f3
	  fmuls     f1, f1, f8
	  fadds     f2, f10, f2
	  fsubs     f7, f3, f5
	  fsubs     f0, f1, f0
	  fsubs     f8, f2, f6
	  fsubs     f9, f9, f3
	  fcmpo     cr0, f0, f4
	  fsubs     f10, f10, f2
	  ble-      .loc_0x94
	  li        r3, 0
	  b         .loc_0xE0

	.loc_0x94:
	  fsubs     f1, f12, f6
	  fsubs     f0, f11, f5
	  fmuls     f1, f7, f1
	  fmuls     f0, f8, f0
	  fsubs     f0, f1, f0
	  fcmpo     cr0, f0, f4
	  ble-      .loc_0xB8
	  li        r3, 0
	  b         .loc_0xE0

	.loc_0xB8:
	  fsubs     f1, f12, f2
	  fsubs     f0, f11, f3
	  fmuls     f1, f9, f1
	  fmuls     f0, f10, f0
	  fsubs     f0, f1, f0
	  fcmpo     cr0, f0, f4
	  ble-      .loc_0xDC
	  li        r3, 0
	  b         .loc_0xE0

	.loc_0xDC:
	  li        r3, 0x1

	.loc_0xE0:
	  addi      r1, r1, 0x200
	  blr
	*/
}

/*
 * --INFO--
 * Address: 80039024
 * Size:    000260
 */
f32 triRectDistance(Vector3f* vecA, Vector3f* vecB, Vector3f* vecC, BoundBox& box, bool p5)
{
	// project triangle points down onto plane
	Vector3f A(*vecA); // 0x148
	Vector3f B(*vecB); // 0x13C
	Vector3f C(*vecC); // 0x130

	A.y = B.y = C.y = 0.0f;

	KTri tri;
	KRect rect;

	tri.set(A, B, C);

	// set rectangle points from XZ of bounding box, projected down to plane
	Vector3f botLeft;  // 0xDC
	Vector3f topLeft;  // 0xD0
	Vector3f botRight; // 0xC4
	Vector3f topRight; // 0xB8

	botLeft   = box.mMin;
	botLeft.y = 0.0f;

	Vector3f boxDiffXZ(box.mMax.x - box.mMin.x, 0.0f, box.mMax.z - box.mMin.z);

	topLeft  = botLeft + Vector3f(boxDiffXZ.x, 0.0f, 0.0f);
	botRight = botLeft + Vector3f(0.0f, 0.0f, boxDiffXZ.z);
	topRight = botLeft + boxDiffXZ;

	rect.mBotTri.set(botLeft, topLeft, botRight);

	if (rect.inside(A)) {
		return 0.0f;
	}
	if (rect.inside(B)) {
		return 0.0f;
	}
	if (rect.inside(C)) {
		return 0.0f;
	}

	if (pointInsideTri(tri, botLeft)) {
		return 0.0f;
	}

	if (pointInsideTri(tri, topLeft)) {
		return 0.0f;
	}

	if (pointInsideTri(tri, botRight)) {
		return 0.0f;
	}

	if (pointInsideTri(tri, topRight)) {
		return 0.0f;
	}

	f32 a, b, c, d;
	u32 badCompiler[7];
	return distanceTriRect(tri, rect, &a, &b, &c, &d);

	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x160(r1)
	  stw       r31, 0x15C(r1)
	  mr        r31, r6
	  lfs       f0, 0x0(r3)
	  stfs      f0, 0x148(r1)
	  lfs       f0, 0x4(r3)
	  stfs      f0, 0x14C(r1)
	  lfs       f0, 0x8(r3)
	  addi      r3, r1, 0x10C
	  stfs      f0, 0x150(r1)
	  lfs       f0, 0x0(r4)
	  stfs      f0, 0x13C(r1)
	  lfs       f0, 0x4(r4)
	  stfs      f0, 0x140(r1)
	  lfs       f0, 0x8(r4)
	  stfs      f0, 0x144(r1)
	  lfs       f0, 0x0(r5)
	  stfs      f0, 0x130(r1)
	  lfs       f0, 0x4(r5)
	  stfs      f0, 0x134(r1)
	  lfs       f1, 0x8(r5)
	  lfs       f0, -0x7C60(r2)
	  stfs      f1, 0x138(r1)
	  stfs      f0, 0x134(r1)
	  stfs      f0, 0x140(r1)
	  stfs      f0, 0x14C(r1)
	  bl        0x408
	  addi      r3, r1, 0xE8
	  bl        0x400
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0x148
	  addi      r5, r1, 0x13C
	  addi      r6, r1, 0x130
	  bl        0x418
	  lfs       f0, -0x7C60(r2)
	  addi      r3, r1, 0xE8
	  addi      r4, r1, 0xDC
	  stfs      f0, 0xE4(r1)
	  addi      r5, r1, 0xD0
	  addi      r6, r1, 0xC4
	  stfs      f0, 0xE0(r1)
	  stfs      f0, 0xDC(r1)
	  stfs      f0, 0xD8(r1)
	  stfs      f0, 0xD4(r1)
	  stfs      f0, 0xD0(r1)
	  stfs      f0, 0xCC(r1)
	  stfs      f0, 0xC8(r1)
	  stfs      f0, 0xC4(r1)
	  stfs      f0, 0xC0(r1)
	  stfs      f0, 0xBC(r1)
	  stfs      f0, 0xB8(r1)
	  lwz       r7, 0x0(r31)
	  lwz       r0, 0x4(r31)
	  stw       r7, 0xDC(r1)
	  stw       r0, 0xE0(r1)
	  lwz       r0, 0x8(r31)
	  stw       r0, 0xE4(r1)
	  stfs      f0, 0xE0(r1)
	  lfs       f1, 0xC(r31)
	  lfs       f0, 0x0(r31)
	  lfs       f4, 0xDC(r1)
	  fsubs     f1, f1, f0
	  lfs       f3, 0x14(r31)
	  lfs       f2, 0x8(r31)
	  lfs       f0, -0x7A28(r13)
	  fadds     f5, f4, f1
	  fsubs     f1, f3, f2
	  stfs      f5, 0xD0(r1)
	  lfs       f2, 0xE0(r1)
	  fadds     f0, f2, f0
	  stfs      f0, 0xD4(r1)
	  lfs       f3, 0xE4(r1)
	  lfs       f0, -0x7A24(r13)
	  fadds     f6, f3, f1
	  fadds     f0, f3, f0
	  stfs      f0, 0xD8(r1)
	  lfs       f1, -0x7A20(r13)
	  lfs       f0, -0x7A1C(r13)
	  fadds     f1, f4, f1
	  fadds     f0, f2, f0
	  stfs      f1, 0xC4(r1)
	  stfs      f0, 0xC8(r1)
	  stfs      f6, 0xCC(r1)
	  lfs       f0, -0x7A18(r13)
	  stfs      f5, 0xB8(r1)
	  fadds     f0, f2, f0
	  stfs      f0, 0xBC(r1)
	  stfs      f6, 0xC0(r1)
	  bl        0x33C
	  addi      r3, r1, 0xE8
	  addi      r4, r1, 0x148
	  bl        0x294
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x188
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x188:
	  addi      r3, r1, 0xE8
	  addi      r4, r1, 0x13C
	  bl        0x278
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1A4
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x1A4:
	  addi      r3, r1, 0xE8
	  addi      r4, r1, 0x130
	  bl        0x25C
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1C0
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x1C0:
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0xDC
	  bl        -0x2B0
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1DC
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x1DC:
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0xD0
	  bl        -0x2CC
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x1F8
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x1F8:
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0xC4
	  bl        -0x2E8
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x214
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x214:
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0xB8
	  bl        -0x304
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x230
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x24C

	.loc_0x230:
	  addi      r3, r1, 0x10C
	  addi      r4, r1, 0xE8
	  addi      r5, r1, 0xA8
	  addi      r6, r1, 0xA4
	  addi      r7, r1, 0xA0
	  addi      r8, r1, 0x9C
	  bl        .loc_0x260

	.loc_0x24C:
	  lwz       r0, 0x164(r1)
	  lwz       r31, 0x15C(r1)
	  addi      r1, r1, 0x160
	  mtlr      r0
	  blr

	.loc_0x260:
	*/
}

/*
 * --INFO--
 * Address: 80039284
 * Size:    0001A8
 */
f32 distanceTriRect(KTri& tri, KRect& rect, f32* p3, f32* p4, f32* p5, f32* p6)
{
	f32 sqrDist = sqrDistance(tri, rect, p3, p4, p5, p6);

	Vector3f vec;
	vec = tri.mVertA + tri.mSideAB * *p3 + tri.mSideAC * *p4;

	if (rect.inside(vec)) {
		return 0.0f;
	}

	u32 badCompiler[4];
	return std::sqrtf(sqrDist);

	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0xC8(r1)
	  stfd      f31, 0xC0(r1)
	  stfd      f30, 0xB8(r1)
	  stfd      f29, 0xB0(r1)
	  stfd      f28, 0xA8(r1)
	  stw       r31, 0xA4(r1)
	  addi      r31, r6, 0
	  stw       r30, 0xA0(r1)
	  addi      r30, r5, 0
	  stw       r29, 0x9C(r1)
	  addi      r29, r4, 0
	  stw       r28, 0x98(r1)
	  addi      r28, r3, 0
	  bl        0x4154
	  lfs       f0, -0x7C60(r2)
	  fmr       f30, f1
	  addi      r6, r1, 0x48
	  stfs      f0, 0x94(r1)
	  addi      r5, r1, 0x44
	  addi      r4, r1, 0x40
	  stfs      f0, 0x90(r1)
	  addi      r3, r1, 0x74
	  stfs      f0, 0x8C(r1)
	  lfs       f1, 0x14(r28)
	  lfs       f0, 0x0(r30)
	  lfs       f3, 0x20(r28)
	  fmuls     f0, f1, f0
	  lfs       f4, 0x0(r31)
	  lfs       f2, 0x1C(r28)
	  lfs       f1, 0x18(r28)
	  fmuls     f31, f3, f4
	  stfs      f0, 0x48(r1)
	  fmuls     f28, f1, f4
	  fmuls     f29, f2, f4
	  lfs       f1, 0x10(r28)
	  lfs       f0, 0x0(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x44(r1)
	  lfs       f1, 0xC(r28)
	  lfs       f0, 0x0(r30)
	  fmuls     f0, f1, f0
	  stfs      f0, 0x40(r1)
	  bl        -0x2218
	  lfs       f1, 0x0(r28)
	  mr        r3, r29
	  lfs       f0, 0x74(r1)
	  addi      r4, r1, 0x8C
	  lfs       f2, 0x4(r28)
	  fadds     f0, f1, f0
	  lfs       f1, 0x78(r1)
	  lfs       f3, 0x8(r28)
	  fadds     f4, f2, f1
	  lfs       f1, 0x7C(r1)
	  fadds     f0, f0, f28
	  fadds     f2, f3, f1
	  fadds     f1, f4, f29
	  stfs      f0, 0x8C(r1)
	  fadds     f0, f2, f31
	  stfs      f1, 0x90(r1)
	  stfs      f0, 0x94(r1)
	  bl        .loc_0x1A8
	  rlwinm.   r0,r3,0,24,31
	  beq-      .loc_0x10C
	  lfs       f1, -0x7C60(r2)
	  b         .loc_0x178

	.loc_0x10C:
	  lfs       f0, -0x7C60(r2)
	  fcmpo     cr0, f30, f0
	  ble-      .loc_0x174
	  fsqrte    f1, f30
	  lfd       f3, -0x7C48(r2)
	  lfd       f2, -0x7C40(r2)
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f30, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f30, f0
	  fsub      f0, f2, f0
	  fmul      f1, f1, f0
	  fmul      f0, f1, f1
	  fmul      f1, f3, f1
	  fmul      f0, f30, f0
	  fsub      f0, f2, f0
	  fmul      f0, f1, f0
	  fmul      f0, f30, f0
	  frsp      f0, f0
	  stfs      f0, 0x58(r1)
	  lfs       f1, 0x58(r1)
	  b         .loc_0x178

	.loc_0x174:
	  fmr       f1, f30

	.loc_0x178:
	  lwz       r0, 0xCC(r1)
	  lfd       f31, 0xC0(r1)
	  lfd       f30, 0xB8(r1)
	  lfd       f29, 0xB0(r1)
	  lfd       f28, 0xA8(r1)
	  lwz       r31, 0xA4(r1)
	  lwz       r30, 0xA0(r1)
	  lwz       r29, 0x9C(r1)
	  lwz       r28, 0x98(r1)
	  addi      r1, r1, 0xC8
	  mtlr      r0
	  blr

	.loc_0x1A8:
	*/
}

/*
 * --INFO--
 * Address: 8003942C
 * Size:    000070
 */
bool KRect::inside(Vector3f& point)
{
	Vector3f botLeft(mBotTri.mVertA);
	Vector3f topRight(mBotTri.mVertA.x + mBotTri.mSideAB.x + mBotTri.mSideAC.x, 0.0f,
	                  mBotTri.mVertA.z + mBotTri.mSideAB.z + mBotTri.mSideAC.z);
	if (point.x >= botLeft.x && point.x <= topRight.x && point.z >= botLeft.z && point.z <= topRight.z) {
		return true;
	}
	return false;
	/*
	.loc_0x0:
	  lfs       f4, 0x8(r3)
	  lfs       f0, 0x14(r3)
	  lfs       f5, 0x0(r3)
	  lfs       f3, 0xC(r3)
	  fadds     f2, f4, f0
	  lfs       f6, 0x0(r4)
	  lfs       f1, 0x20(r3)
	  fadds     f3, f5, f3
	  fcmpo     cr0, f6, f5
	  lfs       f0, 0x18(r3)
	  fadds     f1, f2, f1
	  fadds     f0, f3, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x68
	  fcmpo     cr0, f6, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x68
	  lfs       f0, 0x8(r4)
	  fcmpo     cr0, f0, f4
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x68
	  fcmpo     cr0, f0, f1
	  cror      2, 0, 0x2
	  bne-      .loc_0x68
	  li        r3, 0x1
	  blr

	.loc_0x68:
	  li        r3, 0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 8003949C
 * Size:    00002C
 */
KTri::KTri()
{
}

/*
 * --INFO--
 * Address: 800394C8
 * Size:    0000C4
 */
void KTri::set(Vector3f& pointA, Vector3f& pointB, Vector3f& pointC)
{
	mVertA  = pointA;
	mSideAB = pointB - pointA;
	mSideAC = pointC - pointA;
}

/*
 * --INFO--
 * Address: ........
 * Size:    000020
 */
KSegment::KSegment()
{
	// UNUSED FUNCTION
}

f32 gs_fTolerance = 0.00001f;

/*
 * --INFO--
 * Address: 8003958C
 * Size:    0018C4
 */
f32 sqrDistance(KSegment&, KTri&, f32*, f32*, f32*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x6A8(r1)
	  stfd      f31, 0x6A0(r1)
	  stfd      f30, 0x698(r1)
	  stfd      f29, 0x690(r1)
	  stfd      f28, 0x688(r1)
	  stfd      f27, 0x680(r1)
	  stfd      f26, 0x678(r1)
	  stfd      f25, 0x670(r1)
	  stfd      f24, 0x668(r1)
	  stfd      f23, 0x660(r1)
	  stfd      f22, 0x658(r1)
	  stfd      f21, 0x650(r1)
	  stfd      f20, 0x648(r1)
	  stmw      r24, 0x628(r1)
	  addi      r25, r4, 0
	  addi      r24, r3, 0
	  addi      r31, r24, 0xC
	  addi      r30, r25, 0xC
	  addi      r29, r25, 0x18
	  mr        r26, r5
	  mr        r27, r6
	  mr        r28, r7
	  lfs       f3, 0x4(r4)
	  lfs       f2, 0x4(r3)
	  lfs       f28, 0x10(r4)
	  fsubs     f9, f3, f2
	  lfs       f22, 0x10(r3)
	  lfs       f2, 0x1C(r4)
	  fmuls     f26, f28, f28
	  lfs       f29, 0xC(r4)
	  lfs       f3, 0x18(r4)
	  fmuls     f20, f22, f28
	  lfs       f7, 0xC(r3)
	  fmuls     f12, f9, f22
	  lfs       f5, 0x14(r4)
	  fmuls     f21, f7, f29
	  lfs       f1, 0x0(r4)
	  fmuls     f27, f29, f29
	  lfs       f0, 0x0(r3)
	  fmuls     f25, f29, f3
	  fsubs     f10, f1, f0
	  lfs       f11, 0x14(r3)
	  fmuls     f1, f7, f3
	  lfs       f4, 0x20(r4)
	  fmuls     f0, f22, f2
	  fmuls     f13, f10, f7
	  lfs       f8, 0x8(r4)
	  lfs       f6, 0x8(r3)
	  fadds     f21, f21, f20
	  fmuls     f20, f11, f4
	  fsubs     f8, f8, f6
	  fmuls     f6, f22, f22
	  fadds     f0, f1, f0
	  fmuls     f22, f11, f5
	  fmuls     f7, f7, f7
	  fadds     f0, f20, f0
	  fadds     f1, f22, f21
	  fadds     f20, f13, f12
	  fmuls     f21, f8, f11
	  fmuls     f13, f10, f29
	  fmuls     f12, f9, f28
	  fmuls     f24, f28, f2
	  fadds     f28, f7, f6
	  fadds     f21, f21, f20
	  fadds     f6, f27, f26
	  fmuls     f30, f5, f5
	  fadds     f7, f25, f24
	  fmuls     f26, f5, f4
	  fmuls     f23, f3, f3
	  fmuls     f22, f2, f2
	  fmuls     f29, f11, f11
	  fmuls     f20, f8, f5
	  fadds     f12, f13, f12
	  fadds     f5, f29, f28
	  fmuls     f24, f4, f4
	  fadds     f11, f23, f22
	  fneg      f29, f1
	  fneg      f28, f0
	  fadds     f6, f30, f6
	  fadds     f7, f26, f7
	  fadds     f11, f24, f11
	  fneg      f27, f21
	  fadds     f12, f20, f12
	  lfs       f1, -0x7C60(r2)
	  fmuls     f21, f6, f11
	  fmuls     f20, f7, f7
	  stfs      f1, 0x5F0(r1)
	  fmuls     f13, f28, f7
	  fmuls     f0, f29, f11
	  stfs      f1, 0x5EC(r1)
	  fsubs     f31, f21, f20
	  fsubs     f13, f13, f0
	  stfs      f1, 0x5E8(r1)
	  fmuls     f21, f29, f7
	  fmuls     f0, f28, f6
	  stfs      f1, 0x5FC(r1)
	  fmuls     f20, f5, f31
	  fsubs     f30, f21, f0
	  stfs      f1, 0x5F8(r1)
	  fmuls     f0, f29, f13
	  fmuls     f21, f10, f3
	  stfs      f1, 0x5F4(r1)
	  fmuls     f3, f28, f30
	  fadds     f0, f20, f0
	  stfs      f1, 0x5E4(r1)
	  fmuls     f2, f9, f2
	  stfs      f1, 0x5E0(r1)
	  fadds     f20, f3, f0
	  fmuls     f3, f8, f4
	  lfs       f0, -0x7A14(r13)
	  fadds     f2, f21, f2
	  stfs      f1, 0x5DC(r1)
	  fabs      f4, f20
	  fadds     f2, f3, f2
	  fcmpo     cr0, f4, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x161C
	  lfs       f0, -0x7C5C(r2)
	  fneg      f3, f27
	  fneg      f4, f12
	  fdivs     f20, f0, f20
	  fmuls     f3, f3, f20
	  fmuls     f26, f4, f20
	  fneg      f4, f2
	  fmuls     f22, f31, f3
	  fmuls     f21, f13, f26
	  fmuls     f31, f4, f20
	  fmuls     f20, f28, f29
	  fmuls     f4, f5, f7
	  fmuls     f24, f5, f11
	  fmuls     f23, f28, f28
	  fsubs     f4, f20, f4
	  fmuls     f20, f30, f31
	  fadds     f21, f22, f21
	  fsubs     f23, f24, f23
	  fmuls     f24, f5, f6
	  fmuls     f25, f29, f29
	  fadds     f21, f20, f21
	  fmuls     f22, f13, f3
	  fmuls     f23, f23, f26
	  fsubs     f25, f24, f25
	  stfs      f21, 0x5D8(r1)
	  fmuls     f30, f30, f3
	  fmuls     f13, f4, f26
	  lfs       f3, 0x5D8(r1)
	  fmuls     f21, f4, f31
	  fadds     f24, f22, f23
	  fmuls     f26, f25, f31
	  fadds     f4, f30, f13
	  fadds     f13, f21, f24
	  fcmpo     cr0, f3, f1
	  fadds     f4, f26, f4
	  stfs      f13, 0x5D4(r1)
	  stfs      f4, 0x5D0(r1)
	  bge-      .loc_0x8E4
	  lfs       f3, 0x5D4(r1)
	  lfs       f4, 0x5D0(r1)
	  fadds     f2, f3, f4
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x4E4
	  fcmpo     cr0, f3, f1
	  bge-      .loc_0x428
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0x398
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lwz       r7, 0x0(r25)
	  addi      r6, r1, 0x5C8
	  lwz       r0, 0x4(r25)
	  stw       r7, 0x5E8(r1)
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5C4(r1)
	  bge-      .loc_0x358
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x358:
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x3F88
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x398:
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x3EF8
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x428:
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0x4C0
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D0(r1)
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x3E60
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x4C0:
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5D4
	  addi      r6, r1, 0x5D0
	  bl        0x3E20
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x5D8(r1)
	  b         .loc_0x184C

	.loc_0x4E4:
	  fcmpo     cr0, f3, f1
	  bge-      .loc_0x660
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x480(r1)
	  lfs       f0, 0x480(r1)
	  stfs      f0, 0x5A4(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5A8(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5AC(r1)
	  lwz       r0, 0x5A4(r1)
	  lwz       r7, 0x5A8(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x5AC(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x46C(r1)
	  lfs       f0, 0x46C(r1)
	  stfs      f0, 0x598(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x59C(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x5A0(r1)
	  lwz       r7, 0x598(r1)
	  lwz       r0, 0x59C(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x5A0(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x620
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x620:
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x3CC0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x660:
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0x7DC
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D0(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x458(r1)
	  lfs       f0, 0x458(r1)
	  stfs      f0, 0x58C(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x590(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x594(r1)
	  lwz       r0, 0x58C(r1)
	  lwz       r7, 0x590(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x594(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x444(r1)
	  lfs       f0, 0x444(r1)
	  stfs      f0, 0x580(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x584(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x588(r1)
	  lwz       r7, 0x580(r1)
	  lwz       r0, 0x584(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x588(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x79C
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x79C:
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x3B44
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x7DC:
	  lfs       f1, 0x0(r25)
	  mr        r3, r24
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x5D0
	  stfs      f0, 0x430(r1)
	  lfs       f0, 0x430(r1)
	  stfs      f0, 0x574(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x578(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x57C(r1)
	  lwz       r0, 0x574(r1)
	  lwz       r7, 0x578(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x57C(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x41C(r1)
	  lfs       f0, 0x41C(r1)
	  stfs      f0, 0x568(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x56C(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x570(r1)
	  lwz       r7, 0x568(r1)
	  lwz       r0, 0x56C(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x570(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f2, -0x7C5C(r2)
	  fmr       f31, f1
	  lfs       f0, 0x5D0(r1)
	  mr        r3, r24
	  addi      r4, r25, 0
	  fsubs     f0, f2, f0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  stfs      f0, 0x5D4(r1)
	  bl        0x3A3C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x8E4:
	  fcmpo     cr0, f3, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xE5C
	  lfs       f4, 0x5D4(r1)
	  lfs       f13, 0x5D0(r1)
	  fadds     f26, f4, f13
	  fcmpo     cr0, f26, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xB10
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0xA2C
	  fcmpo     cr0, f13, f1
	  bge-      .loc_0x9D8
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lwz       r7, 0x0(r25)
	  addi      r6, r1, 0x5C8
	  lwz       r0, 0x4(r25)
	  stw       r7, 0x5E8(r1)
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5C4(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x9D8:
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x5D4(r1)
	  b         .loc_0x184C

	.loc_0xA2C:
	  fcmpo     cr0, f13, f1
	  bge-      .loc_0xA88
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0xA88:
	  fmuls     f26, f5, f3
	  lfs       f31, -0x7C58(r2)
	  fmuls     f5, f29, f4
	  fmuls     f1, f29, f3
	  fmuls     f0, f6, f4
	  fmuls     f30, f28, f3
	  fmuls     f29, f7, f4
	  fmuls     f28, f28, f13
	  fadds     f6, f26, f5
	  fmuls     f5, f7, f13
	  fadds     f0, f1, f0
	  fmuls     f26, f11, f13
	  fadds     f11, f30, f29
	  fmuls     f7, f31, f27
	  fadds     f6, f28, f6
	  fmuls     f1, f31, f12
	  fadds     f0, f5, f0
	  fadds     f5, f7, f6
	  fmuls     f6, f31, f2
	  fadds     f2, f26, f11
	  fadds     f0, f1, f0
	  fmuls     f3, f3, f5
	  fadds     f5, f6, f2
	  fmuls     f2, f4, f0
	  fmuls     f1, f10, f10
	  fmuls     f0, f9, f9
	  fmuls     f4, f13, f5
	  fadds     f3, f3, f2
	  fmuls     f2, f8, f8
	  fadds     f0, f1, f0
	  fadds     f1, f4, f3
	  fadds     f0, f2, f0
	  fadds     f31, f1, f0
	  b         .loc_0x184C

	.loc_0xB10:
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0xC50
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x408(r1)
	  lfs       f0, 0x408(r1)
	  stfs      f0, 0x55C(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x560(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x564(r1)
	  lwz       r0, 0x55C(r1)
	  lwz       r7, 0x560(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x564(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x3F4(r1)
	  lfs       f0, 0x3F4(r1)
	  stfs      f0, 0x550(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x554(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x558(r1)
	  lwz       r7, 0x550(r1)
	  lwz       r0, 0x554(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x558(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0xC50:
	  fcmpo     cr0, f13, f1
	  bge-      .loc_0xD90
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D0(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x3E0(r1)
	  lfs       f0, 0x3E0(r1)
	  stfs      f0, 0x544(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x548(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x54C(r1)
	  lwz       r0, 0x544(r1)
	  lwz       r7, 0x548(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x54C(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x3CC(r1)
	  lfs       f0, 0x3CC(r1)
	  stfs      f0, 0x538(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x53C(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x540(r1)
	  lwz       r7, 0x538(r1)
	  lwz       r0, 0x53C(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x540(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0xD90:
	  lfs       f1, 0x0(r25)
	  mr        r3, r24
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x5D0
	  stfs      f0, 0x3B8(r1)
	  lfs       f0, 0x3B8(r1)
	  stfs      f0, 0x52C(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x530(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x534(r1)
	  lwz       r0, 0x52C(r1)
	  lwz       r7, 0x530(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x534(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x3A4(r1)
	  lfs       f0, 0x3A4(r1)
	  stfs      f0, 0x520(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x524(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x528(r1)
	  lwz       r7, 0x520(r1)
	  lwz       r0, 0x524(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x528(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f2, -0x7C5C(r2)
	  fmr       f31, f1
	  lfs       f0, 0x5D0(r1)
	  fsubs     f0, f2, f0
	  stfs      f0, 0x5D4(r1)
	  b         .loc_0x184C

	.loc_0xE5C:
	  lfs       f3, 0x5D4(r1)
	  lfs       f4, 0x5D0(r1)
	  fadds     f2, f3, f4
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x118C
	  fcmpo     cr0, f3, f1
	  bge-      .loc_0x1070
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0xFB0
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lwz       r7, 0x0(r25)
	  addi      r6, r1, 0x5C8
	  lwz       r0, 0x4(r25)
	  stw       r7, 0x5E8(r1)
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5C4(r1)
	  bge-      .loc_0xF40
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0xF40:
	  lfs       f1, 0x0(r24)
	  mr        r4, r25
	  lfs       f0, 0xC(r24)
	  addi      r3, r1, 0x5DC
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x10(r24)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x14(r24)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x5C4
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x3370
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0xFB0:
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r4, r25
	  stfs      f0, 0x5D4(r1)
	  addi      r3, r1, 0x5DC
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x0(r24)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r31)
	  lfs       f2, 0x4(r24)
	  fadds     f0, f1, f0
	  lfs       f1, 0x4(r31)
	  lfs       f4, 0x8(r24)
	  lfs       f3, 0x8(r31)
	  fadds     f1, f2, f1
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x32B0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x1070:
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0x1138
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r4, r25
	  stfs      f0, 0x5D0(r1)
	  addi      r3, r1, 0x5DC
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x0(r24)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r31)
	  lfs       f2, 0x4(r24)
	  fadds     f0, f1, f0
	  lfs       f1, 0x4(r31)
	  lfs       f4, 0x8(r24)
	  lfs       f3, 0x8(r31)
	  fadds     f1, f2, f1
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x31E8
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x1138:
	  lfs       f1, 0x0(r24)
	  mr        r4, r25
	  lfs       f0, 0x0(r31)
	  addi      r3, r1, 0x5DC
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x4(r31)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  addi      r5, r1, 0x5D4
	  lfs       f1, 0x8(r31)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x5D0
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x3178
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  stfs      f0, 0x5D8(r1)
	  b         .loc_0x184C

	.loc_0x118C:
	  fcmpo     cr0, f3, f1
	  bge-      .loc_0x1338
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D0
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0x18(r25)
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D4(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x360(r1)
	  lfs       f0, 0x360(r1)
	  stfs      f0, 0x514(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x518(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x51C(r1)
	  lwz       r0, 0x514(r1)
	  lwz       r7, 0x518(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x51C(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x34C(r1)
	  lfs       f0, 0x34C(r1)
	  stfs      f0, 0x508(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x50C(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x510(r1)
	  lwz       r7, 0x508(r1)
	  lwz       r0, 0x50C(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x510(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x12C8
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x12C8:
	  lfs       f1, 0x0(r24)
	  mr        r4, r25
	  lfs       f0, 0xC(r24)
	  addi      r3, r1, 0x5DC
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x10(r24)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x14(r24)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x5C4
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x2FE8
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x1338:
	  fcmpo     cr0, f4, f1
	  bge-      .loc_0x14E4
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D0(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x5C4
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x32C(r1)
	  lfs       f0, 0x32C(r1)
	  stfs      f0, 0x4FC(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x500(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x504(r1)
	  lwz       r0, 0x4FC(r1)
	  lwz       r7, 0x500(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x504(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x318(r1)
	  lfs       f0, 0x318(r1)
	  stfs      f0, 0x4F0(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4F4(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4F8(r1)
	  lwz       r7, 0x4F0(r1)
	  lwz       r0, 0x4F4(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x4F8(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x1474
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x1474:
	  lfs       f1, 0x0(r24)
	  mr        r4, r25
	  lfs       f0, 0xC(r24)
	  addi      r3, r1, 0x5DC
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x10(r24)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x14(r24)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x5C4
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x2E3C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x14E4:
	  lfs       f1, 0x0(r25)
	  mr        r3, r24
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x5D0
	  stfs      f0, 0x2F8(r1)
	  lfs       f0, 0x2F8(r1)
	  stfs      f0, 0x4E4(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4E8(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4EC(r1)
	  lwz       r0, 0x4E4(r1)
	  lwz       r7, 0x4E8(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x4EC(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x0(r29)
	  lfs       f0, 0x0(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x2E4(r1)
	  lfs       f0, 0x2E4(r1)
	  stfs      f0, 0x4D8(r1)
	  lfs       f1, 0x4(r29)
	  lfs       f0, 0x4(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4DC(r1)
	  lfs       f1, 0x8(r29)
	  lfs       f0, 0x8(r30)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4E0(r1)
	  lwz       r7, 0x4D8(r1)
	  lwz       r0, 0x4DC(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x4E0(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f2, -0x7C5C(r2)
	  fmr       f31, f1
	  lfs       f0, 0x5D0(r1)
	  addi      r4, r25, 0
	  addi      r3, r1, 0x5DC
	  fsubs     f0, f2, f0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  stfs      f0, 0x5D4(r1)
	  lfs       f1, 0x0(r24)
	  lfs       f0, 0x0(r31)
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x4(r31)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  lfs       f1, 0x8(r31)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x2D04
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)
	  b         .loc_0x184C

	.loc_0x161C:
	  lwz       r6, 0x0(r25)
	  mr        r3, r24
	  lwz       r0, 0x4(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5D8
	  stw       r6, 0x5E8(r1)
	  addi      r6, r1, 0x5D4
	  stw       r0, 0x5EC(r1)
	  lwz       r0, 0x8(r25)
	  stw       r0, 0x5F0(r1)
	  lwz       r7, 0xC(r25)
	  lwz       r0, 0x10(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x14(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r24
	  stfs      f0, 0x5D0(r1)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  lwz       r7, 0x18(r25)
	  addi      r6, r1, 0x5C4
	  lwz       r0, 0x1C(r25)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x20(r25)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5C8(r1)
	  bge-      .loc_0x16C0
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f3, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)

	.loc_0x16C0:
	  lfs       f1, 0x0(r25)
	  mr        r3, r24
	  lfs       f0, 0xC(r25)
	  addi      r4, r1, 0x5E8
	  addi      r5, r1, 0x5CC
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x5C4
	  stfs      f0, 0x2C4(r1)
	  lfs       f0, 0x2C4(r1)
	  stfs      f0, 0x4CC(r1)
	  lfs       f1, 0x4(r25)
	  lfs       f0, 0x10(r25)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4D0(r1)
	  lfs       f1, 0x8(r25)
	  lfs       f0, 0x14(r25)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4D4(r1)
	  lwz       r0, 0x4CC(r1)
	  lwz       r7, 0x4D0(r1)
	  stw       r0, 0x5E8(r1)
	  lwz       r0, 0x4D4(r1)
	  stw       r7, 0x5EC(r1)
	  stw       r0, 0x5F0(r1)
	  lfs       f1, 0x18(r25)
	  lfs       f0, 0xC(r25)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x2B0(r1)
	  lfs       f0, 0x2B0(r1)
	  stfs      f0, 0x4C0(r1)
	  lfs       f1, 0x1C(r25)
	  lfs       f0, 0x10(r25)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4C4(r1)
	  lfs       f1, 0x20(r25)
	  lfs       f0, 0x14(r25)
	  fsubs     f0, f1, f0
	  stfs      f0, 0x4C8(r1)
	  lwz       r7, 0x4C0(r1)
	  lwz       r0, 0x4C4(r1)
	  stw       r7, 0x5F4(r1)
	  stw       r0, 0x5F8(r1)
	  lwz       r0, 0x4C8(r1)
	  stw       r0, 0x5FC(r1)
	  bl        .loc_0x18C4
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f31
	  lfs       f3, 0x5C4(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x5C8(r1)
	  bge-      .loc_0x17A4
	  lfs       f2, 0x5CC(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C8(r1)
	  stfs      f2, 0x5D8(r1)
	  stfs      f0, 0x5D4(r1)
	  stfs      f3, 0x5D0(r1)

	.loc_0x17A4:
	  addi      r3, r24, 0
	  addi      r4, r25, 0
	  addi      r5, r1, 0x5C8
	  addi      r6, r1, 0x5C4
	  bl        0x2B3C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x17E0
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)

	.loc_0x17E0:
	  lfs       f1, 0x0(r24)
	  mr        r4, r25
	  lfs       f0, 0xC(r24)
	  addi      r3, r1, 0x5DC
	  lfs       f3, 0x4(r24)
	  lfs       f2, 0x10(r24)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r24)
	  addi      r5, r1, 0x5C8
	  lfs       f1, 0x14(r24)
	  fadds     f2, f3, f2
	  stfs      f0, 0x5DC(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x5C4
	  stfs      f2, 0x5E0(r1)
	  stfs      f0, 0x5E4(r1)
	  bl        0x2AD0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x5CC(r1)
	  bge-      .loc_0x184C
	  lfs       f2, 0x5C8(r1)
	  fmr       f31, f1
	  lfs       f0, 0x5C4(r1)
	  stfs      f3, 0x5D8(r1)
	  stfs      f2, 0x5D4(r1)
	  stfs      f0, 0x5D0(r1)

	.loc_0x184C:
	  cmplwi    r26, 0
	  beq-      .loc_0x185C
	  lfs       f0, 0x5D8(r1)
	  stfs      f0, 0x0(r26)

	.loc_0x185C:
	  cmplwi    r27, 0
	  beq-      .loc_0x186C
	  lfs       f0, 0x5D4(r1)
	  stfs      f0, 0x0(r27)

	.loc_0x186C:
	  cmplwi    r28, 0
	  beq-      .loc_0x187C
	  lfs       f0, 0x5D0(r1)
	  stfs      f0, 0x0(r28)

	.loc_0x187C:
	  lmw       r24, 0x628(r1)
	  fabs      f1, f31
	  lwz       r0, 0x6AC(r1)
	  lfd       f31, 0x6A0(r1)
	  lfd       f30, 0x698(r1)
	  lfd       f29, 0x690(r1)
	  lfd       f28, 0x688(r1)
	  lfd       f27, 0x680(r1)
	  lfd       f26, 0x678(r1)
	  lfd       f25, 0x670(r1)
	  lfd       f24, 0x668(r1)
	  lfd       f23, 0x660(r1)
	  lfd       f22, 0x658(r1)
	  lfd       f21, 0x650(r1)
	  lfd       f20, 0x648(r1)
	  addi      r1, r1, 0x6A8
	  mtlr      r0
	  blr

	.loc_0x18C4:
	*/
}

/*
 * --INFO--
 * Address: 8003AE50
 * Size:    000828
 */
f32 sqrDistance(KSegment&, KSegment&, f32*, f32*)
{
	/*
	.loc_0x0:
	  stwu      r1, -0xE8(r1)
	  stfd      f31, 0xE0(r1)
	  stfd      f30, 0xD8(r1)
	  stfd      f29, 0xD0(r1)
	  stfd      f28, 0xC8(r1)
	  stfd      f27, 0xC0(r1)
	  stfd      f26, 0xB8(r1)
	  stfd      f25, 0xB0(r1)
	  lfs       f9, 0xC(r3)
	  lfs       f1, 0xC(r4)
	  lfs       f8, 0x10(r3)
	  fmuls     f28, f9, f9
	  lfs       f0, 0x10(r4)
	  fmuls     f4, f9, f1
	  lfs       f10, 0x14(r3)
	  fmuls     f3, f8, f0
	  lfs       f2, 0x14(r4)
	  fmuls     f13, f8, f8
	  fmuls     f7, f1, f1
	  lfs       f26, 0x4(r3)
	  fmuls     f6, f0, f0
	  lfs       f27, 0x4(r4)
	  fadds     f3, f4, f3
	  fmuls     f5, f10, f2
	  lfs       f31, 0x0(r3)
	  fadds     f13, f28, f13
	  lfs       f30, 0x0(r4)
	  fadds     f11, f5, f3
	  fsubs     f5, f31, f30
	  lfs       f25, 0x8(r3)
	  fsubs     f4, f26, f27
	  lfs       f3, 0x8(r4)
	  fmuls     f29, f10, f10
	  fadds     f7, f7, f6
	  lfs       f12, -0x7A14(r13)
	  fmuls     f28, f2, f2
	  fadds     f6, f29, f13
	  fneg      f11, f11
	  fmuls     f29, f5, f9
	  fmuls     f30, f4, f8
	  fadds     f7, f28, f7
	  fsubs     f3, f25, f3
	  fmuls     f13, f11, f11
	  fmuls     f8, f6, f7
	  fmuls     f31, f5, f5
	  fmuls     f9, f4, f4
	  fsubs     f8, f8, f13
	  fmuls     f28, f3, f10
	  fadds     f30, f29, f30
	  fabs      f10, f8
	  fmuls     f13, f3, f3
	  fadds     f9, f31, f9
	  fcmpo     cr0, f10, f12
	  fadds     f8, f28, f30
	  fadds     f9, f13, f9
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x664
	  fmuls     f1, f5, f1
	  lfs       f5, -0x7C60(r2)
	  fmuls     f0, f4, f0
	  fmuls     f4, f3, f2
	  fmuls     f3, f7, f8
	  fadds     f0, f1, f0
	  fmuls     f2, f11, f8
	  fadds     f0, f4, f0
	  fneg      f0, f0
	  fmuls     f4, f11, f0
	  fmuls     f1, f6, f0
	  fsubs     f3, f4, f3
	  fsubs     f1, f2, f1
	  fcmpo     cr0, f3, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x4A4
	  fcmpo     cr0, f3, f10
	  cror      2, 0, 0x2
	  bne-      .loc_0x270
	  fcmpo     cr0, f1, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x218
	  fcmpo     cr0, f1, f10
	  cror      2, 0, 0x2
	  bne-      .loc_0x198
	  lfs       f2, -0x7C5C(r2)
	  lfs       f12, -0x7C58(r2)
	  fdivs     f2, f2, f10
	  fmuls     f10, f3, f2
	  fmuls     f1, f1, f2
	  fmuls     f8, f12, f8
	  fmuls     f5, f6, f10
	  fmuls     f4, f11, f1
	  fmuls     f3, f11, f10
	  fmuls     f2, f7, f1
	  fadds     f5, f5, f4
	  fmuls     f4, f12, f0
	  fadds     f0, f3, f2
	  fadds     f2, f8, f5
	  fadds     f0, f4, f0
	  fmuls     f2, f10, f2
	  fmuls     f0, f1, f0
	  fadds     f0, f2, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x198:
	  fadds     f4, f11, f8
	  lfs       f1, -0x7C5C(r2)
	  fcmpo     cr0, f4, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1C4
	  lfs       f2, -0x7C58(r2)
	  fmr       f10, f5
	  fmuls     f0, f2, f0
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x1C4:
	  fneg      f2, f4
	  fcmpo     cr0, f2, f6
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1F4
	  fadds     f3, f6, f7
	  lfs       f2, -0x7C58(r2)
	  fadds     f0, f0, f4
	  fmr       f10, f1
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x1F4:
	  fdivs     f5, f2, f6
	  lfs       f3, -0x7C58(r2)
	  fmuls     f2, f4, f5
	  fmuls     f3, f3, f0
	  fmr       f10, f5
	  fadds     f0, f7, f2
	  fadds     f0, f3, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x218:
	  fcmpo     cr0, f8, f5
	  fmr       f1, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x234
	  fmr       f10, f5
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x234:
	  fneg      f0, f8
	  fcmpo     cr0, f0, f6
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x25C
	  lfs       f0, -0x7C58(r2)
	  lfs       f10, -0x7C5C(r2)
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x25C:
	  fdivs     f2, f0, f6
	  fmuls     f0, f8, f2
	  fmr       f10, f2
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x270:
	  fcmpo     cr0, f1, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x3E8
	  fcmpo     cr0, f1, f10
	  cror      2, 0, 0x2
	  bne-      .loc_0x308
	  fadds     f0, f11, f0
	  lfs       f10, -0x7C5C(r2)
	  fcmpo     cr0, f0, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x2B4
	  lfs       f0, -0x7C58(r2)
	  fmr       f1, f5
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x2B4:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x2E4
	  fadds     f3, f6, f7
	  lfs       f2, -0x7C58(r2)
	  fadds     f0, f8, f0
	  fmr       f1, f10
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x2E4:
	  fdivs     f3, f1, f7
	  lfs       f1, -0x7C58(r2)
	  fmuls     f0, f0, f3
	  fmuls     f2, f1, f8
	  fmr       f1, f3
	  fadds     f0, f6, f0
	  fadds     f0, f2, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x308:
	  fadds     f4, f11, f8
	  fneg      f2, f4
	  fcmpo     cr0, f2, f6
	  cror      2, 0, 0x2
	  bne-      .loc_0x368
	  fcmpo     cr0, f4, f5
	  lfs       f1, -0x7C5C(r2)
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x344
	  lfs       f2, -0x7C58(r2)
	  fmr       f10, f5
	  fmuls     f0, f2, f0
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x344:
	  fdivs     f5, f2, f6
	  lfs       f3, -0x7C58(r2)
	  fmuls     f2, f4, f5
	  fmuls     f3, f3, f0
	  fmr       f10, f5
	  fadds     f0, f7, f2
	  fadds     f0, f3, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x368:
	  fadds     f0, f11, f0
	  lfs       f10, -0x7C5C(r2)
	  fcmpo     cr0, f0, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x394
	  lfs       f0, -0x7C58(r2)
	  fmr       f1, f5
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x394:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x3C4
	  fadds     f3, f6, f7
	  lfs       f2, -0x7C58(r2)
	  fadds     f0, f8, f0
	  fmr       f1, f10
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x3C4:
	  fdivs     f3, f1, f7
	  lfs       f1, -0x7C58(r2)
	  fmuls     f0, f0, f3
	  fmuls     f2, f1, f8
	  fmr       f1, f3
	  fadds     f0, f6, f0
	  fadds     f0, f2, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x3E8:
	  fneg      f2, f8
	  fcmpo     cr0, f2, f6
	  bge-      .loc_0x424
	  fcmpo     cr0, f8, f5
	  fmr       f1, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x410
	  fmr       f10, f5
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x410:
	  fdivs     f2, f2, f6
	  fmuls     f0, f8, f2
	  fmr       f10, f2
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x424:
	  fadds     f0, f11, f0
	  lfs       f10, -0x7C5C(r2)
	  fcmpo     cr0, f0, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x450
	  lfs       f0, -0x7C58(r2)
	  fmr       f1, f5
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x450:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x480
	  fadds     f3, f6, f7
	  lfs       f2, -0x7C58(r2)
	  fadds     f0, f8, f0
	  fmr       f1, f10
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x480:
	  fdivs     f3, f1, f7
	  lfs       f1, -0x7C58(r2)
	  fmuls     f0, f0, f3
	  fmuls     f2, f1, f8
	  fmr       f1, f3
	  fadds     f0, f6, f0
	  fadds     f0, f2, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x4A4:
	  fcmpo     cr0, f1, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x5C8
	  fcmpo     cr0, f1, f10
	  cror      2, 0, 0x2
	  bne-      .loc_0x510
	  fcmpo     cr0, f0, f5
	  fmr       f10, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x4D8
	  fmr       f1, f5
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x4D8:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x500
	  lfs       f2, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f0, f2, f0
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x500:
	  fdivs     f1, f1, f7
	  fmuls     f0, f0, f1
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x510:
	  fadds     f4, f11, f8
	  fcmpo     cr0, f4, f5
	  bge-      .loc_0x574
	  fneg      f2, f4
	  lfs       f1, -0x7C5C(r2)
	  fcmpo     cr0, f2, f6
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x550
	  fadds     f3, f6, f7
	  lfs       f2, -0x7C58(r2)
	  fadds     f0, f0, f4
	  fmr       f10, f1
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x550:
	  fdivs     f5, f2, f6
	  lfs       f3, -0x7C58(r2)
	  fmuls     f2, f4, f5
	  fmuls     f3, f3, f0
	  fmr       f10, f5
	  fadds     f0, f7, f2
	  fadds     f0, f3, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x574:
	  fcmpo     cr0, f0, f5
	  fmr       f10, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x590
	  fmr       f1, f5
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x590:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x5B8
	  lfs       f2, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f0, f2, f0
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x5B8:
	  fdivs     f1, f1, f7
	  fmuls     f0, f0, f1
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x5C8:
	  fcmpo     cr0, f8, f5
	  bge-      .loc_0x610
	  fneg      f0, f8
	  fmr       f1, f5
	  fcmpo     cr0, f0, f6
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x5FC
	  lfs       f0, -0x7C58(r2)
	  lfs       f10, -0x7C5C(r2)
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x5FC:
	  fdivs     f2, f0, f6
	  fmuls     f0, f8, f2
	  fmr       f10, f2
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x610:
	  fcmpo     cr0, f0, f5
	  fmr       f10, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x62C
	  fmr       f1, f5
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x62C:
	  fneg      f1, f0
	  fcmpo     cr0, f1, f7
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x654
	  lfs       f2, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f0, f2, f0
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x654:
	  fdivs     f1, f1, f7
	  fmuls     f0, f0, f1
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x664:
	  lfs       f12, -0x7C60(r2)
	  fcmpo     cr0, f11, f12
	  ble-      .loc_0x738
	  fcmpo     cr0, f8, f12
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x68C
	  fmr       f10, f12
	  fmr       f1, f12
	  fmr       f0, f9
	  b         .loc_0x7E8

	.loc_0x68C:
	  fneg      f10, f8
	  fcmpo     cr0, f10, f6
	  cror      2, 0, 0x2
	  bne-      .loc_0x6B4
	  fdivs     f1, f10, f6
	  fmuls     f0, f8, f1
	  fmr       f10, f1
	  fmr       f1, f12
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x6B4:
	  fadds     f12, f6, f8
	  lfs       f10, -0x7C5C(r2)
	  fmuls     f5, f5, f1
	  fmuls     f1, f4, f0
	  fneg      f0, f12
	  fmuls     f2, f3, f2
	  fadds     f1, f5, f1
	  fcmpo     cr0, f0, f11
	  fadds     f1, f2, f1
	  fneg      f5, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x708
	  fadds     f0, f11, f8
	  lfs       f2, -0x7C58(r2)
	  fadds     f3, f6, f7
	  fmr       f1, f10
	  fadds     f0, f5, f0
	  fadds     f3, f9, f3
	  fmuls     f0, f2, f0
	  fadds     f0, f3, f0
	  b         .loc_0x7E8

	.loc_0x708:
	  fdivs     f1, f0, f11
	  lfs       f4, -0x7C58(r2)
	  fadds     f0, f11, f5
	  fmuls     f3, f4, f8
	  fmuls     f2, f7, f1
	  fmuls     f0, f4, f0
	  fadds     f3, f6, f3
	  fadds     f0, f2, f0
	  fadds     f2, f9, f3
	  fmuls     f0, f1, f0
	  fadds     f0, f2, f0
	  b         .loc_0x7E8

	.loc_0x738:
	  fneg      f13, f8
	  fcmpo     cr0, f13, f6
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x764
	  lfs       f0, -0x7C58(r2)
	  fmr       f1, f12
	  lfs       f10, -0x7C5C(r2)
	  fmuls     f0, f0, f8
	  fadds     f0, f6, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x764:
	  fcmpo     cr0, f8, f12
	  cror      2, 0, 0x2
	  bne-      .loc_0x788
	  fdivs     f1, f13, f6
	  fmuls     f0, f8, f1
	  fmr       f10, f1
	  fmr       f1, f12
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x788:
	  fmuls     f5, f5, f1
	  fmuls     f1, f4, f0
	  fneg      f0, f11
	  fmuls     f2, f3, f2
	  fadds     f1, f5, f1
	  fcmpo     cr0, f8, f0
	  fmr       f10, f12
	  fadds     f0, f2, f1
	  fneg      f2, f0
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x7CC
	  lfs       f0, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f0, f0, f2
	  fadds     f0, f7, f0
	  fadds     f0, f9, f0
	  b         .loc_0x7E8

	.loc_0x7CC:
	  fdivs     f1, f13, f11
	  lfs       f0, -0x7C58(r2)
	  fmuls     f2, f0, f2
	  fmuls     f0, f7, f1
	  fadds     f0, f2, f0
	  fmuls     f0, f1, f0
	  fadds     f0, f9, f0

	.loc_0x7E8:
	  cmplwi    r5, 0
	  beq-      .loc_0x7F4
	  stfs      f10, 0x0(r5)

	.loc_0x7F4:
	  cmplwi    r6, 0
	  beq-      .loc_0x800
	  stfs      f1, 0x0(r6)

	.loc_0x800:
	  fabs      f1, f0
	  lfd       f31, 0xE0(r1)
	  lfd       f30, 0xD8(r1)
	  lfd       f29, 0xD0(r1)
	  lfd       f28, 0xC8(r1)
	  lfd       f27, 0xC0(r1)
	  lfd       f26, 0xB8(r1)
	  lfd       f25, 0xB0(r1)
	  addi      r1, r1, 0xE8
	  blr
	*/
}

/*
 * --INFO--
 * Address: 8003B678
 * Size:    001D9C
 */
f32 sqrDistance(KSegment&, KRect&, f32*, f32*, f32*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x720(r1)
	  stfd      f31, 0x718(r1)
	  stfd      f30, 0x710(r1)
	  stfd      f29, 0x708(r1)
	  stfd      f28, 0x700(r1)
	  stfd      f27, 0x6F8(r1)
	  stfd      f26, 0x6F0(r1)
	  stfd      f25, 0x6E8(r1)
	  stfd      f24, 0x6E0(r1)
	  stfd      f23, 0x6D8(r1)
	  stfd      f22, 0x6D0(r1)
	  stfd      f21, 0x6C8(r1)
	  stmw      r25, 0x6AC(r1)
	  lfs       f31, 0xC(r3)
	  mr        r26, r4
	  lfs       f5, 0xC(r4)
	  mr        r25, r3
	  lfs       f2, 0x18(r4)
	  lfs       f13, 0x10(r3)
	  fmuls     f12, f31, f5
	  lfs       f4, 0x10(r4)
	  fmuls     f10, f31, f2
	  lfs       f0, 0x1C(r4)
	  fmuls     f11, f13, f4
	  fmuls     f9, f13, f0
	  lfs       f30, 0x14(r3)
	  lfs       f6, 0x14(r4)
	  fmuls     f8, f31, f31
	  lfs       f3, 0x20(r4)
	  fadds     f12, f12, f11
	  lfs       f25, 0x4(r4)
	  fmuls     f21, f30, f6
	  lfs       f24, 0x4(r3)
	  fadds     f9, f10, f9
	  fadds     f21, f21, f12
	  lfs       f23, 0x0(r4)
	  fmuls     f11, f30, f3
	  lfs       f22, 0x0(r3)
	  fmuls     f7, f13, f13
	  fadds     f12, f11, f9
	  lfs       f28, 0x8(r4)
	  fsubs     f11, f23, f22
	  lfs       f27, 0x8(r3)
	  fsubs     f10, f25, f24
	  fsubs     f9, f28, f27
	  lfs       f1, -0x7C60(r2)
	  fneg      f26, f21
	  addi      r31, r25, 0xC
	  fneg      f25, f12
	  fmuls     f23, f5, f5
	  stfs      f1, 0x678(r1)
	  fmuls     f21, f4, f4
	  addi      r8, r26, 0xC
	  fmuls     f22, f2, f2
	  fmuls     f12, f0, f0
	  stfs      f1, 0x674(r1)
	  fmuls     f27, f6, f6
	  addi      r30, r26, 0x18
	  fadds     f24, f23, f21
	  fmuls     f23, f3, f3
	  stfs      f1, 0x670(r1)
	  fadds     f12, f22, f12
	  mr        r27, r5
	  fadds     f7, f8, f7
	  fmuls     f28, f30, f30
	  stfs      f1, 0x684(r1)
	  fadds     f12, f23, f12
	  mr        r28, r6
	  fneg      f23, f26
	  stfs      f1, 0x680(r1)
	  fadds     f8, f27, f24
	  fneg      f22, f25
	  mr        r29, r7
	  fadds     f7, f28, f7
	  stfs      f1, 0x67C(r1)
	  fmuls     f27, f22, f8
	  fmuls     f29, f23, f12
	  stfs      f1, 0x66C(r1)
	  fmuls     f28, f8, f12
	  stfs      f1, 0x668(r1)
	  fmuls     f22, f26, f29
	  fmuls     f23, f7, f28
	  lfs       f21, -0x7A14(r13)
	  fmuls     f24, f25, f27
	  stfs      f1, 0x664(r1)
	  fadds     f22, f23, f22
	  fmuls     f23, f9, f30
	  fmuls     f31, f11, f31
	  fmuls     f13, f10, f13
	  fadds     f30, f24, f22
	  fmuls     f5, f11, f5
	  fadds     f13, f31, f13
	  fmuls     f4, f10, f4
	  fabs      f22, f30
	  fadds     f13, f23, f13
	  fmuls     f2, f11, f2
	  fmuls     f0, f10, f0
	  fcmpo     cr0, f22, f21
	  fmuls     f6, f9, f6
	  fadds     f4, f5, f4
	  fadds     f0, f2, f0
	  fmuls     f3, f9, f3
	  fneg      f13, f13
	  cror      2, 0x1, 0x2
	  fadds     f2, f6, f4
	  fadds     f3, f3, f0
	  bne-      .loc_0x1A94
	  lfs       f0, -0x7C5C(r2)
	  fneg      f4, f13
	  fneg      f5, f2
	  fdivs     f21, f0, f30
	  fmuls     f4, f4, f21
	  fmuls     f6, f5, f21
	  fneg      f5, f3
	  fmuls     f23, f28, f4
	  fmuls     f22, f29, f6
	  fmuls     f28, f5, f21
	  fmuls     f30, f7, f12
	  fmuls     f5, f25, f26
	  fmuls     f24, f25, f25
	  fmuls     f21, f27, f28
	  fadds     f22, f23, f22
	  fsubs     f24, f30, f24
	  fmuls     f31, f7, f8
	  fmuls     f30, f26, f26
	  fadds     f22, f21, f22
	  fmuls     f23, f29, f4
	  fmuls     f24, f24, f6
	  fsubs     f29, f31, f30
	  stfs      f22, 0x660(r1)
	  fmuls     f27, f27, f4
	  fmuls     f6, f5, f6
	  lfs       f4, 0x660(r1)
	  fmuls     f31, f5, f28
	  fadds     f30, f23, f24
	  fmuls     f28, f29, f28
	  fadds     f5, f27, f6
	  fadds     f6, f31, f30
	  fcmpo     cr0, f4, f1
	  fadds     f5, f28, f5
	  stfs      f6, 0x65C(r1)
	  stfs      f5, 0x658(r1)
	  bge-      .loc_0xA48
	  lfs       f2, 0x65C(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x528
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x358
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xAC4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xB14
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x318
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x318:
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1EDC
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x358:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x3F4
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xBCC
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1E40
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x3F4:
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xC5C
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x514(r1)
	  lfs       f0, 0x514(r1)
	  stfs      f0, 0x62C(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x630(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x634(r1)
	  lwz       r0, 0x62C(r1)
	  lwz       r7, 0x630(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x634(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xCE4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x4E8
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x4E8:
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1D0C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x528:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x6C8
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x5D0
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x65C
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xDA8
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x658(r1)
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1C64
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x5D0:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x600
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x65C
	  addi      r6, r1, 0x658
	  bl        0x1C18
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x660(r1)
	  b         .loc_0x1D28

	.loc_0x600:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x65C
	  stfs      f0, 0x500(r1)
	  lfs       f0, 0x500(r1)
	  stfs      f0, 0x620(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x624(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x628(r1)
	  lwz       r0, 0x620(r1)
	  lwz       r7, 0x624(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x628(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xEA0
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x658(r1)
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1B6C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x6C8:
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x808
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x4EC(r1)
	  lfs       f0, 0x4EC(r1)
	  stfs      f0, 0x614(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x618(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x61C(r1)
	  lwz       r0, 0x614(r1)
	  lwz       r7, 0x618(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x61C(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xF74
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0xFC4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x7C8
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x7C8:
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1A2C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x808:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x8DC
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x4D8(r1)
	  lfs       f0, 0x4D8(r1)
	  stfs      f0, 0x608(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x60C(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x610(r1)
	  lwz       r0, 0x608(r1)
	  lwz       r7, 0x60C(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x610(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x10B4
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x1958
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x8DC:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x4C4(r1)
	  lfs       f0, 0x4C4(r1)
	  stfs      f0, 0x5FC(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x600(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x604(r1)
	  lwz       r0, 0x5FC(r1)
	  lwz       r7, 0x600(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x604(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x117C
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x4B0(r1)
	  lfs       f0, 0x4B0(r1)
	  stfs      f0, 0x5F0(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5F4(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5F8(r1)
	  lwz       r0, 0x5F0(r1)
	  lwz       r7, 0x5F4(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5F8(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1204
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0xA08
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0xA08:
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x17EC
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xA48:
	  fcmpo     cr0, f4, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x10CC
	  lfs       f5, 0x65C(r1)
	  fcmpo     cr0, f5, f1
	  bge-      .loc_0xC84
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0xB2C
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x12D4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1324
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xB2C:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xB8C
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x13A0
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x65C(r1)
	  b         .loc_0x1D28

	.loc_0xB8C:
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x13F4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x49C(r1)
	  lfs       f0, 0x49C(r1)
	  stfs      f0, 0x5E4(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5E8(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5EC(r1)
	  lwz       r0, 0x5E4(r1)
	  lwz       r7, 0x5E8(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5EC(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x147C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xC84:
	  fcmpo     cr0, f5, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xE00
	  lfs       f6, 0x658(r1)
	  fcmpo     cr0, f6, f1
	  bge-      .loc_0xCF0
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x65C
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1504
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xCF0:
	  fcmpo     cr0, f6, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xD74
	  fmuls     f7, f7, f4
	  lfs       f28, -0x7C58(r2)
	  fmuls     f0, f26, f5
	  fmuls     f27, f25, f6
	  fmuls     f1, f26, f4
	  fadds     f7, f7, f0
	  fmuls     f0, f8, f5
	  fmuls     f25, f25, f4
	  fmuls     f12, f12, f6
	  fmuls     f8, f28, f13
	  fadds     f7, f27, f7
	  fmuls     f2, f28, f2
	  fadds     f0, f1, f0
	  fadds     f1, f8, f7
	  fmuls     f8, f28, f3
	  fadds     f7, f25, f12
	  fadds     f0, f2, f0
	  fmuls     f3, f4, f1
	  fadds     f4, f8, f7
	  fmuls     f2, f5, f0
	  fmuls     f1, f11, f11
	  fmuls     f0, f10, f10
	  fmuls     f4, f6, f4
	  fadds     f3, f3, f2
	  fmuls     f2, f9, f9
	  fadds     f0, f1, f0
	  fadds     f1, f4, f3
	  fadds     f0, f2, f0
	  fadds     f31, f1, f0
	  b         .loc_0x1D28

	.loc_0xD74:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x65C
	  stfs      f0, 0x488(r1)
	  lfs       f0, 0x488(r1)
	  stfs      f0, 0x5D8(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5DC(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5E0(r1)
	  lwz       r0, 0x5D8(r1)
	  lwz       r7, 0x5DC(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5E0(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1614
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xE00:
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0xF04
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x474(r1)
	  lfs       f0, 0x474(r1)
	  stfs      f0, 0x5CC(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5D0(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5D4(r1)
	  lwz       r0, 0x5CC(r1)
	  lwz       r7, 0x5D0(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5D4(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x16AC
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x16FC
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0xF04:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0xF9C
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x460(r1)
	  lfs       f0, 0x460(r1)
	  stfs      f0, 0x5C0(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5C4(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5C8(r1)
	  lwz       r0, 0x5C0(r1)
	  lwz       r7, 0x5C4(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5C8(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x17B0
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  stfs      f0, 0x65C(r1)
	  b         .loc_0x1D28

	.loc_0xF9C:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x44C(r1)
	  lfs       f0, 0x44C(r1)
	  stfs      f0, 0x5B4(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5B8(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5BC(r1)
	  lwz       r0, 0x5B4(r1)
	  lwz       r7, 0x5B8(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5BC(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x183C
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x438(r1)
	  lfs       f0, 0x438(r1)
	  stfs      f0, 0x5A8(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5AC(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5B0(r1)
	  lwz       r0, 0x5A8(r1)
	  lwz       r7, 0x5AC(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5B0(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x18C4
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x10CC:
	  lfs       f2, 0x65C(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x1454
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x1210
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x194C
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x199C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x11A0
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x11A0:
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0xC(r25)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x10(r25)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x14(r25)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0x1024
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x1210:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x12F0
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1A84
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0xF88
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0x0(r31)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x4(r31)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x8(r31)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xF44
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x12F0:
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x658
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1B58
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x40C(r1)
	  lfs       f0, 0x40C(r1)
	  stfs      f0, 0x59C(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5A0(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x5A4(r1)
	  lwz       r0, 0x59C(r1)
	  lwz       r7, 0x5A0(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x5A4(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1BE0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x13E4
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x13E4:
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0xC(r25)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x10(r25)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x14(r25)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xDE0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x1454:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x1684
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x152C
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x65C
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1CD4
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r4, r26
	  stfs      f0, 0x658(r1)
	  addi      r3, r1, 0x664
	  addi      r5, r1, 0x650
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x64C
	  lfs       f0, 0x0(r31)
	  lfs       f2, 0x4(r25)
	  fadds     f0, f1, f0
	  lfs       f1, 0x4(r31)
	  lfs       f4, 0x8(r25)
	  lfs       f3, 0x8(r31)
	  fadds     f1, f2, f1
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xD08
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x152C:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x158C
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0x0(r31)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x4(r31)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x65C
	  lfs       f1, 0x8(r31)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x658
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xC8C
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  stfs      f0, 0x660(r1)
	  b         .loc_0x1D28

	.loc_0x158C:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r30)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x65C
	  stfs      f0, 0x3D4(r1)
	  lfs       f0, 0x3D4(r1)
	  stfs      f0, 0x590(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x594(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x598(r1)
	  lwz       r0, 0x590(r1)
	  lwz       r7, 0x594(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x598(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1E2C
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r4, r26
	  stfs      f0, 0x658(r1)
	  addi      r3, r1, 0x664
	  addi      r5, r1, 0x650
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x64C
	  lfs       f0, 0x0(r31)
	  lfs       f2, 0x4(r25)
	  fadds     f0, f1, f0
	  lfs       f1, 0x4(r31)
	  lfs       f4, 0x8(r25)
	  lfs       f3, 0x8(r31)
	  fadds     f1, f2, f1
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xBB0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x1684:
	  lfs       f2, 0x658(r1)
	  fcmpo     cr0, f2, f1
	  bge-      .loc_0x17F4
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x3B4(r1)
	  lfs       f0, 0x3B4(r1)
	  stfs      f0, 0x584(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x588(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x58C(r1)
	  lwz       r0, 0x584(r1)
	  lwz       r7, 0x588(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x58C(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1F30
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x0(r26)
	  addi      r6, r1, 0x650
	  lwz       r0, 0x4(r26)
	  stw       r7, 0x670(r1)
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x1F80
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1784
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x1784:
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0xC(r25)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x10(r25)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x14(r25)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0xA40
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x17F4:
	  fcmpo     cr0, f2, f0
	  cror      2, 0, 0x2
	  bne-      .loc_0x18F8
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x394(r1)
	  lfs       f0, 0x394(r1)
	  stfs      f0, 0x578(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x57C(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x580(r1)
	  lwz       r0, 0x578(r1)
	  lwz       r7, 0x57C(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x580(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x20A0
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r4, r26
	  stfs      f0, 0x65C(r1)
	  addi      r3, r1, 0x664
	  addi      r5, r1, 0x650
	  lfs       f1, 0x0(r25)
	  addi      r6, r1, 0x64C
	  lfs       f0, 0x0(r31)
	  lfs       f2, 0x4(r25)
	  fadds     f0, f1, f0
	  lfs       f1, 0x4(r31)
	  lfs       f4, 0x8(r25)
	  lfs       f3, 0x8(r31)
	  fadds     f1, f2, f1
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f3
	  stfs      f1, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0x93C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x18F8:
	  lfs       f1, 0x0(r26)
	  mr        r3, r25
	  lfs       f0, 0x0(r8)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x658
	  stfs      f0, 0x374(r1)
	  lfs       f0, 0x374(r1)
	  stfs      f0, 0x56C(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x570(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r8)
	  fadds     f0, f1, f0
	  stfs      f0, 0x574(r1)
	  lwz       r0, 0x56C(r1)
	  lwz       r7, 0x570(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x574(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x2198
	  lfs       f0, -0x7C5C(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x65C(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lfs       f1, 0x0(r26)
	  addi      r6, r1, 0x650
	  lfs       f0, 0x0(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x360(r1)
	  lfs       f0, 0x360(r1)
	  stfs      f0, 0x560(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x4(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x564(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x8(r30)
	  fadds     f0, f1, f0
	  stfs      f0, 0x568(r1)
	  lwz       r0, 0x560(r1)
	  lwz       r7, 0x564(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x568(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x2220
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1A24
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x1A24:
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0xC(r25)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x10(r25)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x14(r25)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0x7A0
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)
	  b         .loc_0x1D28

	.loc_0x1A94:
	  lwz       r6, 0x0(r26)
	  mr        r3, r25
	  lwz       r0, 0x4(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x660
	  stw       r6, 0x670(r1)
	  addi      r6, r1, 0x65C
	  stw       r0, 0x674(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x22FC
	  lfs       f0, -0x7C60(r2)
	  fmr       f31, f1
	  mr        r3, r25
	  stfs      f0, 0x658(r1)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  lwz       r7, 0x18(r26)
	  addi      r6, r1, 0x64C
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x2334
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x650(r1)
	  bge-      .loc_0x1B38
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f3, 0x65C(r1)
	  stfs      f0, 0x658(r1)

	.loc_0x1B38:
	  lfs       f1, 0x0(r26)
	  addi      r3, r25, 0
	  lfs       f0, 0x18(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x650
	  stfs      f0, 0x340(r1)
	  lfs       f0, 0x340(r1)
	  stfs      f0, 0x554(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x1C(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0x558(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x20(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0x55C(r1)
	  lwz       r0, 0x554(r1)
	  lwz       r7, 0x558(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x55C(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x23D8
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x64C(r1)
	  bge-      .loc_0x1BDC
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x650(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f0, 0x65C(r1)
	  stfs      f3, 0x658(r1)

	.loc_0x1BDC:
	  lfs       f1, 0x0(r26)
	  addi      r3, r25, 0
	  lfs       f0, 0xC(r26)
	  addi      r4, r1, 0x670
	  addi      r5, r1, 0x654
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x64C
	  stfs      f0, 0x32C(r1)
	  lfs       f0, 0x32C(r1)
	  stfs      f0, 0x548(r1)
	  lfs       f1, 0x4(r26)
	  lfs       f0, 0x10(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0x54C(r1)
	  lfs       f1, 0x8(r26)
	  lfs       f0, 0x14(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0x550(r1)
	  lwz       r0, 0x548(r1)
	  lwz       r7, 0x54C(r1)
	  stw       r0, 0x670(r1)
	  lwz       r0, 0x550(r1)
	  stw       r7, 0x674(r1)
	  stw       r0, 0x678(r1)
	  lwz       r7, 0x18(r26)
	  lwz       r0, 0x1C(r26)
	  stw       r7, 0x67C(r1)
	  stw       r0, 0x680(r1)
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x684(r1)
	  bl        -0x247C
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x650(r1)
	  bge-      .loc_0x1C80
	  lfs       f2, 0x654(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f2, 0x660(r1)
	  stfs      f3, 0x65C(r1)
	  stfs      f0, 0x658(r1)

	.loc_0x1C80:
	  addi      r3, r25, 0
	  addi      r4, r26, 0
	  addi      r5, r1, 0x650
	  addi      r6, r1, 0x64C
	  bl        0x574
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1CBC
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)

	.loc_0x1CBC:
	  lfs       f1, 0x0(r25)
	  mr        r4, r26
	  lfs       f0, 0xC(r25)
	  addi      r3, r1, 0x664
	  lfs       f3, 0x4(r25)
	  lfs       f2, 0x10(r25)
	  fadds     f0, f1, f0
	  lfs       f4, 0x8(r25)
	  addi      r5, r1, 0x650
	  lfs       f1, 0x14(r25)
	  fadds     f2, f3, f2
	  stfs      f0, 0x664(r1)
	  fadds     f0, f4, f1
	  addi      r6, r1, 0x64C
	  stfs      f2, 0x668(r1)
	  stfs      f0, 0x66C(r1)
	  bl        0x508
	  fcmpo     cr0, f1, f31
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x654(r1)
	  bge-      .loc_0x1D28
	  lfs       f2, 0x650(r1)
	  fmr       f31, f1
	  lfs       f0, 0x64C(r1)
	  stfs      f3, 0x660(r1)
	  stfs      f2, 0x65C(r1)
	  stfs      f0, 0x658(r1)

	.loc_0x1D28:
	  cmplwi    r27, 0
	  beq-      .loc_0x1D38
	  lfs       f0, 0x660(r1)
	  stfs      f0, 0x0(r27)

	.loc_0x1D38:
	  cmplwi    r28, 0
	  beq-      .loc_0x1D48
	  lfs       f0, 0x65C(r1)
	  stfs      f0, 0x0(r28)

	.loc_0x1D48:
	  cmplwi    r29, 0
	  beq-      .loc_0x1D58
	  lfs       f0, 0x658(r1)
	  stfs      f0, 0x0(r29)

	.loc_0x1D58:
	  lmw       r25, 0x6AC(r1)
	  fabs      f1, f31
	  lwz       r0, 0x724(r1)
	  lfd       f31, 0x718(r1)
	  lfd       f30, 0x710(r1)
	  lfd       f29, 0x708(r1)
	  lfd       f28, 0x700(r1)
	  lfd       f27, 0x6F8(r1)
	  lfd       f26, 0x6F0(r1)
	  lfd       f25, 0x6E8(r1)
	  lfd       f24, 0x6E0(r1)
	  lfd       f23, 0x6D8(r1)
	  lfd       f22, 0x6D0(r1)
	  lfd       f21, 0x6C8(r1)
	  addi      r1, r1, 0x720
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 8003D414
 * Size:    000468
 */
f32 sqrDistance(KTri&, KRect&, f32*, f32*, f32*, f32*)
{
	/*
	.loc_0x0:
	  mflr      r0
	  stw       r0, 0x4(r1)
	  stwu      r1, -0x160(r1)
	  stfd      f31, 0x158(r1)
	  stfd      f30, 0x150(r1)
	  stmw      r26, 0x138(r1)
	  addi      r26, r3, 0
	  addi      r28, r5, 0
	  addi      r29, r6, 0
	  addi      r30, r7, 0
	  addi      r31, r8, 0
	  addi      r27, r4, 0
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x130
	  lfs       f0, -0x7C60(r2)
	  addi      r6, r1, 0x124
	  addi      r7, r1, 0x120
	  stfs      f0, 0x108(r1)
	  stfs      f0, 0x104(r1)
	  stfs      f0, 0x100(r1)
	  stfs      f0, 0x114(r1)
	  stfs      f0, 0x110(r1)
	  stfs      f0, 0x10C(r1)
	  lwz       r8, 0x0(r26)
	  lwz       r0, 0x4(r26)
	  stw       r8, 0x100(r1)
	  stw       r0, 0x104(r1)
	  lwz       r0, 0x8(r26)
	  stw       r0, 0x108(r1)
	  lwz       r8, 0xC(r26)
	  lwz       r0, 0x10(r26)
	  stw       r8, 0x10C(r1)
	  stw       r0, 0x110(r1)
	  lwz       r0, 0x14(r26)
	  stw       r0, 0x114(r1)
	  bl        -0x1E28
	  lfs       f31, -0x7C60(r2)
	  fmr       f30, f1
	  lwz       r3, 0x18(r26)
	  mr        r4, r27
	  lwz       r0, 0x1C(r26)
	  addi      r5, r1, 0x128
	  stw       r3, 0x10C(r1)
	  addi      r3, r1, 0x100
	  addi      r6, r1, 0x11C
	  stw       r0, 0x110(r1)
	  addi      r7, r1, 0x118
	  lwz       r0, 0x20(r26)
	  stw       r0, 0x114(r1)
	  bl        -0x1E60
	  fcmpo     cr0, f1, f30
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x12C(r1)
	  bge-      .loc_0xF4
	  lfs       f2, 0x11C(r1)
	  fmr       f30, f1
	  lfs       f0, 0x118(r1)
	  stfs      f3, 0x130(r1)
	  lfs       f31, 0x128(r1)
	  stfs      f2, 0x124(r1)
	  stfs      f0, 0x120(r1)

	.loc_0xF4:
	  lfs       f1, 0x100(r1)
	  addi      r4, r27, 0
	  lfs       f0, 0xC(r26)
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x128
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x11C
	  addi      r7, r1, 0x118
	  stfs      f0, 0xC4(r1)
	  lfs       f0, 0xC4(r1)
	  stfs      f0, 0xF4(r1)
	  lfs       f1, 0x104(r1)
	  lfs       f0, 0x10(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0xF8(r1)
	  lfs       f1, 0x108(r1)
	  lfs       f0, 0x14(r26)
	  fadds     f0, f1, f0
	  stfs      f0, 0xFC(r1)
	  lwz       r0, 0xF4(r1)
	  lwz       r8, 0xF8(r1)
	  stw       r0, 0x100(r1)
	  lwz       r0, 0xFC(r1)
	  stw       r8, 0x104(r1)
	  stw       r0, 0x108(r1)
	  lfs       f1, 0x10C(r1)
	  lfs       f0, 0xC(r26)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xB4(r1)
	  lfs       f0, 0xB4(r1)
	  stfs      f0, 0xE8(r1)
	  lfs       f1, 0x110(r1)
	  lfs       f0, 0x10(r26)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xEC(r1)
	  lfs       f1, 0x114(r1)
	  lfs       f0, 0x14(r26)
	  fsubs     f0, f1, f0
	  stfs      f0, 0xF0(r1)
	  lwz       r8, 0xE8(r1)
	  lwz       r0, 0xEC(r1)
	  stw       r8, 0x10C(r1)
	  stw       r0, 0x110(r1)
	  lwz       r0, 0xF0(r1)
	  stw       r0, 0x114(r1)
	  bl        -0x1F44
	  lfs       f0, -0x7C5C(r2)
	  fcmpo     cr0, f1, f30
	  lfs       f3, 0x128(r1)
	  fsubs     f0, f0, f3
	  stfs      f0, 0x12C(r1)
	  bge-      .loc_0x1E4
	  lfs       f2, 0x12C(r1)
	  fmr       f30, f1
	  lfs       f1, 0x11C(r1)
	  fmr       f31, f3
	  lfs       f0, 0x118(r1)
	  stfs      f2, 0x130(r1)
	  stfs      f1, 0x124(r1)
	  stfs      f0, 0x120(r1)

	.loc_0x1E4:
	  lwz       r6, 0x0(r27)
	  mr        r4, r26
	  lwz       r0, 0x4(r27)
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x11C
	  stw       r6, 0x100(r1)
	  addi      r6, r1, 0x12C
	  addi      r7, r1, 0x128
	  stw       r0, 0x104(r1)
	  lwz       r0, 0x8(r27)
	  stw       r0, 0x108(r1)
	  lwz       r8, 0xC(r27)
	  lwz       r0, 0x10(r27)
	  stw       r8, 0x10C(r1)
	  stw       r0, 0x110(r1)
	  lwz       r0, 0x14(r27)
	  stw       r0, 0x114(r1)
	  bl        -0x40B0
	  fcmpo     cr0, f1, f30
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x118(r1)
	  bge-      .loc_0x258
	  lfs       f2, 0x12C(r1)
	  fmr       f30, f1
	  lfs       f0, 0x11C(r1)
	  stfs      f2, 0x130(r1)
	  lfs       f31, 0x128(r1)
	  stfs      f0, 0x124(r1)
	  stfs      f3, 0x120(r1)

	.loc_0x258:
	  lwz       r6, 0x18(r27)
	  mr        r4, r26
	  lwz       r0, 0x1C(r27)
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x118
	  stw       r6, 0x10C(r1)
	  addi      r6, r1, 0x12C
	  addi      r7, r1, 0x128
	  stw       r0, 0x110(r1)
	  lwz       r0, 0x20(r27)
	  stw       r0, 0x114(r1)
	  bl        -0x410C
	  fcmpo     cr0, f1, f30
	  lfs       f3, -0x7C60(r2)
	  stfs      f3, 0x11C(r1)
	  bge-      .loc_0x2B4
	  lfs       f2, 0x12C(r1)
	  fmr       f30, f1
	  lfs       f0, 0x118(r1)
	  stfs      f2, 0x130(r1)
	  lfs       f31, 0x128(r1)
	  stfs      f3, 0x124(r1)
	  stfs      f0, 0x120(r1)

	.loc_0x2B4:
	  lfs       f1, 0x0(r27)
	  addi      r4, r26, 0
	  lfs       f0, 0x18(r27)
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x11C
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x12C
	  addi      r7, r1, 0x128
	  stfs      f0, 0xA4(r1)
	  lfs       f0, 0xA4(r1)
	  stfs      f0, 0xDC(r1)
	  lfs       f1, 0x4(r27)
	  lfs       f0, 0x1C(r27)
	  fadds     f0, f1, f0
	  stfs      f0, 0xE0(r1)
	  lfs       f1, 0x8(r27)
	  lfs       f0, 0x20(r27)
	  fadds     f0, f1, f0
	  stfs      f0, 0xE4(r1)
	  lwz       r0, 0xDC(r1)
	  lwz       r8, 0xE0(r1)
	  stw       r0, 0x100(r1)
	  lwz       r0, 0xE4(r1)
	  stw       r8, 0x104(r1)
	  stw       r0, 0x108(r1)
	  lwz       r8, 0xC(r27)
	  lwz       r0, 0x10(r27)
	  stw       r8, 0x10C(r1)
	  stw       r0, 0x110(r1)
	  lwz       r0, 0x14(r27)
	  stw       r0, 0x114(r1)
	  bl        -0x41B8
	  fcmpo     cr0, f1, f30
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x118(r1)
	  bge-      .loc_0x360
	  lfs       f2, 0x12C(r1)
	  fmr       f30, f1
	  lfs       f0, 0x11C(r1)
	  stfs      f2, 0x130(r1)
	  lfs       f31, 0x128(r1)
	  stfs      f0, 0x124(r1)
	  stfs      f3, 0x120(r1)

	.loc_0x360:
	  lfs       f1, 0x0(r27)
	  addi      r4, r26, 0
	  lfs       f0, 0xC(r27)
	  addi      r3, r1, 0x100
	  addi      r5, r1, 0x118
	  fadds     f0, f1, f0
	  addi      r6, r1, 0x12C
	  addi      r7, r1, 0x128
	  stfs      f0, 0x90(r1)
	  lfs       f0, 0x90(r1)
	  stfs      f0, 0xD0(r1)
	  lfs       f1, 0x4(r27)
	  lfs       f0, 0x10(r27)
	  fadds     f0, f1, f0
	  stfs      f0, 0xD4(r1)
	  lfs       f1, 0x8(r27)
	  lfs       f0, 0x14(r27)
	  fadds     f0, f1, f0
	  stfs      f0, 0xD8(r1)
	  lwz       r0, 0xD0(r1)
	  lwz       r8, 0xD4(r1)
	  stw       r0, 0x100(r1)
	  lwz       r0, 0xD8(r1)
	  stw       r8, 0x104(r1)
	  stw       r0, 0x108(r1)
	  lwz       r8, 0x18(r27)
	  lwz       r0, 0x1C(r27)
	  stw       r8, 0x10C(r1)
	  stw       r0, 0x110(r1)
	  lwz       r0, 0x20(r27)
	  stw       r0, 0x114(r1)
	  bl        -0x4264
	  fcmpo     cr0, f1, f30
	  lfs       f3, -0x7C5C(r2)
	  stfs      f3, 0x11C(r1)
	  bge-      .loc_0x40C
	  lfs       f2, 0x12C(r1)
	  fmr       f30, f1
	  lfs       f0, 0x118(r1)
	  stfs      f2, 0x130(r1)
	  lfs       f31, 0x128(r1)
	  stfs      f3, 0x124(r1)
	  stfs      f0, 0x120(r1)

	.loc_0x40C:
	  cmplwi    r28, 0
	  beq-      .loc_0x41C
	  lfs       f0, 0x130(r1)
	  stfs      f0, 0x0(r28)

	.loc_0x41C:
	  cmplwi    r29, 0
	  beq-      .loc_0x428
	  stfs      f31, 0x0(r29)

	.loc_0x428:
	  cmplwi    r30, 0
	  beq-      .loc_0x438
	  lfs       f0, 0x124(r1)
	  stfs      f0, 0x0(r30)

	.loc_0x438:
	  cmplwi    r31, 0
	  beq-      .loc_0x448
	  lfs       f0, 0x120(r1)
	  stfs      f0, 0x0(r31)

	.loc_0x448:
	  lmw       r26, 0x138(r1)
	  fabs      f1, f30
	  lwz       r0, 0x164(r1)
	  lfd       f31, 0x158(r1)
	  lfd       f30, 0x150(r1)
	  addi      r1, r1, 0x160
	  mtlr      r0
	  blr
	*/
}

/*
 * --INFO--
 * Address: 8003D87C
 * Size:    000540
 */
f32 sqrDistance(Vector3f&, KTri&, f32*, f32*)
{
	/*
	.loc_0x0:
	  stwu      r1, -0xA8(r1)
	  stfd      f31, 0xA0(r1)
	  stfd      f30, 0x98(r1)
	  stfd      f29, 0x90(r1)
	  lfs       f3, 0x4(r4)
	  lfs       f1, 0x4(r3)
	  lfs       f30, 0x10(r4)
	  fsubs     f1, f3, f1
	  lfs       f3, 0x1C(r4)
	  lfs       f7, 0xC(r4)
	  fmuls     f11, f30, f30
	  lfs       f5, 0x18(r4)
	  fmuls     f12, f7, f7
	  lfs       f2, 0x0(r4)
	  lfs       f0, 0x0(r3)
	  fmuls     f10, f7, f5
	  fmuls     f9, f30, f3
	  fsubs     f2, f2, f0
	  lfs       f29, 0x14(r4)
	  fmuls     f8, f5, f5
	  lfs       f13, 0x20(r4)
	  fadds     f31, f12, f11
	  fmuls     f4, f3, f3
	  lfs       f6, 0x8(r4)
	  lfs       f0, 0x8(r3)
	  fadds     f9, f10, f9
	  fmuls     f7, f2, f7
	  fsubs     f0, f6, f0
	  fmuls     f6, f1, f30
	  fadds     f10, f8, f4
	  fmuls     f12, f29, f13
	  fmuls     f5, f2, f5
	  fmuls     f3, f1, f3
	  fadds     f4, f12, f9
	  fadds     f6, f7, f6
	  fmuls     f9, f0, f29
	  fmuls     f30, f29, f29
	  fadds     f7, f5, f3
	  fmuls     f11, f13, f13
	  fmuls     f8, f0, f13
	  fadds     f3, f30, f31
	  fadds     f5, f11, f10
	  fadds     f6, f9, f6
	  fadds     f7, f8, f7
	  fmuls     f8, f4, f4
	  fmuls     f9, f3, f5
	  fmuls     f11, f4, f7
	  fmuls     f10, f5, f6
	  fsubs     f12, f9, f8
	  fmuls     f9, f4, f6
	  fsubs     f13, f11, f10
	  fmuls     f8, f3, f7
	  fmuls     f10, f2, f2
	  fmuls     f2, f1, f1
	  fsubs     f11, f9, f8
	  fmuls     f8, f0, f0
	  fadds     f0, f10, f2
	  fabs      f9, f12
	  fadds     f1, f13, f11
	  fadds     f0, f8, f0
	  fcmpo     cr0, f1, f9
	  cror      2, 0, 0x2
	  bne-      .loc_0x290
	  lfs       f1, -0x7C60(r2)
	  fcmpo     cr0, f13, f1
	  bge-      .loc_0x1EC
	  fcmpo     cr0, f11, f1
	  bge-      .loc_0x1A0
	  fcmpo     cr0, f6, f1
	  bge-      .loc_0x154
	  fneg      f4, f6
	  fmr       f2, f1
	  fcmpo     cr0, f4, f3
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x144
	  lfs       f4, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f4, f4, f6
	  fadds     f3, f3, f4
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x144:
	  fdivs     f1, f4, f3
	  fmuls     f3, f6, f1
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x154:
	  fcmpo     cr0, f7, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x168
	  fmr       f2, f1
	  b         .loc_0x510

	.loc_0x168:
	  fneg      f2, f7
	  fcmpo     cr0, f2, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x190
	  lfs       f3, -0x7C58(r2)
	  lfs       f2, -0x7C5C(r2)
	  fmuls     f3, f3, f7
	  fadds     f3, f5, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x190:
	  fdivs     f2, f2, f5
	  fmuls     f3, f7, f2
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x1A0:
	  fcmpo     cr0, f7, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1B4
	  fmr       f2, f1
	  b         .loc_0x510

	.loc_0x1B4:
	  fneg      f2, f7
	  fcmpo     cr0, f2, f5
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x1DC
	  lfs       f3, -0x7C58(r2)
	  lfs       f2, -0x7C5C(r2)
	  fmuls     f3, f3, f7
	  fadds     f3, f5, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x1DC:
	  fdivs     f2, f2, f5
	  fmuls     f3, f7, f2
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x1EC:
	  fcmpo     cr0, f11, f1
	  bge-      .loc_0x240
	  fcmpo     cr0, f6, f1
	  fmr       f2, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x208
	  b         .loc_0x510

	.loc_0x208:
	  fneg      f1, f6
	  fcmpo     cr0, f1, f3
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x230
	  lfs       f4, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f4, f4, f6
	  fadds     f3, f3, f4
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x230:
	  fdivs     f1, f1, f3
	  fmuls     f3, f6, f1
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x240:
	  lfs       f1, -0x7C5C(r2)
	  lfs       f10, -0x7C58(r2)
	  fdivs     f2, f1, f9
	  fmuls     f1, f13, f2
	  fmuls     f2, f11, f2
	  fmuls     f9, f10, f6
	  fmuls     f8, f3, f1
	  fmuls     f6, f4, f2
	  fmuls     f4, f4, f1
	  fmuls     f3, f5, f2
	  fadds     f6, f8, f6
	  fmuls     f5, f10, f7
	  fadds     f3, f4, f3
	  fadds     f4, f9, f6
	  fadds     f3, f5, f3
	  fmuls     f4, f1, f4
	  fmuls     f3, f2, f3
	  fadds     f3, f4, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x290:
	  lfs       f8, -0x7C60(r2)
	  fcmpo     cr0, f13, f8
	  bge-      .loc_0x37C
	  fadds     f1, f4, f6
	  fadds     f2, f5, f7
	  fcmpo     cr0, f2, f1
	  ble-      .loc_0x32C
	  lfs       f10, -0x7C58(r2)
	  fsubs     f2, f2, f1
	  fmuls     f1, f10, f4
	  fsubs     f1, f3, f1
	  fadds     f1, f5, f1
	  fcmpo     cr0, f2, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x2E4
	  fmuls     f4, f10, f6
	  lfs       f1, -0x7C5C(r2)
	  fmr       f2, f8
	  fadds     f3, f3, f4
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x2E4:
	  fdivs     f1, f2, f1
	  lfs       f2, -0x7C5C(r2)
	  fsubs     f2, f2, f1
	  fmuls     f9, f3, f1
	  fmuls     f8, f4, f1
	  fmuls     f4, f4, f2
	  fmuls     f3, f5, f2
	  fmuls     f6, f10, f6
	  fadds     f5, f9, f4
	  fmuls     f4, f10, f7
	  fadds     f3, f8, f3
	  fadds     f5, f6, f5
	  fadds     f3, f4, f3
	  fmuls     f4, f1, f5
	  fmuls     f3, f2, f3
	  fadds     f3, f4, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x32C:
	  fcmpo     cr0, f2, f8
	  fmr       f1, f8
	  cror      2, 0, 0x2
	  bne-      .loc_0x354
	  lfs       f3, -0x7C58(r2)
	  lfs       f2, -0x7C5C(r2)
	  fmuls     f3, f3, f7
	  fadds     f3, f5, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x354:
	  fcmpo     cr0, f7, f8
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x368
	  fmr       f2, f8
	  b         .loc_0x510

	.loc_0x368:
	  fneg      f2, f7
	  fdivs     f2, f2, f5
	  fmuls     f3, f7, f2
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x37C:
	  fcmpo     cr0, f11, f8
	  bge-      .loc_0x464
	  fadds     f1, f4, f7
	  fadds     f2, f3, f6
	  fcmpo     cr0, f2, f1
	  ble-      .loc_0x414
	  lfs       f11, -0x7C58(r2)
	  fsubs     f2, f2, f1
	  fmuls     f1, f11, f4
	  fsubs     f1, f3, f1
	  fadds     f1, f5, f1
	  fcmpo     cr0, f2, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x3CC
	  fmuls     f3, f11, f7
	  lfs       f2, -0x7C5C(r2)
	  fmr       f1, f8
	  fadds     f3, f5, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x3CC:
	  fdivs     f2, f2, f1
	  lfs       f1, -0x7C5C(r2)
	  fsubs     f1, f1, f2
	  fmuls     f8, f4, f2
	  fmuls     f5, f5, f2
	  fmuls     f9, f3, f1
	  fmuls     f3, f4, f1
	  fmuls     f10, f11, f6
	  fadds     f6, f9, f8
	  fmuls     f4, f11, f7
	  fadds     f3, f3, f5
	  fadds     f5, f10, f6
	  fadds     f3, f4, f3
	  fmuls     f4, f1, f5
	  fmuls     f3, f2, f3
	  fadds     f3, f4, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x414:
	  fcmpo     cr0, f2, f8
	  fmr       f2, f8
	  cror      2, 0, 0x2
	  bne-      .loc_0x43C
	  lfs       f4, -0x7C58(r2)
	  lfs       f1, -0x7C5C(r2)
	  fmuls     f4, f4, f6
	  fadds     f3, f3, f4
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x43C:
	  fcmpo     cr0, f6, f8
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x450
	  fmr       f1, f8
	  b         .loc_0x510

	.loc_0x450:
	  fneg      f1, f6
	  fdivs     f1, f1, f3
	  fmuls     f3, f6, f1
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x464:
	  fadds     f1, f5, f7
	  fsubs     f1, f1, f4
	  fsubs     f2, f1, f6
	  fcmpo     cr0, f2, f8
	  cror      2, 0, 0x2
	  bne-      .loc_0x498
	  lfs       f3, -0x7C58(r2)
	  fmr       f1, f8
	  lfs       f2, -0x7C5C(r2)
	  fmuls     f3, f3, f7
	  fadds     f3, f5, f3
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x498:
	  lfs       f10, -0x7C58(r2)
	  fmuls     f1, f10, f4
	  fsubs     f1, f3, f1
	  fadds     f1, f5, f1
	  fcmpo     cr0, f2, f1
	  cror      2, 0x1, 0x2
	  bne-      .loc_0x4CC
	  fmuls     f4, f10, f6
	  lfs       f1, -0x7C5C(r2)
	  fmr       f2, f8
	  fadds     f3, f3, f4
	  fadds     f0, f0, f3
	  b         .loc_0x510

	.loc_0x4CC:
	  fdivs     f1, f2, f1
	  lfs       f2, -0x7C5C(r2)
	  fsubs     f2, f2, f1
	  fmuls     f9, f3, f1
	  fmuls     f8, f4, f1
	  fmuls     f4, f4, f2
	  fmuls     f3, f5, f2
	  fmuls     f6, f10, f6
	  fadds     f5, f9, f4
	  fmuls     f4, f10, f7
	  fadds     f3, f8, f3
	  fadds     f5, f6, f5
	  fadds     f3, f4, f3
	  fmuls     f4, f1, f5
	  fmuls     f3, f2, f3
	  fadds     f3, f4, f3
	  fadds     f0, f0, f3

	.loc_0x510:
	  cmplwi    r5, 0
	  beq-      .loc_0x51C
	  stfs      f1, 0x0(r5)

	.loc_0x51C:
	  cmplwi    r6, 0
	  beq-      .loc_0x528
	  stfs      f2, 0x0(r6)

	.loc_0x528:
	  fabs      f1, f0
	  lfd       f31, 0xA0(r1)
	  lfd       f30, 0x98(r1)
	  lfd       f29, 0x90(r1)
	  addi      r1, r1, 0xA8
	  blr
	*/
}
