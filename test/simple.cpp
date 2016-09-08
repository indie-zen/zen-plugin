
#define BOOST_TEST_MODULE Simple_PluginTest
#include <boost/test/unit_test.hpp>

#include <Zen/Plugin/Utilities.hpp>

#include <Zen/Plugin/I_ModuleManager.hpp>
#include <Zen/Plugin/I_ModuleService.hpp>

class TestExtensionFactory
:   public Zen::Plugin::I_ExtensionFactory
{
public:
    static TestExtensionFactory& getSingleton();
    
public:
    virtual ~TestExtensionFactory()
    {
        
    }
};

static TestExtensionFactory sm_factory;
TestExtensionFactory&
TestExtensionFactory::getSingleton()
{
    return sm_factory;
}

IMPLEMENT_SINGLE_ZEN_PLUGIN(ZTestModule, ZTestPlugin)

BEGIN_ZEN_EXTENSION_MAP(ZTestPlugin)
    ZEN_EXTENSION("Zen::Tests", &TestExtensionFactory::getSingleton())
END_ZEN_EXTENSION_MAP()

BOOST_AUTO_TEST_CASE( simple_plugin_example )
{
    // Get the module 
    // getModule is a function defined indirectly by IMPLEMENT_SINGLE_ZEN_PLUGIN macro
    auto &module = getModule();

    auto moduleService = Zen::Plugin::I_ModuleManager::getSingleton().getService(
        Zen::Plugin::I_ModuleManager::STATIC);

    moduleService->install("test", module);
}
