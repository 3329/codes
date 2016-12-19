# -*- coding: utf-8 -*-
from jinja2 import Environment, PackageLoader
env = Environment(loader=PackageLoader('youngapplication', 'templates'))
template = env.get_template('mytemplate.html')
print template.render(the='variables', go='here')
