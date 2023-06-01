#pragma once
#include <ntifs.h>

namespace StarryEye{

class HandleTable
{
public:
	HandleTable(std::nullptr_t);
	HandleTable(ULONG64 address);
	~HandleTable();

	// ��ȡTableCode
	ULONG64 TableCode();
	// ��ȡTableCode�ȼ�
	UCHAR TableLevel();
	// ��ȡTable��ַ(���2λ����)
	ULONG64 TableAddress();

	bool IsVaild();

	operator bool();

private:
	// ��ַ
	ULONG64 address_;
	//TODO TableCodeƫ��
	UINT16 table_code_offset_;
};

}