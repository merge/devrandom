/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of ecdt.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [ECDT]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "ECDT"    [Embedded Controller Boot Resources Table]
[004h 0004   4]                 Table Length : 00000052
[008h 0008   1]                     Revision : 01
[009h 0009   1]                     Checksum : 51
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000002


[024h 0036  12]      Command/Status Register : [Generic Address Structure]
[024h 0036   1]                     Space ID : 01 [SystemIO]
[025h 0037   1]                    Bit Width : 08
[026h 0038   1]                   Bit Offset : 00
[027h 0039   1]         Encoded Access Width : 00 [Undefined/Legacy]
[028h 0040   8]                      Address : 0000000000000066

[030h 0048  12]                Data Register : [Generic Address Structure]
[030h 0048   1]                     Space ID : 01 [SystemIO]
[031h 0049   1]                    Bit Width : 08
[032h 0050   1]                   Bit Offset : 00
[033h 0051   1]         Encoded Access Width : 00 [Undefined/Legacy]
[034h 0052   8]                      Address : 0000000000000062

[03Ch 0060   4]                          UID : 00000000
[040h 0064   1]                   GPE Number : 11
[041h 0065  17]                     Namepath : "\_SB.PCI0.LPC.EC"

Raw Table Data: Length 82 (0x52)

  0000: 45 43 44 54 52 00 00 00 01 51 4C 45 4E 4F 56 4F  // ECDTR....QLENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 02 00 00 00 01 08 00 00 66 00 00 00 00 00 00 00  // ........f.......
  0030: 01 08 00 00 62 00 00 00 00 00 00 00 00 00 00 00  // ....b...........
  0040: 11 5C 5F 53 42 2E 50 43 49 30 2E 4C 50 43 2E 45  // .\_SB.PCI0.LPC.E
  0050: 43 00                                            // C.
