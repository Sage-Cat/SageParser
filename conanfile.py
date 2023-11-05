from conan import ConanFile
from conan.tools.files import copy


class SageDocsPkg(ConanFile):
    name = "docs_processr"
    version = "1.0.0"
    generators = "CMakeDeps", "CMakeToolchain", "VirtualBuildEnv", "VirtualRunEnv"

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def requirements(self):
        self.requires("csvmonkey/[0.0.5]")
        self.requires("pugixml/[1.14]")
        self.requires("xlnt/[1.5.0]")
        self.requires("gtest/[1.14.0]")
