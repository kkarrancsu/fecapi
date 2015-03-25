from gnuradio import gr
import fec
from fec.threaded_encoder import threaded_encoder
from fec.bitflip import read_bitlist
from fec.capillary_threaded_encoder import capillary_threaded_encoder


class extended_encoder_interface(gr.hier_block2):
    def __init__(self, encoder_obj_list, threading, puncpat=None):
        gr.hier_block2.__init__(
            self, "extended_encoder_interface",
            gr.io_signature(1, 1, gr.sizeof_char),
            gr.io_signature(1, 1, gr.sizeof_float)
            )
        self.blocks=[];
        self.puncpat=puncpat;
        
       
        if threading == 'capillary':
            self.blocks.append(capillary_threaded_encoder(encoder_obj_list))
        elif threading == 'ordinary':
            self.blocks.append(threaded_encoder(encoder_obj_list))
        else:
            self.blocks.append(fec.encoder(encoder_obj_list[0]))

       
        if self.puncpat != '11':
            self.blocks.append(fec.puncture_ff(0, read_bitlist(puncpat), puncpat.count('0'), len(puncpat)));
 
        
        

                     

        self.connect((self, 0), (self.blocks[0], 0));
        self.connect((self.blocks[-1], 0), (self, 0));

        for i in range(len(self.blocks) - 1):
            self.connect((self.blocks[i], 0), (self.blocks[i+1], 0));
 
    def set_max_output_buffer(self, m):
        for b in self.blocks:
            b.set_max_output_buffer(m);
       
