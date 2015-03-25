from fec.stringtorand import stringtorand
from gnuradio import gr;
import derand


class generalized_randomizer_bb(gr.hier_block2):
    def __init__(self, randstring, fill=None, width=None, lrs_len=None):
        gr.hier_block2.__init__(
            self, "generalized_randomizer",
            gr.io_signature(1, 1, gr.sizeof_char),
            gr.io_signature(1, 1, gr.sizeof_char)
            )

        if(lrs_len == None):
            lrs_len = width;

        self.randstring = randstring

        myrand = stringtorand(self.randstring);

        if randstring.startswith("F"):
            self._randomizer = fsblks.randomizer_feedthrough_bb(myrand[1]);
            self.connect(self, (self._randomizer, 0));
            self.connect((self._randomizer, 0), self);

        elif randstring.startswith("A"):
            self._pack = gr.unpacked_to_packed_bb(1,gr.GR_MSB_FIRST);
            self._randomizer = fsblks.randomizer_additive_bb(myrand[1], lrs_len, width, fill);
            self._unpack = gr.packed_to_unpacked_bb(1,gr.GR_MSB_FIRST);
            self.connect(self, self._pack, self._randomizer);
            self.connect(self._randomizer, self._unpack, self);

        else:
            assert(False), 'Check randomizer string input: only additive or feedthrough allowed.'

