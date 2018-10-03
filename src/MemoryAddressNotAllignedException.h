#ifndef __MEMORYADDRESSNOTALLIGNEDEXCEPTION_H__
#define __MEMORYADDRESSNOTALLIGNEDEXCEPTION_H__

#include <stdexcept>
#include "MemoryAddress.h"

class MemoryAddressNotAllignedException : public std::runtime_error {
private:
	MemoryAddress address;
public:
	explicit MemoryAddressNotAllignedException(MemoryAddress address);

	MemoryAddress getAddress();
};


#endif //__MEMORYADDRESSNOTALLIGNEDEXCEPTION_H__
