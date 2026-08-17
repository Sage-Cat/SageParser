from conan import ConanFile
from conan.tools.build import check_min_cppstd


class SageParserPkg(ConanFile):
    name = "sageparser"
    version = "1.0.0"
    package_type = "library"
    generators = "CMakeDeps", "CMakeToolchain"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def requirements(self):
        self.requires("rapidcsv/8.84")
        self.requires("pugixml/1.14")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")

    def validate(self):
        check_min_cppstd(self, "20")
