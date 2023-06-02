#pragma once
#include <ntifs.h>
#include "object_type.h"
#include "global_vars.hpp"

namespace StarryEye {

#define OBJECT_HEADER_TO_BODY_SIZE 0x30


class ObjectHeader
{
public:
	// ����TypeIndex
	static UCHAR DecryptTypeIndex(ULONG64 obj_addr, UCHAR type_index);

	ObjectHeader(std::nullptr_t);
	ObjectHeader(ULONG64 address);
	~ObjectHeader();

	// ��ȡTypeIndex
	UCHAR TypeIndex();

	// ��ȡ���ܺ��TypeIndex
	UCHAR TypeIndexDecrypted();

	// ��ȡType����(ע��: ʹ��ǰһ��Ҫ�ȵ���ObjectType::Init()!)
	ObjectType Type();

	bool IsVaild();

private:
	// ��ַ
	ULONG64 address_;
	UINT16 type_index_offset;
};

}