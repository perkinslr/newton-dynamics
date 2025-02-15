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

#ifndef __ND_THREAD_H_
#define __ND_THREAD_H_

#include "ndCoreStdafx.h"
#include "ndSemaphore.h"
#include "ndClassAlloc.h"

class ndThreadName
{
	public:
	ndThreadName()
	{
		strcpy(m_name, "newtonWorker");
	}
	char m_name[32];
};

class ndThread
	:public ndClassAlloc
	,public ndThreadName
	,public ndSemaphore
#ifndef D_USE_THREAD_EMULATION
	,public ndAtomic<bool>
	,public std::condition_variable
	,public std::thread
#endif
{
	public:
	D_CORE_API ndThread();
	D_CORE_API virtual ~ndThread();

	D_CORE_API void SetName(const char* const name);

	D_CORE_API void Finish();
	D_CORE_API void Signal();

	virtual void ThreadFunction() = 0;

	protected:
	virtual void Release(){}

	private:
	void ThreadFunctionCallback();
};

#endif
