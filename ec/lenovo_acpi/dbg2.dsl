/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of dbg2.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [DBG2]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "DBG2"    [Debug Port table type 2]
[004h 0004   4]                 Table Length : 000000E9
[008h 0008   1]                     Revision : 00
[009h 0009   1]                     Checksum : C7
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000002

[024h 0036   4]                  Info Offset : 0000002C
[028h 0040   4]                   Info Count : 00000003

[02Ch 0044   1]                     Revision : 00
[02Dh 0045   2]                       Length : 0044
[02Fh 0047   1]               Register Count : 01
[030h 0048   2]              Namepath Length : 001E
[032h 0050   2]              Namepath Offset : 0026
[034h 0052   2]              OEM Data Length : 0000 [Optional field not present]
[036h 0054   2]              OEM Data Offset : 0000 [Optional field not present]
[038h 0056   2]                    Port Type : 8002
[03Ah 0058   2]                 Port Subtype : 0001
[03Ch 0060   2]                     Reserved : 0000
[03Eh 0062   2]          Base Address Offset : 0016
[040h 0064   2]          Address Size Offset : 0022

[042h 0066  12]        Base Address Register : [Generic Address Structure]
[042h 0066   1]                     Space ID : 00 [SystemMemory]
[043h 0067   1]                    Bit Width : 20
[044h 0068   1]                   Bit Offset : 00
[045h 0069   1]         Encoded Access Width : 00 [Undefined/Legacy]
[046h 0070   8]                      Address : 00000000F25390A0

[04Eh 0078   4]                 Address Size : 0000000C

[052h 0082  30]                     Namepath : "\_SB.PCI0.EHC1.URTH.URMH.PRT1"

[070h 0112   1]                     Revision : 00
[071h 0113   2]                       Length : 0044
[073h 0115   1]               Register Count : 01
[074h 0116   2]              Namepath Length : 001E
[076h 0118   2]              Namepath Offset : 0026
[078h 0120   2]              OEM Data Length : 0000 [Optional field not present]
[07Ah 0122   2]              OEM Data Offset : 0000 [Optional field not present]
[07Ch 0124   2]                    Port Type : 8002
[07Eh 0126   2]                 Port Subtype : 0001
[080h 0128   2]                     Reserved : 0000
[082h 0130   2]          Base Address Offset : 0016
[084h 0132   2]          Address Size Offset : 0022

[086h 0134  12]        Base Address Register : [Generic Address Structure]
[086h 0134   1]                     Space ID : 00 [SystemMemory]
[087h 0135   1]                    Bit Width : 20
[088h 0136   1]                   Bit Offset : 00
[089h 0137   1]         Encoded Access Width : 00 [Undefined/Legacy]
[08Ah 0138   8]                      Address : 00000000F253A0A0

[092h 0146   4]                 Address Size : 0000000C

[096h 0150  30]                     Namepath : "\_SB.PCI0.EHC2.URTH.URMH.PRT9"

[0B4h 0180   1]                     Revision : 00
[0B5h 0181   2]                       Length : 0035
[0B7h 0183   1]               Register Count : 01
[0B8h 0184   2]              Namepath Length : 000F
[0BAh 0186   2]              Namepath Offset : 0026
[0BCh 0188   2]              OEM Data Length : 0000 [Optional field not present]
[0BEh 0190   2]              OEM Data Offset : 0000 [Optional field not present]
[0C0h 0192   2]                    Port Type : 8003
[0C2h 0194   2]                 Port Subtype : 8086
[0C4h 0196   2]                     Reserved : 0000
[0C6h 0198   2]          Base Address Offset : 0016
[0C8h 0200   2]          Address Size Offset : 0022

[0CAh 0202  12]        Base Address Register : [Generic Address Structure]
[0CAh 0202   1]                     Space ID : 00 [SystemMemory]
[0CBh 0203   1]                    Bit Width : 20
[0CCh 0204   1]                   Bit Offset : 00
[0CDh 0205   1]         Encoded Access Width : 00 [Undefined/Legacy]
[0CEh 0206   8]                      Address : 00000000F2500000

[0D6h 0214   4]                 Address Size : 0000000C

[0DAh 0218  15]                     Namepath : "\_SB.PCI0.IGBE"

Raw Table Data: Length 233 (0xE9)

  0000: 44 42 47 32 E9 00 00 00 00 C7 4C 45 4E 4F 56 4F  // DBG2......LENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 02 00 00 00 2C 00 00 00 03 00 00 00 00 44 00 01  // ....,........D..
  0030: 1E 00 26 00 00 00 00 00 02 80 01 00 00 00 16 00  // ..&.............
  0040: 22 00 00 20 00 00 A0 90 53 F2 00 00 00 00 0C 00  // ".. ....S.......
  0050: 00 00 5C 5F 53 42 2E 50 43 49 30 2E 45 48 43 31  // ..\_SB.PCI0.EHC1
  0060: 2E 55 52 54 48 2E 55 52 4D 48 2E 50 52 54 31 00  // .URTH.URMH.PRT1.
  0070: 00 44 00 01 1E 00 26 00 00 00 00 00 02 80 01 00  // .D....&.........
  0080: 00 00 16 00 22 00 00 20 00 00 A0 A0 53 F2 00 00  // ....".. ....S...
  0090: 00 00 0C 00 00 00 5C 5F 53 42 2E 50 43 49 30 2E  // ......\_SB.PCI0.
  00A0: 45 48 43 32 2E 55 52 54 48 2E 55 52 4D 48 2E 50  // EHC2.URTH.URMH.P
  00B0: 52 54 39 00 00 35 00 01 0F 00 26 00 00 00 00 00  // RT9..5....&.....
  00C0: 03 80 86 80 00 00 16 00 22 00 00 20 00 00 00 00  // ........".. ....
  00D0: 50 F2 00 00 00 00 0C 00 00 00 5C 5F 53 42 2E 50  // P.........\_SB.P
  00E0: 43 49 30 2E 49 47 42 45 00                       // CI0.IGBE.
