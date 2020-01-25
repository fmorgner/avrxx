import re

from conans import ConanFile, CMake
from conans.tools import load


def get_version():
    try:
        content = load("CMakeLists.txt")
        version = re.search("project\(\"avrxx\"\s+VERSION \"(.*)\"", content).group(1)
        return version.strip()
    except:
        return None


class AVRXXConan(ConanFile):
    name = 'avrxx'
    scm = {
        'type': 'git',
        'url': 'https://github.com/fmorgner/avrxx.git',
        'revision': 'auto'
    }
    settings = {
        'arch': 'avr',
        'compiler': 'gcc',
        'os': None
    }
    version = get_version()
    license = 'BSD 3-clause'
    url = 'https://github.com/fmorgner/avrxx'
    description = (
        'AVR++ is a C++17 interface to Atmel AVR 8-bit microcontrollers.'
        'The goal of AVR++ is to provide a safe, clean, and zero-cost interface to AVR MCUs.'
        'At the same time, AVR++ provides great flexibility and customizability.'
    )
    author = 'Felix Morgner (felix.morgner@gmail.com)'
    generators = 'cmake'
    default_user = '_'
    default_channel = '_'

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()