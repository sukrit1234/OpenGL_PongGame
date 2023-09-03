#pragma once
#include "GLRenderUtility.h"
#include <cmath>
#include <string.h>

void UDrawUtil::DrawFilledCircle(const FVector2& Center, float Radius, const FLinearColor& FillColor, int SegmentCount) {

	glPushMatrix();
	glTranslatef(Center.X, Center.Y, 0);
	glColor4f(FillColor.R, FillColor.G, FillColor.B, FillColor.A);
	float twicePi = 2.0 * 3.1415926f;
	float x = 0.0f, y = 0.0f;
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glVertex2f(x, y);
	for (int i = 0; i <= SegmentCount; i++)
	{
		float theta = twicePi * float(i) / float(SegmentCount);
		float x = Radius * cos(theta);
		float y = Radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd(); //END
	glPopMatrix();
}
void UDrawUtil::DrawCircle(const FVector2& Center, float Radius, const FLinearColor& FillColor, int SegmentCount) {

	glPushMatrix();
	glTranslatef(Center.X, Center.Y, 0);
	glColor4f(FillColor.R, FillColor.G, FillColor.B, FillColor.A);
	float twicePi = 2.0 * 3.1415926f;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < SegmentCount; i++) {
		float theta = twicePi * float(i) / float(SegmentCount);
		float x = Radius * cosf(theta);
		float y = Radius * sinf(theta);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
void UDrawUtil::DrawFilledRectangle(const FVector2& Center, const FVector2& Extents, float Angle, const FLinearColor& FillColor)
{
	glPushMatrix();
	glTranslatef(Center.X, Center.Y, 0.0f);
	glRotatef(Angle, 0.0f, 0.0f, 1.0f);
	glColor4f(FillColor.R, FillColor.G, FillColor.B, FillColor.A);
	glBegin(GL_QUADS);
	glVertex2f(-Extents.X, -Extents.Y);
	glVertex2f(-Extents.X, Extents.Y);
	glVertex2f(Extents.X, Extents.Y);
	glVertex2f(Extents.X, -Extents.Y);
	glEnd();
	glPopMatrix();
}
void UDrawUtil::DrawRectangle(const FVector2& Center, const FVector2& Extents, float Angle, const FLinearColor& FillColor)
{
	glPushMatrix();
	glTranslatef(Center.X, Center.Y, 0.0f);
	glRotatef(Angle, 0.0f, 0.0f, 1.0f);
	glColor4f(FillColor.R, FillColor.G, FillColor.B, FillColor.A);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-Extents.X, -Extents.Y);
	glVertex2f(Extents.X, -Extents.Y);
	glVertex2f(Extents.X, Extents.Y);
	glVertex2f(-Extents.X, Extents.Y);
	glEnd();
	glPopMatrix();
}
void UDrawUtil::DrawScreenText(const FVector2& Location, const char* string, const FLinearColor& Color,bool bCentered, void *font)
{
	int wLen = glutBitmapLength(font, reinterpret_cast<const unsigned char*>(string));
	float Offset_X = bCentered ? wLen * 0.5f : 0.0f;
	glColor4f(Color.R, Color.G, Color.B, Color.A);
	glRasterPos2f(Location.X - Offset_X, Location.Y);
	int len = strlen(string);
	for (int i = 0; i < len; i++) 
		glutBitmapCharacter(font, string[i]);
}