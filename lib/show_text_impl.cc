/* -*- c++ -*- */
/*
 * Copyright 2013 Volker Schroer, DL1KSV.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include "show_text_impl.h"
#include "show_text_window.h"
#include <gnuradio/io_signature.h>


#include <iostream>

namespace gr {
  namespace display {
    show_text::sptr
    show_text::make(QWidget *parent)
    {
      return gnuradio::get_initial_sptr (new show_text_impl(parent));
    }

	void show_text_impl::disp_pdu(pmt::pmt_t pdu)
	{
	    pmt::pmt_t meta = pmt::car(pdu);
	    pmt::pmt_t vector = pmt::cdr(pdu);
	    std::cout << "* MESSAGE DEBUG PRINT PDU VERBOSE *\n";
	    pmt::print(meta);
	    size_t len = pmt::blob_length(vector);
	    std::cout << "pdu_length = " << len << std::endl;
	    std::cout << "contents = " << std::endl;
	    size_t offset(0);
	    const uint8_t* d = (const uint8_t*)pmt::uniform_vector_elements(vector, offset);
	    for (size_t i = 0; i < len; i += 16) {
		printf("%04x: ", ((unsigned int)i));
		for (size_t j = i; j < std::min(i + 16, len); j++) {
		    printf("%02x ", d[j]);
            	    d_main_gui->set_text(reinterpret_cast<const char*>(&d[j]),-1);
		    // Should -1 be something else?
		}

		std::cout << std::endl;
	    }
	    std::cout << "***********************************\n";
	}
    /*
     * The private constructor
     */
    show_text_impl::show_text_impl(QWidget *parent)
      : gr::sync_block("show_text",
                      gr::io_signature::make(0,0,0),
                      gr::io_signature::make(0,0,0))
                      ,d_parent(parent){
	
    	message_port_register_in(pmt::mp("disp_pdu"));
   	set_msg_handler(pmt::mp("disp_pdu"),
        	boost::bind(&show_text_impl::disp_pdu, this, _1));
        d_main_gui = NULL;
        if(qApp != NULL) {
          d_qApplication = qApp;
         }
        else {
          int argc=1;
          char *argv =new char;
          argv[0] = '\0';

          d_qApplication = new QApplication(argc, &argv);
        }
        d_main_gui = new show_text_window(d_parent);

    }

    /*
     * Our virtual destructor.
     */
    show_text_impl::~show_text_impl()
    {
       d_main_gui->close();
    }

    int
    show_text_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        //const char *in = (const char *) pmt::to_long(print_pdu);

        // Do <+signal processing+>
        //d_main_gui->set_text(in,noutput_items);
        // Tell runtime system how many output items we produced.
        //return noutput_items;
	return 0;
    }

    PyObject *
    show_text_impl::pyqwidget()
    {

     PyObject *w = PyLong_FromVoidPtr((void*)d_main_gui);
     PyObject *retarg = Py_BuildValue("N", w);
     return retarg;
    }

  } /* namespace display */
} /* namespace gr */

