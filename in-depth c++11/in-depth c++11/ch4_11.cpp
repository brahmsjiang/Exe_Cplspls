#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <assert.h>

using namespace std;

inline void* aligned_malloc(size_t size, size_t alignment)
{
	assert(!(alignment & (alignment - 1)));
	size_t offset = sizeof(void*) + (--alignment);

	char* p = static_cast<char*>(malloc(offset + size));
	if (!p) return nullptr;

	void* r = reinterpret_cast<void*>(reinterpret_cast<size_t>(p + offset) & (~alignment));
	static_cast<void**>(r)[-1] = p;
	return r;
}

inline void aligned_free(void* p)
{
	free(static_cast<void**>(p)[-1]);
}





int main(int argc, const char * argv[]) {
	



	return 0;
}
