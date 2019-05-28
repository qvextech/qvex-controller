/*
   Converter module is used to
   - map specific strip channels when using non-addressable led strips
   - calculate enhanced color
*/

#include "Converter.h"
#include "Settings.h"

ColorMessage Converter::convert(ColorMessage msg) {
  Serial.println("Converter: "+String(msg.type)+" -> "+String(STRIP_TYPE));
  switch (msg.type) {
    case 1: //SC msg
      switch (STRIP_TYPE)
      {
        case 1:
          return msg;
          break;
        default:
          Serial.println("Converter: invalid conversion from data type 1 to strip type " + String(STRIP_TYPE));
          break;
      }
      break;
    case 2: //CCT msg
      switch (STRIP_TYPE)
      {
        case 2:
          return msg;
          break;
        default:
          Serial.println("Converter: invalid conversion from data type 2 to strip type " + String(STRIP_TYPE));
          break;
      }
      break;
    case 3: //RGB msg
      switch (STRIP_TYPE)
      {
        case 3:
          return msg;
          break;
        case 4:
        case 14:
        {
          RGB white = {255, 170, 70};
          RGB rgb = {msg.r, msg.g, msg.b};
          RGBW color = getColorFromRGB(rgb, white);
          Serial.println("Converter: RGB " + String(msg.r) + " " + String(msg.g) + " " + String(msg.b) + " converted to RGBW " + String(color.r) + " " + String(color.g) + " " + String(color.b) + " " + String(color.w));
          msg.type = STRIP_TYPE; msg.r = color.r; msg.g = color.g; msg.b = color.b; msg.w = color.w;
          return msg;
          break;
        }
        case 5:
          msg.type = STRIP_TYPE; msg.w = 0; msg.ww = 0;
          return msg;
          break;
        default:
          Serial.println("Converter: invalid conversion from data type 3 to strip type " + String(STRIP_TYPE));
          break;
      }
      break;
    case 4: //RGBW msg
      switch (STRIP_TYPE)
      {
        case 4:
        case 14:
          return msg;
          break;
        default:
          Serial.println("Converter: invalid conversion from data type 4 to strip type " + String(STRIP_TYPE));
          break;
      }
      break;
    case 5: //WRGBWW msg
      switch (STRIP_TYPE)
      {
        case 5:
          return msg;
          break;
        default:
          Serial.println("Converter: invalid conversion from data type 5 to strip type " + String(STRIP_TYPE));
          break;
      }
      break;
  }
}

CHOUT Converter::mapChannels(ColorMessage msg)
{
  CHOUT chout;
  int strip = STRIP_TYPE;
  switch (strip)
  {
    case 1:
      chout.e = msg.w;
      break;
    case 2:
      chout.d = msg.w; chout.e = msg.ww;
      break;
    case 3:
      chout.c = msg.r; chout.d = msg.g; chout.e = msg.b;
      break;
    case 4:
      chout.b = msg.r; chout.c = msg.g; chout.d = msg.b; chout.e = msg.w;
      break;
    case 5:
      chout.a = msg.r; chout.b = msg.g; chout.c = msg.b; chout.d = msg.w; chout.e = msg.ww;
      break;
    default:
      Serial.println("Converter: Unknown strip type: "+String(strip));
      break;
  }
  return chout;
}

RGB Converter::rgbDiff(RGB one, RGB two)
{
  one.r = one.r - two.r;
  one.g = one.g - two.g;
  one.b = one.b - two.b;

  return one;
}

RGBW Converter::getColorFromRGB(RGB rgb, RGB target)
{
  RGBW result;
  int percentage = 100;
  int temp;
  RGB diff;
  int chDiff;

  // 1. poměrem změnit hodnotu bílý (target)
  if (rgb.r < target.r) percentage = (rgb.r * 100) / target.r;
  if (rgb.g < target.g) {
    temp = (rgb.g * 100) / target.g;
    if (temp < percentage) percentage = temp;
  }
  if (rgb.b < target.b) {
    temp = (rgb.b * 100) / target.b;
    if (temp < percentage) percentage = temp;
  }

  target.r = target.r * percentage / 100;
  target.g = target.g * percentage / 100;
  target.b = target.b * percentage / 100;

  result.w = percentage * 2.55;

  // 2. rozdíl požadované bílé
  diff = rgbDiff(rgb, target);

  // 4. Výsledek příčíst k rozdílu všech kanálů
  result.r = diff.r;
  result.g = diff.g;
  result.b = diff.b;

  return result;
}
