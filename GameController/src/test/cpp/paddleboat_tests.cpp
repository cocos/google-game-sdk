/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "../../main/cpp/GameControllerMappingUtils.h"
#include "paddleboat.h"

using namespace paddleboat;
using namespace std;

#define ARRAY_COUNTOF(array) (sizeof(array) / sizeof(array[0]))

// Validation failure test, improper ordering of vendorId
static const Paddleboat_Controller_Mapping_Data pbtest_invalidmap_vendorid[] = {
    {16,
     0,
     0x0010,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0020,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0018,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0030,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}}};

// Validation failure test, improper ordering of productId
static const Paddleboat_Controller_Mapping_Data pbtest_invalidmap_productid[] =
    {{16,
      0,
      0x0010,
      0x0002,
      PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
      {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
       /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* UP     */ 0,
       /* LEFT   */ 0,
       /* DOWN   */ 0,
       /* RIGHT  */ 0,
       /* A      */ 0,
       /* B      */ 0,
       /* X      */ 0,
       /* Y      */ 0,
       /* L1     */ 0,
       /* L2     */ 0,
       /* L3     */ 0,
       /* R1     */ 0,
       /* R2     */ 0,
       /* R3     */ 0,
       /* SELECT */ 0,
       /* START  */ 0,
       /* SYSTEM */ 0,
       /* TOUCHP */ 0,
       /* AUX1-4 */ 0, 0, 0, 0}},
     {16,
      0,
      0x0018,
      0x0002,
      PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
      {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
       /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* UP     */ 0,
       /* LEFT   */ 0,
       /* DOWN   */ 0,
       /* RIGHT  */ 0,
       /* A      */ 0,
       /* B      */ 0,
       /* X      */ 0,
       /* Y      */ 0,
       /* L1     */ 0,
       /* L2     */ 0,
       /* L3     */ 0,
       /* R1     */ 0,
       /* R2     */ 0,
       /* R3     */ 0,
       /* SELECT */ 0,
       /* START  */ 0,
       /* SYSTEM */ 0,
       /* TOUCHP */ 0,
       /* AUX1-4 */ 0, 0, 0, 0}},
     {16,
      0,
      0x0020,
      0x0002,
      PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
      {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
       /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* UP     */ 0,
       /* LEFT   */ 0,
       /* DOWN   */ 0,
       /* RIGHT  */ 0,
       /* A      */ 0,
       /* B      */ 0,
       /* X      */ 0,
       /* Y      */ 0,
       /* L1     */ 0,
       /* L2     */ 0,
       /* L3     */ 0,
       /* R1     */ 0,
       /* R2     */ 0,
       /* R3     */ 0,
       /* SELECT */ 0,
       /* START  */ 0,
       /* SYSTEM */ 0,
       /* TOUCHP */ 0,
       /* AUX1-4 */ 0, 0, 0, 0}},
     {16,
      0,
      0x0020,
      0x0001,
      PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
      {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
       /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* UP     */ 0,
       /* LEFT   */ 0,
       /* DOWN   */ 0,
       /* RIGHT  */ 0,
       /* A      */ 0,
       /* B      */ 0,
       /* X      */ 0,
       /* Y      */ 0,
       /* L1     */ 0,
       /* L2     */ 0,
       /* L3     */ 0,
       /* R1     */ 0,
       /* R2     */ 0,
       /* R3     */ 0,
       /* SELECT */ 0,
       /* START  */ 0,
       /* SYSTEM */ 0,
       /* TOUCHP */ 0,
       /* AUX1-4 */ 0, 0, 0, 0}},
     {16,
      0,
      0x0030,
      0x0002,
      PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
      {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
       /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
       /* L1 */ 0xFF,
       /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
       /* HY */ 0xFF},
      {/* UP     */ 0,
       /* LEFT   */ 0,
       /* DOWN   */ 0,
       /* RIGHT  */ 0,
       /* A      */ 0,
       /* B      */ 0,
       /* X      */ 0,
       /* Y      */ 0,
       /* L1     */ 0,
       /* L2     */ 0,
       /* L3     */ 0,
       /* R1     */ 0,
       /* R2     */ 0,
       /* R3     */ 0,
       /* SELECT */ 0,
       /* START  */ 0,
       /* SYSTEM */ 0,
       /* TOUCHP */ 0,
       /* AUX1-4 */ 0, 0, 0, 0}}};

// Validation failure test, improper ordering of api levels
static const Paddleboat_Controller_Mapping_Data pbtest_invalidmap_apilevel[] = {
    {16,
     0,
     0x0010,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0018,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {19,
     0,
     0x0020,
     0x0001,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0020,
     0x0001,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0030,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}}};

// Validation success test / find-insert tests baseline existing map
static const Paddleboat_Controller_Mapping_Data pbtest_validmap[] = {
    {16,
     0,
     0x0010,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0018,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0020,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {19,
     0,
     0x0020,
     0x0002,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0020,
     0x0004,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}},
    {16,
     0,
     0x0030,
     0x0001,
     PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
     {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
      /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
      /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF,
      /* HY */ 0xFF},
     {/* UP     */ 0,
      /* LEFT   */ 0,
      /* DOWN   */ 0,
      /* RIGHT  */ 0,
      /* A      */ 0,
      /* B      */ 0,
      /* X      */ 0,
      /* Y      */ 0,
      /* L1     */ 0,
      /* L2     */ 0,
      /* L3     */ 0,
      /* R1     */ 0,
      /* R2     */ 0,
      /* R3     */ 0,
      /* SELECT */ 0,
      /* START  */ 0,
      /* SYSTEM */ 0,
      /* TOUCHP */ 0,
      /* AUX1-4 */ 0, 0, 0, 0}}};

static const Paddleboat_Controller_Mapping_Data pbtest_add_entry1 = {
    16,
    0,
    0x0001,
    0x0001,
    PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
    {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0, /* L2 */ 0,
     /* R1 */ 0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
     /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF, /* L1 */ 0xFF,
     /* L2 */ 0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* UP     */ 0,
     /* LEFT   */ 0,
     /* DOWN   */ 0,
     /* RIGHT  */ 0,
     /* A      */ 0,
     /* B      */ 0,
     /* X      */ 0,
     /* Y      */ 0,
     /* L1     */ 0,
     /* L2     */ 0,
     /* L3     */ 0,
     /* R1     */ 0,
     /* R2     */ 0,
     /* R3     */ 0,
     /* SELECT */ 0,
     /* START  */ 0,
     /* SYSTEM */ 0,
     /* TOUCHP */ 0,
     /* AUX1-4 */ 0, 0, 0, 0}};

static const Paddleboat_Controller_Mapping_Data pbtest_add_entry2 = {
    16,
    0,
    0x0020,
    0x0010,
    PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
    {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0,
     /* L2 */ 0, /* R1 */
     0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
     /* L1 */ 0xFF, /* L2 */
     0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
     /* L1 */ 0xFF, /* L2 */
     0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* UP     */ 0,
     /* LEFT   */ 0,
     /* DOWN   */ 0,
     /* RIGHT  */ 0, /* A      */
     0,
     /* B      */ 0,
     /* X      */ 0,
     /* Y      */ 0,
     /* L1     */ 0,
     /* L2     */ 0,
     /* L3     */ 0, /* R1     */
     0,
     /* R2     */ 0,
     /* R3     */ 0,
     /* SELECT */ 0,
     /* START  */ 0,
     /* SYSTEM */ 0,
     /* TOUCHP */ 0,
     /* AUX1-4 */ 0,
     0,
     0,
     0}

};

static const Paddleboat_Controller_Mapping_Data pbtest_add_entry3 = {
    16,
    0,
    0x0040,
    0x0100,
    PADDLEBOAT_CONTROLLER_LAYOUT_STANDARD,
    {/* LX */ 0, /* LY */ 0, /* RX */ 0, /* RY */ 0, /* L1 */ 0,
     /* L2 */ 0, /* R1 */
     0, /* R2 */ 0, /* HX */ 0, /* HY */ 0},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
     /* L1 */ 0xFF, /* L2 */
     0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* LX */ 0xFF, /* LY */ 0xFF, /* RX */ 0xFF, /* RY */ 0xFF,
     /* L1 */ 0xFF, /* L2 */
     0xFF, /* R1 */ 0xFF, /* R2 */ 0xFF, /* HX */ 0xFF, /* HY */ 0xFF},
    {/* UP     */ 0,
     /* LEFT   */ 0,
     /* DOWN   */ 0,
     /* RIGHT  */ 0, /* A      */
     0,
     /* B      */ 0,
     /* X      */ 0,
     /* Y      */ 0,
     /* L1     */ 0,
     /* L2     */ 0,
     /* L3     */ 0, /* R1     */
     0,
     /* R2     */ 0,
     /* R3     */ 0,
     /* SELECT */ 0,
     /* START  */ 0,
     /* SYSTEM */ 0,
     /* TOUCHP */ 0,
     /* AUX1-4 */ 0,
     0,
     0,
     0}

};

#define TEST_MAPPING_TABLE_SIZE 256

static Paddleboat_Controller_Mapping_Data
    testMappingTable[TEST_MAPPING_TABLE_SIZE];

static void InitSearchFromExistingEntry(
    const Paddleboat_Controller_Mapping_Data *sourceEntry,
    MappingTableSearch &mapSearch) {
    mapSearch.initSearchParameters(sourceEntry->vendorId,
                                   sourceEntry->productId,
                                   sourceEntry->minimumEffectiveApiLevel,
                                   sourceEntry->maximumEffectiveApiLevel);
}

// Make sure NotEmpty works
TEST(PaddleboatTestNE, NotEmpty) {
    EXPECT_NE(sizeof(Paddleboat_Controller_Data), 0);
}

// Make sure Validity works
TEST(PaddleboatTestValidity, Validity) {
    const size_t pcd_size = sizeof(Paddleboat_Controller_Data);
    EXPECT_EQ(pcd_size, 80);
    EXPECT_NE(pcd_size, 0);
}

// Test validateMapTable catches improper vendorId ordering
TEST(PaddleboatValidateMapVendorId, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_invalidmap_vendorid));
    const Paddleboat_Controller_Mapping_Data *errorEntry =
        GameControllerMappingUtils::validateMapTable(pbtest_invalidmap_vendorid,
                                                     entryCount);
    EXPECT_NE(errorEntry, nullptr);
    EXPECT_EQ(errorEntry->vendorId, 0x0018);
}

// Test validateMapTable catches improper productId ordering
TEST(PaddleboatValidateMapProductId, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_invalidmap_productid));
    const Paddleboat_Controller_Mapping_Data *errorEntry =
        GameControllerMappingUtils::validateMapTable(
            pbtest_invalidmap_productid, entryCount);
    EXPECT_NE(errorEntry, nullptr);
    EXPECT_EQ(errorEntry->vendorId, 0x0020);
    EXPECT_EQ(errorEntry->productId, 0x0001);
}

// Test validateMapTable catches improper api level ordering
TEST(PaddleboatValidateMapApiLevel, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_invalidmap_apilevel));
    const Paddleboat_Controller_Mapping_Data *errorEntry =
        GameControllerMappingUtils::validateMapTable(pbtest_invalidmap_apilevel,
                                                     entryCount);
    EXPECT_NE(errorEntry, nullptr);
    EXPECT_EQ(errorEntry->vendorId, 0x0020);
    EXPECT_EQ(errorEntry->productId, 0x0001);
    EXPECT_EQ(errorEntry->minimumEffectiveApiLevel, 16);
}

// Test validateMapTable returns nullptr on a successful validation
TEST(PaddleboatValidateMapSuccess, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_validmap));
    const Paddleboat_Controller_Mapping_Data *errorEntry =
        GameControllerMappingUtils::validateMapTable(pbtest_validmap,
                                                     entryCount);
    EXPECT_EQ(errorEntry, nullptr);
}

// Test find functionality
TEST(PaddleboatValidateFindMapEntry, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_validmap));
    memcpy(testMappingTable, pbtest_validmap,
           entryCount * sizeof(Paddleboat_Controller_Mapping_Data));
    MappingTableSearch mapSearch(&testMappingTable[0], entryCount);

    // Should find a match for the first entry
    int32_t targetTableIndex = 0;
    InitSearchFromExistingEntry(&testMappingTable[targetTableIndex], mapSearch);
    bool foundEntry =
        GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, true);
    EXPECT_EQ(mapSearch.tableIndex, targetTableIndex);

    // Should find a match for the fourth entry
    targetTableIndex = 3;
    InitSearchFromExistingEntry(&testMappingTable[targetTableIndex], mapSearch);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, true);
    EXPECT_EQ(mapSearch.tableIndex, targetTableIndex);

    // Should fail to find a match and put insert point at the first entry
    // (unique productId/vendorId)
    mapSearch.initSearchParameters(0x1, 0x1, 16, 0);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, false);
    EXPECT_EQ(mapSearch.tableIndex, 0);

    // Should fail to find a match and put insert point at the third entry
    // (matching productId/new vendorId)
    mapSearch.initSearchParameters(0x20, 0x1, 16, 0);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, false);
    EXPECT_EQ(mapSearch.tableIndex, 2);

    // Should fail to find a match and put insert point at the fifth entry
    // (matching productId/vendorId, new apiLevel)
    mapSearch.initSearchParameters(0x20, 0x2, 22, 0);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, false);
    EXPECT_EQ(mapSearch.tableIndex, 4);

    // Should fail to find a match and put insert point at the sixth entry
    // (unique productId/vendorId)
    mapSearch.initSearchParameters(0x21, 0x1, 16, 0);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, false);
    EXPECT_EQ(mapSearch.tableIndex, 5);

    // Should fail to find a match and put the insert point at the end of the
    // table (unique productId/vendorId)
    mapSearch.initSearchParameters(0x40, 0x1, 16, 0);
    foundEntry = GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    EXPECT_EQ(foundEntry, false);
    EXPECT_EQ(mapSearch.tableIndex, entryCount);
}

// Test add functionality
TEST(PaddleboatValidateAddMapEntry, Validity) {
    const int32_t entryCount =
        static_cast<const int32_t>(ARRAY_COUNTOF(pbtest_validmap));
    memset(
        testMappingTable, 0,
        TEST_MAPPING_TABLE_SIZE * sizeof(Paddleboat_Controller_Mapping_Data));
    memcpy(testMappingTable, pbtest_validmap,
           entryCount * sizeof(Paddleboat_Controller_Mapping_Data));
    MappingTableSearch mapSearch(&testMappingTable[0], entryCount);

    InitSearchFromExistingEntry(&pbtest_add_entry1, mapSearch);
    GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    bool success = GameControllerMappingUtils::insertMapEntry(
        &pbtest_add_entry1, &mapSearch);
    EXPECT_EQ(success, true);
    EXPECT_EQ(testMappingTable[0].vendorId, pbtest_add_entry1.vendorId);
    EXPECT_EQ(testMappingTable[0].productId, pbtest_add_entry1.productId);
    EXPECT_EQ(testMappingTable[6].vendorId, 0x30);
    EXPECT_EQ(testMappingTable[6].productId, 0x1);

    // Reset table
    memset(
        testMappingTable, 0,
        TEST_MAPPING_TABLE_SIZE * sizeof(Paddleboat_Controller_Mapping_Data));
    memcpy(testMappingTable, pbtest_validmap,
           entryCount * sizeof(Paddleboat_Controller_Mapping_Data));
    mapSearch.tableEntryCount = entryCount;

    InitSearchFromExistingEntry(&pbtest_add_entry2, mapSearch);
    GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    success = GameControllerMappingUtils::insertMapEntry(&pbtest_add_entry2,
                                                         &mapSearch);
    EXPECT_EQ(success, true);
    EXPECT_EQ(testMappingTable[5].vendorId, pbtest_add_entry2.vendorId);
    EXPECT_EQ(testMappingTable[5].productId, pbtest_add_entry2.productId);
    EXPECT_EQ(testMappingTable[6].vendorId, 0x30);
    EXPECT_EQ(testMappingTable[6].productId, 0x1);

    // Reset table
    memset(
        testMappingTable, 0,
        TEST_MAPPING_TABLE_SIZE * sizeof(Paddleboat_Controller_Mapping_Data));
    memcpy(testMappingTable, pbtest_validmap,
           entryCount * sizeof(Paddleboat_Controller_Mapping_Data));
    mapSearch.tableEntryCount = entryCount;

    InitSearchFromExistingEntry(&pbtest_add_entry3, mapSearch);
    GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    success = GameControllerMappingUtils::insertMapEntry(&pbtest_add_entry3,
                                                         &mapSearch);
    EXPECT_EQ(success, true);
    EXPECT_EQ(testMappingTable[5].vendorId, 0x30);
    EXPECT_EQ(testMappingTable[5].productId, 0x1);
    EXPECT_EQ(testMappingTable[6].vendorId, pbtest_add_entry3.vendorId);
    EXPECT_EQ(testMappingTable[6].productId, pbtest_add_entry3.productId);

    // Reset table
    memset(
        testMappingTable, 0,
        TEST_MAPPING_TABLE_SIZE * sizeof(Paddleboat_Controller_Mapping_Data));
    memcpy(testMappingTable, pbtest_validmap,
           entryCount * sizeof(Paddleboat_Controller_Mapping_Data));
    mapSearch.tableEntryCount = entryCount;

    // Test failure on full table
    mapSearch.tableMaxEntryCount = entryCount;
    InitSearchFromExistingEntry(&pbtest_add_entry3, mapSearch);
    GameControllerMappingUtils::findMatchingMapEntry(&mapSearch);
    success = GameControllerMappingUtils::insertMapEntry(&pbtest_add_entry3,
                                                         &mapSearch);
    EXPECT_EQ(success, false);
}