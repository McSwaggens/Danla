//
// Created by daniel on 1/17/2018.
//

#pragma once

#include "Danla.h"
#include "Keys.h"
#include "MouseKeys.h"

/*	Input.h Key:
 *		Pressed		= The key is Down but wasn't before.
 *		Down		= The key is being pressed.
 *		Up			= The key is NOT being pressed.
 *		Released	= The key was Down and is not Up
 */

void TickInputSystem ();
void UseWindowForInput (HWindow window);

bool IsKeyDown (Keys key);
bool IsKeyUp (Keys key);
bool IsKeyPressed (Keys key);
bool IsKeyReleased (Keys key);

bool IsMouseKeyDown (MouseKeys mouseKey);
bool IsMouseKeyUp (MouseKeys mouseKey);
bool IsMouseKeyPressed (MouseKeys mouseKey);
bool IsMouseKeyReleased (MouseKeys mouseKey);

float GetScroll ();
