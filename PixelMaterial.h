#pragma once
#include "raylib.h"

enum PixelMaterial {
	NOTHING = 0,
	SAND = 1,
};

Color GetColorFromPixelMaterial(PixelMaterial pixelMaterial)
{
	switch (pixelMaterial)
	{
	case NOTHING:
		return BLACK;
		break;
	case SAND:
		return YELLOW;
		break;
	default:
		break;
	}
}

bool CompareColors(Color a, Color b)
{
	if (a.r == b.r &&
		a.g == b.g &&
		a.b == b.b &&
		a.a == b.a) return true;
	else return false;
}

PixelMaterial GetPixelMaterialFromColor(Color color)
{
	if (CompareColors(color, BLACK)) return NOTHING;
	if (CompareColors(color, YELLOW)) return SAND;
}