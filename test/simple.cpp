
#define BOOST_TEST_MODULE Simple_PluginTest
#include <boost/test/unit_test.hpp>

#include <Zen/Plugin/Utilities.hpp>

#include <Zen/Plugin/I_ModuleManager.hpp>
#include <Zen/Plugin/I_ModuleService.hpp>

#include <Zen/Plugin/extension_point.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
/// I_TestExtension interface
// TODO Should this implement I_Extension or I_Service or something?  Not sure 
// if that's actually required since neither of those interfaces really declare 
// anything.
class I_TestExtension
{
public:
    // This extension / service is indexed by (is this necessary?)
    typedef std::string         index_type;
    
    virtual void test() = 0;

protected:
    I_TestExtension() = default;
    virtual ~I_TestExtension() = default;
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class I_TestExtensionFactory
:   public Zen::Plugin::I_ExtensionFactory
{
public:
    typedef std::shared_ptr<I_TestExtension> pTestExtension_type;
    
public:
    virtual pTestExtension_type create() = 0;
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class TestExtensionPoint
:   public Zen::Plugin::extension_point<I_TestExtension, I_TestExtensionFactory>
{
public:
    TestExtensionPoint(const char* _namespace, const char* _extensionPointName)
    :   extension_point(_namespace, _extensionPointName)
    {
    }

    static TestExtensionPoint& getSingleton()
    {
        static TestExtensionPoint extensionPoint("Zen::Tests", "TestExtensionPoint");
        return extensionPoint;
    }

    TestExtensionPoint(const TestExtensionPoint&) = delete;
    TestExtensionPoint& operator=(const TestExtensionPoint&) = delete;
    
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// TestExtension class
// implements I_TestExtension
class TestExtension
: public I_TestExtension
{
public:
    virtual void test() 
    {
        std::cout << "Hello, from TestExtension!" << std::endl;
    }
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class TestExtensionFactory
:   public I_TestExtensionFactory
{
public:
    virtual pTestExtension_type create()
    {
        std::cout << "TestExtensionFactory::create" << std::endl;
        return pTestExtension_type(new TestExtension);
    }

public:
    static TestExtensionFactory& getSingleton();
    
public:
    virtual ~TestExtensionFactory() = default;
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static TestExtensionFactory sm_factory;

TestExtensionFactory&
TestExtensionFactory::getSingleton()
{
    return sm_factory;
}
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

IMPLEMENT_SINGLE_ZEN_PLUGIN(ZTestModule, ZTestPlugin)

const std::string moduleName("test");

BEGIN_ZEN_EXTENSION_MAP(ZTestPlugin)
    ZEN_EXTENSION("Zen::Tests::TestExtensionPoint", &TestExtensionFactory::getSingleton())
END_ZEN_EXTENSION_MAP()

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
BOOST_AUTO_TEST_CASE(simple_plugin_example)
{
    try 
    {
        // Get the module 
        // getModule is a function defined indirectly by IMPLEMENT_SINGLE_ZEN_PLUGIN macro
        auto& module = getModule();

        auto moduleService = Zen::Plugin::I_ModuleManager::getSingleton().getService(
            Zen::Plugin::I_ModuleManager::STATIC);
    
        moduleService->install(moduleName, module);

        auto& extensionPoint = TestExtensionPoint::getSingleton();
        auto extension = extensionPoint.create("test");
        // extension->test();
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown exception thrown" << std::endl;
    }
}
