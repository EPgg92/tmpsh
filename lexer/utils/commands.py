#!/usr/bin/env python3

import utils.tokenizer as tk
from utils.readgrammar import ShellGrammar
import utils.strcontain as sc
import utils.shift_reduce as sr
global GRAMMAR
GRAMMAR = ShellGrammar()

class Cmd(object):
	def __init__(self, start, tags, ends=[]):
		self.start = start
		self.end = start
		self.ends = GRAMMAR.grammar['TERMINATOR']
		if ends != []:
			self.ends = ends
		self.sub = [] # list de cmd
		self.get_end(tags)
		if ends != []:
			self.start -= 1
		self.tags = tags[self.start: self.end]
		self.stack = sr.reduce_shift(self.tags, GRAMMAR)
		self.incomplete = False
		self.valid = False
		self.error_near = -1
		if self.stack == ['CMD']:
			self.valid = True
		else:
			self.incomplete = sr.incomplete_key(stack, GRAMMAR)
			self.error_near = -1 # find indice in tags of error
		print(self.stack)

	def get_end(self, tags):
		i = self.start
		len_tags = len(tags)
		while i < len_tags:
			curr_tag = tags[i]
			if curr_tag in self.ends:
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


class ListCommands(object):
	def __init__(self, term_inputs):
		self.term_inputs = term_inputs
		self.tokens = []
		tk.tokenize(term_inputs, self.tokens)
		self.get_tags()
		self.get_tree_commands()

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

	def get_tree_commands(self):
		tags = self.tags
		tree_commands = []
		i = 0
		len_tags = len(tags)
		while i < len_tags:
			cmd = Cmd(i, tags)
			i = cmd.end
			tree_commands.append(cmd)
		self.tree_commands = tree_commands
