#!/usr/bin/python
# -*- Mode: Python; py-indent-offset: 4 -*-
#
# Copyright (C) 2005,2007  Ray Burr
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# 

# DISCLAIMER: I don't pretend to be a math wizard.  I don't have a
# deep understanding of all of the theory behind CRCs.  Part of the
# reason I originally wrote this is to help understand and verify CRC
# algorithms in practice.  It is likely that some of my terminology is
# inaccurate.

# Requires at least Python 2.4; tested with 2.4 and 2.5.

"""
This module can model common CRC algorithms given the set of defining
parameters.  This is intended to be easy to use for experimentation
rather than optimized for speed.  It is slow even for a native Python
CRC implementation.

Several common CRC algorithms are predefined in this module.

:authors: Ray Burr
:license: MIT License
:contact: http://www.nightmare.com/~ryb/

Examples
========

  >>> '%X' % CRC32.calcString('123456789')
  'CBF43926'

This test function runs all of the defined algorithms on the test
input string '123456789':

  >>> _printResults()
  CRC-5-USB: 19
  CRC-8-SMBUS: F4
  CRC-15: 059E
  CRC-16: BB3D
  CRC-16-USB: B4C8
  CRC-CCITT: 29B1
  CRC-HDLC: 906E
  CRC-24: 21CF02
  CRC-32: CBF43926
  CRC-32C: E3069283
  CRC-64: 46A5A9388A5BEFFE
  CRC-256: 79B96BDC0C519B239BE759EC0688C86FD25A3F4DF1E7F054AD1F923D0739DAC8

Calculating in parts:

  >>> value = CRC32.calcString('1234')
  >>> '%X' % CRC32.calcString('56789', value)
  'CBF43926'

Or, done a different way:

  >>> crc = CrcRegister(CRC32)
  >>> crc.takeString('1234')
  >>> crc.takeString('56789')
  >>> '%X' % crc.getFinalValue()
  'CBF43926'

Inversion of a CRC function:

  >>> CRC_CCITT.reverse().reflect().calcWord(54321, 16, 0)
  1648
  >>> CRC_CCITT.calcWord(_, 16, 0)
  54321

A 15-bit CRC is used in CAN protocols.  The following sample CAN frame
(in binary here) is converted to hexadecimal for the calcWord call.
The bits after the 15-bit CRC are not included in the CRC::

  0 11101000001 0 0 0 0001 00010010 011000010111011 1 1 1 1111111

This sample CAN frame was found in this paper:
<http://www.anthony-marino.com/documents/HDL_implementation_CAN.pdf>

  >>> '%X' % CRC15.calcWord(0x3A08112, 27)
  '30BB'

If the CRC is included, the remainder should always be zero:

  >>> print CRC15.calcWord(0x1D0408930BB, 42)
  0

A 5-bit CRC is used some kinds of USB packets.  Here is a sample
start-of-frame packet:

  10100101 01100111000 01111

(found at <http://www.nital.com/corporate/usb2snooper.html>)

The first field is the PID (not included in the CRC), the next 11-bit
field is the frame number (0xE6, LSb-first order), and the final five
bits are the CRC (0x1E, LSb-first order).

  >>> '%X' % CRC5_USB.calcWord(0xE6, 11)
  '1E'
"""

# <http://docutils.sourceforge.net/docs/ref/rst/restructuredtext.html>
__docformat__ = "restructuredtext en"

__version__ = "20070611"

class CrcAlgorithm:
    """
    Represents the parameters of a CRC algorithm.
    """

    # FIXME: Instances are supposed to be immutable, but attributes are
    # writable.

    def __init__(self, width, polynomial, name=None, seed=0,
                 lsbFirst=False, lsbFirstData=None, xorMask=0):
        """
        :param width:

          The number of bits in the CRC register, or equivalently, the
          degree of the polynomial.

        :type width:

          an integer

        :param polynomial:

          The generator polynomial as a sequence of exponents

        :type polynomial:

          sequence or integer

        :param name:

          A name identifying algorithm.

        :type name:

          *str*

        :param seed:

          The initial value to load into the register.  (This is the
          value without *xorMask* applied.)

        :type seed:

          an integer

        :param lsbFirst:

          If ``true``, the register shifts toward the
          least-significant bit (sometimes called the *reflected* or
          *reversed* algorithim).  Otherwise, the register shifts
          toward the most-significant bit.

        :type lsbFirst:

          *bool*

        :param lsbFirstData:

          If ``true``, input data is taken least-significant bit
          first.  Otherwise, data is taken most-significant bit first.
          If ``None`` or not given, the value of *lsbFirst* is used.

        :type lsbFirstData:

          *bool*

        :param xorMask:

          An integer mask indicating which bits should be inverted
          when returning the final result.  This is also used for the
          input value if provided.

        :type xorMask:

          an integer
        """

        if width > 0:
            try:
                polyMask = long(polynomial)
            except TypeError:
                # Guess it is already a sequence of exponents.
                polynomial = list(polynomial)
                polynomial.sort()
                polynomial.reverse()
                polynomial = tuple(polynomial)
            else:
                # Convert a mask to a tuple of exponents.
                if lsbFirst:
                    polyMask = reflect(polyMask, width)
                polynomial = (width,)
                for i in range(width-1,-1,-1):
                    if (polyMask >> i) & 1:
                        polynomial += (i,)

            if polynomial[:1] != (width,):
                ValueError("mismatch between width and polynomial degree")

        self.width = width
        self.polynomial = polynomial
        self.name = name
        self.seed = seed
        self.lsbFirst = lsbFirst
        self.lsbFirstData = lsbFirstData
        self.xorMask = xorMask

        if not hasattr(width, "__rlshift__"):
            raise ValueError

        # FIXME: Need more checking of parameters.


    def calcString(self, s, value=None):
        """
        Calculate the CRC of the 8-bit string *s*.
        """
        r = CrcRegister(self, value)
        r.takeString(s)
        return r.getFinalValue()



class CrcRegister:
    """
    Holds the intermediate state of the CRC algorithm.
    """

    def __init__(self, crcAlgorithm, value=None):
        """
        :param crcAlgorithm:

          The CRC algorithm to use.

        :type crcAlgorithm:

          `CrcAlgorithm`

        :param value:

          The initial register value to use.  The result previous of a
          previous CRC calculation, can be used here to continue
          calculation with more data.  If this parameter is ``None``
          or not given, the register will be initialized with
          algorithm's default seed value.

        :type value:

          an integer
        """

        self.crcAlgorithm = crcAlgorithm
        p = crcAlgorithm

        self.bitMask = (1 << p.width) - 1

        word = 0
        for n in p.polynomial:
            word |= 1 << n
        self.polyMask = word & self.bitMask

        if p.lsbFirst:
            self.polyMask = reflect(self.polyMask, p.width)

        if p.lsbFirst:
            self.inBitMask = 1 << (p.width - 1)
            self.outBitMask = 1
        else:
            self.inBitMask = 1
            self.outBitMask = 1 << (p.width - 1)

        if p.lsbFirstData is not None:
            self.lsbFirstData = p.lsbFirstData
        else:
            self.lsbFirstData = p.lsbFirst

        self.reset()

        if value is not None:
            self.value = value ^ p.xorMask

    def __str__(self):
        return formatBinaryString(self.value, self.crcAlgorithm.width)

    def reset(self):
        """
        Reset the state of the register with the default seed value.
        """
        self.value = long(self.crcAlgorithm.seed)
        
    def takeBit(self, bit):
        """
        Process a single input bit.
        """
        outBit = ((self.value & self.outBitMask) != 0)
        if self.crcAlgorithm.lsbFirst:
            self.value >>= 1
        else:
            self.value <<= 1
        self.value &= self.bitMask
        if outBit ^ bool(bit):
            self.value ^= self.polyMask

    def takeWord(self, word, width=8):
        """
        Process a binary input word.

        :param word:

          The input word.  Since this can be a Python ``long``, there
          is no coded limit to the number of bits the word can
          represent.

        :type word:

          an integer

        :param width:

          The number of bits *word* represents.

        :type width:

          an integer
        """
        if self.lsbFirstData:
            bitList = range(0,width)
        else:
            bitList = range(width-1,-1,-1)
        for n in bitList:
            self.takeBit((word >> n) & 1)

    def takeString(self, s):
        """
        Process a string as input.  It is handled as a sequence of
        8-bit integers.
        """
        for c in s:
            self.takeWord(ord(c))

    def getValue(self):
        """
        Return the current value of the register as an integer.
        """
        return self.value

    def getFinalValue(self):
        """
        Return the current value of the register as an integer with
        *xorMask* applied.  This can be used after all input data is
        processed to obtain the final result.
        """
        p = self.crcAlgorithm
        return self.value ^ p.xorMask


def reflect(value, width):
    return sum(
        ((value >> x) & 1) << (width - 1 - x)
        for x in range(width))

def formatBinaryString(value, width):
    return "".join(
        "01"[(value >> i) & 1] for i in range(width-1,-1,-1))

# Some standard algorithms are defined here.  I believe I was able to
# verify the correctness of each of these in some way (against an
# existing implementation or sample data with a known result).

#: Same CRC algorithm as Python's zlib.crc32


# Added by Maarten Damen, special Xmodem polynomial
CRC16X = CrcAlgorithm(
    name         = "CRC16X",
    width        = 16,
    polynomial   = 0x11021,
    seed         = 0,
    lsbFirst     = False,
    xorMask      = 0)


def _callCalcString123456789(v):
    return v.calcString('123456789')

def _printResults(fn=_callCalcString123456789):
    import sys
    d = sys.modules[__name__].__dict__
    algorithms = sorted(
        (v for (k, v) in d.iteritems() if isinstance(v, CrcAlgorithm)),
        key=lambda v: (v.width, v.name))
    for a in algorithms:
        format = ("%%0%dX" % ((a.width + 3) // 4))
        print "%s:" % a.name,
        print format % fn(a)

def _test():
    import doctest, sys
    return doctest.testmod(sys.modules[__name__])

if __name__ == "__main__":
    _test()
