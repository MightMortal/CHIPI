# CHIPI
#
# CHIP-8 interpreter writed in Plain C
#
# Code: MightMortal
# License: Apache License
#
# Copyright 2013 MightMortal
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

chipi_source_path    = 'src'
chipi_lib_list       = ['glfw', 'GL']
chipi_build_path     = 'build'
chipi_output_path    = 'bin'
chipi_target_file    = 'chipi'
chipi_compile_flags  = '-std=c99' # Add space at and for avoid error after adding flags
chipi_config_suffix  = ''
chipi_config_name    = ''

top = '.'
out = chipi_build_path

# if ARGUMENTS.get('debug', 0):
#   chipi_compile_flags  += '-g -DDEBUG'
#   chipi_config_name    = 'debug'
#   chipi_config_suffix  = 'd'
# else:
#   chipi_compile_flags  += '-O2'
#   chipi_config_name    = 'release'
#   chipi_config_suffix  = ''

def options(opt):
  opt.load('compiler_c')

def configure(conf):
  conf.load('compiler_c')
  conf.env.append_value('CFLAGS', chipi_compile_flags)

def build(bld):
  bld.program(source = bld.path.ant_glob(chipi_source_path + '/*.c'), target = chipi_target_file,
              lib = chipi_lib_list)

