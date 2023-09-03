#include "FoundamentalStructures.h"
#include <cmath>
#include <iostream>
#include <random>

FLinearColor FLinearColor::Black = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
FLinearColor FLinearColor::Red = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
FLinearColor FLinearColor::White = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
FLinearColor FLinearColor::Orange = FLinearColor(1.0f, 0.647f, 0.0f, 1.0f);
FLinearColor FLinearColor::Blue = FLinearColor(0.0f, 0.0f, 1.0f, 1.0f);
FLinearColor FLinearColor::Green = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
FLinearColor FLinearColor::Yellow = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
FLinearColor FLinearColor::Magenta = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);

FVector2 FVector2::Zero = FVector2(0.0f, 0.0f);
FVector2 FVector2::One = FVector2(1.0f, 1.0f);
FVector2 FVector2::Right = FVector2(1.0f, 0.0f);
FVector2 FVector2::Left = FVector2(-1.0f, 0.0f);
FVector2 FVector2::Up = FVector2(0.0f, 1.0f);
FVector2 FVector2::Down = FVector2(0.0f, -1.0f);

float FVector2::LengthSquared() const
{
	return (X*X) + (Y*Y);
}
float FVector2::Length() const
{
	return sqrt((X*X) + (Y*Y));
}
FVector2 FVector2::operator*(float Value)  const
{
	return FVector2(X*Value, Y*Value);
}
FVector2 FVector2::operator+(const FVector2& Other) const
{
	return FVector2(X + Other.X, Y + Other.Y);
}
FVector2 FVector2::operator-(const FVector2& Other) const
{
	return FVector2(X - Other.X, Y - Other.Y);
}
void FVector2::operator+=(const FVector2& Other)
{
	X += Other.X;
	Y += Other.Y;
}
void FVector2::operator-=(const FVector2& Other)
{
	X -= Other.X;
	Y -= Other.Y;
}
FVector2 FVector2::GetNormalize(float Tolerance) const
{
	const float SquareSum = X * X + Y * Y;
	if (SquareSum == 1.f)
		return *this;
	else if (SquareSum < Tolerance)
		return FVector2::Zero;
	
	const float Scale = 1.0f/sqrt(SquareSum);
	return FVector2(X*Scale, Y*Scale);
}
FVector2 FVector2::operator/(float Value) const
{
	const float RScale = 1.f / Value;
	return FVector2(X * RScale, Y * RScale);
}
float FVector2::DotProduct(const FVector2& Other) const
{
	return X * Other.X + Y * Other.Y;
}
float FVector2::Max() const
{
	return fmax(X, Y);
}
float FVector2::Min() const
{
	return fmin(X, Y);
}

FVector2 FVector2::RanomDirection()
{
	float Math_PI = 3.1415926f;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 2.0f * Math_PI); // Uniform distribution between 0 and 2*pi

	// Generate a random angle
	float angle = dis(gen);

	// Calculate the 2D direction vector
	return FVector2(cos(angle), sin(angle));
}
FVector2 FVector2::Rotate(float radian) const {
	double newX = X * cos(radian) - Y * sin(radian);
	double newY = Y * sin(radian) + Y * cos(radian);
	return FVector2(newX, newY);
}
FVector2 FVector2::RanomConeDirection(FVector2 Base, float HalfAngle)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-HalfAngle, HalfAngle); 
	return Base.Rotate(dis(gen)).GetNormalize();
}
bool FSphere::IsOverlap(const FSphere& Sphere) const
{
	FVector2 Displacement = Sphere.Center - Center;
	float distance = Displacement.Length();
	return distance < (Sphere.Radius + Radius);
}


FVector2 FBox::ToLocalSpace(const FVector2& WorldPoint) const {
	FVector2 Offset = WorldPoint - Center;
	float localX = cos(-Angle) * Offset.X - sin(-Angle) * Offset.Y;
	float localY = sin(-Angle) * Offset.X + cos(-Angle) * Offset.Y;
	return FVector2(localX, localY);
}
FVector2 FBox::ToWorldSpace(const FVector2& LocalPoint) const {
	float worldX = (cos(Angle) * LocalPoint.X) - (sin(Angle) * LocalPoint.Y) + Center.X;
	float worldY = (sin(Angle) * LocalPoint.X) + (cos(Angle) * LocalPoint.Y) + Center.Y;
	return FVector2(worldX, worldY);
}
bool FBox::PointInBox(const FVector2& WorldPoint) const
{
	FVector2 Local = ToLocalSpace(WorldPoint);
	return ((Local.X >= -Extents.X) && (Local.X <= Extents.X) && (Local.Y >= -Extents.Y) && (Local.Y <= Extents.Y));
}
bool FBox::IsCollide(const FSphere& Sphere, FVector2& OutImpactPoint, FVector2& OutNormal) const
{
	FVector2 LocalPoint = ToLocalSpace(Sphere.Center);

	FVector2 ClampLocalPoint = LocalPoint;
	ClampLocalPoint.X = fmax(-Extents.X, fmin(LocalPoint.X, Extents.X));
	ClampLocalPoint.Y = fmax(-Extents.Y, fmin(LocalPoint.Y, Extents.Y));

	FVector2 Displacement = LocalPoint - ClampLocalPoint;
	float distanceSquared = Displacement.LengthSquared();
	float radiusSquared = Sphere.Radius*Sphere.Radius;
	bool bIsCollide = distanceSquared <= radiusSquared;
	if (bIsCollide) {
		OutImpactPoint = ToWorldSpace(ClampLocalPoint);
		OutNormal = (Sphere.Center - OutImpactPoint).GetNormalize();

	}
	return bIsCollide;
}
bool FBox::IsOverlap(const FSphere& Sphere) const
{
	FVector2 LocalPoint = ToLocalSpace(Sphere.Center);

	FVector2 ClampLocalPoint = LocalPoint;
	ClampLocalPoint.X = fmax(-Extents.X, fmin(LocalPoint.X, Extents.X));
	ClampLocalPoint.Y = fmax(-Extents.Y, fmin(LocalPoint.Y, Extents.Y));

	FVector2 Displacement = LocalPoint - ClampLocalPoint;
	float distanceSquared = Displacement.LengthSquared();
	float radiusSquared = Sphere.Radius*Sphere.Radius;
	return distanceSquared <= radiusSquared;
}
FLinearColor FLinearColor::operator*(float Value) const {
	return FLinearColor(R*Value, G*Value, B*Value, A);
}