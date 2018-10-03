#include "MemoryAddressNotAllignedException.h"

MemoryAddressNotAllignedException::MemoryAddressNotAllignedException(
		MemoryAddress address)
		: runtime_error("Memory Address not alligned"), address(address) {}

MemoryAddress MemoryAddressNotAllignedException::getAddress() {
	return address;
}
