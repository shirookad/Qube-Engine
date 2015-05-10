#ifndef __QUBE_PROJECTDEFINES_H__
#define __QUBE_PROJECTDEFINES_H__

#pragma once

#ifdef QUBE_EXPORTS
#	define QUBE_API __declspec(dllexport)
#else
#	define QUBE_API __declspec(dllimport)
#endif

#endif
