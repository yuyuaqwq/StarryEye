#pragma once
#include "Config/base.h"
#include "Handle/object_type.h"

namespace StarryEye {
class ObjectHeader: public KObjectBase
{
public:
	inline static UCHAR ObHeaderCookie;

	static void Init();
	static ULONG64 GetBodyOffset();

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
	inline static ULONG64 TypeIndexOffset;
	inline static ULONG64 BodyOffset;
};

template<class T>
inline T ObjectHeader::BodyObject()
{
	return T((ULONG64)Body());
}

}