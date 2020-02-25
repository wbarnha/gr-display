#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2020 William Barnhart.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

import numpy
from gnuradio import gr

class utf2ascii(gr.sync_block):
    """
    docstring for block utf2ascii
    """
    def __init__(self):
        gr.sync_block.__init__(self,
            name="utf2ascii",
            in_sig=None,
            out_sig=[numpy.uint8])

        self.message_port_register_in(pmt.intern('in'))

    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        # <+signal processing here+>
        output_items[0][:] = input_items.decode(encoding='UTF-8')
        out[:] = in0
        return len(output_items[0])
