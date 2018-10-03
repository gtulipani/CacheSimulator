#ifndef __MEMORY_ADDRESS_H__
#define __MEMORY_ADDRESS_H__

#include <string>

class MemoryAddress {
private:
	unsigned long complete_address;
	int offset_bits;
	int index_bits;
	bool valid;

public:
	MemoryAddress();

	explicit MemoryAddress(unsigned long hex_address, int offset_bits,
			int index_bits, bool valid);

	explicit MemoryAddress(std::string hex_address, int offset_bits,
			int index_bits);

	MemoryAddress(const MemoryAddress &other);

	MemoryAddress(MemoryAddress &&other) noexcept;

	// Overloading the assignment by copy
	MemoryAddress &operator=(const MemoryAddress &other);

	// Overloading the assignment by movement
	MemoryAddress &operator=(MemoryAddress &&other) noexcept;

	// Overloading the unsigned long casting to take the complete
	// address as primitive
	explicit operator unsigned long() const;

	// Overloading the std::string casting to take the complete
	// address as char sequence
	explicit operator std::string() const;

	// Overloading equals operator to take the complete_address
	// without the offset_bits
	bool operator==(const MemoryAddress &other) const;

	// Overloading the << operator but we make it friend to be
	// callable from outside
	friend std::ostream &operator<<(std::ostream &out, const MemoryAddress &m);

	bool isAlligned();

	unsigned long getIndex() const;
};


#endif //__MEMORY_ADDRESS_H__
