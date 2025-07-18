#include <iostream>
#include "raylib.h"

#include "RulesCheck.h"
#include "PixelMaterial.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1600;
	const int screenHeight = 900;
	const int pixelSize = 5;
	const int pixelsWidth = screenWidth / pixelSize;
	const int pixelsHeight = screenHeight / pixelSize;
	
	
	InitWindow(screenWidth, screenHeight, "falling sand");

	Color* pixels = (Color*)malloc(pixelsWidth * pixelsHeight * sizeof(Color));

	for (int i = 0; i < pixelsWidth * pixelsHeight; i++)
	{
		pixels[i] = BLACK;
	}
	InitRules(pixelsWidth, pixelsHeight);
	PixelMaterial::Init();

	Image image;
	image.data = pixels;
	image.width = screenWidth/pixelSize;
	image.height = screenHeight/pixelSize;
	image.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	image.mipmaps = 1;

	ImageFormat(&image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	Texture2D texture = LoadTextureFromImage(image);


	PixelMaterial* currentMaterial = PixelMaterial::SAND;
	int frameDelay = 0;
	int currentDelay = 0;
	int currentRadius = 100/pixelSize/2;
	
	// 0-100
	int brushHardness = 20;

	SetTargetFPS(144);
	//---------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_P))
		{
			frameDelay++;
		}
		if (IsKeyDown(KEY_O))
		{
			frameDelay=0;
		}
		if (IsKeyDown(KEY_I))
		{
			frameDelay--;
		}
		
		if (GetMouseWheelMove())
		{
			currentRadius += GetMouseWheelMove() * 5;
			if (currentRadius < 1) currentRadius = 1;
			if (currentRadius > 100 / pixelSize) currentRadius = 100 / pixelSize;
		}

		if (IsKeyDown(KEY_ZERO))
		{
			currentMaterial = PixelMaterial::NOTHING;
		}
		if (IsKeyDown(KEY_ONE))
		{
			currentMaterial = PixelMaterial::SAND;
		}
		if (IsKeyDown(KEY_TWO))
		{
			currentMaterial = PixelMaterial::WATER;
		}
		if (IsKeyDown(KEY_THREE))
		{
			currentMaterial = PixelMaterial::MUD;
		}
		if (IsKeyDown(KEY_FOUR))
		{
			currentMaterial = PixelMaterial::SMOKE;
		}
		if (IsKeyDown(KEY_FIVE))
		{
			currentMaterial = PixelMaterial::STONE;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 mousePos = GetMousePosition();
			int mousePosX = (int)(mousePos.x/pixelSize);
			int mousePosY = (int)(mousePos.y/pixelSize);
			for (int y = mousePosY - currentRadius / 2; y < mousePosY + currentRadius / 2; y++)
			{
				for (int x = mousePosX - currentRadius / 2; x < mousePosX + currentRadius / 2; x++)
				{
					if (y > 0 && y < pixelsHeight - 1 && x > 0 && x < pixelsWidth - 1)
					{
						if(rand()%100 < brushHardness)
							pixels[x + y * pixelsWidth] = currentMaterial->GetColor();
					}
				}
			}
			//std::cout << mousePos.x << " " << mousePos.y << std::endl;
			
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTextureEx(texture, {0,0}, 0, pixelSize, WHITE);

		DrawFPS(10, 10);

		int rectSize = pixelSize * currentRadius;
		DrawRectangle(GetMouseX() - rectSize/2, GetMouseY() - rectSize/2, rectSize, rectSize, { 125,125,0,50 });

		EndDrawing();
		//----------------------------------------------------------------------------------


		// UpdateTexture
		//----------------------------------------------------------------------------------
		if (currentDelay >= frameDelay)
		{
			CheckRules(pixels, pixelsWidth, pixelsHeight);
			currentDelay = 0;
		}
		else
		{
			currentDelay++;
		}

		UpdateTexture(texture, pixels);
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------

	// Unload textures data (GPU VRAM)
	UnloadTexture(texture);

	CloseWindow();                // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}