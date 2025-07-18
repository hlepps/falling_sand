#include "PixelMaterial.h"

PixelMaterial* PixelMaterial::NOTHING;
PixelMaterial* PixelMaterial::SAND;
PixelMaterial* PixelMaterial::WATER;
PixelMaterial* PixelMaterial::MUD;
PixelMaterial* PixelMaterial::SMOKE;
PixelMaterial* PixelMaterial::STONE;

bool CompareColors(Color a, Color b)
{
	if (a.r == b.r &&
		a.g == b.g &&
		a.b == b.b &&
		a.a == b.a) return true;
	else return false;
}

PixelMaterial* GetPixelMaterialFromColor(Color color)
{
	if (CompareColors(color, BLACK)) return PixelMaterial::NOTHING;
	if (CompareColors(color, YELLOW)) return PixelMaterial::SAND;
	if (CompareColors(color, BLUE)) return PixelMaterial::WATER;
	if (CompareColors(color, BROWN)) return PixelMaterial::MUD;
	if (CompareColors(color, LIGHTGRAY)) return PixelMaterial::SMOKE;
	if (CompareColors(color, DARKGRAY)) return PixelMaterial::STONE;
}