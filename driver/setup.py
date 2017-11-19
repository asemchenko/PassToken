#!/usr/bin/env python

from distutils.core import setup

setup(name='PT',
      version='1.0',
      description='Interface for PT device',
      author='BMS',
      author_email='rashpilxd@gmail.com',
      py_modules=['main', 'interface.arduino'],
      requires=['serial', 'threading', 'sys', 'PyQt4'],
      data_files=[('interface', ['interface/logo.jpg'])]
     )