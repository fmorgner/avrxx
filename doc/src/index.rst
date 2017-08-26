#####
AVR++
#####

**AVR++** is a C++17 interface to Atmel AVR 8-bit microcontrollers. The goal of
AVR++ is to provide a safe, clean, and zero-overhead interface to work with with
AVR microcontrollers while still allowing for great flexibility and
customizability.

Public API
==========

The AVR++ public API provides access to all features of the microcontroller. It
abstracts away tedious bit manipulations an presents a type-safe interface that
catches a wide variety of programming errors during compilation. The underlying
implementation has been designed to provide zero- or near-zero overhead.

This part of the documentation describes how to use AVR++ to program
microcontrollers in a safe and efficient manner.

.. toctree::
  :maxdepth: 2

  public/index

Library Internals
=================

The AVR++ internals are extensively documented to make it easy to extend and
improve. All subsystems have been designed to provide clean and stable
interfaces, to make it easy to build derivative libraries or implement custom
features as standalone libraries.

This part of the documentation describes how to work with the underlying
implementation of AVR++.

.. toctree::
  :maxdepth: 2

  internal/index
