project('rpncalc', 'c')
src = ['main.c', 'state.c', 'util.c']
cc = meson.get_compiler('c')
deps = cc.find_library('m', required : true)
executable('rpncalc', src, dependencies : deps)
