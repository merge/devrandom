/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of uefi2.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [UEFI]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "UEFI"    [UEFI Boot Optimization Table]
[004h 0004   4]                 Table Length : 000002A6
[008h 0008   1]                     Revision : 01
[009h 0009   1]                     Checksum : 40
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000002

[024h 0036  16]              UUID Identifier : 0D9FB197-CEFC-4E91-ACB1-2535D9E5A844
[034h 0052   2]                  Data Offset : 0036

Raw Table Data: Length 678 (0x2A6)

  0000: 55 45 46 49 A6 02 00 00 01 40 4C 45 4E 4F 56 4F  // UEFI.....@LENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 02 00 00 00 97 B1 9F 0D FC CE 91 4E AC B1 25 35  // ...........N..%5
  0030: D9 E5 A8 44 36 00 1F 00 00 00 42 00 00 00 43 00  // ...D6.....B...C.
  0040: 00 00 44 00 00 00 45 00 00 00 46 00 00 00 47 00  // ..D...E...F...G.
  0050: 00 00 48 00 00 00 49 00 00 00 4A 00 00 00 4B 00  // ..H...I...J...K.
  0060: 00 00 4D 00 00 00 51 00 00 00 F2 00 00 00 F1 00  // ..M...Q.........
  0070: 00 00 52 00 00 00 E9 00 00 00 01 00 00 00 02 00  // ..R.............
  0080: 00 00 AB 00 00 00 03 00 00 00 20 00 00 00 04 00  // .......... .....
  0090: 00 00 05 00 00 00 06 00 00 00 07 00 00 00 C1 00  // ................
  00A0: 00 00 08 00 00 00 09 00 00 00 0A 00 00 00 0B 00  // ................
  00B0: 00 00 0C 00 00 00 83 0C FA 0E D7 03 B9 44 9C 8D  // .............D..
  00C0: 6F 32 E6 3E C0 98 78 98 E4 93 55 AD FD 46 B6 16  // o2.>..x...U..F..
  00D0: 6C 4E 69 9A 6B 9E E9 79 FB C0 21 28 21 4C 9A BB  // lNi.k..y..!(!L..
  00E0: 9E 7E B2 CA 15 F4 39 12 2F CE 28 7D F2 43 B5 15  // .~....9./.(}.C..
  00F0: 5E 60 9F 10 06 0C B8 6E 83 9E 86 8A 60 4A 83 A9  // ^`.....n....`J..
  0100: D4 41 E9 6A 27 05 62 40 78 F8 BD 63 DE 44 AF 27  // .A.j'.b@x..c.D.'
  0110: F8 27 FD 67 89 06 C5 C0 04 AE 4C 4B 82 44 A3 53  // .'.g......LK.D.S
  0120: C1 38 2B 4A 08 48 ED 36 EC CA AE C7 D9 4E B5 E1  // .8+J.H.6.....N..
  0130: E3 4E 15 CB 8F 04 4A DF A9 58 EF FB C8 4D A3 9F  // .N....J..X...M..
  0140: 8D B6 BE 0F 83 70 1D B2 04 DC 15 5D 50 4D A2 D8  // .....p.....]PM..
  0150: 5D 1B 4F 82 AC 11 8F 0A 9E CA 15 F8 29 4A A7 16  // ].O.........)J..
  0160: EB AE 45 CA 63 6E 63 DB 4B CC A3 AD 42 48 BA 0C  // ..E.cnc.K...BH..
  0170: 50 58 AD 17 D3 D8 E2 36 F7 1B FC F4 39 4C 9E 9B  // PX.....6....9L..
  0180: CE A8 35 39 C3 1A 9C 9C C7 C4 09 9F 51 41 99 C4  // ..59........QA..
  0190: 53 A0 0A 4A 94 96 00 A8 63 EF 86 95 FB 42 84 AB  // S..J....c....B..
  01A0: EA 59 0B F1 41 AA 58 DC AF D8 22 6E F8 42 99 66  // .Y..A.X..."n.B.f
  01B0: 36 FF 78 8C 9C AF CF 73 D7 68 B2 FB DD 47 AC D1  // 6.x....s.h...G..
  01C0: 21 8E F9 19 A5 2C 5E 1D 9C 62 BD F6 52 4F 8A 5F  // !....,^..b..RO._
  01D0: 93 96 E7 28 9B EC C1 50 59 3F BA 9C 76 4E B2 AA  // ...(...PY?..vN..
  01E0: 83 4F DA 5E 07 C9 65 00 9B 59 30 86 71 4B B4 9C  // .O.^..e..Y0.qK..
  01F0: 0B 12 AF 56 07 80 66 73 5E 52 29 84 65 4B B1 77  // ...V..fs^R).eK.w
  0200: 3B 79 04 DD BF 85 05 9E E1 EE 9A 07 17 4D 8F 46  // ;y...........M.F
  0210: CF 81 12 60 DB 26 7F EE 45 D0 BE 98 EB 4F BD 30  // ...`.&..E....O.0
  0220: D6 76 37 7D CE F8 A9 0B 09 B4 66 D2 03 4E BE 37  // .v7}......f..N.7
  0230: AD BD BC 85 63 FD 25 51 B0 6D BB 88 8E 41 A4 BC  // ....c.%Q.m...A..
  0240: EF C4 17 4D 69 BC 38 B4 91 DA 47 8B 0A 4D AD 56  // ...Mi.8...G..M.V
  0250: C7 28 A9 4C 7F 58 9C 7C 96 6E 42 8E 65 48 9D 6C  // .(.L.X.|.nB.eH.l
  0260: 4F 80 05 2F 2C 0E C9 27 0D B0 DC CC 13 44 90 78  // O../,..'.....D.x
  0270: 14 88 A0 0C B6 FE EC 9A 91 B8 9C 93 4B 47 A9 18  // ............KG..
  0280: 29 9F B2 65 93 6C 8A 8C 3C 24 D0 BB A9 4A BE 17  // )..e.l..<$...J..
  0290: CF 9B 58 31 30 EC C7 76 9F 9B FA 28 2B 45 97 1F  // ..X10..v...(+E..
  02A0: C1 20 ED 9F 5E 99                                // . ..^.
