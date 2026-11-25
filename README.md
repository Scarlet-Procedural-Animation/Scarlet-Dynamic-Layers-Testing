# Scarlet-Dynamic-Layers-Testing
Unit tests for the Scarlet-Dynamic-Layers library

---

### File Structure
* **Tests** - contains c++ unit test files;
* **Scarlet-Dynamic-Layers** - submodule containing the library that is tested;
* **doctest** - testing framework of choice.

### Build Instructions

**1. Configure**
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
**2. Build**
```sh
cmake --build build --config Release -j
```
**3.1 Launch Windows**
```sh
build\Release\dl_tests.exe
```