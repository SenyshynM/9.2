#include "pch.h"
#include "CppUnitTest.h"
#include "../9.2.1/9.2.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student* N = new Student[1];
			N->mat = 2;
			N->fiz = 4;
			N->spec = KN;
			N->prog = 4;
			double av = average(N[0]);
			Assert::AreEqual(av, 3.333, 0.001);
		}
	};
}
