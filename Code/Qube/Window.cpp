#include "stdafx.h"
#include "Window.h"

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

	Window::Window(const char *title, int x, int y, int w, int h) {
		if (!SDL_WasInit(SDL_INIT_VIDEO)) {
			auto error = SDL_Init(SDL_INIT_VIDEO);
			if (error) { throw std::runtime_error{ std::string("Failed to initialize SDLs video subsystem, error code: ") + std::to_string(error) + ", error message: " + SDL_GetError() }; }
		}

		m_window = (__SDL_Window)SDL_CreateWindow(title, x, y, w, h, 0);
		if (!m_window) { throw std::runtime_error{ std::string("Failed to create SDL window, error message: ") + SDL_GetError() }; }
	}

	Window::~Window() {
		if (m_window) { SDL_DestroyWindow((SDL_Window *)m_window); }

		// TODO: No.
		SDL_Quit();
	}

	void Window::setTitle(const char *title) noexcept { SDL_SetWindowTitle((SDL_Window *)m_window, title); }
	const char *Window::title() const noexcept { return SDL_GetWindowTitle((SDL_Window *)m_window); }
}