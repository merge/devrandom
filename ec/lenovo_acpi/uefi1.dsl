/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of uefi1.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [UEFI]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "UEFI"    [UEFI Boot Optimization Table]
[004h 0004   4]                 Table Length : 00000042
[008h 0008   1]                     Revision : 01
[009h 0009   1]                     Checksum : FA
[00Ah 0010   6]                       Oem ID : "PTL   "
[010h 0016   8]                 Oem Table ID : "COMBUF"
[018h 0024   4]                 Oem Revision : 00000001
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000001

[024h 0036  16]              UUID Identifier : 15E896BE-0CDF-47E2-9B97-A28A398BC765
[034h 0052   2]                  Data Offset : 0036

Raw Table Data: Length 66 (0x42)

  0000: 55 45 46 49 42 00 00 00 01 FA 50 54 4C 20 20 20  // UEFIB.....PTL   
  0010: 43 4F 4D 42 55 46 00 00 01 00 00 00 50 54 4C 20  // COMBUF......PTL 
  0020: 01 00 00 00 BE 96 E8 15 DF 0C E2 47 9B 97 A2 8A  // ...........G....
  0030: 39 8B C7 65 36 00 02 00 00 00 A8 76 9D D6 00 00  // 9..e6......v....
  0040: 00 00                                            // ..
