#pragma once
#include <ntifs.h>

// ���õ�ȫ�ֱ�������������
namespace StarryEye {
	extern UNICODE_STRING ProcessTypeString;
	extern UNICODE_STRING ThreadTypeString;

	extern UCHAR ObHeaderCookie;
	extern PVOID PspCidTable;
	extern PULONG64 ObTypeIndexTable;

	// ��ʼ��ȫ�ֱ���
	inline void InitGlobalVars()
	{
		RtlInitUnicodeString(&ProcessTypeString, L"Process");
		RtlInitUnicodeString(&ThreadTypeString, L"Thread");
		PspCidTable = (PVOID)0xffffcb0e0960ab40;	//TODO
		ObTypeIndexTable = (PULONG64)0xfffff8066f911e80;
		ObHeaderCookie = 0xd3;
	}

}