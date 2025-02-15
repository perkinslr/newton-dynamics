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

#ifndef __ND_CUMATRIX3x3_H__
#define __ND_CUMATRIX3x3_H__

#include "cuVector.h"
#include "cuIntrinsics.h"

class cuMatrix3x3
{
	public:
	inline __device__ __host__ cuMatrix3x3()
	{
	}

	inline __device__ __host__ cuMatrix3x3(const cuMatrix3x3& src)
		:m_front(src.m_front)
		,m_up(src.m_up)
		,m_right(src.m_right)
	{
	}

	inline __device__ __host__ cuMatrix3x3(const cuVector& front, const cuVector& up, const cuVector& right)
		:m_front(front)
		,m_up(up)
		,m_right(right)
	{
	}

	inline cuMatrix3x3 __device__ __host__ operator* (const cuMatrix3x3& A) const
	{
		return cuMatrix3x3(A.RotateVector(m_front), A.RotateVector(m_up), A.RotateVector(m_right));
	}

	inline cuVector __device__ __host__ UnrotateVector(const cuVector &v) const
	{
		return cuVector((m_front * v).AddHorizontal(), (m_up * v).AddHorizontal(), (m_right * v).AddHorizontal(), 0.0f);
	}

	inline cuVector __device__ __host__ RotateVector(const cuVector& v) const
	{
		return m_front.Scale(v.x) + m_up.Scale(v.y) + m_right.Scale(v.z);
	}

	inline cuVector __device__ __host__ SolveByGaussianElimination(const cuVector &v) const
	{
		cuMatrix3x3 tmp(*this);
		cuVector ret(v);
		for (int i = 0; i < 3; ++i)
		{
			float pivot = cuAbs(tmp.m_data[i].GetElement(i));
			if (pivot < float(0.01f))
			{
				int permute = i;
				for (int j = i + 1; j < 3; ++j)
				{
					float pivot1 = cuAbs(tmp.m_data[j].GetElement(i));
					if (pivot1 > pivot)
					{
						permute = j;
						pivot = pivot1;
					}
				}

				if (permute != i)
				{
					float a0 = ret.GetElement(i);
					ret.SetElement(i, ret.GetElement(permute));
					ret.SetElement(permute, a0);
					cuSwap(tmp.m_data[i], tmp.m_data[permute]);
				}
			}

			for (int j = i + 1; j < 3; ++j)
			{
				const cuVector scale(tmp.m_data[j].GetElement(i) / tmp.m_data[i].GetElement(i));
				tmp.m_data[j] = tmp.m_data[j] - tmp.m_data[i] * scale;
				ret.SetElement(j, ret.GetElement(j) - ret.GetElement(i) * scale.x);
				tmp.m_data[j].SetElement(i, 0.0f);
			}
		}

		for (int i = 2; i >= 0; --i)
		{
			const cuVector pivot(tmp.m_data[i] * ret);
			ret.SetElement(i, (ret.GetElement(i) - pivot.AddHorizontal() + tmp.m_data[i].GetElement(i) * ret.GetElement(i)) / tmp.m_data[i].GetElement(i));
		}

		return ret;
	}

	union
	{
		struct
		{
			cuVector m_front;
			cuVector m_up;
			cuVector m_right;
		};
		cuVector m_data[3];
	};
};

#endif