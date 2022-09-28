
#include "stdlib.h"
#include "stdio.h"

#include "CRC.h"


uint16_t calc_crc(uint8_t *b, uint8_t len)
{
  uint16_t crc;
  crc = 0xffff;
  while(len--) {
    crc = _crc_ccitt_update(crc, *b++);
  }
  return crc;
}



unsigned int _crc_ccitt_update (unsigned int crc, unsigned char data)
    {
        data ^= (unsigned char)(crc & 0xff);
        data ^= data << 4;

        return ((((unsigned int)data << 8) | (crc >> 8)) ^ (unsigned int)(data >> 4)
                ^ ((unsigned int)data << 3));
    }
