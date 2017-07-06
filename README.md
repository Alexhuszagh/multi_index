multi_index
===========

BoostLess MultiIndex, for a C++11 compiler.

[![Build Status](https://travis-ci.org/Alexhuszagh/multi_index.svg?branch=master)](https://travis-ci.org/Alexhuszagh/multi_index)
[![Build Status](https://tea-ci.org/api/badges/Alexhuszagh/multi_index/status.svg)](https://tea-ci.org/Alexhuszagh/multi_index)
[![Build status](https://ci.appveyor.com/api/projects/status/9qe50kigu2pp1j7v?svg=true)](https://ci.appveyor.com/project/Alexhuszagh/multi-index)

**Table of Contents**

- [Introduction](#introduction)
- [Changes](#changes)
- [Documentation](#documentation)
- [Platforms](#platforms)
- [Contributors](#contributors)
- [License](#license)

## Introduction

Boost, although a great library, aims to maintain compatibility with as many compilers as possible, with workarounds for the buggiest of systems. These abstractions have a cost, and now that C++11 compilers are available for every major system, most of the Boost machinery is now more trouble than it's worth.

Boost.MultiIndex is an excellent library, with use for modern code, however, it depends on archaic machinery. Removing this machinery to use variadic templates removes ~140,000 lines of code, and dramatically improves compilation time and memory, simplifying its integration in a modern development environment.

## Changes

This fork aims to maintain as much compatibility with the original implementation as possible. Only a few, significant changes were made:

 - Removing the Boost namespace to avoid inclusion/compatibility issues with other Boost libraries.
 - Removing Boost.MPL to use [Brigand](https://github.com/edouarda/brigand) and std::tuple.

## Documentation

The documentation, with the exception of the Boost namespace, should be identical to [Boost's reference](http://www.boost.org/doc/libs/1_62_0/libs/multi_index/doc/index.html).

## Platforms

MultiIndex is continually built with the following compiler and compiler versions:

- Clang 3.8+
- GCC 5.3+
- MinGW 5.3.0 (MXE, MinGW, and MSYS2)
- Visual Studio 14 2017

Visual Studio 2015 has various bugs with nested templates, and is therefore not supported. These bugs are fixed in Visual Studio 2017.

## Contributors

- Alex Huszagh

MultiIndex is forked from Boost's implementation, and shares nearly all of it's code from it. Joaquin M Lopez Munoz is the author of the Boost implementation, and therefore of the nearly all of the source code, although he is unaffilitate with the project.

## License

Boost, see [license](LICENSE.md).
