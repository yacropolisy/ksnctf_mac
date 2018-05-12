//alphanumeric_opcodes_defines.h
#ifndef _alphanumeric_opcodes_defines_
  #define _alphanumeric_opcodes_defines_

  // ALPHA NUMERIC OPCODES

  #define XOR8_      "0" // xor a byte in memory with an 8 bit register
  #define XOR32_     "1" // xor 32 bits in memory with a 32 bit register
  #define XOR8_X_    "2" // xor an 8 bit register with a byte in memory
  #define XOR32_X_   "3" // xor a 32 bit register with 32 bits in memory
  #define XOR_AL_I_  "4" // xor the al register with a immediate byte
  #define XOR_EAX_I_ "5" // xor the eax register with a immediate 32 bit value
  #define SS         "6"
  #define AAA        "7"
  #define CMP8_      "8" // cmp a byte in memory with an 8 bit register
  #define CMP32_     "9" // xor 32 bits in memory with a 32 bit register

  #define INC_ECX   "A"
  #define INC_EDX   "B"
  #define INC_EBX   "C"
  #define INC_ESP   "D"
  #define INC_EBP   "E"
  #define INC_ESI   "F"
  #define INC_EDI   "G"

  #define DEC_EAX   "H"
  #define DEC_ECX   "I"
  #define DEC_EDX   "J"
  #define DEC_EBX   "K"
  #define DEC_ESP   "L"
  #define DEC_EBP   "M"
  #define DEC_ESI   "N"
  #define DEC_EDI   "O"

  #define PUSH_EAX  "P"
  #define PUSH_ECX  "Q"
  #define PUSH_EDX  "R"
  #define PUSH_EBX  "S"
  #define PUSH_ESP  "T"
  #define PUSH_EBP  "U"
  #define PUSH_ESI  "V"
  #define PUSH_EDI  "W"

  #define POP_EAX   "X"
  #define POP_ECX   "Y"
  #define POP_EDX   "Z"

  // 8 BIT ALPHA NUMERIC PARAMETERS
  #define DH_MEAX   "0"
  #define DH_MECX   "1"
  #define DH_MEDX   "2"
  #define DH_MEBX   "3"
  #define DH_MR_    "4"  // 2nd param. is 1 byte (a combination of two registers)
  #define DH_MI_    "5"  // 2nd param. is 32 bit immediate value
  #define DH_MESI   "6"
  #define DH_MEDI   "7"
  #define BH_MEAX   "8"
  #define BH_MECX   "9"

  #define AL_MECX_O8_  "A"
  #define AL_MEDX_O8_  "B"
  #define AL_MEBX_O8_  "C"
  #define AL_MESP_O8_  "D"
  #define AL_MEBP_O8_  "E"
  #define AL_MESI_O8_  "F"
  #define AL_MEDI_O8_  "G"

  #define CL_MEAX_O8_  "H"
  #define CL_MECX_O8_  "I"
  #define CL_MEDX_O8_  "J"
  #define CL_MEBX_O8_  "K"
  #define CL_MESP_O8_  "L"
  #define CL_MEBP_O8_  "M"
  #define CL_MESI_O8_  "N"
  #define CL_MEDI_O8_  "O"

  #define DL_MEAX_O8_  "P"
  #define DL_MECX_O8_  "Q"
  #define DL_MEDX_O8_  "R"
  #define DL_MEBX_O8_  "S"
  #define DL_MESP_O8_  "T"
  #define DL_MEBP_O8_  "U"
  #define DL_MESI_O8_  "V"
  #define DL_MEDI_O8_  "W"

  #define BL_MEAX_O8_  "X"
  #define BL_MECX_O8_  "Y"
  #define BL_MEDX_O8_  "Z"

  // 32 BIT ALPHA NUMERIC PARAMETERS

  #define ESI_MEAX "0"
  #define ESI_MECX "1"
  #define ESI_MEDX "2"
  #define ESI_MEBX "3"
  #define ESI_MR_  "4"  // 2nd param. is 1 byte (see below)
  #define ESI_MI_  "5"  // 2nd param. is 32 bit immediate value
  #define ESI_MESI "6"
  #define ESI_MEDI "7"
  #define EDI_MEAX "8"
  #define EDI_MECX "9"

  // all the following have a 1 byte second parameter containing an offset
  #define EAX_MECX_O8_  "A"
  #define EAX_MEDX_O8_  "B"
  #define EAX_MEBX_O8_  "C"
  #define EAX_MESP_O8_  "D"
  #define EAX_MEBP_O8_  "E"
  #define EAX_MESI_O8_  "F"
  #define EAX_MEDI_O8_  "G"

  #define ECX_MEAX_O8_  "H"
  #define ECX_MECX_O8_  "I"
  #define ECX_MEDX_O8_  "J"
  #define ECX_MEBX_O8_  "K"
  #define ECX_MESP_O8_  "L"
  #define ECX_MEBP_O8_  "M"
  #define ECX_MESI_O8_  "N"
  #define ECX_MEDI_O8_  "O"

  #define EDX_MEAX_O8_  "P"
  #define EDX_MECX_O8_  "Q"
  #define EDX_MEDX_O8_  "R"
  #define EDX_MEBX_O8_  "S"
  #define EDX_MESP_O8_  "T"
  #define EDX_MEBP_O8_  "U"
  #define EDX_MESI_O8_  "V"
  #define EDX_MEDI_O8_  "W"

  #define EBX_MEAX_O8_  "X"
  #define EBX_MECX_O8_  "Y"
  #define EBX_MEDX_O8_  "Z"

  // ALPHA NUMERIC SECOND PARAMETERS

  #define MEAXESI "0"
  #define MECXESI "1"
  #define MEDXESI "2"
  #define MEBXESI "3"
  #define MESPESI "4"
  #define MESI_I32_ "5"  // 3rd parameters is a 32 bit immediate value
  #define MESIESI "6"
  #define MEDIESI "7"
  #define MEAXEDI "8"
  #define MECXEDI "9"

  #define EAX_MECX_x2  "A"
  #define EAX_MEDX_x2  "B"
  #define EAX_MEBX_x2  "C"
  #define EAX_MESP_x2  "D"
  #define EAX_x2_I32_  "E"  // 3rd parameters is a 32 bit immediate value
  #define EAX_MESI_x2  "F"
  #define EAX_MEDI_x2  "G"

  #define ECX_MEAX_x2  "H"
  #define ECX_MECX_x2  "I"
  #define ECX_MEDX_x2  "J"
  #define ECX_MEBX_x2  "K"
  #define ECX_MESP_x2  "L"
  #define ECX_x2_I32_  "M"  // 3rd parameters is a 32 bit immediate value
  #define ECX_MESI_x2  "N"
  #define ECX_MEDI_x2  "O"

  #define EDX_MEAX_x2  "P"
  #define EDX_MECX_x2  "Q"
  #define EDX_MEDX_x2  "R"
  #define EDX_MEBX_x2  "S"
  #define EDX_MESP_x2  "T"
  #define EDX_x2_I32_  "U"  // 3rd parameters is a 32 bit immediate value
  #define EDX_MESI_x2  "V"
  #define EDX_MEDI_x2  "W"

  #define EBX_MEAX_x2  "X"
  #define EBX_MECX_x2  "Y"
  #define EBX_MEDX_x2  "Z"
#endif
