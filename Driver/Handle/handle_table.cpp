#include "handle_table.h"

ULONG64 StarryEye::HandleTable::DecryptHandleAddress(ULONG64 addr)
{
	return ((LONG64)addr >> 0x10) & ~0xF;
}

StarryEye::HandleTable::HandleTable(std::nullptr_t): KObjectBase(nullptr)
{
	table_code_offset_ = 0;
}

StarryEye::HandleTable::HandleTable(ULONG64 address): KObjectBase(address)
{
	table_code_offset_ = 0x8;	//TODO TableCodeƫ��
}

StarryEye::HandleTable::~HandleTable()
{
}

ULONG64 StarryEye::HandleTable::TableCode()
{
	return *(ULONG64*)(address_ + table_code_offset_);
}

UCHAR StarryEye::HandleTable::TableLevel()
{
	return TableCode() & 0b11;
}

ULONG64 StarryEye::HandleTable::TableAddress()
{
	return TableCode() & ~0b11;
}

StarryEye::ObjectHeader StarryEye::HandleTable::GetHandleObject(ULONG64 index)
{
	// ���������
	switch (TableLevel())
	{
	case 0:
	{
		if (index > 512) return nullptr;
		return GetHandleObjectInLv1TableCode((PULONG64)TableAddress(), index);
	}
	case 1:
	{
		if (index > 512ULL * 512) return nullptr;
		return GetHandleObjectInLv2TableCode((PULONG64)TableAddress(), index / 512, index % 512);
	}
	case 2:
	{
		if (index > 512ULL * 512 * 512) return nullptr;
		return GetHandleObjectInLv3TableCode((PULONG64)TableAddress(), index / (512ULL * 512), (index % (512ULL * 512)) / 512, (index % (512ULL * 512)) % 512);
	}
	default:
		return nullptr;
	}
}


StarryEye::ObjectHeader StarryEye::HandleTable::GetHandleObjectInLv1TableCode(PULONG64 table, USHORT index)
{
	if (MmIsAddressValid(table) && index < 512)	// �ж�Ŀ���ַ�Ƿ���Ч
		return ObjectHeader(
			DecryptHandleAddress(table[index]) - OBJECT_HEADER_TO_BODY_SIZE);	// ��Ŀ���ַ����, �ٽ���ַ�ƶ���OBJECT_HEADERͷ��
	return nullptr;
}

StarryEye::ObjectHeader StarryEye::HandleTable::GetHandleObjectInLv2TableCode(PULONG64 table, USHORT index_lv2, USHORT index_lv1)
{
	if (MmIsAddressValid(table) && index_lv2 < 512 && index_lv1 < 512)
		return GetHandleObjectInLv1TableCode((PULONG64)table[index_lv2], index_lv1);
	return nullptr;
}

StarryEye::ObjectHeader StarryEye::HandleTable::GetHandleObjectInLv3TableCode(PULONG64 table, USHORT index_lv3, USHORT index_lv2, USHORT index_lv1)
{
	if (MmIsAddressValid(table) && index_lv3 < 512 && index_lv2 < 512 && index_lv1 < 512)
		return GetHandleObjectInLv2TableCode((PULONG64)table[index_lv3], index_lv2, index_lv1);
	return nullptr;
}
