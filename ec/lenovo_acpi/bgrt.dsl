/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of bgrt.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [BGRT]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "BGRT"    [Boot Graphics Resource Table]
[004h 0004   4]                 Table Length : 00000038
[008h 0008   1]                     Revision : 00
[009h 0009   1]                     Checksum : EC
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000002

[024h 0036   2]                      Version : 0000
[026h 0038   1]                       Status : 01
[027h 0039   1]                   Image Type : 00
[028h 0040   8]                Image Address : 00000000D38C9018
[030h 0048   4]                Image OffsetX : 000002AF
[034h 0052   4]                Image OffsetY : 000000F0

Raw Table Data: Length 56 (0x38)

  0000: 42 47 52 54 38 00 00 00 00 EC 4C 45 4E 4F 56 4F  // BGRT8.....LENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 02 00 00 00 00 00 01 00 18 90 8C D3 00 00 00 00  // ................
  0030: AF 02 00 00 F0 00 00 00                          // ........
