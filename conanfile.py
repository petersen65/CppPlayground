from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout


class ConanRecipe(ConanFile):
    settings = "os", "arch", "compiler", "build_type"
    default_options = {"gtest/*:build_gmock": True}

    def requirements(self):
        self.requires("gtest/1.16.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        toolchain = CMakeToolchain(self)
        toolchain.blocks["cppstd"].values = {"cppstd": "26", "cppstd_extensions": "OFF"}
        toolchain.cache_variables["BUILD_TESTING"] = "ON"
        toolchain.generate()