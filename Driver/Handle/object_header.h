#pragma once
#include "Config/kobject_base.h"
#include "object_type.h"
#include "Config/global_vars.h"

namespace StarryEye {

#define OBJECT_HEADER_TO_BODY_SIZE 0x30


class ObjectHeader: public KObjectBase
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

	// ��ȡBody
	PVOID Body();

	// ��ȡBody��ת��Ϊ����
	template<class T>
	T BodyObject();

private:
	UINT16 type_index_offset;
	UINT16 body_offset_;
};

template<class T>
inline T ObjectHeader::BodyObject()
{
	return T((ULONG64)Body());
}

}