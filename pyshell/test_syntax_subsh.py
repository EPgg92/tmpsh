#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestSyntaxSubsh(unittest.TestCase):

    def test_subsh_001(self):
        term_input = ''
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual([], tt.tags)
        self.assertEqual([], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)


if __name__ == '__main__':
    unittest.main()
