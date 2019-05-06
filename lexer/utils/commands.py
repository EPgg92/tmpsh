#!/usr/bin/env python3

import utils.tokenizer as tk
from utils.readgrammar import ShellGrammar
import utils.strcontain as sc
import utils.shift_reduce as sr
global GRAMMAR
GRAMMAR = ShellGrammar()


class Cmd():
    def __init__(self, start, tags, ends):
        self.start = start
        self.end = start
        self.incomplete = False
        self.valid = True
        self.tags = []
        self.sub = []
        self.stack = []
        self.error_near = -1

        if ends != []:
            self.get_end(tags, ends)
            self.start -= 1
        else:
            self.get_end(tags, GRAMMAR.grammar['TERMINATOR'])
        self.tags = tags[self.start: self.end]
        self.is_valid()
        print('valid:', self.valid, '| incomplete:', self.incomplete)
        if self.error_near != -1:
            print('error near:', self.error_near)

    def is_valid(self):
        for subcmd in self.sub:
            if not subcmd.valid:
                self.valid = False
                self.error_near = subcmd.error_near
            if subcmd.incomplete:
                self.incomplete = True
        if self.valid:
            self.reduce_shift()

    def reduce_shift(self):
        stack = []
        i = 0
        len_tags = len(self.tags)
        while i <= len_tags:
            instack = sr.keyinstack(stack, GRAMMAR)
            if instack > -1:
                stack = sr.reduce_all(stack, instack, GRAMMAR)
            else:
                if i < len_tags and self.tags[i] == 'SPACES':
                    pass
                elif stack == [] or sr.revkeyinstack(stack, GRAMMAR):
                    if i < len_tags:
                        stack.append(self.tags[i])
                else:
                    self.valid = False
                    self.error_near = i - 1
                    break
                i += 1
        if self.valid and stack != ['CMD']:
            self.incomplete = True
        self.stack = stack
        print(stack)

    def get_end(self, tags, ends):
        i = self.start
        len_tags = len(tags)
        while i < len_tags:
            curr_tag = tags[i]
            if curr_tag in ends:
                break
            elif curr_tag in GRAMMAR.opening_tags:
                i += 1
                subcmd = Cmd(i, tags, [GRAMMAR.opening_tags[curr_tag]])
                i = subcmd.end
                self.sub.append(subcmd)
            else:
                i += 1
        i += 1
        if i > len_tags:
            i = len_tags
        self.end = i


class ListCommands():
    def __init__(self, term_inputs):
        self.term_inputs = term_inputs
        self.tokens = []
        self.tree_commands = []
        self.to_complete = []
        self.error = ''
        self.valid = True
        self.incomplete = False


        tk.tokenize(term_inputs, self.tokens)
        self.get_tags()
        self.get_tree_commands()
        print('#################### ListCommands ####################')
        if self.error != '':
            print('tmpsh: parse error near `{}\''.format(self.error))
        if self.incomplete or term_inputs[-1] == '\\':
            self.incomplete = True
            self.to_complete.append('>')
            print('{}'.format(' '.join(self.to_complete).lower()))
        print('Resume:\nvalid:', self.valid, '| incomplete:', self.incomplete)

    def get_tags(self):
        tags = []
        for tok in self.tokens:
            if tok in GRAMMAR.leaf_op:
                tags.append(GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                tags.append('SPACES')
            else:
                tags.append('STMT')
        self.tags = tags

    def get_error(self, ind_error):
        len_tokens = len(self.tokens) - 1
        while ind_error > len_tokens:
            ind_error -= 1
        while ind_error > 0:
            if self.tags[ind_error] != 'SPACES':
                self.error = self.tokens[ind_error]
                break
            ind_error -= 1

    def get_to_complete(self, stack):
        i = 0
        len_stack = len(stack)
        while i < len_stack:
            if stack[i] != 'CMD':
                self.to_complete.append(stack[i])
            i += 1

    def get_tree_commands(self):
        tags = self.tags
        tree_commands = []
        i = 0
        len_tags = len(tags)
        while i < len_tags and self.valid:
            cmd = Cmd(i, tags, [])
            if not cmd.valid:
                self.valid = False
                self.get_error(i + cmd.error_near)
                break
            if cmd.incomplete:
                self.incomplete = True
                self.get_to_complete(cmd.stack)
                break
            i = cmd.end
            tree_commands.append(cmd)
        self.tree_commands = tree_commands
