// Suck these nutz my nigga


#pragma once

#include "stdafx.h"

#define PI (3.141592653589793f)
#define M_PI	3.14159265358979323846264338327950288419716939937510
#define M_RADPI    57.295779513082f
#define rva(addr, size) (reinterpret_cast<unsigned char*>(addr + *reinterpret_cast<int*>(addr + (size - 4)) + size))



namespace hkfunctions {

	inline SDK::UCanvas* pCanvas;
	
	inline void SetAim(SDK::APlayerCameraManager* MyCamera, SDK::AFortPlayerPawn* Target);
	inline void SetSilentAim(SDK::APlayerCameraManager* MyCamera, SDK::AFortPlayerPawn* Target);
	inline SDK::FVector GetBoneLocByIdx(PVOID mesh, int id);
	inline void RadarRange(float* x, float* y, float range);
	inline void CalcRadarPoint(SDK::APlayerCameraManager* MyCamera, FVector vOrigin, int& screenx, int& screeny);
	inline bool GetBoneWorld(ACharacter* pActor, int nBone, FVector* vBonePos);
	inline bool GetBoneScreen(ACharacter* pActor, int nBone, FVector2D* vBonePos);
	inline void RenderRadar();
	inline void DrawAimingEnemy(SDK::AFortPlayerPawn* Target);
	inline SDK::FVector2D Translate(SDK::FVector2D fear);
	inline FVector W2S(FVector worldloc, FRotator camrot);
	inline FVector GetBoneWithRotation(USkeletalMeshComponent* mesh, int id);
	inline __forceinline float fast_sqrt(float x);
	inline __forceinline float fast_dist2D(const FVector2D& Src, const FVector& Dst);
	inline float calc_distance(FVector camera_location, FVector pawn);
	inline void SetMouseAim(AFortPawn* target_pawn);
	inline std::vector<uint64_t> radarPawns;
	inline void drawRect(UCanvas* canvas, const FVector2D& min, const FVector2D& max, FLinearColor& color, float thickness);
	inline double GetCrossDistance(double x1, double y1, double x2, double y2);
	inline bool GetClosestPlayerToCrossHair(FVector Pos, float& max, SDK::AFortPlayerPawn* Target);
	inline void CheckClosestFOVEntity(SDK::AFortPlayerPawn* Target, SDK::FVector Localcam, float& max);
	
	inline void WeakSpotAim(SDK::APlayerCameraManager* MyCamera, SDK::ABuildingWeakSpot* WeakSpot);

	inline bool IsTargetVisible(SDK::AFortPlayerPawn* Target);
}


__forceinline float hkfunctions::fast_sqrt(float x)
{
	union { int i; float x; } u;
	u.x = x; u.i = (u.i >> 1) + 0x1FC00000;
	u.x = u.x + x / u.x;
	return .25f * u.x + x / u.x;
}

__forceinline float hkfunctions::fast_dist2D(const FVector2D& Src, const FVector& Dst)
{
	return fast_sqrt(powf(Src.X - Dst.X, 2.f) + powf(Src.Y - Dst.Y, 2.f));
}

typedef struct _D3DMATRIX
{
	union
	{
		struct
		{
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
} D3DMATRIX;

struct FTransform
{
	FQuat rot;
	FVector translation;
	char pad[4];
	FVector scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.X;
		m._42 = translation.Y;
		m._43 = translation.Z;

		float x2 = rot.X + rot.X;
		float y2 = rot.Y + rot.Y;
		float z2 = rot.Z + rot.Z;

		float xx2 = rot.X * x2;
		float yy2 = rot.Y * y2;
		float zz2 = rot.Z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.X;
		m._22 = (1.0f - (xx2 + zz2)) * scale.Y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.Z;

		float yz2 = rot.Y * z2;
		float wx2 = rot.W * x2;
		m._32 = (yz2 - wx2) * scale.Z;
		m._23 = (yz2 + wx2) * scale.Y;

		float xy2 = rot.X * y2;
		float wz2 = rot.W * z2;
		m._21 = (xy2 - wz2) * scale.Y;
		m._12 = (xy2 + wz2) * scale.X;

		float xz2 = rot.X * z2;
		float wy2 = rot.W * y2;
		m._31 = (xz2 + wy2) * scale.Z;
		m._13 = (xz2 - wy2) * scale.X;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

inline D3DMATRIX matrix_multiplication(D3DMATRIX p1, D3DMATRIX p2)
{
	D3DMATRIX p_out;
	p_out._11 = p1._11 * p2._11 + p1._12 * p2._21 + p1._13 * p2._31 + p1._14 * p2._41;
	p_out._12 = p1._11 * p2._12 + p1._12 * p2._22 + p1._13 * p2._32 + p1._14 * p2._42;
	p_out._13 = p1._11 * p2._13 + p1._12 * p2._23 + p1._13 * p2._33 + p1._14 * p2._43;
	p_out._14 = p1._11 * p2._14 + p1._12 * p2._24 + p1._13 * p2._34 + p1._14 * p2._44;
	p_out._21 = p1._21 * p2._11 + p1._22 * p2._21 + p1._23 * p2._31 + p1._24 * p2._41;
	p_out._22 = p1._21 * p2._12 + p1._22 * p2._22 + p1._23 * p2._32 + p1._24 * p2._42;
	p_out._23 = p1._21 * p2._13 + p1._22 * p2._23 + p1._23 * p2._33 + p1._24 * p2._43;
	p_out._24 = p1._21 * p2._14 + p1._22 * p2._24 + p1._23 * p2._34 + p1._24 * p2._44;
	p_out._31 = p1._31 * p2._11 + p1._32 * p2._21 + p1._33 * p2._31 + p1._34 * p2._41;
	p_out._32 = p1._31 * p2._12 + p1._32 * p2._22 + p1._33 * p2._32 + p1._34 * p2._42;
	p_out._33 = p1._31 * p2._13 + p1._32 * p2._23 + p1._33 * p2._33 + p1._34 * p2._43;
	p_out._34 = p1._31 * p2._14 + p1._32 * p2._24 + p1._33 * p2._34 + p1._34 * p2._44;
	p_out._41 = p1._41 * p2._11 + p1._42 * p2._21 + p1._43 * p2._31 + p1._44 * p2._41;
	p_out._42 = p1._41 * p2._12 + p1._42 * p2._22 + p1._43 * p2._32 + p1._44 * p2._42;
	p_out._43 = p1._41 * p2._13 + p1._42 * p2._23 + p1._43 * p2._33 + p1._44 * p2._43;
	p_out._44 = p1._41 * p2._14 + p1._42 * p2._24 + p1._43 * p2._34 + p1._44 * p2._44;

	return p_out;
}

FVector hkfunctions::GetBoneWithRotation(USkeletalMeshComponent* mesh, int id)
{
	DWORD_PTR bone_array = (unsigned long long)read_ptr((PBYTE)mesh, 0x4A8); //SkeletalMesh
	if (!bone_array) bone_array = (unsigned long long)read_ptr((PBYTE)mesh, 0x4A8 + 0x10);
	if (!bone_array) return FVector(0, 0, 0);

	FTransform comp_to_world = (FTransform&)read_ptr(mesh, 0x01C0);
	FTransform bone = *(FTransform*)(bone_array + (id * 0x30));
	D3DMATRIX matrix = matrix_multiplication(bone.ToMatrixWithScale(), comp_to_world.ToMatrixWithScale());

	return FVector(matrix._41, matrix._42, matrix._43);
}

inline D3DMATRIX matrix(FRotator rot, FVector origin = FVector(0, 0, 0))
{
	float radPitch = (rot.Pitch * float(M_PI) / 180.f);
	float radYaw = (rot.Yaw * float(M_PI) / 180.f);
	float radRoll = (rot.Roll * float(M_PI) / 180.f);

	float SP = SpoofCall(sinf, radPitch);
	float CP = SpoofCall(cosf, radPitch);
	float SY = SpoofCall(sinf, radYaw);
	float CY = SpoofCall(cosf, radYaw);
	float SR = SpoofCall(sinf, radRoll);
	float CR = SpoofCall(cosf, radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.X;
	matrix.m[3][1] = origin.Y;
	matrix.m[3][2] = origin.Z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

FVector hkfunctions::W2S(FVector worldloc, FRotator camrot)
{
	// Sussy balls???
	return { 0, 0, 0 };
}


inline SDK::FVector hkfunctions::GetBoneLocByIdx(PVOID mesh, int id)
{
	if (!mesh) return { 0,0,0 };
	auto fGetBoneMatrix = ((SDK::FMatrix * (__fastcall*)(PVOID, SDK::FMatrix*, int))(pGetBoneMatrix));
	fGetBoneMatrix(mesh, Basic::myMatrix, id);

	return SDK::FVector(Basic::myMatrix->M[3][0], Basic::myMatrix->M[3][1], Basic::myMatrix->M[3][2]);
}

inline SDK::FVector2D hkfunctions::Translate(SDK::FVector2D fear)
{
	return SDK::FVector2D(fear.X, fear.Y);
}

FVector2D inline Subtract(SDK::FVector2D point1, SDK::FVector point2)
{
	SDK::FVector2D vector{ 0, 0 };
	vector.X = point1.X - point2.X;
	vector.Y = point1.Y - point2.Y;
	return vector;
}

FVector inline VectorSubtract(FVector Vector1, FVector Vector2)
{
	FVector Vec { 0, 0, 0 };
	Vec.X = Vector1.X - Vector2.X;
	Vec.Y = Vector1.Y - Vector2.Y;
	Vec.Z = Vector1.Z - Vector2.Z;
	return Vec;
}

FVector inline VectorAdd(FVector Vector1, FVector Vector2)
{
	FVector Vec{ 0, 0, 0 };
	Vec.X = Vector1.X + Vector2.X;
	Vec.Y = Vector1.Y + Vector2.Y;
	Vec.Z = Vector1.Z + Vector2.Z;
	return Vec;
}

FRotator inline RotatorAdd(FRotator Vector1, FRotator Vector2)
{
	FRotator Vec;
	Vec.Pitch = Vector1.Pitch + Vector2.Pitch;
	Vec.Yaw = Vector1.Yaw + Vector2.Yaw;
	Vec.Roll = Vector1.Roll + Vector2.Roll;
	return Vec;
}
FRotator inline SmoothMe(FRotator rStartRotation, FRotator rEndRotation)
{
	options::Aim::smooth;
	int ScreenCenterX = width / 2.0f;
	int ScreenCenterY = height / 2.0f;

	FRotator rDeltaRotation;

	return RotatorAdd(rStartRotation, rDeltaRotation);
}

FRotator inline LimitRotation(FRotator rStartRotation, FRotator rEndRotation)
{
	float nMaxRotation = 0.16;

	FRotator rDeltaRotation;

	return RotatorAdd(rStartRotation, rDeltaRotation);
}

inline bool hkfunctions::GetBoneWorld(ACharacter* pActor, int nBone, FVector* vBonePos)
{
	if (!pActor) return false;
	if (!pActor->Mesh) return false;
	
	

	auto GetBoneMatrix = reinterpret_cast<Matrix4 * (__fastcall*)(uintptr_t, Matrix4*, int)>(pGetBoneMatrix);

	

	Matrix4 BoneMatrix;
	if (!GetBoneMatrix((uintptr_t)pActor->Mesh, &BoneMatrix, nBone)) return false;

	vBonePos->X = BoneMatrix._41;
	vBonePos->Y = BoneMatrix._42;
	vBonePos->Z = BoneMatrix._43;

	return true;
}

bool hkfunctions::GetBoneScreen(ACharacter* pActor, int nBone, FVector2D* vBonePos)
{
	if (!pActor) return false;

	FVector vWorldPos;
	if (!GetBoneWorld(pActor, nBone, &vWorldPos))
		return false;

	if (!Basic::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, vBonePos))
		return false;

	return true;
}



inline float calc_distance(FVector camera_location, FVector pawn)
{

	float x = camera_location.X - pawn.X;
	float y = camera_location.Y - pawn.Y;
	float z = camera_location.Z - pawn.Z;
	float distance = SpoofCall(sqrtf, x * x + y * y + z * z) / 100.0f;
	return distance;
}

inline float GetDistance(SDK::FVector point1, SDK::FVector point2)
{
	SDK::FVector heading = VectorSubtract(point2, point1);
	float distanceSquared;
	float distance;

	distanceSquared = heading.X * heading.X + heading.Y * heading.Y + heading.Z * heading.Z;
	distance = sqrt(distanceSquared);

	return distance;
}


// Niggor moment.
static FRotator calc_angle(FVector loc, FVector bone_loc)
{
	FRotator result;

	auto delta = bone_loc - loc;
	auto distance = delta.distance();

	result.Yaw = SpoofCall(atan2f, delta.Y, delta.X) * (180.0f / PI);
	result.Pitch = (-(SpoofCall(acosf, (delta.Z / distance)) * 180.0f / PI) - 90.0f);
	result.Roll = NULL;

	return result;
}


inline float GetDistance2D(SDK::FVector2D point1, const FVector& point2)
{
	SDK::FVector2D heading = Subtract(point1, point2);
	float distanceSquared;
	float distance;

	distanceSquared = heading.X * heading.X + heading.Y * heading.Y;
	distance = sqrt(distanceSquared);

	return distance;
}



inline void hkfunctions::SetAim(SDK::APlayerCameraManager* MyCamera, SDK::AFortPlayerPawn* Target)
{
	// No more fornite
}


void hkfunctions::drawRect(UCanvas* canvas, const FVector2D& min, const FVector2D& max, FLinearColor& color, float thickness)
{
	canvas->K2_DrawLine(min, FVector2D(max.X, min.Y), thickness, color);
	canvas->K2_DrawLine(min, FVector2D(min.X, max.Y), thickness, color);
	canvas->K2_DrawLine(FVector2D(min.X, max.Y), max, thickness, color);
	canvas->K2_DrawLine(FVector2D(max.X, min.Y), max, thickness, color);
}
