#! /usr/bin/env python

top = '.'
out = 'build'
APPNAME = 'art'
VERSION = '0.1.0'

def options(opt):
  opt.load('compiler_cxx')
  opt.recurse('src')
  opt.recurse('test')

def configure(conf):
  conf.load('compiler_cxx')
  conf.recurse('src')
  conf.recurse('test')
  conf.env.append_value('CXXFLAGS', '-std=c++11')

def build(bld):
  bld.recurse('src')
  bld.recurse('test')

