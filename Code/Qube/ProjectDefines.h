#ifndef __QUBE_PROJECTDEFINES_H__
#define __QUBE_PROJECTDEFINES_H__

#pragma once

#ifdef QUBE_EXPORTS
#	define QUBE_API __declspec(dllexport)
#else
#	define QUBE_API __declspec(dllimport)
#endif

#ifdef _WIN32
#	define QUBE_OS_WINDOWS
#	ifdef _WIN64
#		define QUBE_OS_64
#	else
#		define QUBE_OS_32
#	endif
#endif

#endif
