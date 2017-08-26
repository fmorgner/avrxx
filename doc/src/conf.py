# pylint: disable=missing-docstring,invalid-name,redefined-builtin

import os
import subprocess

subprocess.call('cd ../../ && doxygen', shell=True)

html_theme = 'sphinx_rtd_theme'

extensions = [
    'breathe',
    'sphinx.ext.todo',
]

breathe_projects = {
    'AVR++': os.path.abspath('../xml'),
}
breathe_default_project = 'AVR++'

highlight_language = 'c++'

source_suffix = '.rst'
master_doc = 'index'

project = 'AVR++'
copyright = '2017, Felix Morgner'
author = 'Felix Morgner'

version = '1.0.0'
release = '1.0.0'

language = 'en'

exclude_patterns = [
    'build',
    'Thumbs.db',
    '.DS_Store',
]

todo_include_todos = True

htmlhelp_basename = 'AVR++doc'

man_pages = [
    (master_doc, 'AVR++', 'AVR++ Documentation',
     [author], 1)
]

primary_domain = 'cpp'
