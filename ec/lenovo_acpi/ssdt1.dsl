/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160831-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of ssdt1.dat, Thu Mar 14 15:14:21 2019
 *
 * Original Table Header:
 *     Signature        "SSDT"
 *     Length           0x00000C79 (3193)
 *     Revision         0x01
 *     Checksum         0x11
 *     OEM ID           "PmRef"
 *     OEM Table ID     "Cpu0Ist"
 *     OEM Revision     0x00003000 (12288)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20061109 (537268489)
 */
DefinitionBlock ("", "SSDT", 1, "PmRef", "Cpu0Ist", 0x00003000)
{
    External (_PR_.CLVL, IntObj)
    External (_PR_.CPPC, IntObj)
    External (_PR_.CPU0, DeviceObj)
    External (_SB_.PCI0.LPC_.EC__.AC__._PSR, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.LPMD, IntObj)
    External (_SB_.PCI0.LPC_.EC__.PIBS, IntObj)
    External (_SB_.PCI0.LPC_.EC__.PLLS, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.PLMS, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.PLSL, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.PLTU, UnknownObj)
    External (_SB_.PCI0.LPC_.EC__.TSL0, UnknownObj)
    External (APMD, IntObj)
    External (APST, IntObj)
    External (CFGD, UnknownObj)
    External (CTDP, IntObj)
    External (FTPS, IntObj)
    External (GFPL, IntObj)
    External (LWST, IntObj)
    External (MTAU, IntObj)
    External (NPSS, IntObj)
    External (PDC0, UnknownObj)
    External (PL1L, IntObj)
    External (PL1M, IntObj)
    External (PPCA, IntObj)
    External (PPCR, UnknownObj)
    External (TCFA, UnknownObj)
    External (TCFD, UnknownObj)
    External (TCNT, IntObj)

    Scope (\_PR.CPU0)
    {
        Method (_PPC, 0, NotSerialized)  // _PPC: Performance Present Capabilities
        {
            Local0 = Zero
            Local0 = \_SB.PCI0.LPC.EC.LPMD /* External reference */
            If (!Local0)
            {
                If ((\_SB.PCI0.LPC.EC.AC._PSR && \TCFA) || (!\_SB.PCI0.LPC.EC.AC._PSR && \TCFD))
                {
                    If (\_SB.PCI0.LPC.EC.TSL0 & 0x76)
                    {
                        Local0 = \LWST /* External reference */
                    }
                }
                ElseIf (\_SB.PCI0.LPC.EC.TSL0 & 0x77)
                {
                    Local0 = \LWST /* External reference */
                }

                If (!Local0)
                {
                    If (\APMD)
                    {
                        Local0 = \APST /* External reference */
                    }

                    If (!Local0)
                    {
                        If (\_PR.CLVL)
                        {
                            If (\PPCA)
                            {
                                Local0 = \PPCA /* External reference */
                            }
                        }
                        ElseIf (\PPCA || \FTPS)
                        {
                            If (\FTPS <= \PPCA)
                            {
                                Local0 = \PPCA /* External reference */
                            }
                            Else
                            {
                                Local0 = \FTPS /* External reference */
                            }
                        }
                    }
                }
            }

            If ((\GFPL && !Local0) || (!\GFPL && Local0))
            {
                Local1 = 0x03E8
                While (\_SB.PCI0.LPC.EC.PIBS)
                {
                    Sleep (One)
                    Local1--
                    If (!Local1)
                    {
                        \PPCR = Local0
                        Return (Local0)
                    }
                }

                If (Local0)
                {
                    If (!\GFPL)
                    {
                        \GFPL = One
                        \_SB.PCI0.LPC.EC.PLSL = 0x04
                        \_SB.PCI0.LPC.EC.PLTU = One
                        \_SB.PCI0.LPC.EC.PLLS = 0x0D
                        \_SB.PCI0.LPC.EC.PLMS = Zero
                    }
                }
                ElseIf (\GFPL)
                {
                    \GFPL = Zero
                    \_SB.PCI0.LPC.EC.PLSL = 0x04
                    If (\MTAU)
                    {
                        \_SB.PCI0.LPC.EC.PLTU = \MTAU /* External reference */
                    }
                    Else
                    {
                        \_SB.PCI0.LPC.EC.PLTU = 0x1C
                    }

                    \_SB.PCI0.LPC.EC.PLLS = \PL1L /* External reference */
                    \_SB.PCI0.LPC.EC.PLMS = \PL1M /* External reference */
                }
            }

            If (\_PR.CLVL)
            {
                If (Local0 == Zero)
                {
                    If (\CTDP < \FTPS)
                    {
                        Local0 = \FTPS /* External reference */
                    }
                    Else
                    {
                        Local0 = \CTDP /* External reference */
                    }
                }
                ElseIf (\CTDP >= Local0)
                {
                    Local0 = \CTDP /* External reference */
                    If (\LWST > Local0)
                    {
                        Local0++
                    }
                }
            }

            \PPCR = Local0
            Return (Local0)
        }

        Method (_PCT, 0, NotSerialized)  // _PCT: Performance Control
        {
            If (\_PR.CLVL)
            {
                \CTDP = \_PR.CPPC /* External reference */
            }

            If ((CFGD & One) && (PDC0 & One))
            {
                Return (Package (0x02)
                {
                    ResourceTemplate ()
                    {
                        Register (FFixedHW, 
                            0x00,               // Bit Width
                            0x00,               // Bit Offset
                            0x0000000000000000, // Address
                            ,)
                    }, 

                    ResourceTemplate ()
                    {
                        Register (FFixedHW, 
                            0x00,               // Bit Width
                            0x00,               // Bit Offset
                            0x0000000000000000, // Address
                            ,)
                    }
                })
            }

            Return (Package (0x02)
            {
                ResourceTemplate ()
                {
                    Register (SystemIO, 
                        0x10,               // Bit Width
                        0x00,               // Bit Offset
                        0x0000000000000800, // Address
                        ,)
                }, 

                ResourceTemplate ()
                {
                    Register (SystemIO, 
                        0x08,               // Bit Width
                        0x00,               // Bit Offset
                        0x00000000000000B3, // Address
                        ,)
                }
            })
        }

        Method (XPSS, 0, NotSerialized)
        {
            If (PDC0 & One)
            {
                Return (NPSS) /* External reference */
            }

            Return (SPSS) /* \_PR_.CPU0.SPSS */
        }

        Name (SPSS, Package (0x10)
        {
            Package (0x06)
            {
                0x00000A29, 
                0x000088B8, 
                0x0000006E, 
                0x0000000A, 
                0x00000083, 
                0x00000000
            }, 

            Package (0x06)
            {
                0x00000A28, 
                0x000088B8, 
                0x0000006E, 
                0x0000000A, 
                0x00000183, 
                0x00000001
            }, 

            Package (0x06)
            {
                0x000009C4, 
                0x000081C2, 
                0x0000006E, 
                0x0000000A, 
                0x00000283, 
                0x00000002
            }, 

            Package (0x06)
            {
                0x00000960, 
                0x00007AEE, 
                0x0000006E, 
                0x0000000A, 
                0x00000383, 
                0x00000003
            }, 

            Package (0x06)
            {
                0x000008FC, 
                0x0000743B, 
                0x0000006E, 
                0x0000000A, 
                0x00000483, 
                0x00000004
            }, 

            Package (0x06)
            {
                0x00000898, 
                0x00006DAA, 
                0x0000006E, 
                0x0000000A, 
                0x00000583, 
                0x00000005
            }, 

            Package (0x06)
            {
                0x00000834, 
                0x0000673A, 
                0x0000006E, 
                0x0000000A, 
                0x00000683, 
                0x00000006
            }, 

            Package (0x06)
            {
                0x000007D0, 
                0x000060F0, 
                0x0000006E, 
                0x0000000A, 
                0x00000783, 
                0x00000007
            }, 

            Package (0x06)
            {
                0x0000076C, 
                0x00005C04, 
                0x0000006E, 
                0x0000000A, 
                0x00000883, 
                0x00000008
            }, 

            Package (0x06)
            {
                0x00000708, 
                0x000055F2, 
                0x0000006E, 
                0x0000000A, 
                0x00000983, 
                0x00000009
            }, 

            Package (0x06)
            {
                0x000006A4, 
                0x00005000, 
                0x0000006E, 
                0x0000000A, 
                0x00000A83, 
                0x0000000A
            }, 

            Package (0x06)
            {
                0x00000640, 
                0x00004A2D, 
                0x0000006E, 
                0x0000000A, 
                0x00000B83, 
                0x0000000B
            }, 

            Package (0x06)
            {
                0x000005DC, 
                0x0000447E, 
                0x0000006E, 
                0x0000000A, 
                0x00000C83, 
                0x0000000C
            }, 

            Package (0x06)
            {
                0x00000578, 
                0x00003EEA, 
                0x0000006E, 
                0x0000000A, 
                0x00000D83, 
                0x0000000D
            }, 

            Package (0x06)
            {
                0x00000514, 
                0x00003AA1, 
                0x0000006E, 
                0x0000000A, 
                0x00000E83, 
                0x0000000E
            }, 

            Package (0x06)
            {
                0x000004B0, 
                0x00003546, 
                0x0000006E, 
                0x0000000A, 
                0x00000F83, 
                0x0000000F
            }
        })
        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Name (_PSS, Package (0x10)  // _PSS: Performance Supported States
        {
            Package (0x06)
            {
                0x00000A29, 
                0x000088B8, 
                0x0000000A, 
                0x0000000A, 
                0x00002100, 
                0x00002100
            }, 

            Package (0x06)
            {
                0x00000A28, 
                0x000088B8, 
                0x0000000A, 
                0x0000000A, 
                0x00001A00, 
                0x00001A00
            }, 

            Package (0x06)
            {
                0x000009C4, 
                0x000081C2, 
                0x0000000A, 
                0x0000000A, 
                0x00001900, 
                0x00001900
            }, 

            Package (0x06)
            {
                0x00000960, 
                0x00007AEE, 
                0x0000000A, 
                0x0000000A, 
                0x00001800, 
                0x00001800
            }, 

            Package (0x06)
            {
                0x000008FC, 
                0x0000743B, 
                0x0000000A, 
                0x0000000A, 
                0x00001700, 
                0x00001700
            }, 

            Package (0x06)
            {
                0x00000898, 
                0x00006DAA, 
                0x0000000A, 
                0x0000000A, 
                0x00001600, 
                0x00001600
            }, 

            Package (0x06)
            {
                0x00000834, 
                0x0000673A, 
                0x0000000A, 
                0x0000000A, 
                0x00001500, 
                0x00001500
            }, 

            Package (0x06)
            {
                0x000007D0, 
                0x000060F0, 
                0x0000000A, 
                0x0000000A, 
                0x00001400, 
                0x00001400
            }, 

            Package (0x06)
            {
                0x0000076C, 
                0x00005C04, 
                0x0000000A, 
                0x0000000A, 
                0x00001300, 
                0x00001300
            }, 

            Package (0x06)
            {
                0x00000708, 
                0x000055F2, 
                0x0000000A, 
                0x0000000A, 
                0x00001200, 
                0x00001200
            }, 

            Package (0x06)
            {
                0x000006A4, 
                0x00005000, 
                0x0000000A, 
                0x0000000A, 
                0x00001100, 
                0x00001100
            }, 

            Package (0x06)
            {
                0x00000640, 
                0x00004A2D, 
                0x0000000A, 
                0x0000000A, 
                0x00001000, 
                0x00001000
            }, 

            Package (0x06)
            {
                0x000005DC, 
                0x0000447E, 
                0x0000000A, 
                0x0000000A, 
                0x00000F00, 
                0x00000F00
            }, 

            Package (0x06)
            {
                0x00000578, 
                0x00003EEA, 
                0x0000000A, 
                0x0000000A, 
                0x00000E00, 
                0x00000E00
            }, 

            Package (0x06)
            {
                0x00000514, 
                0x00003AA1, 
                0x0000000A, 
                0x0000000A, 
                0x00000D00, 
                0x00000D00
            }, 

            Package (0x06)
            {
                0x000004B0, 
                0x00003546, 
                0x0000000A, 
                0x0000000A, 
                0x00000C00, 
                0x00000C00
            }
        })
        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Package (0x06)
        {
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000, 
            0x80000000
        }

        Name (PSDF, Zero)
        Method (_PSD, 0, NotSerialized)  // _PSD: Power State Dependencies
        {
            If (!PSDF)
            {
                DerefOf (HPSD [Zero]) [0x04] = TCNT /* External reference */
                DerefOf (SPSD [Zero]) [0x04] = TCNT /* External reference */
                PSDF = Ones
            }

            If (PDC0 & 0x0800)
            {
                Return (HPSD) /* \_PR_.CPU0.HPSD */
            }

            Return (SPSD) /* \_PR_.CPU0.SPSD */
        }

        Name (HPSD, Package (0x01)
        {
            Package (0x05)
            {
                0x05, 
                Zero, 
                Zero, 
                0xFE, 
                0x80
            }
        })
        Name (SPSD, Package (0x01)
        {
            Package (0x05)
            {
                0x05, 
                Zero, 
                Zero, 
                0xFC, 
                0x80
            }
        })
    }
}

