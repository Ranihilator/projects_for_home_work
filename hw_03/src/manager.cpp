#include "manager.h"
#include <system_error>

namespace ALLOCATOR
{

ArenaMemoryManager::ArenaMemoryManager(std::size_t asize, std::size_t adata) : m_chunks(asize), data_size(adata)
{
}

ArenaMemoryManager::ArenaMemoryManager(const ArenaMemoryManager &other) : m_chunks(PointerManager<chunk_t>(other.m_chunks.size)), data_size(other.data_size)
{
	for (decltype(other.m_chunks.pos) i = 0; i < other.m_chunks.pos; ++i)
	{
		chunk_t data;
		data = std::make_pair(std::get<0>(*other.m_chunks.data(i)), (uint8_t*) std::malloc(std::get<0>(*other.m_chunks.data(i))));

		std::memcpy(std::get<1>(data), std::get<1>(*other.m_chunks.data(i)), std::get<0>(*other.m_chunks.data(i)));

		m_chunks.add(data);
	}
}

ArenaMemoryManager::~ArenaMemoryManager()
{
	for (decltype(m_chunks.pos) i = 0; i < m_chunks.pos; ++i)
	{
		std::free(std::get<1>(*m_chunks.data(i)));
	}
}

ArenaMemoryManager& ArenaMemoryManager::operator=(const ArenaMemoryManager &other)
{
	for (decltype(m_chunks.pos) i = 0; i < m_chunks.pos; ++i)
	{
		std::free(std::get<1>(*m_chunks.data(i)));
	}
	m_chunks.pos = 0;

	if (m_chunks.size < other.m_chunks.size)
	{
		m_chunks = PointerManager<chunk_t>(other.m_chunks.size);
	}

	for (decltype(m_chunks.pos) i = 0; i < m_chunks.pos; ++i)
	{
		chunk_t data;
		data = std::make_pair(std::get<0>(*other.m_chunks.data(i)), (uint8_t*) std::malloc(std::get<0>(*other.m_chunks.data(i))));

		std::memcpy(std::get<1>(data), std::get<1>(*other.m_chunks.data(i)), std::get<0>(*other.m_chunks.data(i)));

		m_chunks.add(data);
	}

	return *this;
}

void* ArenaMemoryManager::allocate(std::size_t n)
{
	if (n > m_available)
	{
		chunk_t data = std::make_pair(n * data_size, (uint8_t*) std::malloc(n * data_size));
		
		if (!data.second)
			std::bad_alloc();
		
		m_available = std::get<0>(data);

		m_chunks.add(data);
		m_memory = std::get<1>(*m_chunks.data());
	}

	auto mem = m_memory;
	m_available -= n;
	m_memory += n;
	return mem;
}

void ArenaMemoryManager::deallocate(void* p, std::size_t n)
{
	auto mem = (uint8_t*) p;

	if (mem + n == m_memory)
	{
		m_memory = mem;
		m_available += n;
	}
	else
	{
		std::runtime_error{"deallocate error"};
	}
}

}
