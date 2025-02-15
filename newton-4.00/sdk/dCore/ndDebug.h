/* Copyright (c) <2003-2021> <Julio Jerez, Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __ND_DEBUG_H__
#define __ND_DEBUG_H__

#include "ndCoreStdafx.h"
#include "ndTypes.h"

#ifdef _MSC_VER 
	#ifdef _DEBUG 
		#define D_TRACE
	#endif
#endif

#ifdef D_TRACE
	D_CORE_API void ndExpandTraceMessage(const char* const fmt, ...);
	#define dTrace(x) ndExpandTraceMessage x;
#else
	#define dTrace(x);
#endif


#ifdef _DEBUG
	inline void TraceFuntionName (const char *name)
	{
		//	static dInt32 trace;
		//	dTrace (("%d %s\n", trace, name));
		dTrace (("%s\n", name));
	}

	//#define TRACE_FUNCTION(name) TraceFuntionName (name)
	#define TRACE_FUNCTION(name)
#else
	#define TRACE_FUNCTION(name)
#endif

	
#endif

