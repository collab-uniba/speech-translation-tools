#include "stdafx.h"
#include "CppUnitTest.h"
#include "NationList.cpp"
#include "NationInfo.cpp"
#include "ArchiveLog.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{

	public:


		TEST_METHOD(TEST_ARCHIVELOG_NICK)
		{
			ArchiveLog* al = new ArchiveLog("Sergio");
			Assert::AreEqual(al->getNick(), "Sergio");
		}

		TEST_METHOD(TEST_ARCHIVELOG_PATH)
		{
			ArchiveLog* al = new ArchiveLog("Sergio");
			Assert::AreEqual(al->getPath(), "logs/");

		}

		TEST_METHOD(TEST_NATION_LIST_EMPTY)
		{
			NationList* nat = new NationList();
			Assert::AreEqual(nat->GetSize(), 0);
		}

		TEST_METHOD(TEST_NATION_LIST_READ_FILE)
		{
			NationList* nat = new NationList();
			Assert::IsTrue(nat->ReadFromFile("..//conf//locales_code.txt"));
		}

		TEST_METHOD(TEST_NATION_LIST_NOT_NULL)
		{
			NationList* nat = new NationList();
			nat->ReadFromFile("..//conf//locales_code.txt");
			Assert::IsNotNull(nat->GetList());

		}

		TEST_METHOD(TEST_NATION_LIST_SEARCH_PARAMETERS_OK)
		{
			NationList* nat = new NationList();
			nat->ReadFromFile("..//conf//locales_code.txt");
			wxString* wxs = new wxString(0, "Spanish(Ar)");				
			Assert::AreEqual(nat->Search(wxs, COUNTRY), "Argentina");
		}

		TEST_METHOD(TEST_NATION_LIST_SEARCH_PARAMETERS_WRONG)
		{
			NationList* nat = new NationList();
			nat->ReadFromFile("..//conf//locales_code.txt");
			wxString* wxs = new wxString(0, "gravinese(Gr)");
			Assert::AreEqual(nat->Search(wxs, COUNTRY), "true");
		}

	};
}