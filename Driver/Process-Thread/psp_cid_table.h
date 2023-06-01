#pragma once
#include "object_header.h"
#include "handle_table.h"
#include "ynstd.hpp"
#include <algorithm>


namespace StarryEye{

class PspCidTable
{
public:
	PspCidTable() = delete;

	// PspCidTable��ַ
	static ULONG64 Address;

	// ����HandleTable��Handle���·��
	static ULONG64 DecryptHandleAddress(ULONG64 addr);
	// ����������ȡHandle����
	static ObjectHeader GetHandleObject(ULONG64 index);

	// ��ȡһ��TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv1TableCode(PULONG64 table, CallBackT callback)
	{
		ObjectHeader temp = nullptr;
		for (size_t i = 0; i < 512; i++)
		{
			temp = GetHandleObjectInLv1TableCode(table, i);
			if (temp)
				callback(temp);
		}
	}
	// ��ȡ����TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv2TableCode(PULONG64 table, CallBackT callback)
	{
		for (size_t i = 0; i < 512; i++)
		{
			if (MmIsAddressValid(table + i))
				ForeachAllHandleObjectsInLv1TableCode((PULONG64)table[i], callback);
		}
	}
	// ��ȡ����TableCode������Handle����
	template<class CallBackT>
	static void ForeachAllHandleObjectsInLv3TableCode(PULONG64 table, CallBackT callback)
	{
		for (size_t i = 0; i < 512; i++)
		{
			if (MmIsAddressValid(table + i))
				ForeachAllHandleObjectsInLv2TableCode((PULONG64)table[i], callback);
		}
	}

	// ��ȡһ��TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv1TableCode(PULONG64 table, USHORT index);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv2TableCode(PULONG64 table, USHORT index_lv2, USHORT index_lv1);
	// ��ȡ����TableCode��ָ��������Handle����
	static ObjectHeader GetHandleObjectInLv2TableCode(PULONG64 table, USHORT index_lv3, USHORT index_lv2, USHORT index_lv1);

	// ���ݾ�̬PspCidTable��ַ, �Զ���������Handle, �����ֽ��̺��߳�
	template<class ProcHandleCallBack, class ThdHandleCallBack>
	static void AutoForeachAllHandleObjects(ProcHandleCallBack proc_handle_callback, ThdHandleCallBack thd_handle_callback)
	{
		auto foreach_all_handle = [&](ObjectHeader& obj)
		{
			// TODO
		};
		HandleTable pspcidtable{ Address };
		PULONG64 table = (PULONG64)pspcidtable.TableAddress();
		switch (pspcidtable.TableLevel())
		{
		case 0:
			ForeachAllHandleObjectsInLv1TableCode(table, foreach_all_handle);
			break;
		case 1:
			ForeachAllHandleObjectsInLv2TableCode(table, foreach_all_handle);
			break;
		case 2:
			ForeachAllHandleObjectsInLv3TableCode(table, foreach_all_handle);
			break;
		default:
			break;
		}
	}
};

}
