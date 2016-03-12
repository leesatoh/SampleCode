#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<iostream>
#include	<msgpack.hpp>
//-------------------------------------------------------------------------------
//GLOBAL OBJECT struct
//-------------------------------------------------------------------------------
struct	GLOBAL{
	msgpack::zone	Zone;
	msgpack::object	Obj;
	char			hex[10000000*2];
	char			bin[10000000];
}G;
///////////////////////////////////////////////////////////////////////////////
char*
mhex2bin(void* arg_bin, const void* arg_hex, size_t hexlen){
	size_t		i;
	      char	hi, lo;
	      char*	bin	= (      char*)arg_bin;
	const char*	hex	= (const char*)arg_hex;


	if((hexlen % 2) != 0){
		fprintf(stderr, "hexlen %zd (=odd number) error.", hexlen);
		return(NULL);
	}
	for(i=0; i<(hexlen/2); i++){
		hi = hex[i*2  ];
		lo = hex[i*2+1];
		if		((hi <= '9') && (hi >= '0'))	{	hi = (char)(hi - '0');							}
		else if	((hi <= 'f') && (hi >= 'a'))	{	hi = (char)(hi - 'a');	hi = (char)(hi + 10);	}
		else if	((hi <= 'F') && (hi >= 'A'))	{	hi = (char)(hi - 'A');	hi = (char)(hi + 10);	}
		else{	fprintf(stderr, "<%c> is not hex char error.", hi);	return(NULL);	}
		if		((lo <= '9') && (lo >= '0'))	{	lo = (char)(lo - '0');							}
		else if	((lo <= 'f') && (lo >= 'a'))	{	lo = (char)(lo - 'a');	lo = (char)(lo + 10);	}
		else if	((lo <= 'F') && (lo >= 'A'))	{	lo = (char)(lo - 'A');	lo = (char)(lo + 10);	}
		else{	fprintf(stderr, "<%c> is not hex char error.", lo);	return(NULL);	}

		bin[i] = (char)(hi * 0x10 + lo);
	}
	return((char*)arg_bin);
}
///////////////////////////////////////////////////////////////////////////////
int
main(){
	size_t			hexlen;


	while(fgets(G.hex, sizeof(G.hex), stdin) != NULL){
		hexlen = strlen(G.hex);
		if(G.hex[hexlen-1] == '\n'){	hexlen --;}
		mhex2bin(G.bin, G.hex, hexlen);
		G.Zone.clear();
		G.Obj = msgpack::unpack(G.Zone, G.bin, hexlen/2);
//		std::cout << G.Obj;
//		printf("\n");
	}
	return(0);
}
