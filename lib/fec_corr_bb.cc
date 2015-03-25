
#include <fec_corr_bb.h>
#include <gnuradio/io_signature.h>
#include <pmt/pmt.h>
#include <gnuradio/messages/msg_passing.h>
#include <stdio.h>





fec_corr_bb_sptr
fec_make_corr_bb(std::vector<unsigned long long> correlator, int corr_sym, int corr_len, int cut, int flush, float thresh)
{
    return gnuradio::get_initial_sptr(new fec_corr_bb(correlator, corr_sym, corr_len, cut, flush, thresh));
}

fec_corr_bb::fec_corr_bb (std::vector<unsigned long long> correlator, int corr_sym, int corr_len, int cut, int flush, float thresh)
  : gr::block("corr_bb",
	       gr::io_signature::make(1, 1, sizeof(unsigned char)),
	       gr::io_signature::make(1, 1, sizeof(unsigned char))),
      d_corr_len(corr_len), 
      d_cut(cut), 
      d_counter(cut),
      d_corr_sym(corr_sym),
      d_produce(0),
      d_thresh(cut * thresh),
      d_message(0),
      d_acquire(-1),
      d_op(0),
      d_havelock(false),
      d_lane(0),
      d_flush(flush),
      d_flush_count(0),
      d_data_garble_rate(0.0)
      //d_acquire_track(-1)

#ifdef GR_CTRLPORT
      ,d_msgrecv_rpc(alias(), "messages_recieved",  &d_msgrecv, pmt::mp(0), pmt::mp(65536), pmt::mp(0), "messages", "Asynch Messages Recieved", RPC_PRIVLVL_MIN, DISPTIME | DISPOPTSTRIP),
      d_msgsent_rpc(alias(), "messages_sent",  &d_msgsent, pmt::mp(0), pmt::mp(65536), pmt::mp(0), "messages", "Asynch Messages Sent", RPC_PRIVLVL_MIN, DISPTIME | DISPOPTSTRIP),
      d_flush_rpc(alias(), "flush_constant",  (int*)&d_flush, pmt::mp(0), pmt::mp(1), pmt::mp(0), "int", "Flush Distance", RPC_PRIVLVL_MIN, DISPTIME | DISPOPTSTRIP),
      d_cut_rpc(alias(), "integration_period",  &d_cut, pmt::from_uint64(0), pmt::from_uint64(65536), pmt::from_uint64(d_cut), "uint64_t", "Integration Time"),
      d_data_garble_rate_rpc(alias(), "norm_garble_rate", &d_data_garble_rate, pmt::mp(0.0f), pmt::mp(0.0f), pmt::mp(1.0f), "normalized_garble_rate", "Normalized Data Garble Rate", RPC_PRIVLVL_MIN),
    d_havelock_rpc(alias(), "locked",  &d_havelock, pmt::mp(0), pmt::mp(1), pmt::mp(0),
                          "bool","Sync Locked", RPC_PRIVLVL_MIN, DISPTIME)
#endif /* GR_CTRLPORT */

{
  
  //big correlator mode (ugh)
  std::vector<unsigned char> temp;
  for(int k = 0; k < d_corr_sym; ++k) {
    d_acc.push_back(0);
  }
  for(int i = 0; i < d_corr_len; ++i) {  
    if((correlator[i/64] >> (64 - (i%64) - 1)) & 1) {
      temp.push_back(i);
      
    }
  }
  d_correlator.push_back(temp);

  
  for(int j = 0; j < d_correlator.size(); ++j) {
    std::vector<int> temp(d_corr_sym); 
      d_score_keeper.push_back(temp);
  }
  
  set_history(d_corr_len + d_corr_sym);
  d_flush_count = d_corr_len + d_corr_sym - 1;
  set_output_multiple(d_corr_sym);
  

}

void fec_corr_bb::catch_msg(pmt::pmt_t msg) {
    //stub code
    d_msgrecv++;
}




  
int fec_corr_bb::general_work (int noutput_items,
			       gr_vector_int& ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{


    if(d_flush_count > 0) {
	int items = (ninput_items[0] > d_flush_count) ? d_flush_count : ninput_items[0];
	consume_each(items);
	d_flush_count -= items;
	return 0;
	
    }


    
    
    const uint8_t *in = (const uint8_t *) input_items[0];
    uint8_t *score_in = (uint8_t *) input_items[0];
    
    

    //counting on  1:1 forecast + history to provide enough ninput_items... may need to insert check
    //printf("%d, %d, %d\n", ninput_items[0], noutput_items, d_counter);
    int correlation_cycles = (noutput_items/output_multiple() <= d_counter) ? noutput_items/output_multiple() : d_counter;
  

    for(int p = 0; p < correlation_cycles; ++p) {

	//reset scores
	for(int j = 0; j < d_correlator.size(); ++j) {
	    for(int i = 0; i < d_corr_sym; ++i) {
		d_score_keeper[j][i] = 0;
	    }
	}

    

	//correlate against each correlation constant
	for(int j = 0; j < d_correlator.size(); ++j) {
	    for(int k = 0; k < d_corr_sym; ++k) {
		for(int i = 0; i < d_correlator[j].size(); ++i) {
		
		    
		    d_score_keeper[j][k] += (score_in[d_correlator[j][i] + k] >= 128) ? 1 : 0;
		}
	    }
	    
	    for(int k = 0; k < d_corr_sym; ++k) {
		
		d_acc[j * (d_corr_sym) + k] += d_score_keeper[j][k] % 2;
	    }
	}
	score_in += d_corr_sym;
    }

    //decrement the cut counter
    
    d_counter -= correlation_cycles;
    
    
    //d_counter == 0: check the accumulator and update states
    if(d_counter == 0) {
    d_message = 1;
	d_produce = 0;
	float my_min = 1.0;
	for(int i = 0; (i < d_correlator.size()) && (!d_produce); ++i) {
	    for(int k = 0; k < d_corr_sym; ++k) {
	      
	        my_min = (d_acc[i * (d_corr_sym) + k]/(float)d_cut < my_min)?d_acc[i * (d_corr_sym) + k]/(float)d_cut:my_min;

		if (d_acc[i * (d_corr_sym) + k] < d_thresh) {	
		    d_produce = 1;
            d_message = 0;
		    d_acquire = k;
		    d_lane = i + 1;
		    d_op = 1;
		    //printf("winner: lane %u, punc_cycle %u, pos/neg corr %d\n", i, k, d_op);
		    break;
		}
		else if (d_acc[i * (d_corr_sym) + k] > (d_cut - d_thresh)) {
		    d_acquire = k;
		    d_lane = i + 1;
		    d_op = -1;
		    //printf("winner: lane %u, punc_cycle %u, pos/neg corr %d\n", i, k, d_op);
		    break;
		}
	    }
	    d_data_garble_rate = 100.0 * get_data_garble_rate(d_correlator[i].size(), my_min);
	    d_havelock = d_data_garble_rate < 3;
	    
	}
	
	//clear the accumulator, reset the counter
	d_counter = d_cut;
	for(int i = 0; i < d_correlator.size(); ++i) {
	    for(int k = 0; k < d_corr_sym; ++k) {
		d_acc[i * (d_corr_sym) + k] = 0;
	    }
	}
	
	//examine the new states and react to environment, make a final production decision
	if(d_message) {
        d_msgsent++;
        //stub code
        d_message = 0;
    }
    
    }
    //states are set
    
    
    

    
    if(d_produce) {
        //printf("producing\n");
	unsigned char *out = (unsigned char *) output_items[0];
	memcpy(out, &(in[d_acquire]), correlation_cycles * d_corr_sym * sizeof(unsigned char));
	
	consume_each(d_corr_sym * correlation_cycles);
	return d_corr_sym * correlation_cycles;
    }
    
    else {
	
	consume_each(d_corr_sym * correlation_cycles);
	return 0;
    }
}



float fec_corr_bb::get_data_garble_rate(int taps, float target) {
  /* This subroutine will find the encoded data garble rate
     corresponding to a syndrome density of `target', that is created
     with an annihilating polynomial with 'taps' number of taps.
  */
  double base,expo,answer;
  
  if (target > 0.5)
    target=1-target;
  
  base=1.0-2.0*target;
  expo=(double) 1/taps;
  answer=0.5*(1-pow(base,expo));
  
  if ((errno==EDOM) || (errno==ERANGE))
    {
      fprintf(stderr,"Out of range errors while computing garble rate.\n");
      exit(-1);
    }
  return answer;
}				    


fec_corr_bb::~fec_corr_bb()
{
}
    



