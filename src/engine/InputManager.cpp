#define INCLUDE_SDL
#include "engine/SDL_include.h"
#include "engine/InputManager.h"
#include <iostream>
#include <cstring>

InputManager::InputManager() {
	memset(mousePressed, 0, sizeof(mousePressed));
	memset(mouseUpdate, 0, sizeof(mouseUpdate));

	quitRequested = false;
	
	updateCounter = 0;

	mouseX = mouseY = 0;
}

InputManager::~InputManager() {}

void InputManager::Update() {
	SDL_GetMouseState(&mouseX, &mouseY);	// * Get mouse coordinates.

	quitRequested = false;

	updateCounter = (updateCounter+1) % UINT32_MAX;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				mousePressed[event.button.button] = (event.type == SDL_MOUSEBUTTONDOWN) ? true : false;
				mouseUpdate[event.button.button] = updateCounter;
				//std::cout << "Button id: " << (int)event.button.button << std::endl;
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (!event.key.repeat) {
					auto mapStateIt = keyPressed.find(event.key.keysym.sym);
					//auto mapUpdateIt = keyUpdate.find(event.key.keysym.sym);

					if (mapStateIt != keyPressed.end()) {	// Is in the map.
						mapStateIt->second = (event.type == SDL_KEYDOWN) ? true : false;
						keyUpdate.find(event.key.keysym.sym)->second = updateCounter;
					}
					else {
						keyPressed[event.key.keysym.sym] = (event.type == SDL_KEYDOWN) ? true : false;
						keyUpdate[event.key.keysym.sym] = updateCounter;
					}
					//std::cout << "Key id: " << (int)event.key.keysym.sym << std::endl;
				}
				break;

			case SDL_QUIT:
				quitRequested = true;
				break;
		}
	}
} 

bool InputManager::KeyPress(KEYS key) {
	auto isKey = keyPressed.find(int(key)) != keyPressed.end();

	if (isKey && keyPressed.at(int(key)) && keyUpdate.at(int(key)) == updateCounter ||
			mousePressed[int(key)] && mouseUpdate[int(key)] == updateCounter) {
		return true;
	}

	return false;
}

bool InputManager::KeyRelease(KEYS key) {
	auto isKey = keyPressed.find(int(key)) != keyPressed.end();

	if (isKey && !keyPressed.at(int(key)) && keyUpdate.at(int(key)) == updateCounter ||
			!mousePressed[int(key)] && mouseUpdate[int(key)] == updateCounter) {
		return true;
	}

	return false;
}

bool InputManager::IsKeyDown(KEYS key) {
	auto isKey = keyPressed.find(int(key)) != keyPressed.end();

	if (isKey && keyPressed.at(int(key)) || mousePressed[int(key)]) {
		return true;
	}
	
	return false;
}

int InputManager::GetMouseX() { return mouseX; }

int InputManager::GetMouseY() { return mouseY; }

bool InputManager::QuitRequested() { return quitRequested; }

InputManager& InputManager::GetInstance() {
	static InputManager inst;
	return inst;
}
