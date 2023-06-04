#pragma once
#include <ntifs.h>

namespace StarryEye {
	// ����Kernel Object�Ļ���, ��Ҫ��Ϊ���ṩһ��IsVaild������nullptr���캯��
	class KObjectBase
	{
	public:
		KObjectBase(ULONG64 address);
		KObjectBase(std::nullptr_t);
		~KObjectBase();

		bool IsVaild();

	protected:
		ULONG64 address_;
	};
}