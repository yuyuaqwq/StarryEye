#pragma once
#include <ntddk.h>

namespace StarryEye{

class HandleTable
{
public:
	HandleTable(ULONG64 address);
	~HandleTable();

	// ��ȡTableCode
	ULONG64 table_code();
	// ��ȡTableCode�ȼ�
	UCHAR table_level();

private:
	// ��ַ
	ULONG64 address_;
	//TODO TableCodeƫ��
	ULONG32 table_code_offset_;
};

}