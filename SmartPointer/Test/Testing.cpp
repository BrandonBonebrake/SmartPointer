#include <cassert>
#include <iostream>

#include "../src/Pointer/SmartPointer.h"
#include "../src/TestClass/TestClass.h"

int main()
{
	// Smart Pointer information
	{
		std::cout << "Smart pointer information " << std::endl;
		std::cout << "Size of SmartPointer: " << sizeof(SmartPointer<TestClass>) << " bytes" << std::endl;
	}
	
	// Test destructor in SmartPointer
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing default constructor allocation" << std::endl;

		const SmartPointer<TestClass> smart;
		const uint32_t refs = smart.References();
		assert(refs == 1);

		std::cout << "Default constructor allocation success" << std::endl;
	}

	// Testing * operator and Get()
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing * operator" << std::endl;

		auto* testClass = new TestClass;
		
		const SmartPointer<TestClass> smart(testClass);
		
		assert(testClass == *smart);
		assert(testClass == smart.Get());

		std::cout << "* operator success" << std::endl;
	}

	// Test multiple assignment
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing multi-assignment" << std::endl;

		const SmartPointer<TestClass> smart;
		const SmartPointer<TestClass> smart1(smart);

		const uint32_t refs = smart.References();
		const uint32_t refs1 = smart1.References();
		
		assert(refs == 2);
		assert(refs1 == 2);
		assert(*smart == *smart1);

		std::cout << "Multi-assignment success" << std::endl;
	}

	// Test assignment operator
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing assignment operator" << std::endl;
		
		const SmartPointer<TestClass> smart;

		TestClass* smartObjPointer = *smart;
		
		SmartPointer<TestClass> smart1;
		smart1 = smart;

		const uint32_t refs = smart.References();
		const uint32_t refs1 = smart1.References();
		
		assert(smartObjPointer == *smart1);
		assert(*smart == *smart1);
		assert(refs == refs1);
		assert(refs == 2);
		assert(refs1 == 2);

		std::cout << "Assignment operator success" << std::endl;
	}

	// Handle self assignment
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing self assignment" << std::endl;

		SmartPointer<TestClass> smart;
		const SmartPointer<TestClass> smart1(smart);

		smart = smart1;
		const uint32_t refs = smart.References();
		
		assert(refs == 2);
		
		std::cout << "Self assignment success" << std::endl;
	}

	// Handle rvalues
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing rvalues" << std::endl;

		SmartPointer<TestClass> smart;
		const SmartPointer<TestClass> smart1 = smart;
		const SmartPointer<TestClass> smart2 = SmartPointer<TestClass>();
		smart = SmartPointer<TestClass>();

		const uint32_t refs = smart.References();
		const uint32_t refs1 = smart1.References();
		const uint32_t refs2 = smart1.References();
		
		assert(*smart != *smart1);
		assert((*smart1)->id + 1 == (*smart2)->id);
		assert(refs == 1);
		assert(refs1 == 1);
		assert(refs2 == 1);
		
		std::cout << "rvalue success" << std::endl;
	}

	// Test Remove
	{
		std::cout << std::endl << std::endl;
		std::cout << "Testing Remove method" << std::endl;

		SmartPointer<TestClass> smart;
		const SmartPointer<TestClass> smart1 = smart;

		smart.Remove();

		const uint32_t refs = smart.References();
		const uint32_t refs1 = smart1.References();
		
		assert(*smart == nullptr);
		assert(refs == 0);
		assert(*smart1 != nullptr);
		assert(refs1 == 1);

		std::cout << "Remove() success" << std::endl;
	}

	std::cout << std::endl << "End of testing" << std::endl;

	return 0;
}
