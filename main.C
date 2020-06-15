#include <iostream>
#include <fstream>
#include <assert.h>
#include "Tools.h"

void buildLongTests();
void getByteTests();
void getBitsTests();
void setBitsTests();
void clearBitsTests();
void copyBitsTests();
void setByteTests();
void signTests();
void addOverflowTests();
void subOverflowTests();

/* If you implement the Tools in an order different from 
 * how the tests are performed, you can reorder the tests.
 * The assert will stop execution at the first assert that
 * fails and report the line number of the failed assert.
*/
int main(int argc, char * argv[])
{
   buildLongTests();
   std::cout << "buildLong tests pass.\n";
   getByteTests();
   std::cout << "getByte tests pass.\n";
   getBitsTests();
   std::cout << "getBits tests pass.\n";
   setBitsTests();
   std::cout << "setBits tests pass.\n";
   clearBitsTests();
   std::cout << "clearBits tests pass.\n";
   copyBitsTests();
   std::cout << "copyBits tests pass.\n";
   setByteTests();
   std::cout << "setByte tests pass.\n";
   signTests();
   std::cout << "sign tests pass.\n";
   addOverflowTests();
   std::cout << "addOverflow tests pass.\n";
   subOverflowTests();
   std::cout << "subOverflow tests pass.\n";

   std::cout << "\nCongratulations!  All tests have passed.\n\n";
}

/** 
 * tests the buildLong method in the Tools class.
 *
 * buildLong takes an array of unsigned chars (uint8_t)
 * and returns an unsigned long (uint64_t) built from
 * the bytes in the array ordering such that the low
 * order byte is the 0th element of the array 
 * uint64_t Tools::buildLong(uint8_t bytes[LONGSIZE]);
*/
void buildLongTests()
{
   uint8_t bytes1[LONGSIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
   assert(Tools::buildLong(bytes1) == 0x8877665544332211);

   uint8_t bytes2[LONGSIZE] = {0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
   assert(Tools::buildLong(bytes2) == 0x1122334455667788);

   uint8_t bytes3[LONGSIZE] = {0x78, 0x67, 0x56, 0x45, 0x34, 0x23, 0x12, 0x01};
   assert(Tools::buildLong(bytes3) == 0x0112233445566778);

   uint8_t bytes4[LONGSIZE] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
   assert(Tools::buildLong(bytes4) == 0x0102030405060708);

   uint8_t bytes5[LONGSIZE] = {0x80, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10};
   assert(Tools::buildLong(bytes5) == 0x1020304050607080);

   uint8_t bytes6[LONGSIZE] = {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff};
   assert(Tools::buildLong(bytes6) == 0xffffffff00000000);

   uint8_t bytes7[LONGSIZE] = {0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00};
   assert(Tools::buildLong(bytes7) == 0x00000000ffffffff);
}

/**
 * tests the getByte method in the Tools class
 *
 * getByte takes an uint64_t as input that is the source 
 * and an int32_t containing a byte number in the range 0 to 7.
 * getByte returns the numbered byte from the source. If the byte number
 * is out of range, getByte returns 0.
 * uint64_t Tools::getByte(uint64_t ul, int32_t byteNum);
*/
void getByteTests()
{
   /* getByte tests */
   assert(Tools::getByte(0x8877665544332211, 0) == 0x11);
   assert(Tools::getByte(0x8877665544332211, 1) == 0x22);
   assert(Tools::getByte(0x8877665544332211, 2) == 0x33);
   assert(Tools::getByte(0x8877665544332211, 3) == 0x44);
   assert(Tools::getByte(0x8877665544332211, 4) == 0x55);
   assert(Tools::getByte(0x8877665544332211, 5) == 0x66);
   assert(Tools::getByte(0x8877665544332211, 6) == 0x77);
   assert(Tools::getByte(0x8877665544332211, 7) == 0x88);
   assert(Tools::getByte(0x1234567821436587, 0) == 0x87);
   assert(Tools::getByte(0x1234567821436587, 1) == 0x65);
   assert(Tools::getByte(0x1234567821436587, 2) == 0x43);
   assert(Tools::getByte(0x1234567821436587, 3) == 0x21);
   assert(Tools::getByte(0x1234567821436587, 4) == 0x78);
   assert(Tools::getByte(0x1234567821436587, 5) == 0x56);
   assert(Tools::getByte(0x1234567821436587, 6) == 0x34);
   assert(Tools::getByte(0x1234567821436587, 7) == 0x12);
   assert(Tools::getByte(0x1234567821436587, 8) == 0x00);
   assert(Tools::getByte(0x1234567821436587, -1) == 0x00);
   assert(Tools::getByte(0x1234567821436587, 0x7fffffff) == 0x00);
   assert(Tools::getByte(0x1234567821436587, 9) == 0x00);
   assert(Tools::getByte(0x1234567821436587, 10) == 0x00);
}

/**
 * tests the getBits method in the Tools class
 *
 * getBits accepts as input an uint64_t and two ints that
 * indicate a range of bits to grab andreturns the bits
 * low through * high of the uint64_t.  bit 0 is the low order bit
 * and bit 63 is the high order bit. returns 0 if the low or 
 * high bit numbers are out of range
 * uint64_t Tools::getBits(uint64_t source, int32_t low, int32_t high);
*/
void getBitsTests()
{
   assert(Tools::getBits(0x1122334455667788, 0, 7) == 0x88);
   assert(Tools::getBits(0x1122334455667788, 8, 0xf) == 0x77);
   assert(Tools::getBits(0x1122334455667788, 0x10, 0x17) == 0x66);
   assert(Tools::getBits(0x1122334455667788, 0x18, 0x1f) == 0x55);
   assert(Tools::getBits(0x1122334455667788, 0x20, 0x27) == 0x44);
   assert(Tools::getBits(0x1122334455667788, 0x28, 0x2f) == 0x33);
   assert(Tools::getBits(0x1122334455667788, 0x30, 0x37) == 0x22);
   assert(Tools::getBits(0x1122334455667788, 0x38, 0x3f) == 0x11);
   assert(Tools::getBits(0x1122334455667788, 0, 0x3f) == 0x1122334455667788);
   assert(Tools::getBits(0x1122334455667788, 0x3f, 0) == 0);
   assert(Tools::getBits(0xffffffffffffffff, 0x3f, 0x3f) == 1);
   assert(Tools::getBits(0x8000000000000001, 0, 0) == 1);
   assert(Tools::getBits(0x700000000000000e, 0, 0) == 0);
   assert(Tools::getBits(0x700000000000000e, 0x3f, 0x3f) == 0);
}

/**
 * tests the setBits method in the Tools class
 *
 * setBits sets the bits of source in the range specified by the low and high
 * parameters to 1 and returns that value. returns source if the low or high
 * bit numbers are out of range
 * uint64_t Tools::setBits(uint64_t source, int32_t low, int32_t high)
*/
void setBitsTests()
{
   assert(Tools::setBits(0x1122334455667788, 0, 7) == 0x11223344556677ff);
   assert(Tools::setBits(0x1122334455667788, 8, 0xf) ==  0x112233445566ff88);
   assert(Tools::setBits(0x1122334455667788, 0x10, 0x17) == 0x1122334455ff7788);
   assert(Tools::setBits(0x1122334455667788, 0x18, 0x1f) == 0x11223344ff667788);
   assert(Tools::setBits(0x1122334455667788, 0x20, 0x27)== 0x112233ff55667788);
   assert(Tools::setBits(0x1122334455667788, 0x28, 0x2f) == 0x1122ff4455667788);
   assert(Tools::setBits(0x1122334455667788, 0x30, 0x37) == 0x11ff334455667788);
   assert(Tools::setBits(0x1122334455667788, 0x38, 0x3f) == 0xff22334455667788);
   assert(Tools::setBits(0x1122334455667788, 0, 0x3f) == 0xffffffffffffffff);
   assert(Tools::setBits(0x1122334455667788, 0x3f, 0) == 0x1122334455667788);
   assert(Tools::setBits(0x7fffffffffffffff, 0x3f, 0x3f) ==  0xffffffffffffffff);
   assert(Tools::setBits(0xfffffffffffffffe, 0, 0) == 0xffffffffffffffff);
   assert(Tools::setBits(0x0000000000000001, 0x3f, 0x3f) == 0x8000000000000001);
   assert(Tools::setBits(0x8000000000000001, 0x3f, 0x3f) == 0x8000000000000001);
   assert(Tools::setBits(0x8000000000000000, 0, 0) == 0x8000000000000001);
   assert(Tools::setBits(0x8000000000000001, 0, 0) == 0x8000000000000001);
   assert(Tools::setBits(0x8000000000000001, 2, 3) == 0x800000000000000d);
}

/**
 * tests the clearBits method in the Tools class
 *
 * clearBits sets the bits of source in the range low
 * to high to 0 (clears them) and returns that value. 
 * returns source if the low or high
 * bit numbers are out of range
 * uint64_t Tools::clearBits(uint64_t source, int32_t low, int32_t high)
*/
void clearBitsTests()
{
   assert(Tools::clearBits(0x1122334455667788, 0, 7) ==  0x1122334455667700);
   assert(Tools::clearBits(0x1122334455667788, 4, 7) ==  0x1122334455667708);
   assert(Tools::clearBits(0x1122334455667788, 8, 0xf) == 0x1122334455660088);
   assert(Tools::clearBits(0x1122334455667788, 0x10, 0x13) == 0x1122334455607788);
   assert(Tools::clearBits(0x1122334455667789, 0, 0) ==   0x1122334455667788);
   assert(Tools::clearBits(0x9122334455667788, 0x3f, 0x3f) == 0x1122334455667788);
   assert(Tools::clearBits(0x1122334455667788, 0x30, 0x3f) == 0x0000334455667788);
   assert(Tools::clearBits(0x1122334455667788, 0x40, 0x3f) == 0x1122334455667788);
   assert(Tools::clearBits(0x1122334455667788, 0x30, 0x40) == 0x1122334455667788);
}

/**
 * tests the copyBits method in the Tools class
 *
 * copyBits copies length bits from the source to a destination and returns the
 * modified destination. If low bit number of the source or
 * dest is out of range or the calculated source or dest high bit
 * number is out of range, then the unmodified destination is returned.
 * uint64_t Tools::copyBits(uint64_t source, uint64_t dest,
 *                          int32_t srclow, int32_t dstlow, int32_t length)
*/
void copyBitsTests()
{
   assert(Tools::copyBits(0x1122334455667788, 0x8877665544332211, 0, 0, 8)
          == 0x8877665544332288);
   assert(Tools::copyBits(0x1122334455667788, 0x8877665544332211, 0, 8, 8)
          == 0x8877665544338811);
   assert(Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 4, 4)
          == 0x8877665544332271);
   assert(Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x3f, 1)
          == 0x9877665544332211);
   assert(Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x40, 1)
          == 0x1877665544332211);
   assert(Tools::copyBits(0x1122334455667788, 0x1877665544332211, 0xfffffffe, 
          0x3f, 1) ==  0x1877665544332211);
   assert(Tools::copyBits(0x1122334455667788, 0x1877665544332211, 3, 0x3f, 2)
          == 0x1877665544332211);
   assert(Tools::copyBits(0x1122334455667788, 0x8877665544332211, 8, 8, 0x10)
          == 0x8877665544667711);
}

/**
 * tests the setByte method in the Tools class
 *
 * setByte sets the bits of source identfied by the byte number to 1 and
 * returns that value. if the byte number is out of range then source
 * is returned unchanged.
 * uint64_t Tools::setByte(uint64_t source, int32_t byteNum)
*/
void setByteTests()
{
   assert(Tools::setByte(0x1122334455667788, 0) == 0x11223344556677ff);
   assert(Tools::setByte(0x1122334455667788, 1) == 0x112233445566ff88);
   assert(Tools::setByte(0x1122334455667788, 2) == 0x1122334455ff7788);
   assert(Tools::setByte(0x1122334455667788, 3) == 0x11223344ff667788);
   assert(Tools::setByte(0x1122334455667788, 4) == 0x112233ff55667788);
   assert(Tools::setByte(0x1122334455667788, 5) == 0x1122ff4455667788);
   assert(Tools::setByte(0x1122334455667788, 6) == 0x11ff334455667788);
   assert(Tools::setByte(0x1122334455667788, 7) == 0xff22334455667788);
   assert(Tools::setByte(0x1122334455667788, 8) == 0x1122334455667788);
   assert(Tools::setByte(0x1122334455667788, -1) == 0x1122334455667788);
   assert(Tools::setByte(0x1122334455667788, -2) == 0x1122334455667788);
   assert(Tools::setByte(0x0000000000000000, 7) == 0xff00000000000000);
   assert(Tools::setByte(0x0000000000000000, 6) == 0x00ff000000000000);
   assert(Tools::setByte(0x0000000000000000, 5) == 0x0000ff0000000000);
   assert(Tools::setByte(0x0000000000000000, 4) == 0x000000ff00000000);
   assert(Tools::setByte(0x0000000000000000, 3) == 0x00000000ff000000);
   assert(Tools::setByte(0x0000000000000000, 2) == 0x0000000000ff0000);
   assert(Tools::setByte(0x0000000000000000, 1) == 0x000000000000ff00);
   assert(Tools::setByte(0x0000000000000000, 0) == 0x00000000000000ff);
   assert(Tools::setByte(0x0000000000000000, 8) == 0x0000000000000000);
   assert(Tools::setByte(0x0000000000000000, -1) == 0x0000000000000000);
   assert(Tools::setByte(0x0023000000000000, -2) == 0x0023000000000000);
   assert(Tools::setByte(0x0023000000000000, 0x7fffffff) == 0x0023000000000000);
}

/**
 * tests the sign method in the Tools class
 *
 * sign assumes source contains a 64 bit two's complement value and
 * returns the sign (1 or 0)
 * uint8_t Tools::sign(uint64_t source)
*/
void signTests()
{
   assert(Tools::sign(0x1122334455667788) == 0);
   assert(Tools::sign(0x8877665544332211) == 1);
   assert(Tools::sign(0x0000000000000000) == 0);
   assert(Tools::sign(0x1111111111111111) == 0);
   assert(Tools::sign(0xffffffffffffffff) == 1);
}

/**
 * tests the addOverflow method in the Tools class
 *
 * addOverflow assumes that op1 and op2 contain 64 bit two's 
 * complement values and returns true if an overflow would 
 * occur if they are summed and false otherwise
 * bool Tools::addOverflow(uint64_t op1, uint64_t op2)
*/
void addOverflowTests()
{
   assert(Tools::addOverflow(0xffffffffffffffff, 0xffffffffffffffff) == false);
   assert(Tools::addOverflow(0x8000000000000000, 0x8000000000000000) == true);

/* 
 *    Add four more tests.  You need to replace N, M, R, and S. 
 *    See lab directions. 
 */

/*
   assert(Tools::addOverflow(1, N) == true);
   assert(Tools::addOverflow(1, M) == false);
   assert(Tools::addOverflow(-1, R) == true);
   assert(Tools::addOverflow(-1, S) == false);
*/
}

/**
 * tests the subOverflow method in the Tools class
 *
 * subOverflow assumes that op1 and op2 contain 64 bit two's 
 * complement values and returns true if an overflow would occur 
 * from op2 - op1 and false otherwise
 * bool Tools::subOverflow(uint64_t op1, uint64_t op2)
*/
void subOverflowTests()
{
   assert(Tools::subOverflow(0xffffffffffffffff, 0xffffffffffffffff) == false);
   assert(Tools::subOverflow(0x0000000000000004, 0x8000000000000003) == true);

/* 
 *    Add four more tests.  You need to replace N, M, R, and S. 
 *    See lab directions. 
 */
/*
   assert(Tools::subOverflow(N, 1) == true);
   assert(Tools::subOverflow(M, 1) == false);
   assert(Tools::subOverflow(R, -2) == true);
   assert(Tools::subOverflow(S, -2) == false);
*/
}
