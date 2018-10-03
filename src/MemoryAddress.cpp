#include <iomanip>
#include <sstream>
#include <string>
#include "MemoryAddress.h"
#include "TransformationUtils.h"

MemoryAddress::MemoryAddress() :
			complete_address(0),
			offset_bits(0),
			index_bits(0),
			valid(false) {}

MemoryAddress::MemoryAddress(unsigned long complete_address, int offset_bits,
		int index_bits, bool valid) :
			complete_address(complete_address),
			offset_bits(offset_bits),
			index_bits(index_bits),
			valid(valid) {}

MemoryAddress::MemoryAddress(std::string hex_address,
		int offset_bits, int index_bits) : MemoryAddress(
			hex_to_ulong(std::move(hex_address)),
			offset_bits,
			index_bits,
			true) {}

MemoryAddress::MemoryAddress(const MemoryAddress &other) : MemoryAddress(
			other.complete_address,
			other.offset_bits,
			other.index_bits,
			other.valid) {}

MemoryAddress::MemoryAddress(MemoryAddress &&other) noexcept : MemoryAddress(
			other.complete_address,
			other.offset_bits,
			other.index_bits,
			other.valid) {
	other.complete_address = 0UL;
	other.offset_bits = 0;
	other.index_bits = 0;
	other.valid = false;
}

MemoryAddress &MemoryAddress::operator=(const MemoryAddress &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->complete_address = other.complete_address;
	this->offset_bits = other.offset_bits;
	this->index_bits = other.index_bits;
	this->valid = other.valid;

	return *this;
}

MemoryAddress &MemoryAddress::operator=(MemoryAddress &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values
	this->complete_address = other.complete_address;
	this->offset_bits = other.offset_bits;
	this->index_bits = other.index_bits;
	this->valid = other.valid;

	other.complete_address = 0UL;
	other.offset_bits = 0;
	other.index_bits = 0;
	other.valid = false;

	return *this;
}

MemoryAddress::operator unsigned long() const {
	return complete_address;
}

MemoryAddress::operator std::string() const {
	std::stringstream stream;
	stream << "0x"
		   << std::setfill('0') << std::setw(8)
		   << std::hex << complete_address;
	return stream.str();
}

bool MemoryAddress::operator==(const MemoryAddress &other) const {
	return valid && other.valid &&
		   ((complete_address >> offset_bits >> index_bits) ==
			((unsigned long) other >> offset_bits >> index_bits));
}

bool MemoryAddress::isAlligned() {
	return (complete_address % 4 == 0);
}

unsigned long MemoryAddress::getIndex() const {
	return (complete_address >> offset_bits) & ((1 << index_bits) - 1);
}
