#include <Zen/Plugin/I_ExtensionRegistry.hpp>

#define BOOST_TEST_MODULE Simple_PluginTest
#include <boost/test/unit_test.hpp>

#include <Zen/Plugin/Utilities.hpp>

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
    
}
