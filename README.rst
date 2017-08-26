#####
AVR++
#####

.. image:: https://api.bintray.com/packages/fmorgner/conan-fmorgner/AVR%2B%2B%3Afmorgner/images/download.svg
   :target: https://bintray.com/fmorgner/conan-fmorgner/AVR%2B%2B%3Afmorgner/_latestVersion)
   :alt: Conan Package

.. image:: https://readthedocs.org/projects/avrxx/badge/?version=latest
   :target: http://avrxx.readthedocs.io/en/latest/?badge=latest
   :alt: Documentation Status

**AVR++** is a C++17 interface to Atmel AVR 8-bit microcontrollers. The goal of
AVR++ is to provide a safe, clean, and zero-overhead interface to work with with
AVR microcontrollers while still allowing for great flexibility and
customizability.

*****
Setup
*****

This chapter describes how to setup AVR++ for use in modern AVR projects. It
explains how to install the dependencies of AVR++ on different operating systems
and the requirement for building the library documentation

Library Dependencies
====================

AVR++ is a header-only library with minimal dependencies on external libraries.
It is designed to be as self-contained as possible.

+--------------+---------+---------------------------------------------+
| Dependency   | Version | Required By/For                             |
+==============+=========+=============================================+
| AVR GCC      | >=7.1   | Compilation                                 |
+--------------+---------+---------------------------------------------+
| AVR libc     | >=2.0   | Current Implementation                      |
+--------------+---------+---------------------------------------------+
| AVR binutils | >=2.29  | Firmware hex-files / Disassembly / Analysis |
+--------------+---------+---------------------------------------------+

Installation on Arch Linux
--------------------------

**Arch Linux** provides all of the requirements in the default *community*
package repository. You can install all of them using the following command:

.. code-block:: bash

  $ sudo pacman -S --needed avr-gcc avr-libc

Please note that **AVR binutils** will be installed as a dependency of the
**avr-gcc** package.

Using the Library
=================

Since AVR++ is a header-only library, you can simply copy the contents of the
`include` folder into your own project and start using it. Alternatively, AVR++
is also availabe as a `Conan Package
<https://bintray.com/fmorgner/conan-fmorgner/AVR%2B%2B%3Afmorgner>`_.

Building the Documentation
==========================

AVR++ features an extensive documentation based on `Sphinx
<https://www.sphinx-doc.org>`_. You can find the documentation online on `Read
the Docs <http://avrxx.readthedocs.io/>`_ or build it yourself.

Build Requirements
------------------

AVR++ provides a **pip** requirements file at `doc/requirements.txt`. You can
use this file to install **Sphinx**, **Breathe**, and the **Sphix Read the Docs
theme**. In addition to a basic Sphinx setup, you will also need a reasonably
modern version of `Doxygen <http://www.stack.nl/~dimitri/doxygen/>`_. A clean
way to manage the Python dependencies is to use **virtualenv** or
**virtualenvwrapper** to create an isolated Python environment.

To install the required Python packages, simply run the following command on
Linux from the source root of the project:

.. code-block:: bash

  $ pip install -r doc/requirements.txt

After successfully installing the require Python packages, you can build the
documentation using either the following command from the source root:

.. code-block:: bash

  $ make doc

or if you want to have more control over the build product, using the following
command from the `doc` directory:

.. code-block:: bash

  $ make <output-format>

where you replace `<output-format>` by your desired output format, for example
`man`, `epub`, `pdf`, or `html`.
