/*
 * debug.c
 *
 *  Created on: 2015/04/14
 *      Author: akira
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label.h"

extern char * card_string;
extern int    item_length;
extern int    card_size ;
extern int    item_size ;
extern int    line ;
extern int   *first;
extern int   *last ;
extern int   *cache_count;
extern int   *cache_hash;
extern int   *crnt_items;
extern int    get_card_count();
extern int    get_card_hash();
extern int    cached_item();


inline char * make_cardinarity_label(int index, int pos){
	int i ;
	memset(card_string,0,item_length);
	for(i=0;i<card_size;i++){
		int len = strlen(card_string) ;
		if (len+1>item_length) break ;
		snprintf(card_string+len,item_length-len-1,"%d:",get_card_count(index,pos,i));
	}
	return card_string;
}

inline void debug_print_header(FILE *fd,int index, char *str){
	fprintf(fd,"%1s%06d:%8x:%6d:%6d:%6d",str,line,index,cache_count[index],first[index],last[index]);
}

inline void debug_print_header_simple(FILE *fd,char *str1,char *str2){
	fprintf(fd,"%1s%06d:%8s:%6s:%6s:%6s",str1,line,str2,"","","");
}

inline void debug_print_header_dummy(FILE *fd){
	fprintf(fd,"%1s%6s %8s %6s %6s %6s","","","","","","");
}


inline void debug_print_itemsets(FILE *fd,int *sets,int index ){
	int i ;
	for(i=0;i<item_size;i++)
		if(*(sets+i)<=0){
			fprintf(fd,":%8d:%-16s",*(sets+i),(index==0)?"(NA)":make_cardinarity_label(index,i));
		}else{
			fprintf(fd,":%8x:%-16s",*(sets+i),get_label_by(*(sets+i)));
		}
	fprintf(fd,"\n");
}

inline void debug_print_crnt_itemset(){
	debug_print_header_simple(stderr,"d","crnt");
	debug_print_itemsets(stderr,crnt_items,0);
}


inline void debug_print_cache_hash(int index,char *str){
    debug_print_header(stderr,index,str);
	debug_print_itemsets(stderr,cache_hash+item_size*index,0);
}

inline void print_out(int index,char *str){
    debug_print_header(stdout,index,str);
	debug_print_itemsets(stdout,cache_hash+item_size*index,index);

	int i,j ;
	for(j=0;j<card_size;j++){
		printf("%1s%6s %8s %6s %6s %6s","","","","","","");
		for(i=0;i<item_size;i++)
			if((cached_item(index,i)<=0)&&(get_card_count(index,i,j)>0)){
				printf(":%8x:%-16s",get_card_hash(index,i,j),get_label_by(get_card_hash(index,i,j)));
			}else{
				printf(":%-8s:%-16s","","");
			}
		printf("\n");
	}
}
