#!/usr/bin/env python3

import unittest
from unittest import TestCase, TextTestRunner
from ProjectFuncCffi import ffi, lib

class Test_t_caps_utils(TestCase):

	def test_t_caps_utils(self):
		self.assertEqual(lib.DEFAULT_UNIT_TEST, 0)

if __name__ == '__main__':
	print("\n\n{:*^70}".format("#:~- T_CAPS_UTILS -~:#"))
	unittest.main()