//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-03
// PURPOSE: unit tests for the BH1750FVI_RT (GY-30) lux sensor library
//          https://github.com/RobTillaart/BH1750FVI_RT
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)

#include <ArduinoUnitTests.h>

#include "BH1750FVI.h"



unittest_setup()
{
}

unittest_teardown()
{
}

unittest(test_constructor)
{
  BH1750FVI myLux(0x23);

  myLux.setContHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setContHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setContLowRes();
  assertEqual(0, myLux.getMode());
  
  myLux.setOnceHigh2Res();
  assertEqual(2, myLux.getMode());
  myLux.setOnceHighRes();
  assertEqual(1, myLux.getMode());
  myLux.setOnceLowRes();
  assertEqual(0, myLux.getMode());

}


unittest(test_read)
{
  BH1750FVI myLux(0x23);

  assertEqual(0, myLux.getError());

  // TODO
  // float getRaw()
  // float getLux()
}



unittest(test_parameters)
{
  BH1750FVI myLux(0x23);

  // 0.45 .. 3.68
  myLux.setCorrectionFactor(3.14);
  assertEqual(3.14, myLux.getCorrectionFactor());

  // -89 - 89
  myLux.setAngle(30);
  assertEqual(30, myLux.getAngle());

  // 
  myLux.setTemperature(42);
  assertEqual(42, myLux.getTemperature());

  myLux.setCorrectionFactor(3.14);
  assertEqual(3.14, myLux.getCorrectionFactor());

  // 400 - 715
  myLux.setWaveLength(700);
  assertEqual(700, myLux.getWaveLength());
}

unittest_main()

// --------
