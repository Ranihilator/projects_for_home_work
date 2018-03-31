#pragma once

#include <cstring>
#include <memory>

namespace ALLOCATOR
{

/*!
@brief Класс менеджер памяти
@detailed Выделяет память для хранения блоков (блок линейный массив из байтов данных)
 */
template <class T>
class PointerManager
{
public:

	/*!
	@brief конструктор по умолчанию
	@detailed выделяет память для блока
	@param p_size - кол-во блоков
	 */
	PointerManager(std::size_t p_size = 10);

	/*!
	@brief конструктор копирования
	@detailed создает новый блок
	 */
	PointerManager(const PointerManager& other);

	/*!
	@brief деструктор
	@detailed уничтожает память блоков
	 */
	~PointerManager();

	/*!
	@brief копирования данных в первый свободный блок
	 */
	void add(T val);

	/*!
	@brief получить указатель на последний добавленных блок
	 */
	T* data();

	std::size_t length() {return pos;}

	/*!
	@brief получить указатель на указанный блок
	 */
	const T* data(std::size_t n) const;

	/*!
	@brief оператор копирования
	@detailed освобождает память и создает новый блок
	 */
	PointerManager& operator=(const PointerManager &other)
	{
		if (size != 0 && memory != nullptr)
		{
			for (decltype(size) i = 0; i < size; ++i)
			{
				((T*) & memory[i])->~T();
			}
			std::free(memory);
		}

		size = other.size;

		if (size != 0 && other.memory != nullptr)
		{
			memory = (T*) std::malloc(size * sizeof (T));
			for (decltype(size) i = 0; i < size; ++i)
			{
				new (&memory[i]) T();
			}

			std::memcpy(memory, other.memory, size * sizeof (T));
		}

		return *this;
	}

private:
	T* memory = nullptr;
	std::size_t pos = 0;
	std::size_t size = 0;

	const uint8_t rising_count = 10;
};

template <class T>
PointerManager<T>::PointerManager(std::size_t p_size) : size(p_size)
{
	if (size < 1)
		size = rising_count;

	memory = (T*) std::malloc(p_size * sizeof (T));
	for (decltype(size) i = 0; i < size; ++i)
	{
		new (&memory[i]) T();
	}
}

template <class T>
PointerManager<T>::PointerManager(const PointerManager& other) : size(other.size)
{
	if (size != 0 && other.memory != nullptr)
	{
		memory = (T*) std::malloc(size * sizeof (T));
		for (decltype(size) i = 0; i < size; ++i)
		{
			new (&memory[i]) T();
		}

		std::memcpy(memory, other.memory, size * sizeof (T));
	}
	else
	{
		size = 0;
	}
}

template <class T>
PointerManager<T>::~PointerManager()
{
	for (decltype(size) i = 0; i < size; ++i)
	{
		((T*) & memory[i])->~T();
	}
	std::free(memory);
}

template <class T>
void PointerManager<T>::add(T val)
{
	if (pos > size - 1)
	{
		std::size_t new_size = size*rising_count;
		T* new_mem = (T*) std::malloc(new_size * sizeof (T));

		for (decltype(size) i = 0; i < new_size; ++i)
		{
			new (&new_mem[i]) T();
		}

		std::memcpy(new_mem, memory, size * sizeof (T));

		for (decltype(size) i = 0; i < size; ++i)
		{
			((T*) & memory[i])->~T();
		}
		std::free(memory);

		memory = new_mem;
		size = new_size;
	}

	memory[pos++] = val;
}

template <class T>
T* PointerManager<T>::data()
{
	if (pos == 0) return nullptr;
	auto mem = memory;
	mem += pos - 1;
	return mem;
}

template <class T>
const T* PointerManager<T>::data(std::size_t n) const
{
	if (pos == 0) return nullptr;
	if (n > pos - 1) return nullptr;
	auto mem = memory;
	mem += n;
	return mem;
}

}
