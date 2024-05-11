
#ifndef Bit_Math_H_
#define Bit_Math_H_

#define Set_Bit(Var,Bit_no) (Var|=(1<<Bit_no))
#define Clr_Bit(Var,Bit_no) (Var&=(~(1<<Bit_no)))
#define Tog_Bit(Var,Bit_no) (Var^=(1<<Bit_no))
#define Get_Bit(Var,Bit_no) ((Var>>Bit_no)&1)

#endif