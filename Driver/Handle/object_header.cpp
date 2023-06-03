#include "object_header.h"

UCHAR StarryEye::ObjectHeader::DecryptTypeIndex(ULONG64 obj_addr, UCHAR type_index)
{
	UCHAR x = (UCHAR)(obj_addr >> 8);
	return 0xd3 ^ type_index ^ x;
}

StarryEye::ObjectHeader::ObjectHeader(std::nullptr_t)
{
	address_ = 0;
}

StarryEye::ObjectHeader::ObjectHeader(ULONG64 address)
{
	address_ = address;
	type_index_offset = 0x18;		//TODO TypeIndexƫ��
}

StarryEye::ObjectHeader::~ObjectHeader()
{
}

UCHAR StarryEye::ObjectHeader::TypeIndex()
{
	return *(UCHAR*)(address_ + type_index_offset);
}

UCHAR StarryEye::ObjectHeader::TypeIndexDecrypted()
{
	return DecryptTypeIndex(address_, TypeIndex());
}

StarryEye::ObjectType StarryEye::ObjectHeader::Type()
{
	auto cnm = &ObTypeIndexTable - 1;					//TODO ����Ϊʲô��ôд, �ʾ�����Ҫ����ɵ�Ʊ�������ƨ��!!!!!!!!!!!
	return ObjectType((*cnm)[TypeIndexDecrypted()]);	// ����TypeIndex��ObTypeIndexTable�л�ȡ_OBJECT_TYPE
}

bool StarryEye::ObjectHeader::IsVaild()
{
	return MmIsAddressValid((PVOID)address_);
}
