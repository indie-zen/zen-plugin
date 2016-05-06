# Zen C++ Plugin library

This library, inspired by OSGi and Eclipse's plugin system, is an updated version from the 1.x implementation of the Zen Core Plugin library.

The purpose of this library is to facilitate the creation and utilization of C++ **Plugins** using an **Extension** and **Extension Point** paradigm.

**Plugins** are components inside of shared libraries (.DLL / .SO) files that are loaded dynamically at runtime.

**Extensions Points** are well defined interfaces that declare a common API for a particular subject area.  `I_ScriptEngine` in the Zen Script library is a good example.

**Extensions** are implementations of the interfaces.

This allows a robust API to be developed as an extension point for areas where multiple implementations exist (databases, scripting engines, game engine components, networking libraries, cloud management API's and many others), and plugins can be created for each specific implementation.

If done properly, application developers can utilize the extension points without having to decide up front which implementation / plugin to use.  Software vendors then have the added advantage of being able to support multiple plugins thus providing a more versatile product.

## Version 2.0

There are a number of breaking changes in this version, and it is still under heavy development.  None of the Zen Plugins for version 1.0 have been re-implemented to use this new version, and so if you're using the older implementation then you should probably reconsider before adopting this new implementation.

### C++ 14 and beyond

This library is now utilizing some of the new features provided by C++ 11/14 (and some experimental C++ 17 features).

### Zero Dependencies

Well, at least that's the goal.  With this version we're removing (as much as possible) all dependencies from other libraries, including boost, libxml and Zen Core 1.0.

### Zero Configuration

Configuration of plugins is now handled outside of this library; the API user is expected to provide their own implementation for configurations.  This allows us to remove the libxml dependency, and allows you as the API user to use something else (hard-coded, .ini, JSON or whatever else you desire).
