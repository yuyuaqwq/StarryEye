#include "psp_cid_table.h"

using namespace StarryEye;


ULONG64 PspCidTable::DecryptHandleAddress(ULONG64 addr)
{
	return (addr >> 0x10) & ~0xF;
}

ObjectHeader PspCidTable::GetHandleObject(ULONG64 index)
{
	// TODO
	return ObjectHeader(114514);
}


ObjectHeader StarryEye::PspCidTable::GetHandleObjectInLv1TableCode(PULONG64 table, USHORT index)
{
	if (MmIsAddressValid(table + index))	// �ж�Ŀ���ַ�Ƿ���Ч
		return ObjectHeader(
			DecryptHandleAddress(table[index]) - OBJECT_HEADER_TO_BODY_SIZE);	// ��Ŀ���ַ����, �ٽ���ַ�ƶ���OBJECT_HEADERͷ��
	return nullptr;
}

ObjectHeader StarryEye::PspCidTable::GetHandleObjectInLv2TableCode(PULONG64 table, USHORT index_lv2, USHORT index_lv1)
{
	if (MmIsAddressValid(table + index_lv2))
		return GetHandleObjectInLv1TableCode((PULONG64)table[index_lv2], index_lv1);
	return nullptr;
}

ObjectHeader StarryEye::PspCidTable::GetHandleObjectInLv2TableCode(PULONG64 table, USHORT index_lv3, USHORT index_lv2, USHORT index_lv1)
{
	if (MmIsAddressValid(table + index_lv3))
		return GetHandleObjectInLv2TableCode((PULONG64)table[index_lv3], index_lv2, index_lv1);
	return nullptr;
}
