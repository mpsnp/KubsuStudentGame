#!/usr/bin/env python
# -*- coding: utf-8 -*-

print("Map name:")
name = raw_input(">>")
print("width:")
width = input(">>")
print("height")
height = input(">>")

with open(name, "wt") as fd :
	fd.write(str(width)+" "+str(height)+"\n")
	
	for i in range(0, width) :
		fd.write('1')
	fd.write('\n')
	
	for i in range(2, height) :
		fd.write('1')
		for j in range(2, width) :
			fd.write("0")
		fd.write('1\n')
	
	for i in range(0, width) :
		fd.write('1')
	fd.write('\n')	
