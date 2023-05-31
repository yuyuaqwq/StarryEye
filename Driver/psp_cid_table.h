#pragma once
#include "object_header.h"
#include "ynstd.hpp"


namespace StarryEye{

class PspCidTable
{
public:
	PspCidTable() = delete;

	// PspCidTable��ַ
	static ULONG64 Address;

	// ����HandleTable��Handle���·��
	static ULONG64 DecrypteHandleAddress(ULONG64 addr);

	// ����������ȡHandle����
	static ObjectHeader GetHandleObject(ULONG64 index);

	// ��ȡ�����һ��TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectIfLv1TableCode();
	// ��ȡ����Ƕ���TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectIfLv2TableCode();
	// ��ȡ���������TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectIfLv3TableCode();
};

ULONG64 PspCidTable::Address = 0x114514;

}