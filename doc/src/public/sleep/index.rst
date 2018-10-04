AVR Power Saving Sleep Modes
============================

This section introduces the **AVR Power Saving Sleep API**. This API provides
the necessary functions and constants to configure and manage sleep states on
AVR microcontrollers. Not all AVR microcontrollers implement the same set of
functionality with respect to sleep modes. Using a feature that is not supported
by the targeted controller will result in a compile error.

Sleep Modes
-----------

.. doxygenenum:: avr::sleep::mode

Configuring Sleep Modes
-----------------------

.. doxygenfunction:: avr::sleep::select()
.. doxygenfunction:: avr::sleep::disable_brownout_detector()

Managing Sleep State
--------------------

.. doxygenfunction:: avr::sleep::enter()
.. doxygenfunction:: avr::sleep::select_enter()
.. doxygenfunction:: avr::sleep::enable()
.. doxygenfunction:: avr::sleep::select_enable()
.. doxygenfunction:: avr::sleep::sleep()
