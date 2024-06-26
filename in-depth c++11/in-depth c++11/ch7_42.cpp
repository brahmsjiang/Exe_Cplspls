#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>

using namespace std;


inline void* aligned_malloc(size_t size, size_t alignment)
{
	assert(!(alignment & (alignment - 1)));
	size_t offset = sizeof(void*) + (--alignment);
	cout << "sizeof(void*): " << sizeof(void*) << endl;

	char* reqBlockAddr = static_cast<char*>(malloc(offset + size));
	if (!reqBlockAddr) return nullptr;

	void* alignedAddr = reinterpret_cast<void*>(reinterpret_cast<size_t>(reqBlockAddr + offset) & (~alignment));
	cout << "alignedAddr: " << alignedAddr << endl;
	auto reqBlockAddrAddr = (void**)((size_t)alignedAddr - sizeof(void*));
	cout << "reqBlockAddrAddr: " << reqBlockAddrAddr << endl;

	*reqBlockAddrAddr = reqBlockAddr;
	cout << "reqBlockAddr: " << *reqBlockAddrAddr << endl;

	auto ori = static_cast<void**>(alignedAddr)[-1]; //ori == reqBlockAddr
	cout << "ori: " << ori << endl;

	//alignedAddr - reqBlockAddr = 4byte (32bit)
	//alignedAddr - reqBlockAddrAddr = 1byte (8bit)
	return alignedAddr;
}

inline void aligned_free(void* p)
{
	free(static_cast<void**>(p)[-1]);
}

int main(int argc, const char * argv[]) {

	aligned_malloc(100, 32);
	return 0;
}
