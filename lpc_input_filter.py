#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# This currently has a known deficiency in that it'll improperly identify the word "inherit" in running comments and mess up.

# @LICENSE

import os.path
import sys


def writeLine(txt):
	sys.stdout.write(txt + "\n")

def parseInherit(root, txt):

	inherits = [x for x in txt if x.find("inherit ") != -1]

	[txt.remove(x) for x in inherits]

	includes = [x for x in txt if x.find("#include ") == 0]

	last_include_line = 0
	if len(includes):
		last_include_line = txt.index(includes[-1]) + 1

	inherit_replacements = []
	for inherit_str in inherits:
		pair = inherit_str.split("inherit")
		modifiers = pair[0]
		inherit_class = pair[1].split("/").pop().split(".")[0].strip('"; ')
		inherit_replacements.append(modifiers + inherit_class + "::"+inherit_class)

	replacement_text = ", ".join(inherit_replacements)
	filename = root.split("/").pop()

	txt.insert(last_include_line, "public class "+filename+" : "+ replacement_text + " {\n")
	txt.append("}")

	showLines(txt)

## @returns the complete file content as an array of lines
def readFile(filename):
	f = open(filename)
	r = f.read().splitlines()
	f.close()
	return r

## dump all lines to stdout
def showLines(r):
	sys.stdout.write("\n".join(r))

## main method - open a file and see what can be done
def inherit_filter(filename):

	try:
		root, ext = os.path.splitext(filename)
		txt = readFile(filename)
		if (ext.lower() == ".c" or ext.lower() == ".h"):
			parseInherit(filename, txt)
		else:
			showLines(txt)
	except IOError as e:
		sys.stderr.write(e[1]+"\n")

if len(sys.argv) != 2:
	print("usage: ", sys.argv[0], " filename")
	sys.exit(1)

filename = sys.argv[1]
inherit_filter(filename)
sys.exit(0)
