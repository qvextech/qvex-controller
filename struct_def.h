#ifndef struct_def
#define struct_def

struct RGB {
  byte r, g, b;
};

struct RGBW {
  byte r, g, b, w;
};

struct ColorMessage {
  byte type,r,g,b,w,ww;
  uint16_t t;
};

struct CHOUT {
  byte a, b, c, d, e;
  uint16_t t;
};

struct CH2B {
	uint16_t a,b,c,d,e;
};

#endif
