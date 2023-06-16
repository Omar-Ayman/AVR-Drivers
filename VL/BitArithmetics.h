/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
#ifndef _BIT_ARITHMETICS
#define _BIT_ARITHMETICS

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 1)

#define ONES(NUM) (((1 % ((NUM) + 1)) << (NUM)) - 1)
#define ONES_SHFT(NUM, SHFT) (ONES(NUM) << (SHFT))

#define SET_BITS(VAR,BITNUM,BITOFF) (VAR) |=  ONES_SHFT(BITNUM, BITOFF)
#define CLR_BITS(VAR,BITNUM,BITOFF) (VAR) &= ~ONES_SHFT(BITNUM, BITOFF)
#define TOG_BITS(VAR,BITNUM,BITOFF) (VAR) ^=  ONES_SHFT(BITNUM, BITOFF)
#define GET_BITS(VAR,BITNUM,BITOFF) (((VAR) >> (BITOFF)) & ONES(BITNUM))
#define ASS_BITS(VAR,BITNUM,BITOFF,VALS) (VAR) = ((VAR) & ~ONES_SHFT(BITNUM, BITOFF)) | (((VALS) & ONES(BITNUM)) << (BITOFF))

#endif