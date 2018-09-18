/*
 * CUpdateMaskSingle.h
 *
 *  Created by: 2011-10-21
 *      Creator: liukai
 */

#ifndef CUPDATEMASKSINGLE_H_
#define CUPDATEMASKSINGLE_H_

#include "NiSmartPointer.h"
#include "NiRefObject.h"

	class CUpdateMaskSingle : public NiRefObject
	{
	public:
		CUpdateMaskSingle():m_nValue(0) {}
		CUpdateMaskSingle(uint nValue) :m_nValue(nValue) {}
		CUpdateMaskSingle(const CUpdateMaskSingle & mask) {}
		~CUpdateMaskSingle() { Cleanup(); }

	public:

		void SetBit(uint nIndex)
		{
			((uchar *)&m_nValue)[nIndex >> 3] |= 1 << (nIndex & 0x7);
		}

		void UnsetBit(uint nIndex)
		{
			((uchar *)&m_nValue)[nIndex >> 3] &= (0xFF ^ (1 << (nIndex & 0x7)));
		}

		bool GetBit(uint nIndex)
		{
			return (((uchar *)&m_nValue)[nIndex >> 3] & (1 << (nIndex & 0x7))) != 0;
		}

		void Cleanup() { m_nValue = 0; }


	public:
		void SetValue(uint nValue) { m_nValue = nValue; }
		uint GetValue() { return m_nValue; }

	public:
		CUpdateMaskSingle & operator = (const CUpdateMaskSingle & mask)
		{
			m_nValue = mask.m_nValue;

			return *this;
		}

		void operator &= (const CUpdateMaskSingle & mask)
		{
			m_nValue &= mask.m_nValue;
		}

		void operator |= (const CUpdateMaskSingle & mask)
		{
			m_nValue |= mask.m_nValue;
		}

		CUpdateMaskSingle operator & (const CUpdateMaskSingle & mask)
		{
			CUpdateMaskSingle newmask;
			newmask = *this;
			newmask &= mask;

			return newmask;
		}

		CUpdateMaskSingle operator | (const CUpdateMaskSingle & mask)
		{
			CUpdateMaskSingle newmask;
			newmask = *this;
			newmask |= mask;

			return newmask;
		}

	private:
		uint m_nValue;
	};

#endif /* CUPDATEMASKSINGLE_H_ */
