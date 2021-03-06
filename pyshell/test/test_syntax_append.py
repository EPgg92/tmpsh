#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestSyntaxAppendValid(unittest.TestCase):

    def test_append_001(self):
        term_input = '>>a'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['APPEND', 'STMT'], tt.tags)
        self.assertEqual(['>>', 'a'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)


class TestSyntaxAppendInvalid(unittest.TestCase):

    def test_append_001(self):
        term_input = '>>'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['APPEND'], tt.tags)
        self.assertEqual(['>>'], tt.tokens)
        # self.assertEqual([], tt.stack)
        self.assertEqual('>>', tt.token_error)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)


if __name__ == '__main__':
    unittest.main()
