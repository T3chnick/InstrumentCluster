
const unsigned char  oil [] PROGMEM = { // oil , 62x21px
	0x03, 0x80, 0x1f, 0xfc, 0x00, 0x00, 0x07, 0x80, 0x07, 0xc0, 0x1f, 0xfc, 0x00, 0x00, 0x1f, 0xc0, 
	0x0e, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x7f, 0xe0, 0x1c, 0x70, 0x01, 0xc0, 0x00, 0x01, 0xfe, 0xf0, 
	0x38, 0x3f, 0xff, 0xff, 0xf8, 0x07, 0xfc, 0x70, 0x70, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xf8, 0x30, 
	0xe0, 0x0f, 0xff, 0xff, 0xfe, 0x7e, 0xf0, 0x00, 0xc0, 0x0e, 0x00, 0x00, 0x0f, 0xf9, 0xe0, 0x00, 
	0xc0, 0x0e, 0x00, 0x00, 0x07, 0xe3, 0xc0, 0x10, 0xe0, 0x0e, 0x00, 0x00, 0x03, 0x87, 0x80, 0x38, 
	0x70, 0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x38, 0x38, 0x0e, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x7c, 
	0x1c, 0x0e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x7c, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x7c, 
	0x07, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x38, 0x03, 0x8e, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 
	0x01, 0xce, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0xee, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 
	0x00, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
	0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00
  };


const unsigned char batt [] PROGMEM = { // 'batt icon', 32x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x0f, 0x80, 0x01, 0xf0, 0x0f, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 
  0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0xf8, 0x1f, 0xff, 0xf8, 0xf8, 
  0x1f, 0xff, 0xf8, 0xf8, 0x18, 0x03, 0xc0, 0x18, 0x18, 0x03, 0xc0, 0x18, 0x18, 0x03, 0xc0, 0x18, 
  0x1f, 0xff, 0xf8, 0xf8, 0x1f, 0xff, 0xf8, 0xf8, 0x1f, 0xff, 0xf8, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 
  0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };


const unsigned char temp [] PROGMEM = { // 'temp icon', 20x64px
  0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x03, 0xfc, 0x00, 0x07, 0x0e, 0x00, 0x06, 0x06, 0x00, 0x06, 
  0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 
  0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 
  0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 
  0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 
  0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 
  0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 
  0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 
  0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x06, 0x66, 0x00, 0x0e, 0x67, 0x00, 
  0x1c, 0x63, 0x80, 0x38, 0xf1, 0xc0, 0x31, 0xf8, 0xc0, 0x73, 0xfc, 0xe0, 0x67, 0xfe, 0x60, 0x67, 
  0xfe, 0x60, 0x67, 0xfe, 0x60, 0x67, 0xfe, 0x60, 0x73, 0xfc, 0xe0, 0x31, 0xf8, 0xc0, 0x38, 0xf1, 
  0xc0, 0x1c, 0x03, 0x80, 0x1e, 0x07, 0x80, 0x0f, 0xff, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00
  };