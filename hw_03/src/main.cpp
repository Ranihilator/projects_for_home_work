#include "main.h"

int main()
{
	MAP<uint64_t, uint64_t>()();
	MAP<uint64_t, uint64_t, 1, 10>()();

	CUSTOM_CONTAINER<uint64_t>()();
	CUSTOM_CONTAINER<uint64_t, 1, 10>()();
	return 0;
}