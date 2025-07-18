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
	const int pixelSize = 1;
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

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 mousePos = GetMousePosition();
			mousePos.x = (int)(mousePos.x/pixelSize);
			mousePos.y = (int)(mousePos.y/pixelSize);
			//std::cout << mousePos.x << " " << mousePos.y << std::endl;
			pixels[(int)mousePos.x + (int)mousePos.y * pixelsWidth] = currentMaterial->GetColor();
			std::cout << currentMaterial->GetColor().r << std::endl;
			
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTextureEx(texture, {0,0}, 0, pixelSize, WHITE);

		DrawFPS(10, 10);

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