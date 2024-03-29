//
// Created by daniel on 1/17/2018.
//

#pragma once


// Taken from glfw3.h
// Shortened for ease of use.

static const int keyCodes[] = { 32, 39, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 59, 61, 65, 66, 67, 68, 69, 70,
				   71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 96, 161,
				   162, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 280, 281, 282, 283, 284,
				   290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309,
				   310, 311, 312, 313, 314, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334,
				   335, 336, 340, 341, 342, 343, 344, 345, 346, 347, 348 };

enum class Keys : int
{
	Unknown        = -1,
	Space              ,
	Apostrophe         ,
	Comma              ,
	Minus              ,
	Period             ,
	Slash              ,
	D0                 ,
	D1                 ,
	D2                 ,
	D3                 ,
	D4                 ,
	D5                 ,
	D6                 ,
	D7                 ,
	D8                 ,
	D9                 ,
	Semicolon          ,
	Equal              ,
	A                  ,
	B                  ,
	C                  ,
	D                  ,
	E                  ,
	F                  ,
	G                  ,
	H                  ,
	I                  ,
	J                  ,
	K                  ,
	L                  ,
	M                  ,
	N                  ,
	O                  ,
	P                  ,
	Q                  ,
	R                  ,
	S                  ,
	T                  ,
	U                  ,
	V                  ,
	W                  ,
	X                  ,
	Y                  ,
	Z                  ,
	LeftBracket        ,
	Backslash          ,
	RightBracket       ,
	GraveAccent        ,
	World1             ,
	World2             ,
	Escape             ,
	Enter              ,
	Tab                ,
	Backspace          ,
	Insert             ,
	Delete             ,
	Right              ,
	Left               ,
	Down               ,
	Up                 ,
	PageUp             ,
	PageDown           ,
	Home               ,
	End                ,
	CapsLock           ,
	ScrollLock         ,
	NumLock            ,
	PrintScreen        ,
	Pause              ,
	F1                 ,
	F2                 ,
	F3                 ,
	F4                 ,
	F5                 ,
	F6                 ,
	F7                 ,
	F8                 ,
	F9                 ,
	F10                ,
	F11                ,
	F12                ,
	F13                ,
	F14                ,
	F15                ,
	F16                ,
	F17                ,
	F18                ,
	F19                ,
	F20                ,
	F21                ,
	F22                ,
	F23                ,
	F24                ,
	F25                ,
	Keypad0            ,
	Keypad1            ,
	Keypad2            ,
	Keypad3            ,
	Keypad4            ,
	Keypad5            ,
	Keypad6            ,
	Keypad7            ,
	Keypad8            ,
	Keypad9            ,
	KeypadDecimal      ,
	KeypadDivide       ,
	KeypadMultiply     ,
	KeypadSubtract     ,
	KeypadAdd          ,
	KeypadEnter        ,
	KeypadEqual        ,
	LeftShift          ,
	LeftControl        ,
	LeftAlt            ,
	LeftSuper          ,
	RightShift         ,
	RightControl       ,
	RightAlt           ,
	RightSuper         ,
	Menu               ,
};


// Mods

enum class Mods
{
	Shift           = 0x0001,
	Control         = 0x0002,
	Alt             = 0x0004,
	Super           = 0x0008,
	CapsLock        = 0x0010,
	NumLock         = 0x0020,
};
