#ifndef __QUBE_WINDOW_H__
#define __QUBE_WINDOW_H__

#pragma once

#include "ProjectDefines.h"

#include <string>
#include <vec2.hpp>

namespace qube {
	class Window {
	public:
		enum class Flag : int32 {
			FULLSCREEN,
			FULLSCREEN_DESKTOP,
			OPENGL,
			HIDDEN,
			BORDERLESS,
			RESIZABLE,
			MINIMIZED,
			MAXIMIZED,
			ALLOW_HIGHDPI,
			__COUNT
		};

		enum class FlagBit : uint32 {
			FULLSCREEN = 1 << static_cast<uint32>(Flag::FULLSCREEN),
			FULLSCREEN_DESKTOP = 1 << static_cast<uint32>(Flag::FULLSCREEN_DESKTOP),
			OPENGL = 1 << static_cast<uint32>(Flag::OPENGL),
			HIDDEN = 1 << static_cast<uint32>(Flag::HIDDEN),
			BORDERLESS = 1 << static_cast<uint32>(Flag::BORDERLESS),
			RESIZABLE = 1 << static_cast<uint32>(Flag::RESIZABLE),
			MINIMIZED = 1 << static_cast<uint32>(Flag::MINIMIZED),
			MAXIMIZED = 1 << static_cast<uint32>(Flag::MAXIMIZED),
			ALLOW_HIGHDPI = 1 << static_cast<uint32>(Flag::ALLOW_HIGHDPI),
			__COUNT
		};

	private:
		using __SDL_Window = void *;
		__SDL_Window m_window{ nullptr };

	public:
		QUBE_API Window(const char *title, int x, int y, int w, int h, FlagBit options);
		QUBE_API ~Window();

		QUBE_API void setTitle(const char *title);
		QUBE_API const char *title() const;
	};

	constexpr uint32 operator & (Window::FlagBit lhs, Window::FlagBit rhs) {
		return static_cast<uint32>(lhs) & static_cast<uint32>(rhs);
	}
	constexpr Window::FlagBit operator | (Window::FlagBit lhs, Window::FlagBit rhs) {
		return static_cast<Window::FlagBit>(static_cast<uint32>(lhs) | static_cast<uint32>(rhs));
	}
}

#endif