#pragma once
#include "stdafx.h"
#include "spoof_call.h"


#define E(str) skCrypt(str)

namespace framework {

	
	inline POINT cursor;
	inline POINT cursor_corrected;
	inline bool should_drag = false;
	inline bool should_move = false;
	inline int x = 140, y = 140;
	inline int w = 400, h = 300;
	inline int current_tab = 0;
	inline bool show_menu = false;
	inline auto RobotoFont = UObject::FindObject<UFont>(skCrypt("Allahu Akbar"));

	inline void K2_DrawFilledRect(UCanvas* canvas, const FVector2D& initial_pos, float w, float h, const FLinearColor& color);
	inline void groupbox(UCanvas* canvas, int x, int y, int w, int h, const FString string, bool show_label);
	inline void tab(UCanvas* canvas, int x, int y, int w, int h, const FString string, int& tab, int count, bool show_outline);
	inline bool checkbox(UCanvas* canvas, int x, int y, int position, const FString string, bool& value);
	inline void slider(UCanvas* canvas, int x, int y, int position, const FString string, float& value, float min_value, float max_value);
	inline void movement(int& x, int& y, int w, int h);
	inline void render_menu(UCanvas* canvas);
}


inline void framework::K2_DrawFilledRect(UCanvas* canvas, const FVector2D& initial_pos, float w, float h, const FLinearColor& color)
{
	//Sussy Balls
}

inline void K2_DrawRect(UCanvas* canvas, const FVector2D& initial_pos, float w, float h, const FLinearColor& color, float thickness = 1.f)
{
	//Sussy Balls
}

inline void framework::groupbox(UCanvas* canvas, int x, int y, int w, int h, const FString string, bool show_label)
{
	//Sussy Balls
}

inline void framework::tab(UCanvas* canvas, int x, int y, int w, int h, const FString string, int& tab, int count, bool show_outline)
{
	//Cock and ball torture omg
}

inline bool framework::checkbox(UCanvas* canvas, int x, int y, int position, const FString string, bool& value)
{
	// Nigger
	return value;
}

inline void framework::slider(UCanvas* canvas, int x, int y, int position, const FString string, float& value, float min_value, float max_value)
{
	//Sussy Balls
}

inline void framework::movement(int& x, int& y, int w, int h)
{
	//Nig nog
}

inline auto begin_frame = [&](UCanvas* canvas, int x, int y, int w, int h, FLinearColor bg, FLinearColor header_text, FLinearColor header_line, FString name)
{
	//bazhar is black
};

inline void framework::render_menu(UCanvas* canvas)
{
	//i am gay
}