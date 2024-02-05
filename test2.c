
/* Video IO Ports */

__sfr __at(0x70) VRAM_ADDR_L;
__sfr __at(0x71) VRAM_ADDR_H;
__sfr __at(0x72) VRAM_DATA_W;
__sfr __at(0x73) VRAM_DATA_R;
__sfr __at(0x74) VIDC_CTRL_W;
__sfr __at(0x75) VRAM_CRSR_L;
__sfr __at(0x76) VRAM_CRSR_H;
__sfr __at(0x77) VIDC_UNKNOWN;

#define CRSR    1 << 7
#define BLINK   1 << 6

#define CR_SZ0  0
#define CR_SZ1  1 << 4
#define CR_SZ2  2 << 4
#define CR_SZ3  3 << 4

#define INC_0   0
#define INC_1   1 << 2
#define INC_2   2 << 2
#define INC_3   3 << 2

#define DISP_EN 1 << 1
#define REVERSE 1 << 0



 #pragma constseg .apl
 const unsigned long header1 = 0x0101C181;
 const unsigned long header2 = 0x52420000;


void main () {
       __asm
       di
       __endasm;

       unsigned int max = 0x7fff; //32kb vram
       VIDC_CTRL_W = 0x83;
       VRAM_ADDR_L = 0;
       VRAM_ADDR_H = 0;
       for (unsigned int i = 0; i <= max; i++) {
          VRAM_DATA_W = 0x00;
       }
       
       //enable screen
       VIDC_CTRL_W = 0x81; //inc = 0   vram addr = vram addr + 1
       //VIDC_CTRL_W = 0x85; //inc = 1
       //VIDC_CTRL_W = 0x89; //inc = 2
       //VIDC_CTRL_W = 0x8D; //inc = 3

       //inc mode 0
       // VIDC_CTRL_W = (CRSR | BLINK | INC_0 | DISP_EN );
       //VIDC_CTRL_W = 0xC3;
       
       __asm
       ei
       __endasm;

       for(;;) {

        VIDC_CTRL_W = 0x81; //inc = 0 vram addr = vram addr + 1

       VRAM_ADDR_H = 0x00;
       VRAM_ADDR_L = 0x00;

       for(unsigned int j=0;j<0x7fff;j++) {
          VRAM_DATA_W = 0x00;
       }

       //enable screen
       // VIDC_CTRL_W = 0x81; //inc = 0 vram addr = vram addr + 1
        VIDC_CTRL_W = 0x85; //inc = 1      displays nothing?
       // VIDC_CTRL_W = 0x89; //inc = 2    displays nothing?
       // VIDC_CTRL_W = 0x8D; //inc = 3 ???


       VRAM_ADDR_H = 0x04;
       VRAM_ADDR_L = 0x9F;

       for(unsigned int j=0x1000;j<0x3fff;j++) {
          VRAM_DATA_W = 0xff;
       }

       VRAM_ADDR_H = 0x00;
       VRAM_ADDR_L = 0x00;
       VIDC_CTRL_W = 0x8D;

       VRAM_ADDR_H = 0x00;
       VRAM_ADDR_L = 0x00;
       VIDC_CTRL_W = 0x81;



       }
       //no return
}
