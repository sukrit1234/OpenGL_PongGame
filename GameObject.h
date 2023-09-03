#pragma once
#include "FoundamentalStructures.h"

class UGameObject
{
public:

	inline bool IsMovable() const { return bMovable; }

	virtual FVector2 GetCenter() const = 0;
	virtual FVector2 GetExtent() const = 0;
	virtual float GetRadius() const = 0;
	virtual void SetLocation(const FVector2& Location) = 0;

	virtual void SetLinearVelocity(const FVector2& Velocity);
	virtual void SetAngleSpeed(float Speed);

	const FVector2& GetLinearVelocity() const { return LinearVelocity; }
	float GetAngularSpeed() const { return AngularSpeed; }
	
	void Update(float DeltaSeconds);
	virtual void Draw(float DeltaSeconds) = 0;

protected:

	virtual void OnUpdated(float DeltaSeconds);
	virtual void Move(const FVector2& Delta) = 0;
	virtual void Rotate(float Delta) = 0;

	bool bMovable = false;
	FVector2 LinearVelocity = FVector2::Zero;
	float AngularSpeed = 0.0f;
	bool CheckCanMovable() const;
};

class USphereObject : public UGameObject {

public:

	virtual FVector2 GetCenter() const override { return Sphere.Center; }
	virtual FVector2 GetExtent() const override { return FVector2(Sphere.Radius, Sphere.Radius); }
	virtual float GetRadius() const override { return Sphere.Radius; }

	void SetColor(const FLinearColor& color) { Color = color; }
	void SetRadius(float Radius) { Sphere.Radius = Radius; }
	virtual void SetLocation(const FVector2& Location) override { Sphere.Center = Location; }
	void SetIsFilled(bool bFilled) { bIsFilled = bFilled; }

	virtual void Draw(float DeltaSeconds);
	const FSphere& GetSphere() const { return Sphere; }

protected:

	virtual void Move(const FVector2& Delta) override;
	virtual void Rotate(float Delta) override;

	FSphere Sphere;
	FLinearColor Color;
	bool bIsFilled = true;
};
class URectangleObject : public UGameObject
{
public:

	virtual FVector2 GetCenter() const override { return Box.Center; }
	virtual FVector2 GetExtent() const override { return Box.Extents; }
	virtual float GetRadius() const override { return Box.Extents.Max(); }

	void SetColor(const FLinearColor& color) { Color = color; }
	void SetSize(const FVector2& Size) { Box.Extents = Size * 0.5f; }
	virtual void SetLocation(const FVector2& Location) override { Box.Center = Location; }
	void SetIsFilled(bool bFilled) { bIsFilled = bFilled; }

	virtual void Draw(float DeltaSeconds);
	const FBox& GetBox() const { return Box; }

protected:

	/*Control Plank Alway move by player*/
	virtual void Move(const FVector2& Delta) override;
	virtual void Rotate(float Delta) override;

	FBox Box;
	FLinearColor Color;
	bool bIsFilled = true;
};

