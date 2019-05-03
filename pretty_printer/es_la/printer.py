import gdb
import gdb.printing
import gdb.types
import re

def strip_namespace_name(str):
	return str.split('::', 1).pop()

def get_vector_element(vec, index):
	type = gdb.types.get_basic_type(vec.type)
	return gdb.parse_and_eval('(*(%s*)(%s))[%d]' % (type, vec.address, index))

class Matrix_printer(object):
	def __init__(self, val):
		self.val = val

	def to_string(self):
		type = gdb.types.get_basic_type(self.val.type)
		type_name = str(gdb.types.get_basic_type(type))

		return '%s' % (type_name)

	def display_hint(self):
		return 'array'

def build_pretty_printer():
	printer = gdb.printing.RegexpCollectionPrettyPrinter('es_la')

	printer.add_printer('Matrix', '^es_la::Matrix', Matrix_printer)

	return printer

def register_printers():
	gdb.printing.register_pretty_printer(gdb.current_objfile(), build_pretty_printer())
