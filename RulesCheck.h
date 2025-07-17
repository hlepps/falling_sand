#pragma once
#include <cstdlib>
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
			
			switch (GetPixelMaterialFromColor(pixels[(int)(x) + (int)(y) * width]))
			{
			case SAND: {
				if (y != height - 1)
				{
					if (GetPixelMaterialFromColor(pixels[(int)(x)+(int)(y + 1) * width]) == NOTHING)
					{
						newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
						newPixels[(int)(x)+(int)(y + 1) * width] = GetColorFromPixelMaterial(SAND);
					}
					else
					{
						int side = (int)std::pow(-1, rand() % 2);
						if (GetPixelMaterialFromColor(pixels[(int)(x + side) + (int)(y + 1) * width]) == NOTHING)
						{
							newPixels[(int)(x)+(int)(y)*width] = GetColorFromPixelMaterial(NOTHING);
							newPixels[(int)(x+side)+(int)(y + 1) * width] = GetColorFromPixelMaterial(SAND);
						}
					}
				}
			}break;
			default: {

			}break;
			}
			
		}
	}
	for (int i = 0; i < width * height; i++) {
		pixels[i] = newPixels[i];
	}
}
