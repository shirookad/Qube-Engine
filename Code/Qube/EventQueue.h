#ifndef __QUBE_EVENTQUEUE_H__
#define __QUBE_EVENTQUEUE_H__

#pragma once

#include "ProjectDefines.h"

namespace qube {
	struct Event {
		enum class Type : int32 {
			NONE,
			APP_TERMINATING,
			APP_LOWMEMORY,
			APP_WILLENTERBACKGROUND,
			APP_DIDENTERBACKGROUND,
			APP_WILLENTERFOREGROUND,
			APP_DIDENTERFOREGROUND,
			CONTROLLER_AXIS_MOTION,
			CONTROLLER_BUTTON_DOWN,
			CONTROLLER_BUTTON_UP,
			CONTROLLER_DEVICE_ADDED,
			CONTROLLER_DEVICE_REMOVED,
			CONTROLLER_DEVICE_REMAPPED,
			DROP_FILE,
			TOUCH_MOTION,
			TOUCH_BEGAN,
			TOUCH_ENDED,
			KEY_DOWN,
			KEY_UP,
			JOYSTICK_AXIS_MOTION,
			JOYSTICK_BALL_MOTION,
			JOYSTICK_HAT_MOTION,
			JOYSTICK_BUTTON_DOWN,
			JOYSTICK_BUTTON_UP,
			JOYSTICK_DEVICE_ADDED,
			JOYSTICK_DEVICE_REMOVED,
			MOUSE_MOTION,
			MOUSE_MOTION_WHEEL,
			MOUSE_BUTTON_DOWN,
			MOUSE_BUTTON_UP,
			QUIT,
			WINDOW,
			USER,
			__COUNT
		};

		Type type;

		constexpr Event() : type(Type::NONE) {  }
		constexpr Event(Type _type) : type(_type) {  }
	};
	
	class EventQueue {
	public:
		QUBE_API void pushAll() const;
		QUBE_API void push(const Event& in) const;
		QUBE_API bool poll(Event *out) const;
	};
}

#endif
