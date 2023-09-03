#include "GameObject.h"

void UGameObject::SetLinearVelocity(const FVector2& Velocity) {
	LinearVelocity = Velocity;
	bMovable = CheckCanMovable();
}
void UGameObject::SetAngleSpeed(float Speed) {
	AngularSpeed = Speed;
	bMovable = CheckCanMovable();
}
bool UGameObject::CheckCanMovable() const
{
	return (AngularSpeed > 0.0f) || (LinearVelocity.LengthSquared() > 0.0f);
}
void UGameObject::Update(float DeltaSeconds)
{
	if (bMovable) {
		Move(LinearVelocity*DeltaSeconds);
		Rotate(AngularSpeed*DeltaSeconds);
	}
	OnUpdated(DeltaSeconds);
}
void UGameObject::OnUpdated(float DeltaSeconds)
{

}