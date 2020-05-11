#include <stdio.h>
#include <stdlib.h>

typedef union FLOAT_UN {
  float float_in_decimal;
  struct {
    unsigned int mantissa: 23;
    unsigned int exponent:  8;
    unsigned int     sign:  1;
  } f_bits;
  struct single_bits {
	  
    // Mantissa, b0 to b22.
    unsigned  b0 :1;  
	unsigned  b1 :1;  
	unsigned  b2 :1;  
	unsigned  b3 :1;
    unsigned  b4 :1;  
	unsigned  b5 :1;  
	unsigned  b6 :1;  
	unsigned  b7 :1;
    unsigned  b8 :1;  
	unsigned  b9 :1;  
	unsigned  b10:1;  
	unsigned  b11:1;
    unsigned  b12:1;  
	unsigned  b13:1;  
	unsigned  b14:1;  
	unsigned  b15:1;
    unsigned  b16:1;  
	unsigned  b17:1;  
	unsigned  b18:1;  
	unsigned  b19:1;
    unsigned  b20:1;  
	unsigned  b21:1;  
	unsigned  b22:1;
	
    // Exponent, b23 to b30.
    unsigned  b23:1;  
	unsigned  b24:1;  
	unsigned  b25:1;  
	unsigned  b26:1;
    unsigned  b27:1;  
	unsigned  b28:1;  
	unsigned  b29:1;  
	unsigned  b30:1;

    // Sign, b31.
    unsigned  b31:1;
	
  } bit;
} FLOAT_UN;

void print(FLOAT_UN result);
void print_binary(FLOAT_UN result);

float float_addition(FLOAT_UN val1, FLOAT_UN val2);

int main() 
{
  float float1;
  float float2;
  float hardware;
  float emulated;
  
  FLOAT_UN float1_Obj;
  FLOAT_UN float2_Obj;
  FLOAT_UN hardware_Obj;
  FLOAT_UN emulated_Obj;

  for(int i = 0; i < 6; i++)
  {
    printf("Enter Float 1: ");
    scanf("%f", &float1);

    printf("Enter Float 2: ");
    scanf("%f", &float2);

    float1_Obj.float_in_decimal = float1;
    float2_Obj.float_in_decimal = float2;

    hardware = float1 + float2;
	hardware_Obj.float_in_decimal = hardware;  
	
    printf("\n\nOriginal pattern of Float 1: ");
	print(float1_Obj);
	printf("Original pattern of Float 2: ");
    print(float2_Obj);

    emulated = float_addition(float1_Obj, float2_Obj);
    if(float1_Obj.f_bits.exponent < float2_Obj.f_bits.exponent) 
	{
      emulated = float_addition(float2_Obj, float1_Obj);
    }

    emulated_Obj.float_in_decimal = emulated;
	emulated_Obj.bit.b31 = 0;
	printf("      Bit pattern of result: ");
	
    print(emulated_Obj);
	printf("\nEMULATED FLOATING RESULT FROM PRINTF ==>>>%f", emulated_Obj.float_in_decimal);
	printf("\nHARDWARE FLOATING RESULT FROM PRINTF ==>>>%f\n", hardware_Obj.float_in_decimal);
    printf("\n");
   }
  return 0;
}

void print(FLOAT_UN result) {
  static char bit_string[43]; 

  for(int i = 0; i < 42; i++) 
  {
    bit_string[i] = ' '; 
  }

   bit_string[42] = '\0';
   bit_string[0] = result.bit.b31?'1':'0';

   bit_string[2] = result.bit.b30?'1':'0';
   bit_string[3] = result.bit.b29?'1':'0';
   bit_string[4] = result.bit.b28?'1':'0';
   bit_string[5] = result.bit.b27?'1':'0';

   bit_string[7] = result.bit.b26?'1':'0';
   bit_string[8] = result.bit.b25?'1':'0';
   bit_string[9] = result.bit.b24?'1':'0';
   bit_string[10] = result.bit.b23?'1':'0';

   bit_string[12] = result.bit.b22?'1':'0';
   bit_string[13] = result.bit.b21?'1':'0';
   bit_string[14] = result.bit.b20?'1':'0';

   bit_string[16] = result.bit.b19?'1':'0';
   bit_string[17] = result.bit.b18?'1':'0';
   bit_string[18] = result.bit.b17?'1':'0';
   bit_string[19] = result.bit.b16?'1':'0';

   bit_string[21] = result.bit.b15?'1':'0';
   bit_string[22] = result.bit.b14?'1':'0';
   bit_string[23] = result.bit.b13?'1':'0';
   bit_string[24] = result.bit.b12?'1':'0';

   bit_string[26] = result.bit.b11?'1':'0';
   bit_string[27] = result.bit.b10?'1':'0';
   bit_string[28] = result.bit.b9?'1':'0';
   bit_string[29] = result.bit.b8?'1':'0';

   bit_string[31] = result.bit.b7?'1':'0';
   bit_string[32] = result.bit.b6?'1':'0';
   bit_string[33] = result.bit.b5?'1':'0';
   bit_string[34] = result.bit.b4?'1':'0';

   bit_string[36] = result.bit.b3?'1':'0';
   bit_string[37] = result.bit.b2?'1':'0';
   bit_string[38] = result.bit.b1?'1':'0';
   bit_string[39] = result.bit.b0?'1':'0';

  printf("%s\n", bit_string);
}

float float_addition(FLOAT_UN val1, FLOAT_UN val2) 
{
  int bit_counter = 0;
  FLOAT_UN float_sum;
  
  int firstExp = val1.f_bits.exponent;
  int secondExp = val2.f_bits.exponent;
  int firstMan =val1.f_bits.mantissa;
  int secondMan = val2.f_bits.mantissa;
  
  firstExp++;
  secondExp++;
  
  if (val1.f_bits.exponent == 254 || val2.f_bits.exponent == 254) 
  {
    float_sum.f_bits.exponent = 255;
    float_sum.f_bits.mantissa = 0;
  return float_sum.float_in_decimal;
  }
  if (val1.f_bits.exponent == val2.f_bits.exponent) 
  {

    float_sum.f_bits.exponent = firstExp;

    float_sum.f_bits.mantissa = firstMan + secondMan;
    float_sum.f_bits.mantissa >>= 1;  
    float_sum.bit.b22 = 1;              
  }
  else
  {
    val2.f_bits.mantissa  >>= 1;  
    val2.bit.b22 = 1;    

    bit_counter = val1.f_bits.exponent - val2.f_bits.exponent;
    if (--bit_counter > 24) 
	{
	bit_counter = 24;    
    }
	
    val2.f_bits.mantissa  >>= bit_counter - 1;

    if (val2.bit.b0 == 1) 
	{      
      val2.f_bits.mantissa >>= 1;
      val2.f_bits.mantissa += 1;    
    }
    else 
	{
      val2.f_bits.mantissa >>= 1;
    }

    float_sum.f_bits.exponent = val1.f_bits.exponent;
    float_sum.f_bits.mantissa = val1.f_bits.mantissa + val2.f_bits.mantissa;
  }
  return float_sum.float_in_decimal;
}
