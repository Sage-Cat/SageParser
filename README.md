# SageDocs

Applicaition for parsing some spesific CSV, XML, XLSX documents

```
conan install . --output-folder=build --build=missing
cd build
conanbuild.bat
cmake .. --preset conan-debug
cmake --build .
conanrun.bat
```
