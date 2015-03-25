#ifndef INCLUDED_FEC_CORR_BB_H
#define INCLUDED_FEC_CORR_BB_H

#include <gnuradio/block.h>
#include <inttypes.h>
#include <vector>
#include <fec_api.h>
#include <pmt/pmt.h>
#include <boost/bind.hpp>
#ifdef GR_CTRLPORT
#include <gnuradio/rpcregisterhelpers.h>
#endif /* GR_CTRLPORT */

class fec_corr_bb;
typedef boost::shared_ptr<fec_corr_bb> fec_corr_bb_sptr;



FEC_API fec_corr_bb_sptr
fec_make_corr_bb (std::vector<unsigned long long> correlator, int corr_sym, int corr_len, int cut, int flush, float thresh);



class FEC_API fec_corr_bb : public gr::block
{
    std::vector< std::vector<int> > d_score_keeper;
    unsigned int d_lane;
    unsigned int d_op;

     
    void catch_msg(pmt::pmt_t msg);
    
    int d_angry_fop;
    int d_acquire;
    //int d_acquire_track;
    unsigned int d_produce;
    unsigned int d_message;
    unsigned int d_thresh;
    unsigned int d_corr_len;
    std::vector< std::vector<unsigned char> > d_correlator;
    std::vector<unsigned int> d_acc;
    uint64_t d_cut;
    unsigned int d_flush;
    uint64_t d_counter;
    unsigned int d_flush_count;
    unsigned int d_corr_sym;
    void alert_fops();
    float d_data_garble_rate;

    friend fec_corr_bb_sptr
	fec_make_corr_bb (std::vector<unsigned long long> correlator, int corr_sym, int corr_len, int cut, int flush, float thresh);
    
    fec_corr_bb (std::vector<unsigned long long> correlator, int corr_sym, int corr_len, int cut, int flush, float thresh);
 
#ifdef GR_CTRLPORT
    //rpcbasic_register_get<fec_corr_bb, std::vector< int> > d_correlator_rpc;
    rpcbasic_register_variable_rw<uint64_t> d_cut_rpc; // integration period
    rpcbasic_register_variable_rw<int> d_flush_rpc; // time to flush
    rpcbasic_register_variable<uint64_t> d_msgsent_rpc;
    rpcbasic_register_variable<uint64_t> d_msgrecv_rpc; 
    rpcbasic_register_variable<float> d_data_garble_rate_rpc; 
#endif /* GR_CTRLPORT */
    
    uint64_t d_msgsent,d_msgrecv;
    std::vector<int> get_corr(){
        std::vector<int> bits;
        if(d_correlator.size() < 1){ return bits; }
        for(int i=0; i<d_correlator[0].size(); i++){
            bits.push_back( d_correlator[0][i] );
            }
        return bits;
        }
    
     
    bool d_havelock;
#ifdef GR_CTRLPORT
    rpcbasic_register_variable<bool> d_havelock_rpc; 
#endif /* GR_CTRLPORT */

 public:
    
  float get_data_garble_rate(int taps, float syn_density);
  ~fec_corr_bb ();
  int general_work (int noutput_items,
		    gr_vector_int& ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

  
};

#endif /* INCLUDED_FEC_CORR_BB_H */
