import os

project = 'AVR++'
author = 'Felix Morgner'
copyright = '2020, Felix Morgner'

version = '1.0'
release = '1.0.0'

master_doc = 'index'

extensions = [
    'sphinx.ext.todo',
    'sphinx.ext.githubpages',
]

todo_include_todos = True

highlight_language = 'c++'

pygments_style = 'tango'

exclude_patterns = []

numfig = True

html_theme = 'haiku'

man_pages = [
    (
        'index',
        'AVR++',
        'A modern C++17 interface to AVR controllers',
        ["Felix Morgner <felix.morgner@gmail.com"],
        3
    ),
]
