#ifndef INCLUDED_CC_COMMON_H
#define INCLUDED_CC_COMMON_H


typedef unsigned char DECISIONTYPE;
typedef unsigned char COMPUTETYPE;



typedef union {
  //decision_t is a BIT vector
  DECISIONTYPE* t;
  unsigned int* w;
  unsigned short* s;
  unsigned char* c;
} decision_t;

typedef union {
  COMPUTETYPE* t;
} metric_t;



struct v {
  COMPUTETYPE *metrics;
  metric_t old_metrics,new_metrics,metrics1,metrics2; /* Pointers to path metrics, swapped on every bit */
  DECISIONTYPE *decisions;  
};

#endif /*INCLUDED_CC_COMMON_H*/
