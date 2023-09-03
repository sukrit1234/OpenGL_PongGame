#pragma once

#define SMALL_NUMBER (1.e-8f)
struct FVector2
{
	float X;
	float Y;
	FVector2()
		:X(0.0f), Y(0.0f){}
	FVector2(float x, float y)
		: X(x), Y(y){}

	float LengthSquared() const;
	float Length() const;

	FVector2 operator*(float Value) const;
	FVector2 operator/(float Value) const;
	FVector2 operator+(const FVector2& Other) const;
	FVector2 operator-(const FVector2& Other) const;
	void operator+=(const FVector2& Other);
	void operator-=(const FVector2& Other);
	FVector2 GetNormalize(float Tolerance= SMALL_NUMBER) const;
	
	/*Normal must be normalized*/
	FVector2 Reflect(const FVector2& normal) const {
		float dotProduct = DotProduct(normal);
		return (*this) - (normal* 2.0f * dotProduct);
	}
	
	float DotProduct(const FVector2& Other) const;
	float Max() const;
	float Min() const;

	FVector2 Rotate(float radian) const;

	static FVector2 RanomDirection();
	static FVector2 RanomConeDirection(FVector2 Base, float radian);

	static FVector2 Zero;
	static FVector2 One;
	static FVector2 Right;
	static FVector2 Left;
	static FVector2 Up;
	static FVector2 Down;
};

struct FLinearColor {
	float R;
	float G;
	float B;
	float A;
	FLinearColor() :
		R(0.0f), G(0.0f), B(0.0f), A(1.0f)
	{

	}
	FLinearColor(float r,float g,float b,float a=1.0f)
		: R(r), G(g), B(b), A(a)
	{

	}
	FLinearColor operator*(float Value) const;

	static FLinearColor Black;
	static FLinearColor Red;
	static FLinearColor White;
	static FLinearColor Orange;
	static FLinearColor Blue;
	static FLinearColor Green;
	static FLinearColor Yellow;
	static FLinearColor Magenta;
	//100 % , 100 % , 0 %
};

struct FSphere
{
	float Radius;
	FVector2 Center;

	FSphere()
		: Center(FVector2::Zero), Radius(1.0f)
	{

	}

	FSphere(const FVector2& center, float radius)
		: Center(center), Radius(radius)
	{

	}
	bool IsOverlap(const FSphere& Sphere) const;

};
struct FBox
{
	FVector2 Center;
	FVector2 Extents;
	float Angle;

	FBox()
		: Center(FVector2::Zero), Extents(FVector2::Zero), Angle(0.0f)
	{

	}

	FBox(const FVector2& center, const FVector2& extents, float Angle)
		: Center(center), Extents(extents), Angle(Angle)
	{

	}

	FVector2 ToLocalSpace(const FVector2& WorldPoint) const;
	FVector2 ToWorldSpace(const FVector2& LocalPoint) const;
	
	bool PointInBox(const FVector2& WorldPoint) const;
	bool IsCollide(const FSphere& Sphere, FVector2& OutImpactPoint, FVector2& OutNormal) const;
	bool IsOverlap(const FSphere& Sphere) const;
};