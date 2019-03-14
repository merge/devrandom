/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of fpdt.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [FPDT]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "FPDT"    [Firmware Performance Data Table]
[004h 0004   4]                 Table Length : 00000064
[008h 0008   1]                     Revision : 01
[009h 0009   1]                     Checksum : ED
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000002


[024h 0036   2]                Subtable Type : 0000
[026h 0038   1]                       Length : 10
[027h 0039   1]                     Revision : 01
[028h 0040   4]                     Reserved : 00000000
[02Ch 0044   8]     FPDT Boot Record Address : 00000000D9E8A498

[034h 0052   2]                Subtable Type : 0001
[036h 0054   1]                       Length : 10
[037h 0055   1]                     Revision : 01
[038h 0056   4]                     Reserved : 00000000
[03Ch 0060   8]          S3PT Record Address : 00000000D9E8A418

[044h 0068   2]                Subtable Type : 3000
[046h 0070   1]                       Length : 10
[047h 0071   1]                     Revision : 01

**** Unknown FPDT subtable type 0x3000


[054h 0084   2]                Subtable Type : 3001
[056h 0086   1]                       Length : 10
[057h 0087   1]                     Revision : 01

**** Unknown FPDT subtable type 0x3001


Raw Table Data: Length 100 (0x64)

  0000: 46 50 44 54 64 00 00 00 01 ED 4C 45 4E 4F 56 4F  // FPDTd.....LENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 02 00 00 00 00 00 10 01 00 00 00 00 98 A4 E8 D9  // ................
  0030: 00 00 00 00 01 00 10 01 00 00 00 00 18 A4 E8 D9  // ................
  0040: 00 00 00 00 00 30 10 01 00 00 00 00 18 80 E8 D9  // .....0..........
  0050: 00 00 00 00 01 30 10 01 00 00 00 00 18 30 E2 D9  // .....0.......0..
  0060: 00 00 00 00                                      // ....
