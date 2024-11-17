unsigned char multiplyFloats(unsigned char f1, unsigned char f2)
{
  unsigned char theFloat = 0; // the answer to return
    
  // repack the bits to a 'bit field' keep it normalized
  // get the exponent
  // mask off everything except mantissa
  // put on the leading 1
  // scoot into normal position
  // REPEAT FOR SECOND NUMBER
  // multiply them with ordinary integer multiplication!
  //buffer3 = buffer1 * buffer2;
  // normalize the result
  // check if answer is >= 2
  // normalize and set rollover value
  // calculate exponent for answer
  //int exponent3 = exponent1 + exponent2 + rollover;
  //printf("exp: %d\n", exponent3);
  // overflow check - if exponent is greater than 3
  // underflow check - if exponent is less than -4
  // final packing
  // scoot into normal position
  // pack the mantissa
  // mask off the other stuff
  // add the excess 4 thing
  // insert the exponent
  // insert sign bit
    
  unsigned char e1;
  e1 = f1 & 0x07;
  int e1_int = (int)e1 - 4;
  unsigned char m1;
  m1 = f1 & 0x78;
  
  f1 = m1 | 0x80;
  
  unsigned long f1_32;
  f1_32 = f1;
  f1_32 = f1_32 << 8;
  f1_32 = f1_32 >> 7 - e1_int;
  int count_f1 = 0;
  unsigned long tem_mask_f1 = 0x80000000;
  for (int i = 0; i < 32; ++i) {
    if ( (f1_32 & tem_mask_f1) != 0x00000000) {
      count_f1 = i;
      break;
    }
    tem_mask_f1 = tem_mask_f1 >> 1;
  }
  printf("f1 count %i\n", count_f1);
  unsigned char e2;
  e2 = f2 & 0x07;
  int e2_int = (int)e2 - 4;
  unsigned char m2;
  m2 = f2 & 0x78;
  
  f2 = m2 | 0x80;
  unsigned long f2_32;
  f2_32 = f2;
  f2_32 = f2_32 << 8;
  f2_32 = f2_32 >> 7 - e2_int;
  int count_f2 = 0;
  unsigned long tem_mask_f2 = 0x80000000;
  for (int i = 0; i < 32; ++i) {
    if ( (f2_32 & tem_mask_f2) != 0x00000000) {
      count_f2 = i;
    
      break;
    }
      tem_mask_f2 = tem_mask_f2 >> 1;
  }
  printf("f2 count %i\n", count_f2);
  int ea = 23 - count_f1;
  
  if (ea < 0) {
    f1_32 = f1_32 << -ea;
  }
  else {
    f1_32 = f1_32 >> ea;
  }
  
  int eb = 23 - count_f2;
  
  if (eb < 0) {
    f2_32 = f2_32 << -eb;
  }
  else {
    f2_32 = f2_32 >> eb;
  }
  unsigned long f3_32;
  f3_32 = f1_32 * f2_32;
  int ec = ea + eb;
  printf("A Expanded: "); print32bits(f1_32); printf(" e1 = %i\n",
  ea);
  printf("B Expanded: "); print32bits(f2_32); printf(" e2 = %i\n",
  eb);
  printf("Product: "); print32bits(f3_32); printf(" e3 = %i\n",
  ec);
  unsigned long roll_over_mask = 0x00020000;
  int roll_over = 0;
  
  if ((f3_32 & roll_over_mask) != 0x0000000) {
    roll_over = 1;
  }
  f3_32 = f3_32 >> 9;
  f3_32 = f3_32 >> roll_over;
  ec += 4 + roll_over;
  theFloat = f3_32;
  
  std::bitset<8> binary(ec);
  unsigned char tem_e = static_cast<unsigned char>(binary.to_ulong());
  theFloat = theFloat & 0x7F;
  theFloat = theFloat | tem_e;
  
  printf("Packed Prod: "); print8bits(theFloat); printf("\n");
  return theFloat;
}
