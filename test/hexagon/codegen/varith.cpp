#include <Halide.h>
#include "varith.h"
#include <stdio.h>
using namespace Halide;

// RUN: ./varith.out | FileCheck %s

int main(int argc, char **argv) {
  Target target;
  setupHexagonTarget(target, Target::HVX_64);
  commonTestSetup(target);

  /* Test variants of vector add */
  //CHECK: vadd(v{{[0-9]+}}.b,v{{[0-9]+}}.b)
  testAdd<int8_t>(target);
  //CHECK: vadd(v{{[0-9]+}}.b,v{{[0-9]+}}.b)
  testAdd<uint8_t>(target);
  //CHECK_DS: vadd(v{{[0-9]+}}.ub,v{{[0-9]+}}.ub):sat
  // This is not a saturating add?
  //testAdd<uint8_t>(target);

  //CHECK: vadd(v{{[0-9]+}}.h,v{{[0-9]+}}.h)
  testAdd<int16_t>(target);
  //CHECK: vadd(v{{[0-9]+}}.h,v{{[0-9]+}}.h)
  testAdd<uint16_t>(target);

  //CHECK: vadd(v{{[0-9]+}}.w,v{{[0-9]+}}.w)
  testAdd<int32_t>(target);
  //CHECK: vadd(v{{[0-9]+}}.w,v{{[0-9]+}}.w)
  testAdd<uint32_t>(target);
  // Commenting these two tests out until bug 20163 is fixed.

  //CHECK_DS: vadd(v{{[0-9]+}}:{{[0-9]+}}.b,v{{[0-9]+}}:{{[0-9]+}}.b)
  // This gets eaten by handleLargeVectors
  //testAddDouble<int8_t>(target);
  //CHECK_DS: vadd(v{{[0-9]+}}:{{[0-9]+}}.ub,v{{[0-9]+}}:{{[0-9]+}}.ub):sat
  // This is not a saturating add?
  //testAddDouble<uint8_t>(target);
  // Commenting these two tests out until bug 20163 is fixed.
  // //CHECK_PDB: vadd(v{{[0-9]+}}:{{[0-9]+}}.h,v{{[0-9]+}}:{{[0-9]+}}.h)
  // testAddDouble<int16_t>(target);
  // //CHECK_PDB: vadd(v{{[0-9]+}}:{{[0-9]+}}.uh,v{{[0-9]+}}:{{[0-9]+}}.uh):sat
  // testAddDouble<uint16_t>(target);

  //CHECK_DS: vadd(v{{[0-9]+}}:{{[0-9]+}}.w,v{{[0-9]+}}:{{[0-9]+}}.w)
  // This gets eaten by handleLargeVectors
  //testAddDouble<int32_t>(target);

  /* Test variants of vector sub */
  //CHECK: vsub(v{{[0-9]+}}.b,v{{[0-9]+}}.b)
  testSub<int8_t>(target);
  //CHECK: vsub(v{{[0-9]+}}.b,v{{[0-9]+}}.b)
  testSub<uint8_t>(target);

  //CHECK: vsub(v{{[0-9]+}}.h,v{{[0-9]+}}.h)
  testSub<int16_t>(target);
  //CHECK: vsub(v{{[0-9]+}}.h,v{{[0-9]+}}.h)
  testSub<uint16_t>(target);

  //CHECK: vsub(v{{[0-9]+}}.w,v{{[0-9]+}}.w)
  testSub<int32_t>(target);
  //CHECK: vsub(v{{[0-9]+}}.w,v{{[0-9]+}}.w)
  testSub<uint32_t>(target);

  //CHECK: vsub(v{{[0-9]+}}:{{[0-9]+}}.b,v{{[0-9]+}}:{{[0-9]+}}.b)
  testSubDouble<int8_t>(target);
  //CHECK_DS: vsub(v{{[0-9]+}}:{{[0-9]+}}.ub,v{{[0-9]+}}:{{[0-9]+}}.ub):sat
  // This is not a saturating subtract?
  //testSubDouble<uint8_t>(target);
  // Commenting these two tests out until bug 20163 is fixed.
  // //CHECK_PDB: vsub(v{{[0-9]+}}:{{[0-9]+}}.h,v{{[0-9]+}}:{{[0-9]+}}.h)
  // testSubDouble<int16_t>(target);
  // //CHECK_PDB: vsub(v{{[0-9]+}}:{{[0-9]+}}.uh,v{{[0-9]+}}:{{[0-9]+}}.uh):sat
  // testSubDouble<uint16_t>(target);

  //CHECK: vsub(v{{[0-9]+}}:{{[0-9]+}}.w,v{{[0-9]+}}:{{[0-9]+}}.w)
  testSubDouble<int32_t>(target);

  printf ("Done\n");

  return 0;
}
