#include "RulesCheck.h"

#include <cstdlib>
#include <cmath>
#include <ctime>
#include "raylib.h"

#include "PixelMaterial.h"

Color* newPixels;

void InitRules(int width, int height)
{
	newPixels = (Color*)malloc(width * height * sizeof(Color));
	std::srand(std::time(NULL));
}

void CheckRules(Color* pixels, int width, int height)
{
	for (int i = 0; i < width * height; i++) {
		newPixels[i] = pixels[i];
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			PixelMaterial* current = GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y)*width]);
			if (current != PixelMaterial::NOTHING)
			{
				if (current->IsLiquid())
				{

				}
				else if (current->IsGas())
				{

				}
				else
				{
					if (y < height - 1)
					{
						if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == PixelMaterial::NOTHING)
						{
							newPixels[(int)(x)+(int)(y)*width] = PixelMaterial::NOTHING->GetColor();
							newPixels[(int)(x)+(int)(y + 1) * width] = current->GetColor();
						}
						else
						{
							int side = (int)std::pow(-1, rand() % 2);
							if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 1) * width]) == PixelMaterial::NOTHING)
							{
								newPixels[(int)(x)+(int)(y)*width] = PixelMaterial::NOTHING->GetColor();
								newPixels[(int)(x + side) + (int)(y + 1) * width] = current->GetColor();
							}
						}
					}
				}
			}
			/*
			switch ()
			{
			case SAND: {
				if (y > 0 && y < height - 1 && x > 0 && x < width - 1)
				{
					if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == NOTHING)
					{
						newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
						newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(SAND);
					}
					else if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == WATER)
					{
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y)*width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x + side) + (int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
						else if (GetPixelMaterialFromColor(pixels[(int)(x - side) + (int)(y)*width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x - side) + (int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
						else
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
					}
					else
					{
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 1) * width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x + side) + (int)(y + 1) * width] = GetColorFromPixelMaterial(SAND);
						}
					}
				}
			}break;
			case WATER: {
				if (y > 0 && y < height - 1 && x > 0 && x < width - 1)
				{
					if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == NOTHING)
					{
						newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
						newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(WATER);
					}
					else // something is under
					{
						if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == SAND) // sand is under
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
						}
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(newPixels[(int)(x + side) + (int)(y + 1) * width]) == NOTHING) // nothing on side
						{
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x + side) + (int)(y + 1) * width] = GetColorFromPixelMaterial(WATER);
						}
						else if (GetPixelMaterialFromColor(newPixels[(int)(x + side) + (int)(y + 1) * width]) == WATER) // water on side
						{
							if (GetPixelMaterialFromColor(newPixels[(int)(x + side) + (int)(y)*width]) == NOTHING)
							{
								newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
								newPixels[(int)(x + side) + (int)(y)*width] = GetColorFromPixelMaterial(WATER);
							}
						}
					}
				}
			}break;
			case MUD: {
				if (y > 0 && y < height - 1 && x > 0 && x < width - 1)
				{
					if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == NOTHING)
					{
						newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
						newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
					}
					else if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == WATER)
					{
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y)*width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x + side) + (int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
						else if (GetPixelMaterialFromColor(pixels[(int)(x - side) + (int)(y)*width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x - side) + (int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
						else
						{
							newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(WATER);
						}
					}
					else
					{
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 1) * width]) == NOTHING && y < height - 2)
						{
							if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 2) * width]) == NOTHING && y < height - 3)
							{
								if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 3) * width]) == NOTHING && y < height - 4)
								{
									if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 4) * width]) == NOTHING)
									{
										newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
										newPixels[(int)(x + side) + (int)(y + 1) * width] = GetColorFromPixelMaterial(MUD);
									}
								}
							}
						}


					}
				}
			}break;
			default: {

			}break;
			}*/

		}
	}
	for (int i = 0; i < width * height; i++) {
		pixels[i] = newPixels[i];
	}
}