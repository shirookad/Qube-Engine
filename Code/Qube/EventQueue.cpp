#include "stdafx.h"
#include "EventQueue.h"

#include <SDL.h>
#include <assert.h>

namespace qube {

	void EventQueue::pushAll() const {
		SDL_PumpEvents();
	}

	bool EventQueue::poll(Event *out) const {
		assert(out != nullptr);
		
		static SDL_Event sdlEvent;
		if (!SDL_PollEvent(&sdlEvent)) { return false; }

		switch (sdlEvent.type) {
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
		case SDL_MOUSEMOTION: out->type = Event::Type::MOUSE_MOTION; break;
		case SDL_MOUSEWHEEL: out->type = Event::Type::MOUSE_MOTION_WHEEL; break;
		case SDL_MOUSEBUTTONDOWN: out->type = Event::Type::MOUSE_BUTTON_DOWN; break;
		case SDL_MOUSEBUTTONUP: out->type = Event::Type::MOUSE_BUTTON_UP; break;
		case SDL_QUIT: out->type = Event::Type::QUIT; break;
		case SDL_WINDOWEVENT: out->type = Event::Type::WINDOW; break;
		case SDL_USEREVENT: out->type = Event::Type::USER; break;
		}

		return true;
	}
}