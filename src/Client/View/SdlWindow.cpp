#include "SdlWindow.h"
#include "SdlException.h"

SdlWindow::SdlWindow(const int width, const int height) :
	width(width),
	height(height),
	full_screen(false),
	window(nullptr),
	renderer(nullptr),
	iconSurface(nullptr) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		throw SdlException("Error en la inicialización", SDL_GetError());
	}
	if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
	                                &this->window, &this->renderer)) {
		throw SdlException("Error al crear ventana", SDL_GetError());
	}
	SDL_SetWindowTitle(this->window, "Dune");
}

SdlWindow::~SdlWindow() {
	if (this->iconSurface != nullptr) {
		SDL_FreeSurface(this->iconSurface);
		this->iconSurface = nullptr;
	}
	if (this->renderer != nullptr) {
		SDL_DestroyRenderer(this->renderer);
		this->renderer = nullptr;
	}
	this->destroyWindow();
	SDL_Quit();
}

void SdlWindow::destroyWindow() {
	if (this->window != nullptr) {
		SDL_DestroyWindow(this->window);
		this->window = nullptr;
	}
}

void SdlWindow::grabMouse(bool grab) {
	if (grab) {
		SDL_SetWindowGrab(window, SDL_TRUE);
	} else {
		SDL_SetWindowGrab(window, SDL_FALSE);
	}
}

void SdlWindow::fill(const Uint8 r, const Uint8 g,
                     const Uint8 b, const Uint8 alpha) {
	SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
	SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
	this->fill(0x0, 0x0, 0x0, 0x0);
}

void SdlWindow::render() {
	SDL_RenderPresent(this->renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
	return this->renderer;
}

void SdlWindow::toggleFullScreen() {
	if (full_screen) {
		SDL_SetWindowFullscreen(window, 0);
		full_screen = false;
	} else {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		full_screen = true;
	}
}
