#pragma once

#include <cstdint>

// Cut-down implementation of the smart pointer class
template <typename T>
class SmartPointer
{
	// The object that the smart pointer is holding
	T* objectRef;

	// The number of references that hold this class;
	uint32_t* references;
	
public:
	SmartPointer<T>();
	explicit SmartPointer<T>(T* obj);
	SmartPointer<T>(const SmartPointer<T>& cpy);
	SmartPointer<T>(const SmartPointer<T>&& cpy) noexcept;

	~SmartPointer<T>();

	// Getters for the data to the pointer
	uint32_t References() const;
	T* Get() const noexcept;
	void Remove();
	
	// Disallow heap allocations
	void* operator new(size_t size) = delete;
	void operator delete(void* obj) = delete;

	// Handle different operators that are overloaded
	SmartPointer<T>& operator=(const SmartPointer<T>& smart);
	SmartPointer<T>& operator=(SmartPointer<T>&& smart) noexcept;

	T* operator*() const noexcept;

private:
	static void DecrementReference(const SmartPointer& smart);
};

template <typename T>
SmartPointer<T>::SmartPointer()
	: objectRef(new T), references(new uint32_t(1))
{
}

template <typename T>
SmartPointer<T>::SmartPointer(T* obj)
	: objectRef(obj), references(new uint32_t(1))
{
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& cpy)
	: objectRef(cpy.objectRef), references(&++*cpy.references)
{
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>&& cpy) noexcept
	: objectRef(cpy.objectRef), references(cpy.references)
{
}

template <typename T>
SmartPointer<T>::~SmartPointer()
{
	// Delete held object if there are no more references for it
	if (--*references <= 0)
	{
		delete objectRef;
		delete references;
	}
}

template<typename T>
uint32_t SmartPointer<T>::References() const
{
	return *references;
}

template<typename T>
T* SmartPointer<T>::Get() const noexcept
{
	return objectRef;
}

template<typename T>
void SmartPointer<T>::Remove()
{
	DecrementReference(*this);

	objectRef = nullptr;
	references = new uint32_t(0);
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& smart)
{
	if (this != &smart)
	{
		++*smart.references;

		// Decrement the references held by this object
		DecrementReference(*this);
		
		objectRef = smart.objectRef;
		references = smart.references;
	}
	
	return *this;
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>&& smart) noexcept
{
	DecrementReference(*this);

	objectRef = new T(*smart.objectRef);
	*references = *smart.references;
	
	return *this;
}

template<typename T>
T* SmartPointer<T>::operator*() const noexcept
{
	return objectRef;
}

template<typename T>
 void SmartPointer<T>::DecrementReference(const SmartPointer<T>& smart)
{
	// Decrement the number of reference held by the class and if it
	// has nothing else holding it, delete it
	if (--*smart.references <= 0)
	{
		delete smart.objectRef;
	}
}
