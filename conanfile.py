from conan import ConanFile


class SageParserPkg(ConanFile):
    name = "sage_docs"
    version = "1.0.0"
    generators = "CMakeDeps", "CMakeToolchain"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def requirements(self):
        self.requires("rapidcsv/[8.80]")
        self.requires("pugixml/[1.14]")
        self.requires("gtest/[1.14.0]")
