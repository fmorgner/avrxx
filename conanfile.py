# pylint: disable=missing-docstring,not-callable
from conans import ConanFile


class AVRXXConan(ConanFile):
    name = 'AVR++'
    description = (
        'AVR++ is a C++17 interface to Atmel AVR 8-bit microcontrollers. The '
        'goal of AVR++ is to provide a safe, clean, and zero-overhead '
        'interface to work with with AVR microcontrollers while still '
        'allowing for great flexibility and customizability.'
    )
    version = '1.0.0'
    settings = (
        'os',
    )
    url = 'https://github.com/fmorgner/avrxx.git'
    author = 'Felix Morgner (felix.morgner@gmail.com)'
    license = 'BSD 3-clause'
    exports_sources = (
        'include/*',
    )

    def package(self):
        self.copy('*.hpp', src='include', dst='include')

    def package_info(self):
        self.cpp_info.includedirs = ['include']
