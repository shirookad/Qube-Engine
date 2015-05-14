#include "stdafx.h"
#include "EventQueue.h"

#include "ErrorHandler.h"

#include <SDL.h>
#include <assert.h>
#include <array>
#include <string>

namespace qube {

	void EventQueue::pushAll() const {
		SDL_PumpEvents();
	}

	constexpr std::array<uint32, QUBE_ENUM_ELEMENT_COUNT(Event::Type)> QubeEventType2SdlEventType = {
		0,
		SDL_APP_TERMINATING,
		SDL_APP_LOWMEMORY,
		SDL_APP_WILLENTERBACKGROUND,
		SDL_APP_DIDENTERBACKGROUND,
		SDL_APP_WILLENTERFOREGROUND,
		SDL_APP_DIDENTERFOREGROUND,
		SDL_CONTROLLERAXISMOTION,
		SDL_CONTROLLERBUTTONDOWN,
		SDL_CONTROLLERBUTTONUP,
		SDL_CONTROLLERDEVICEADDED,
		SDL_CONTROLLERDEVICEREMOVED,
		SDL_CONTROLLERDEVICEREMAPPED,
		SDL_DROPFILE,
		SDL_FINGERMOTION,
		SDL_FINGERDOWN,
		SDL_FINGERUP,
		SDL_KEYDOWN,
		SDL_KEYUP,
		SDL_JOYAXISMOTION,
		SDL_JOYBALLMOTION,
		SDL_JOYHATMOTION,
		SDL_JOYBUTTONDOWN,
		SDL_JOYBUTTONUP,
		SDL_JOYDEVICEADDED,
		SDL_JOYDEVICEREMOVED,
		SDL_MOUSEMOTION,
		SDL_MOUSEWHEEL,
		SDL_MOUSEBUTTONDOWN,
		SDL_MOUSEBUTTONUP,
		SDL_QUIT,
		SDL_WINDOWEVENT,
		SDL_USEREVENT
	};

	void EventQueue::push(const Event& in) const {
		SDL_Event sdlEvent;
		sdlEvent.type = QubeEventType2SdlEventType[static_cast<int32>(in.type)];
		if (auto error = SDL_PushEvent(&sdlEvent)) {
			QUBE_PUSH_ERROR(g_errorHandler,
				std::string("Failed to push event to the SDL event queue, error code: ")
				+ std::to_string(error)
				+ ", error message: "
				+ SDL_GetError());
			return;
		}
	}

	bool EventQueue::poll(Event *out) const {
		assert(out != nullptr);

		static SDL_Event sdlEvent;
		if (!SDL_PollEvent(&sdlEvent)) { return false; }

		switch (sdlEvent.type) {
		case SDL_APP_TERMINATING: out->type = Event::Type::APP_TERMINATING; break;
		case SDL_APP_LOWMEMORY: out->type = Event::Type::APP_LOWMEMORY; break;
		case SDL_APP_WILLENTERBACKGROUND: out->type = Event::Type::APP_WILLENTERBACKGROUND; break;
		case SDL_APP_DIDENTERBACKGROUND: out->type = Event::Type::APP_DIDENTERBACKGROUND; break;
		case SDL_APP_WILLENTERFOREGROUND: out->type = Event::Type::APP_WILLENTERFOREGROUND; break;
		case SDL_APP_DIDENTERFOREGROUND: out->type = Event::Type::APP_DIDENTERFOREGROUND; break;
		case SDL_CONTROLLERAXISMOTION: out->type = Event::Type::CONTROLLER_AXIS_MOTION; break;
		case SDL_CONTROLLERBUTTONDOWN: out->type = Event::Type::CONTROLLER_BUTTON_DOWN; break;
		case SDL_CONTROLLERBUTTONUP: out->type = Event::Type::CONTROLLER_BUTTON_UP; break;
		case SDL_CONTROLLERDEVICEADDED: out->type = Event::Type::CONTROLLER_DEVICE_ADDED; break;
		case SDL_CONTROLLERDEVICEREMOVED: out->type = Event::Type::CONTROLLER_DEVICE_REMOVED; break;
		case SDL_CONTROLLERDEVICEREMAPPED: out->type = Event::Type::CONTROLLER_DEVICE_REMAPPED; break;
		case SDL_DROPFILE: out->type = Event::Type::DROP_FILE; break;
		case SDL_FINGERMOTION: out->type = Event::Type::TOUCH_MOTION; break;
		case SDL_FINGERDOWN: out->type = Event::Type::TOUCH_BEGAN; break;
		case SDL_FINGERUP: out->type = Event::Type::TOUCH_ENDED; break;
		case SDL_KEYDOWN: out->type = Event::Type::KEY_DOWN; break;
		case SDL_KEYUP: out->type = Event::Type::KEY_UP; break;
		case SDL_JOYAXISMOTION: out->type = Event::Type::JOYSTICK_AXIS_MOTION; break;
		case SDL_JOYBALLMOTION: out->type = Event::Type::JOYSTICK_BALL_MOTION; break;
		case SDL_JOYHATMOTION: out->type = Event::Type::JOYSTICK_HAT_MOTION; break;
		case SDL_JOYBUTTONDOWN: out->type = Event::Type::JOYSTICK_BUTTON_DOWN; break;
		case SDL_JOYBUTTONUP: out->type = Event::Type::JOYSTICK_BUTTON_UP; break;
		case SDL_JOYDEVICEADDED: out->type = Event::Type::JOYSTICK_DEVICE_ADDED; break;
		case SDL_JOYDEVICEREMOVED: out->type = Event::Type::JOYSTICK_DEVICE_REMOVED; break;
		case SDL_MOUSEMOTION:
			if (sdlEvent.button.which == SDL_TOUCH_MOUSEID) { break; }
			out->type = Event::Type::MOUSE_MOTION;
			break;
		case SDL_MOUSEWHEEL: out->type = Event::Type::MOUSE_MOTION_WHEEL; break;
		case SDL_MOUSEBUTTONDOWN:
			if (sdlEvent.button.which == SDL_TOUCH_MOUSEID) { break; }
			out->type = Event::Type::MOUSE_BUTTON_DOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			if (sdlEvent.button.which == SDL_TOUCH_MOUSEID) { break; }
			out->type = Event::Type::MOUSE_BUTTON_UP;
			break;
		case SDL_QUIT: out->type = Event::Type::QUIT; break;
		case SDL_WINDOWEVENT: out->type = Event::Type::WINDOW; break;
		case SDL_USEREVENT: out->type = Event::Type::USER; break;
		}

		return true;
	}
}