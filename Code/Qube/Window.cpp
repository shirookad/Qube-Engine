#include "stdafx.h"
#include "Window.h"

#include "ErrorHandler.h"

#include <SDL.h>

namespace qube {
	constexpr uint32 QubeWindowFlag2SdlFlag[QUBE_ENUM_ELEMENT_COUNT(Window::Flag)] = {
		SDL_WINDOW_FULLSCREEN,
		SDL_WINDOW_FULLSCREEN_DESKTOP,
		SDL_WINDOW_OPENGL,
		SDL_WINDOW_HIDDEN,
		SDL_WINDOW_BORDERLESS,
		SDL_WINDOW_RESIZABLE,
		SDL_WINDOW_MINIMIZED,
		SDL_WINDOW_MAXIMIZED,
		SDL_WINDOW_ALLOW_HIGHDPI
	};

	inline uint32 QubeWindowFlags2SdlWindowFlags(Window::FlagBit options) {
		uint32 sdlWindowFlags = 0;
		if (options & Window::FlagBit::FULLSCREEN) { sdlWindowFlags |= SDL_WINDOW_FULLSCREEN; }
		if (options & Window::FlagBit::FULLSCREEN_DESKTOP) { sdlWindowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }
		if (options & Window::FlagBit::OPENGL) { sdlWindowFlags |= SDL_WINDOW_OPENGL; }
		if (options & Window::FlagBit::HIDDEN) { sdlWindowFlags |= SDL_WINDOW_HIDDEN; }
		if (options & Window::FlagBit::BORDERLESS) { sdlWindowFlags |= SDL_WINDOW_BORDERLESS; }
		if (options & Window::FlagBit::RESIZABLE) { sdlWindowFlags |= SDL_WINDOW_RESIZABLE; }
		if (options & Window::FlagBit::MINIMIZED) { sdlWindowFlags |= SDL_WINDOW_MINIMIZED; }
		if (options & Window::FlagBit::MAXIMIZED) { sdlWindowFlags |= SDL_WINDOW_MAXIMIZED; }
		if (options & Window::FlagBit::ALLOW_HIGHDPI) { sdlWindowFlags |= SDL_WINDOW_ALLOW_HIGHDPI; }
		return sdlWindowFlags;
	}

	Window::Window(const char *title, int x, int y, int w, int h, FlagBit options) {
		if (!SDL_WasInit(SDL_INIT_VIDEO)) {
			auto error = SDL_Init(SDL_INIT_VIDEO);
			if (error) { QUBE_PUSH_ERROR(g_errorHandler, std::string("Failed to initialize SDLs video subsystem, error code: ") + std::to_string(error) + ", error message: " + SDL_GetError()); return; }
		}

		m_window = (__SDL_Window)SDL_CreateWindow(title, x, y, w, h, QubeWindowFlags2SdlWindowFlags(options));
		if (!m_window) { QUBE_PUSH_ERROR(g_errorHandler, std::string("Failed to create SDL window, error message: ") + SDL_GetError()); }
	}

	Window::~Window() {
		if (m_window) { SDL_DestroyWindow((SDL_Window *)m_window); }

		// TODO: No.
		SDL_Quit();
	}

	void Window::setTitle(const char *title) { SDL_SetWindowTitle((SDL_Window *)m_window, title); }
	const char *Window::title() const { return SDL_GetWindowTitle((SDL_Window *)m_window); }
}