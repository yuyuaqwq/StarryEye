#pragma once
#include "object_header.h"
#include "handle_table.h"
#include "ynstd.hpp"


namespace StarryEye{

class PspCidTable
{
public:
	PspCidTable() = delete;

	// PspCidTable����
	static HandleTable Object;

	// ����HandleTable��Handle���·��
	static ULONG64 DecrypteHandleAddress(ULONG64 addr);
	// ����������ȡHandle����
	static ObjectHeader GetHandleObject(ULONG64 index);

	// ��ȡһ��TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectsInLv1TableCode(ULONG64 table_addr);
	// ��ȡ����TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectsInLv2TableCode(ULONG64 table_addr);
	// ��ȡ����TableCode������Handle����
	static ynstd::list<ObjectHeader> GetAllHandleObjectsInLv3TableCode(ULONG64 table_addr);

	// ��ȡһ��TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv1TableCode(ULONG64 table_addr, USHORT index);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv2TableCode(ULONG64 table_addr, USHORT index_lv2, USHORT index_lv1);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv2TableCode(ULONG64 table_addr, USHORT index_lv3, USHORT index_lv2, USHORT index_lv1);
};

}