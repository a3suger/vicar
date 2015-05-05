/*
 * debug.h
 *
 *  Created on: 2015/05/05
 *      Author: akira
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUG_INPUT 0x01

extern inline void debug_print_crnt_itemset();
extern  unsigned int debug_level ;
#define is_for_debug(NUM) (debug_level & (NUM))

#endif /* DEBUG_H_ */
