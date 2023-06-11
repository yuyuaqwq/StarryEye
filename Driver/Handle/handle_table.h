#pragma once
#include "Config/base.h"
#include "Handle/object_header.h"

namespace StarryEye {

class HandleTable: public KObjectBase
{
public:
	inline static PVOID PspCidTable;
	static void Init();

	HandleTable(std::nullptr_t);
	HandleTable(ULONG64 address);
	~HandleTable();

	// ����HandleTable��Handle���·��
	static ULONG64 DecryptHandleAddress(ULONG64 addr);

	// ��ȡһ��TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv1TableCode(PULONG64 table, CallBackT callback);
	// ��ȡ����TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv2TableCode(PULONG64 table, CallBackT callback);
	// ��ȡ����TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv3TableCode(PULONG64 table, CallBackT callback);

	// ��ȡһ��TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv1TableCode(PULONG64 table, ULONG64 index);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv2TableCode(PULONG64 table, ULONG64 index_lv2, ULONG64 index_lv1);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv3TableCode(PULONG64 table, ULONG64 index_lv3, ULONG64 index_lv2, ULONG64 index_lv1);

	// ��ȡTableCode
	ULONG64 TableCode();
	// ��ȡTableCode�ȼ�
	UCHAR TableLevel();
	// ��ȡTable��ַ(���2λ����)
	ULONG64 TableAddress();

	// ����������ȡHandle����
	ObjectHeader GetHandleObject(ULONG64 index);

	// �Զ�����TableCode�ȼ���������Handle
	template<class CallBackT>
	bool AutoForeachAllHandleObjects(CallBackT callback);

private:
	inline static ULONG64 TableCodeOffset;
};


template<class CallBackT>
inline void HandleTable::ForeachAllHandleObjectsInLv1TableCode(PULONG64 table, CallBackT callback)
{
	ObjectHeader temp = nullptr;
	for (SHORT i = 0; i < 512; i++)
	{
		temp = GetHandleObjectInLv1TableCode(table, i);
		if (temp.IsVaild())
			callback(temp);
	}
}

template<class CallBackT>
inline void HandleTable::ForeachAllHandleObjectsInLv2TableCode(PULONG64 table, CallBackT callback)
{
	for (size_t i = 0; i < 512; i++)
	{
		if (MmIsAddressValid(table + i))
			HandleTable::ForeachAllHandleObjectsInLv1TableCode((PULONG64)table[i], callback);
	}
}

template<class CallBackT>
inline void HandleTable::ForeachAllHandleObjectsInLv3TableCode(PULONG64 table, CallBackT callback)
{
	for (size_t i = 0; i < 512; i++)
	{
		if (MmIsAddressValid(table + i))
			HandleTable::ForeachAllHandleObjectsInLv2TableCode((PULONG64)table[i], callback);
	}
}

template<class CallBackT>
inline bool HandleTable::AutoForeachAllHandleObjects(CallBackT callback)
{
	switch (TableLevel())
	{
	case 0:
		HandleTable::ForeachAllHandleObjectsInLv1TableCode((PULONG64)TableAddress(), callback);
		return true;
	case 1:
		HandleTable::ForeachAllHandleObjectsInLv2TableCode((PULONG64)TableAddress(), callback);
		return true;
	case 2:
		HandleTable::ForeachAllHandleObjectsInLv3TableCode((PULONG64)TableAddress(), callback);
		return true;
	default:
		return false;
	}
}

}