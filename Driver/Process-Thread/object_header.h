#pragma once
#include <ntddk.h>

namespace StarryEye {

class ObjectHeader
{
public:
	ObjectHeader(ULONG64 address);
	~ObjectHeader();

private:
	// ��ַ
	ULONG64 address_;
};

}