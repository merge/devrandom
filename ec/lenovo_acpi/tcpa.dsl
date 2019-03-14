/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of tcpa.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [TCPA]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "TCPA"    [Trusted Computing Platform Alliance table]
[004h 0004   4]                 Table Length : 00000032
[008h 0008   1]                     Revision : 02
[009h 0009   1]                     Checksum : F6
[00Ah 0010   6]                       Oem ID : "PTL"
[010h 0016   8]                 Oem Table ID : "LENOVO"
[018h 0024   4]                 Oem Revision : 06040000
[01Ch 0028   4]              Asl Compiler ID : "LNVO"
[020h 0032   4]        Asl Compiler Revision : 00000001

[024h 0036   2]               Platform Class : 0000
[026h 0038   4]         Min Event Log Length : 00010000
[02Ah 0042   8]            Event Log Address : 00000000DAF6D000

Raw Table Data: Length 50 (0x32)

  0000: 54 43 50 41 32 00 00 00 02 F6 50 54 4C 00 00 00  // TCPA2.....PTL...
  0010: 4C 45 4E 4F 56 4F 00 00 00 00 04 06 4C 4E 56 4F  // LENOVO......LNVO
  0020: 01 00 00 00 00 00 00 00 01 00 00 D0 F6 DA 00 00  // ................
  0030: 00 00                                            // ..
