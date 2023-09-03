#pragma once

#include <glut.h>
#include "FoundamentalStructures.h"

class UDrawUtil
{
public:

	static void DrawFilledCircle(const FVector2& Center, float Radius, const FLinearColor& FillColor, int SegmentCount = 20);
	static void DrawCircle(const FVector2& Center, float Radius, const FLinearColor& FillColor, int SegmentCount = 20);
	static void DrawFilledRectangle(const FVector2& Center, const FVector2& Extents, float Angle, const FLinearColor& FillColor);
	static void DrawRectangle(const FVector2& Center, const FVector2& Extents, float Angle, const FLinearColor& FillColor);
	static void DrawScreenText(const FVector2& Location, const char* Text, const FLinearColor& Color,bool bCentered, void *font = GLUT_BITMAP_TIMES_ROMAN_24);
};