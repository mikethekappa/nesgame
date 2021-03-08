
/*
A simple "hello world" example.
Set the screen background color and palette colors.
Then write a message to the nametable.
Finally, turn on the PPU to display video.
*/

#include "neslib.h"
#include "vrambuf.h"
#include "bcd.h"
#include "vrambuf.c"

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// main function, run after console reset
void main(void) {
  // set palette colors
  unsigned int x = 15;
  bool left = true;
  pal_col(0,0x19);	// set screen to dark blue
  pal_col(1,0x14);	// fuchsia
  pal_col(2,0x30);	// grey
  pal_col(3,0x30);	// white
  pal_col(17,0x05);
  pal_col(18,0x05);
  pal_col(19,0x02);

  // write text to name table
  vram_adr(NTADR_A(1,1));		// set address
  vram_write("This is", 7);// write bytes to video RAM
  vram_adr(NTADR_A(1,2));
  vram_write("John Gilliland's", 16);// write bytes to video RAM
  vram_adr(NTADR_A(1,3));
  vram_write("First Nes Game", 14);// write bytes to video RAM
  

  // enable PPU rendering (turn on screen)
  ppu_on_all();
  vrambuf_clear();
  set_vram_update(updbuf);
  // infinite loop
  while (1) {
    char cur_oam = 0;
    if(left){
      x-= 1;
      cur_oam = oam_spr(x, 100, 0x3f, 0x40, cur_oam);
      vrambuf_put(NTADR_A(1, 4), "On door", 7);
    }
    else{
      x+=1;
      cur_oam = oam_spr(x, 100, 0x3f, 0x0, cur_oam);
    }
    if (x < 8){
      left = false;
    }
    if (x > 238){
      left = true;
    }
    vrambuf_flush();
  }
}
