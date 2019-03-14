/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of ssdt4.dat, Thu Mar 14 15:14:21 2019
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x000007A8 (1960)
 *     Revision         0x01
 *     Checksum         0x7B
 *     OEM ID           "LENOVO"
 *     OEM Table ID     "SataAhci"
 *     OEM Revision     0x00001000 (4096)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20061109 (537268489)
 */
DefinitionBlock ("", "SSDT", 1, "LENOVO", "SataAhci", 0x00001000)
{
    /*
     * iASL Warning: There were 2 external control methods found during
     * disassembly, but only 0 were resolved (2 unresolved). Additional
     * ACPI tables may be required to properly disassemble the code. This
     * resulting disassembler output file may not compile because the
     * disassembler did not know how many arguments to assign to the
     * unresolved methods. Note: SSDTs can be dynamically loaded at
     * runtime and may or may not be available via the host OS.
     *
     * To specify the tables needed to resolve external control method
     * references, the -e option can be used to specify the filenames.
     * Example iASL invocations:
     *     iasl -e ssdt1.aml ssdt2.aml ssdt3.aml -d dsdt.aml
     *     iasl -e dsdt.aml ssdt2.aml -d ssdt1.aml
     *     iasl -e ssdt*.aml -d dsdt.aml
     *
     * In addition, the -fe option can be used to specify a file containing
     * control method external declarations with the associated method
     * argument counts. Each line of the file must be of the form:
     *     External (<method pathname>, MethodObj, <argument count>)
     * Invocation:
     *     iasl -fe refs.txt -d dsdt.aml
     *
     * The following methods were unresolved and many not compile properly
     * because the disassembler had to guess at the number of arguments
     * required for each:
     */
    External (_SB_.GDCK.GGID, IntObj)
    External (_SB_.PCI0.LPC_.EC__.BDEV, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.BEJ0, MethodObj)    // Warning: Unknown method, guessing 1 arguments
    External (_SB_.PCI0.LPC_.EC__.BGID, IntObj)
    External (_SB_.PCI0.LPC_.EC__.BSTA, MethodObj)    // Warning: Unknown method, guessing 1 arguments
    External (_SB_.PCI0.SAT1, DeviceObj)
    External (CDAH, IntObj)
    External (CDFL, IntObj)
    External (DPP0, UnknownObj)
    External (DPP1, UnknownObj)
    External (DPP2, UnknownObj)
    External (DPP3, UnknownObj)
    External (DPP4, UnknownObj)
    External (IDET, UnknownObj)

    Scope (\_SB.PCI0.SAT1)
    {
        Device (PRT0)
        {
            Name (DIP0, 0x00)
            Name (HDTF, Buffer (0x0E)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5               /* ...... */
            })
            Name (ERTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HPTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HXTF, Buffer (0x1C)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF, 0x10, 0x03, 0x00,  /* ........ */
                /* 0018 */  0x00, 0x00, 0xA0, 0xEF                           /* .... */
            })
            Name (DDTF, Buffer (0x0E)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3               /* ...... */
            })
            CreateByteField (DDTF, 0x01, DTAT)
            CreateByteField (DDTF, 0x08, DTFT)
            Name (DGTF, Buffer (0x15)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            CreateByteField (DGTF, 0x01, GTAT)
            CreateByteField (DGTF, 0x08, GTFT)
            Name (_ADR, 0xFFFF)  // _ADR: Address
            Method (_SDD, 1, NotSerialized)  // _SDD: Set Device Data
            {
                DIP0 = 0x00
                If (SizeOf (Arg0) == 0x0200)
                {
                    CreateWordField (Arg0, 0x9C, M078)
                    If (\DPP0 && (M078 & 0x08))
                    {
                        DIP0 = 0x01
                    }
                }
            }

            Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
            {
                If (DIP0)
                {
                    Return (HPTF) /* \_SB_.PCI0.SAT1.PRT0.HPTF */
                }

                Return (HDTF) /* \_SB_.PCI0.SAT1.PRT0.HDTF */
            }
        }

        Device (PRT1)
        {
            Name (DIP0, 0x00)
            Name (HDTF, Buffer (0x0E)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5               /* ...... */
            })
            Name (ERTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HPTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HXTF, Buffer (0x1C)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF, 0x10, 0x03, 0x00,  /* ........ */
                /* 0018 */  0x00, 0x00, 0xA0, 0xEF                           /* .... */
            })
            Name (DDTF, Buffer (0x0E)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3               /* ...... */
            })
            CreateByteField (DDTF, 0x01, DTAT)
            CreateByteField (DDTF, 0x08, DTFT)
            Name (DGTF, Buffer (0x15)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            CreateByteField (DGTF, 0x01, GTAT)
            CreateByteField (DGTF, 0x08, GTFT)
            Method (_EJ0, 1, NotSerialized)  // _EJx: Eject Device
            {
                \_SB.PCI0.LPC.EC.BEJ0 (Arg0)
            }

            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                If (\_SB.PCI0.LPC.EC.BSTA (0x01))
                {
                    Return (0x0F)
                }
                Else
                {
                    Return (0x00)
                }
            }

            Name (_ADR, 0x0001FFFF)  // _ADR: Address
            Method (_SDD, 1, NotSerialized)  // _SDD: Set Device Data
            {
                DIP0 = 0x00
                If (SizeOf (Arg0) == 0x0200)
                {
                    CreateWordField (Arg0, 0x9C, M078)
                    CreateWordField (Arg0, 0x00, M000)
                    If (M000 & 0xC000)
                    {
                        If (!(M000 & 0x4000))
                        {
                            \IDET = 0x03
                            \_SB.PCI0.LPC.EC.BDEV = 0x03
                        }
                    }
                    Else
                    {
                        \IDET = 0x06
                        \_SB.PCI0.LPC.EC.BDEV = 0x06
                    }

                    If (\DPP1 && (M078 & 0x08))
                    {
                        DIP0 = 0x01
                    }
                }
            }

            Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
            {
                Local1 = \_SB.GDCK.GGID /* External reference */
                If (Local1 == 0x00)
                {
                    If (DIP0)
                    {
                        Return (HPTF) /* \_SB_.PCI0.SAT1.PRT1.HPTF */
                    }

                    Return (HDTF) /* \_SB_.PCI0.SAT1.PRT1.HDTF */
                }
                Else
                {
                    0x00 = \_SB.PCI0.LPC.EC.BGID /* External reference */
                    Local0
                    If (Local0 == 0x07)
                    {
                        Local0 = 0x06
                    }

                    If (Local0 == 0x06)
                    {
                        If (DIP0)
                        {
                            Return (HPTF) /* \_SB_.PCI0.SAT1.PRT1.HPTF */
                        }

                        Return (HDTF) /* \_SB_.PCI0.SAT1.PRT1.HDTF */
                    }

                    If (DIP0)
                    {
                        GTFT = \CDFL /* External reference */
                        GTAT = \CDAH /* External reference */
                        Return (DGTF) /* \_SB_.PCI0.SAT1.PRT1.DGTF */
                    }

                    DTFT = \CDFL /* External reference */
                    DTAT = \CDAH /* External reference */
                    Return (DDTF) /* \_SB_.PCI0.SAT1.PRT1.DDTF */
                }
            }
        }

        Device (PRT2)
        {
            Name (DIP0, 0x00)
            Name (HDTF, Buffer (0x0E)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5               /* ...... */
            })
            Name (ERTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HPTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HXTF, Buffer (0x1C)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF, 0x10, 0x03, 0x00,  /* ........ */
                /* 0018 */  0x00, 0x00, 0xA0, 0xEF                           /* .... */
            })
            Name (DDTF, Buffer (0x0E)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3               /* ...... */
            })
            CreateByteField (DDTF, 0x01, DTAT)
            CreateByteField (DDTF, 0x08, DTFT)
            Name (DGTF, Buffer (0x15)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            CreateByteField (DGTF, 0x01, GTAT)
            CreateByteField (DGTF, 0x08, GTFT)
            Name (_ADR, 0x0002FFFF)  // _ADR: Address
            Method (_SDD, 1, NotSerialized)  // _SDD: Set Device Data
            {
                DIP0 = 0x00
                If (SizeOf (Arg0) == 0x0200)
                {
                    CreateWordField (Arg0, 0x9C, M078)
                    If (\DPP2 && (M078 & 0x08))
                    {
                        DIP0 = 0x01
                    }
                }
            }

            Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
            {
                If (DIP0)
                {
                    Return (HPTF) /* \_SB_.PCI0.SAT1.PRT2.HPTF */
                }

                Return (HDTF) /* \_SB_.PCI0.SAT1.PRT2.HDTF */
            }
        }

        Device (PRT3)
        {
            Name (DIP0, 0x00)
            Name (HDTF, Buffer (0x0E)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5               /* ...... */
            })
            Name (ERTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HPTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HXTF, Buffer (0x1C)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF, 0x10, 0x03, 0x00,  /* ........ */
                /* 0018 */  0x00, 0x00, 0xA0, 0xEF                           /* .... */
            })
            Name (DDTF, Buffer (0x0E)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3               /* ...... */
            })
            CreateByteField (DDTF, 0x01, DTAT)
            CreateByteField (DDTF, 0x08, DTFT)
            Name (DGTF, Buffer (0x15)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            CreateByteField (DGTF, 0x01, GTAT)
            CreateByteField (DGTF, 0x08, GTFT)
            Name (_ADR, 0x0003FFFF)  // _ADR: Address
            Method (_SDD, 1, NotSerialized)  // _SDD: Set Device Data
            {
                DIP0 = 0x00
                If (SizeOf (Arg0) == 0x0200)
                {
                    CreateWordField (Arg0, 0x9C, M078)
                    If (\DPP3 && (M078 & 0x08))
                    {
                        DIP0 = 0x01
                    }
                }
            }

            Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
            {
                If (DIP0)
                {
                    Return (HPTF) /* \_SB_.PCI0.SAT1.PRT3.HPTF */
                }

                Return (HDTF) /* \_SB_.PCI0.SAT1.PRT3.HDTF */
            }
        }

        Device (PRT4)
        {
            Name (DIP0, 0x00)
            Name (HDTF, Buffer (0x0E)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5               /* ...... */
            })
            Name (ERTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HPTF, Buffer (0x15)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            Name (HXTF, Buffer (0x1C)
            {
                /* 0000 */  0x02, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xEF, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xF5, 0x5F, 0x00,  /* ......_. */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF, 0x10, 0x03, 0x00,  /* ........ */
                /* 0018 */  0x00, 0x00, 0xA0, 0xEF                           /* .... */
            })
            Name (DDTF, Buffer (0x0E)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3               /* ...... */
            })
            CreateByteField (DDTF, 0x01, DTAT)
            CreateByteField (DDTF, 0x08, DTFT)
            Name (DGTF, Buffer (0x15)
            {
                /* 0000 */  0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x00,  /* ........ */
                /* 0008 */  0x00, 0x00, 0x00, 0x00, 0xA0, 0xE3, 0x10, 0x03,  /* ........ */
                /* 0010 */  0x00, 0x00, 0x00, 0xA0, 0xEF                     /* ..... */
            })
            CreateByteField (DGTF, 0x01, GTAT)
            CreateByteField (DGTF, 0x08, GTFT)
            Name (_ADR, 0x0004FFFF)  // _ADR: Address
            Method (_SDD, 1, NotSerialized)  // _SDD: Set Device Data
            {
                DIP0 = 0x00
                If (SizeOf (Arg0) == 0x0200)
                {
                    CreateWordField (Arg0, 0x9C, M078)
                    If (\DPP4 && (M078 & 0x08))
                    {
                        DIP0 = 0x01
                    }
                }
            }

            Method (_GTF, 0, NotSerialized)  // _GTF: Get Task File
            {
                If (DIP0)
                {
                    Return (HPTF) /* \_SB_.PCI0.SAT1.PRT4.HPTF */
                }

                Return (HDTF) /* \_SB_.PCI0.SAT1.PRT4.HDTF */
            }
        }
    }
}

