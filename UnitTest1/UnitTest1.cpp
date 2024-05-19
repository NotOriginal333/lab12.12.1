#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.12.1/FileName.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestSearchProductByName)
        {
            Price* priceList = nullptr;
            addPrice(priceList, "Product1", "Shop1", 10.0);
            addPrice(priceList, "Product2", "Shop2", 20.0);
            addPrice(priceList, "Product3", "Shop3", 30.0);

            stringstream buffer;
            streambuf* oldOut = cout.rdbuf(buffer.rdbuf());
            searchProductByName(priceList, "Product2");
            string output = buffer.str();
            cout.rdbuf(oldOut);

            Assert::IsTrue(output.find("Product2") != string::npos, L"Product2 should be found in the list.");

            deletePriceList(priceList);
        }
    };
}
