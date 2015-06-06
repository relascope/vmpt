#ifndef TESTRUNNER_H
#define TESTRUNNER_H

// Qt includes
#include <QTest>
#include <QSharedPointer>
// std includes
#include <algorithm>
#include <list>
#include <iostream>

//////////////////////////////////////////////////////////////////////////
// Test Runner allows automatic execution of tests
class TestRunner
{
public:

static TestRunner& Instance()
{
   static TestRunner instance;
   return instance;
}

template <typename T>
char RegisterTest(char* name)
{
   if ( std::find_if( begin(m_tests), end(m_tests), [&name](QSharedPointer<QObject>& elem)
   { return elem->objectName() == name; }) == end(m_tests) )
    {
      QSharedPointer<QObject> test(new T());
      test->setObjectName(name);
      m_tests.push_back(test);
   }
   return char(1);
}

template <typename T>
char RegisterTest(std::string name)
{
    return RegisterTest<T>(name.c_str());
}

#define RESET_COLOR "\e[m"
#define MAKE_GREEN "\e[32m"
#define MAKE_RED "\e[31m"

int RunAll(int argc, char *argv[])
{
   int errorCode = 0;
   std::vector<const char*> failingTestClasses;

   int bugCount = 0;

   std::for_each( begin(m_tests), end(m_tests), [&] (QSharedPointer<QObject>& test)
   {
      int testResult = QTest::qExec(test.data(), argc, argv);
      errorCode |= testResult;
      std::cout << std::endl;

      bugCount++;

      if (testResult) {
          failingTestClasses.push_back(test.data()->metaObject()->className());
      }
   } );

   std::cout << "Test classes run: " << std::endl;
   foreach (auto test, m_tests) {
       std::cout << "\t" << test.data()->metaObject()->className();
   }

   if (failingTestClasses.size()) {
       std::cout << MAKE_RED << std::endl << "====FAIL====" << RESET_COLOR << std::endl;
       std::cout << "Failing classes are: " << std::endl;
   } else {
       std::cout << MAKE_GREEN << std::endl << "====PASS====" << RESET_COLOR << std::endl;
   }

   foreach (const char *failingClassName, failingTestClasses) {
       std::cout << "\t" << failingClassName << std::endl;
   }

   return errorCode;
}

private:
   std::list<QSharedPointer<QObject>> m_tests;
};

// Use this macro after your test declaration
#define DECLARE_TEST(className)\
    static char test_##className = TestRunner::Instance().RegisterTest<className>(#className);

// Use this macro to execute all tests
#define RUN_ALL_TESTS(argc, argv)\
    TestRunner::Instance().RunAll(argc, argv);

#endif // TESTRUNNER_H
