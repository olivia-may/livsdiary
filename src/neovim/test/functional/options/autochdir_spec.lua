local lfs = require('lfs')
local helpers = require('test.functional.helpers')(after_each)
local clear = helpers.clear
local eq = helpers.eq
local funcs = helpers.funcs
local command = helpers.command

describe("'autochdir'", function()
  it('given on the shell gets processed properly', function()
    local targetdir = 'test/functional/fixtures'

    -- By default 'autochdir' is off, thus getcwd() returns the repo root.
    clear(targetdir..'/tty-test.c')
    local rootdir = funcs.getcwd()
    local expected = rootdir .. '/' .. targetdir

    -- With 'autochdir' on, we should get the directory of tty-test.c.
    clear('--cmd', 'set autochdir', targetdir..'/tty-test.c')
    eq(helpers.iswin() and expected:gsub('/', '\\') or expected, funcs.getcwd())
  end)

  it('is not overwritten by getwinvar() call #17609',function()
    local curdir = string.gsub(lfs.currentdir(), '\\', '/')
    local dir_a = curdir..'/Xtest-functional-options-autochdir.dir_a'
    local dir_b = curdir..'/Xtest-functional-options-autochdir.dir_b'
    lfs.mkdir(dir_a)
    lfs.mkdir(dir_b)
    clear()
    command('set shellslash')
    command('set autochdir')
    command('edit '..dir_a..'/file1')
    eq(dir_a, funcs.getcwd())
    command('lcd '..dir_b)
    eq(dir_b, funcs.getcwd())
    command('botright vnew ../file2')
    eq(curdir, funcs.getcwd())
    command('wincmd w')
    eq(dir_a, funcs.getcwd())
    funcs.getwinvar(2, 'foo')
    eq(dir_a, funcs.getcwd())
    helpers.rmdir(dir_a)
    helpers.rmdir(dir_b)
  end)
end)