/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembly of slic.dat, Thu Mar 14 15:14:21 2019
 *
 * ACPI Data Table [SLIC]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 0000   4]                    Signature : "SLIC"    [Software Licensing Description Table]
[004h 0004   4]                 Table Length : 00000176
[008h 0008   1]                     Revision : 01
[009h 0009   1]                     Checksum : 6F
[00Ah 0010   6]                       Oem ID : "LENOVO"
[010h 0016   8]                 Oem Table ID : "TP-G2   "
[018h 0024   4]                 Oem Revision : 00002550
[01Ch 0028   4]              Asl Compiler ID : "PTL "
[020h 0032   4]        Asl Compiler Revision : 00000001

[024h 0036 338] Software Licensing Structure : \
    00 00 00 00 9C 00 00 00 06 02 00 00 00 24 00 00 \
    52 53 41 31 00 04 00 00 01 00 01 00 69 16 4A 9F \
    B1 4B 3A FB 80 20 AA AF C4 F9 3E C1 80 49 EE 6A \
    65 26 72 1E CD BF 5F 2F 96 D6 C0 0A 92 F5 06 B5 \
    00 B2 3B 29 02 E2 4C 8D C2 F2 BC 41 77 9C 70 F0 \
    F3 1B 09 D2 63 5A DC A8 83 F8 5E C9 15 95 F9 FA \
    FD DC 05 B7 4D 67 7F 2D B3 84 33 20 E1 D1 79 2A \
    A7 6A 77 D1 B6 20 2A 76 42 C5 D5 E9 B6 43 40 55 \
    44 C3 C9 37 99 5F 41 97 70 F3 D1 F6 07 EC 7B 1A \
    29 A1 C1 F1 91 FD 48 86 6E 3E CE CB 01 00 00 00 \
    B6 00 00 00 00 00 02 00 4C 45 4E 4F 56 4F 54 50 \
    2D 47 32 20 20 20 57 49 4E 44 4F 57 53 20 01 00 \
    02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
    00 00 71 C8 5A 3A 03 F6 43 06 26 CE B3 7C 04 21 \
    76 BA A3 79 1F 85 8C 96 94 0A 74 BE BB A4 B8 35 \
    CA FB EB CA 42 2E AF 9B 7F 62 AD C9 AB 2B 59 33 \
    00 CA 3F 17 B4 5D F9 C9 36 38 BC 60 5D C2 CA 84 \
    4A 9B 79 5C ED AD EC B9 93 76 8B 03 4A 29 6D 09 \
    29 8B FF C9 E4 AA 37 FA A4 42 57 B7 88 2E E1 6E \
    88 4D DC AB 1A E1 4C 26 F7 87 09 24 32 06 86 F6 \
    5F 9B 9A 0B 3C 32 A0 EB E8 C6 4C F6 B2 8D C3 65 \
    27 23 

Raw Table Data: Length 374 (0x176)

  0000: 53 4C 49 43 76 01 00 00 01 6F 4C 45 4E 4F 56 4F  // SLICv....oLENOVO
  0010: 54 50 2D 47 32 20 20 20 50 25 00 00 50 54 4C 20  // TP-G2   P%..PTL 
  0020: 01 00 00 00 00 00 00 00 9C 00 00 00 06 02 00 00  // ................
  0030: 00 24 00 00 52 53 41 31 00 04 00 00 01 00 01 00  // .$..RSA1........
  0040: 69 16 4A 9F B1 4B 3A FB 80 20 AA AF C4 F9 3E C1  // i.J..K:.. ....>.
  0050: 80 49 EE 6A 65 26 72 1E CD BF 5F 2F 96 D6 C0 0A  // .I.je&r..._/....
  0060: 92 F5 06 B5 00 B2 3B 29 02 E2 4C 8D C2 F2 BC 41  // ......;)..L....A
  0070: 77 9C 70 F0 F3 1B 09 D2 63 5A DC A8 83 F8 5E C9  // w.p.....cZ....^.
  0080: 15 95 F9 FA FD DC 05 B7 4D 67 7F 2D B3 84 33 20  // ........Mg.-..3 
  0090: E1 D1 79 2A A7 6A 77 D1 B6 20 2A 76 42 C5 D5 E9  // ..y*.jw.. *vB...
  00A0: B6 43 40 55 44 C3 C9 37 99 5F 41 97 70 F3 D1 F6  // .C@UD..7._A.p...
  00B0: 07 EC 7B 1A 29 A1 C1 F1 91 FD 48 86 6E 3E CE CB  // ..{.).....H.n>..
  00C0: 01 00 00 00 B6 00 00 00 00 00 02 00 4C 45 4E 4F  // ............LENO
  00D0: 56 4F 54 50 2D 47 32 20 20 20 57 49 4E 44 4F 57  // VOTP-G2   WINDOW
  00E0: 53 20 01 00 02 00 00 00 00 00 00 00 00 00 00 00  // S ..............
  00F0: 00 00 00 00 00 00 71 C8 5A 3A 03 F6 43 06 26 CE  // ......q.Z:..C.&.
  0100: B3 7C 04 21 76 BA A3 79 1F 85 8C 96 94 0A 74 BE  // .|.!v..y......t.
  0110: BB A4 B8 35 CA FB EB CA 42 2E AF 9B 7F 62 AD C9  // ...5....B....b..
  0120: AB 2B 59 33 00 CA 3F 17 B4 5D F9 C9 36 38 BC 60  // .+Y3..?..]..68.`
  0130: 5D C2 CA 84 4A 9B 79 5C ED AD EC B9 93 76 8B 03  // ]...J.y\.....v..
  0140: 4A 29 6D 09 29 8B FF C9 E4 AA 37 FA A4 42 57 B7  // J)m.).....7..BW.
  0150: 88 2E E1 6E 88 4D DC AB 1A E1 4C 26 F7 87 09 24  // ...n.M....L&...$
  0160: 32 06 86 F6 5F 9B 9A 0B 3C 32 A0 EB E8 C6 4C F6  // 2..._...<2....L.
  0170: B2 8D C3 65 27 23                                // ...e'#
