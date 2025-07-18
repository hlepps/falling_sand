#pragma once
#include "raylib.h"

class PixelMaterial {
private:
	Color _color = BLACK;

	bool _isLiquid = false;
	bool _isGas = false;

	bool _isSinkable = false;
	PixelMaterial* _materialWhenSinked;

	/// <summary>
	/// 0 - none
	/// 100 - instant
	/// </summary>
	int _burnChance = 0;
	PixelMaterial* _materialWhenBurn;

	/// <summary>
	/// positive - goes down
	/// negative - goes up
	/// </summary>
	float _gravityForce = 0;

public:
	PixelMaterial(Color color, bool isLiquid, bool isGas,
		bool isSinkable, PixelMaterial* materialWhenSinked,
		int burnChance, PixelMaterial* materialWhenBurn,
		float gravityForce)
	{
		_color = color;
		_isLiquid = isLiquid;
		_isGas = isGas;
		_isSinkable = isSinkable;
		_materialWhenSinked = materialWhenSinked;
		_burnChance = burnChance;
		_materialWhenBurn = materialWhenBurn;
		_gravityForce = gravityForce;
	}

	static PixelMaterial* NOTHING;
	static PixelMaterial* SAND;
	static PixelMaterial* WATER;
	static PixelMaterial* MUD;
	static void Init()
	{
		NOTHING = new PixelMaterial(BLACK, false, false, false, NOTHING, 0, NOTHING, 0);
		SAND = new PixelMaterial(YELLOW, false, false, true, MUD, 0, NOTHING, 1);
		WATER = new PixelMaterial(BLUE, true, false, false, NOTHING, 0, NOTHING, 1);
		MUD = new PixelMaterial(BROWN, false, false, true, MUD, 0, NOTHING, 1);
	}

	Color GetColor() { return _color; }
	bool IsLiquid() { return _isLiquid; }
	bool IsGas() { return _isGas; }
	bool IsSinkable() { return _isSinkable; }
	PixelMaterial* GetMaterialWhenSinked() { return _materialWhenSinked; }
	int GetBurnChance() { return _burnChance; }
	PixelMaterial* GetMaterialWhenBurn() { return _materialWhenBurn; }
	float GetGravityForce() { return _gravityForce; }
};

bool CompareColors(Color a, Color b);
PixelMaterial* GetPixelMaterialFromColor(Color color);