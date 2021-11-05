.include "macros.inc"

.section .data, "wa"  # 0x80222DC0 - 0x802E9640
.global lbl_802C4378
lbl_802C4378:
	.4byte 0x6E6C6962
	.4byte 0x6D617468
	.4byte 0x2E637070
	.4byte 0x00000000
	.4byte 0x6E6C6962
	.4byte 0x6D617468
	.4byte 0x00000000
.global AtanTable
AtanTable:
	.4byte 0x0000000A
	.4byte 0x0014001F
	.4byte 0x00290033
	.4byte 0x003D0047
	.4byte 0x0051005C
	.4byte 0x00660070
	.4byte 0x007A0084
	.4byte 0x008F0099
	.4byte 0x00A300AD
	.4byte 0x00B700C2
	.4byte 0x00CC00D6
	.4byte 0x00E000EA
	.4byte 0x00F400FF
	.4byte 0x01090113
	.4byte 0x011D0127
	.4byte 0x0131013C
	.4byte 0x01460150
	.4byte 0x015A0164
	.4byte 0x016F0179
	.4byte 0x0183018D
	.4byte 0x019701A1
	.4byte 0x01AC01B6
	.4byte 0x01C001CA
	.4byte 0x01D401DE
	.4byte 0x01E901F3
	.4byte 0x01FD0207
	.4byte 0x0211021B
	.4byte 0x02260230
	.4byte 0x023A0244
	.4byte 0x024E0258
	.4byte 0x0262026D
	.4byte 0x02770281
	.4byte 0x028B0295
	.4byte 0x029F02A9
	.4byte 0x02B402BE
	.4byte 0x02C802D2
	.4byte 0x02DC02E6
	.4byte 0x02F002FB
	.4byte 0x0305030F
	.4byte 0x03190323
	.4byte 0x032D0337
	.4byte 0x0341034C
	.4byte 0x03560360
	.4byte 0x036A0374
	.4byte 0x037E0388
	.4byte 0x0392039C
	.4byte 0x03A703B1
	.4byte 0x03BB03C5
	.4byte 0x03CF03D9
	.4byte 0x03E303ED
	.4byte 0x03F70401
	.4byte 0x040C0416
	.4byte 0x0420042A
	.4byte 0x0434043E
	.4byte 0x04480452
	.4byte 0x045C0466
	.4byte 0x0470047A
	.4byte 0x0484048E
	.4byte 0x049904A3
	.4byte 0x04AD04B7
	.4byte 0x04C104CB
	.4byte 0x04D504DF
	.4byte 0x04E904F3
	.4byte 0x04FD0507
	.4byte 0x0511051B
	.4byte 0x0525052F
	.4byte 0x05390543
	.4byte 0x054D0557
	.4byte 0x0561056B
	.4byte 0x0575057F
	.4byte 0x05890593
	.4byte 0x059D05A7
	.4byte 0x05B105BB
	.4byte 0x05C505CF
	.4byte 0x05D905E3
	.4byte 0x05ED05F7
	.4byte 0x0601060B
	.4byte 0x0615061F
	.4byte 0x06290633
	.4byte 0x063D0647
	.4byte 0x0651065B
	.4byte 0x0665066E
	.4byte 0x06780682
	.4byte 0x068C0696
	.4byte 0x06A006AA
	.4byte 0x06B406BE
	.4byte 0x06C806D2
	.4byte 0x06DC06E5
	.4byte 0x06EF06F9
	.4byte 0x0703070D
	.4byte 0x07170721
	.4byte 0x072B0735
	.4byte 0x073E0748
	.4byte 0x0752075C
	.4byte 0x07660770
	.4byte 0x077A0783
	.4byte 0x078D0797
	.4byte 0x07A107AB
	.4byte 0x07B507BE
	.4byte 0x07C807D2
	.4byte 0x07DC07E6
	.4byte 0x07EF07F9
	.4byte 0x0803080D
	.4byte 0x08170820
	.4byte 0x082A0834
	.4byte 0x083E0848
	.4byte 0x0851085B
	.4byte 0x0865086F
	.4byte 0x08780882
	.4byte 0x088C0896
	.4byte 0x089F08A9
	.4byte 0x08B308BD
	.4byte 0x08C608D0
	.4byte 0x08DA08E3
	.4byte 0x08ED08F7
	.4byte 0x0901090A
	.4byte 0x0914091E
	.4byte 0x09270931
	.4byte 0x093B0944
	.4byte 0x094E0958
	.4byte 0x0961096B
	.4byte 0x0975097E
	.4byte 0x09880992
	.4byte 0x099B09A5
	.4byte 0x09AE09B8
	.4byte 0x09C209CB
	.4byte 0x09D509DE
	.4byte 0x09E809F2
	.4byte 0x09FB0A05
	.4byte 0x0A0E0A18
	.4byte 0x0A220A2B
	.4byte 0x0A350A3E
	.4byte 0x0A480A51
	.4byte 0x0A5B0A64
	.4byte 0x0A6E0A77
	.4byte 0x0A810A8B
	.4byte 0x0A940A9E
	.4byte 0x0AA70AB1
	.4byte 0x0ABA0AC4
	.4byte 0x0ACD0AD7
	.4byte 0x0AE00AE9
	.4byte 0x0AF30AFC
	.4byte 0x0B060B0F
	.4byte 0x0B190B22
	.4byte 0x0B2C0B35
	.4byte 0x0B3F0B48
	.4byte 0x0B510B5B
	.4byte 0x0B640B6E
	.4byte 0x0B770B80
	.4byte 0x0B8A0B93
	.4byte 0x0B9D0BA6
	.4byte 0x0BAF0BB9
	.4byte 0x0BC20BCB
	.4byte 0x0BD50BDE
	.4byte 0x0BE70BF1
	.4byte 0x0BFA0C03
	.4byte 0x0C0D0C16
	.4byte 0x0C1F0C29
	.4byte 0x0C320C3B
	.4byte 0x0C450C4E
	.4byte 0x0C570C60
	.4byte 0x0C6A0C73
	.4byte 0x0C7C0C86
	.4byte 0x0C8F0C98
	.4byte 0x0CA10CAB
	.4byte 0x0CB40CBD
	.4byte 0x0CC60CCF
	.4byte 0x0CD90CE2
	.4byte 0x0CEB0CF4
	.4byte 0x0CFD0D07
	.4byte 0x0D100D19
	.4byte 0x0D220D2B
	.4byte 0x0D340D3E
	.4byte 0x0D470D50
	.4byte 0x0D590D62
	.4byte 0x0D6B0D74
	.4byte 0x0D7D0D87
	.4byte 0x0D900D99
	.4byte 0x0DA20DAB
	.4byte 0x0DB40DBD
	.4byte 0x0DC60DCF
	.4byte 0x0DD80DE1
	.4byte 0x0DEA0DF3
	.4byte 0x0DFC0E05
	.4byte 0x0E0F0E18
	.4byte 0x0E210E2A
	.4byte 0x0E330E3C
	.4byte 0x0E450E4E
	.4byte 0x0E560E5F
	.4byte 0x0E680E71
	.4byte 0x0E7A0E83
	.4byte 0x0E8C0E95
	.4byte 0x0E9E0EA7
	.4byte 0x0EB00EB9
	.4byte 0x0EC20ECB
	.4byte 0x0ED40EDC
	.4byte 0x0EE50EEE
	.4byte 0x0EF70F00
	.4byte 0x0F090F12
	.4byte 0x0F1B0F23
	.4byte 0x0F2C0F35
	.4byte 0x0F3E0F47
	.4byte 0x0F500F58
	.4byte 0x0F610F6A
	.4byte 0x0F730F7C
	.4byte 0x0F840F8D
	.4byte 0x0F960F9F
	.4byte 0x0FA70FB0
	.4byte 0x0FB90FC2
	.4byte 0x0FCA0FD3
	.4byte 0x0FDC0FE5
	.4byte 0x0FED0FF6
	.4byte 0x0FFF1007
	.4byte 0x10101019
	.4byte 0x1021102A
	.4byte 0x1033103B
	.4byte 0x1044104D
	.4byte 0x1055105E
	.4byte 0x1067106F
	.4byte 0x10781080
	.4byte 0x10891092
	.4byte 0x109A10A3
	.4byte 0x10AB10B4
	.4byte 0x10BC10C5
	.4byte 0x10CE10D6
	.4byte 0x10DF10E7
	.4byte 0x10F010F8
	.4byte 0x11011109
	.4byte 0x1112111A
	.4byte 0x1123112B
	.4byte 0x1134113C
	.4byte 0x1145114D
	.4byte 0x1156115E
	.4byte 0x1166116F
	.4byte 0x11771180
	.4byte 0x11881191
	.4byte 0x119911A1
	.4byte 0x11AA11B2
	.4byte 0x11BB11C3
	.4byte 0x11CB11D4
	.4byte 0x11DC11E4
	.4byte 0x11ED11F5
	.4byte 0x11FD1206
	.4byte 0x120E1216
	.4byte 0x121F1227
	.4byte 0x122F1237
	.4byte 0x12401248
	.4byte 0x12501259
	.4byte 0x12611269
	.4byte 0x1271127A
	.4byte 0x1282128A
	.4byte 0x1292129A
	.4byte 0x12A312AB
	.4byte 0x12B312BB
	.4byte 0x12C312CC
	.4byte 0x12D412DC
	.4byte 0x12E412EC
	.4byte 0x12F412FC
	.4byte 0x1305130D
	.4byte 0x1315131D
	.4byte 0x1325132D
	.4byte 0x1335133D
	.4byte 0x1345134D
	.4byte 0x1355135E
	.4byte 0x1366136E
	.4byte 0x1376137E
	.4byte 0x1386138E
	.4byte 0x1396139E
	.4byte 0x13A613AE
	.4byte 0x13B613BE
	.4byte 0x13C613CE
	.4byte 0x13D613DE
	.4byte 0x13E613ED
	.4byte 0x13F513FD
	.4byte 0x1405140D
	.4byte 0x1415141D
	.4byte 0x1425142D
	.4byte 0x1435143D
	.4byte 0x1444144C
	.4byte 0x1454145C
	.4byte 0x1464146C
	.4byte 0x1473147B
	.4byte 0x1483148B
	.4byte 0x1493149B
	.4byte 0x14A214AA
	.4byte 0x14B214BA
	.4byte 0x14C114C9
	.4byte 0x14D114D9
	.4byte 0x14E014E8
	.4byte 0x14F014F8
	.4byte 0x14FF1507
	.4byte 0x150F1516
	.4byte 0x151E1526
	.4byte 0x152D1535
	.4byte 0x153D1544
	.4byte 0x154C1554
	.4byte 0x155B1563
	.4byte 0x156B1572
	.4byte 0x157A1581
	.4byte 0x15891591
	.4byte 0x159815A0
	.4byte 0x15A715AF
	.4byte 0x15B715BE
	.4byte 0x15C615CD
	.4byte 0x15D515DC
	.4byte 0x15E415EB
	.4byte 0x15F315FA
	.4byte 0x16021609
	.4byte 0x16111618
	.4byte 0x16201627
	.4byte 0x162F1636
	.4byte 0x163E1645
	.4byte 0x164C1654
	.4byte 0x165B1663
	.4byte 0x166A1671
	.4byte 0x16791680
	.4byte 0x1688168F
	.4byte 0x1696169E
	.4byte 0x16A516AC
	.4byte 0x16B416BB
	.4byte 0x16C216CA
	.4byte 0x16D116D8
	.4byte 0x16E016E7
	.4byte 0x16EE16F6
	.4byte 0x16FD1704
	.4byte 0x170B1713
	.4byte 0x171A1721
	.4byte 0x17281730
	.4byte 0x1737173E
	.4byte 0x1745174C
	.4byte 0x1754175B
	.4byte 0x17621769
	.4byte 0x17701778
	.4byte 0x177F1786
	.4byte 0x178D1794
	.4byte 0x179B17A2
	.4byte 0x17AA17B1
	.4byte 0x17B817BF
	.4byte 0x17C617CD
	.4byte 0x17D417DB
	.4byte 0x17E217E9
	.4byte 0x17F017F7
	.4byte 0x17FE1806
	.4byte 0x180D1814
	.4byte 0x181B1822
	.4byte 0x18291830
	.4byte 0x1837183E
	.4byte 0x1845184C
	.4byte 0x1853185A
	.4byte 0x18601867
	.4byte 0x186E1875
	.4byte 0x187C1883
	.4byte 0x188A1891
	.4byte 0x1898189F
	.4byte 0x18A618AD
	.4byte 0x18B318BA
	.4byte 0x18C118C8
	.4byte 0x18CF18D6
	.4byte 0x18DD18E3
	.4byte 0x18EA18F1
	.4byte 0x18F818FF
	.4byte 0x1906190C
	.4byte 0x1913191A
	.4byte 0x19211928
	.4byte 0x192E1935
	.4byte 0x193C1943
	.4byte 0x19491950
	.4byte 0x1957195D
	.4byte 0x1964196B
	.4byte 0x19721978
	.4byte 0x197F1986
	.4byte 0x198C1993
	.4byte 0x199A19A0
	.4byte 0x19A719AE
	.4byte 0x19B419BB
	.4byte 0x19C219C8
	.4byte 0x19CF19D5
	.4byte 0x19DC19E3
	.4byte 0x19E919F0
	.4byte 0x19F619FD
	.4byte 0x1A041A0A
	.4byte 0x1A111A17
	.4byte 0x1A1E1A24
	.4byte 0x1A2B1A31
	.4byte 0x1A381A3E
	.4byte 0x1A451A4B
	.4byte 0x1A521A58
	.4byte 0x1A5F1A65
	.4byte 0x1A6C1A72
	.4byte 0x1A791A7F
	.4byte 0x1A861A8C
	.4byte 0x1A931A99
	.4byte 0x1A9F1AA6
	.4byte 0x1AAC1AB3
	.4byte 0x1AB91AC0
	.4byte 0x1AC61ACC
	.4byte 0x1AD31AD9
	.4byte 0x1ADF1AE6
	.4byte 0x1AEC1AF2
	.4byte 0x1AF91AFF
	.4byte 0x1B051B0C
	.4byte 0x1B121B18
	.4byte 0x1B1F1B25
	.4byte 0x1B2B1B32
	.4byte 0x1B381B3E
	.4byte 0x1B441B4B
	.4byte 0x1B511B57
	.4byte 0x1B5D1B64
	.4byte 0x1B6A1B70
	.4byte 0x1B761B7D
	.4byte 0x1B831B89
	.4byte 0x1B8F1B95
	.4byte 0x1B9C1BA2
	.4byte 0x1BA81BAE
	.4byte 0x1BB41BBA
	.4byte 0x1BC11BC7
	.4byte 0x1BCD1BD3
	.4byte 0x1BD91BDF
	.4byte 0x1BE51BEB
	.4byte 0x1BF21BF8
	.4byte 0x1BFE1C04
	.4byte 0x1C0A1C10
	.4byte 0x1C161C1C
	.4byte 0x1C221C28
	.4byte 0x1C2E1C34
	.4byte 0x1C3A1C40
	.4byte 0x1C461C4C
	.4byte 0x1C521C58
	.4byte 0x1C5E1C64
	.4byte 0x1C6A1C70
	.4byte 0x1C761C7C
	.4byte 0x1C821C88
	.4byte 0x1C8E1C94
	.4byte 0x1C9A1CA0
	.4byte 0x1CA61CAC
	.4byte 0x1CB21CB8
	.4byte 0x1CBE1CC3
	.4byte 0x1CC91CCF
	.4byte 0x1CD51CDB
	.4byte 0x1CE11CE7
	.4byte 0x1CED1CF3
	.4byte 0x1CF81CFE
	.4byte 0x1D041D0A
	.4byte 0x1D101D16
	.4byte 0x1D1B1D21
	.4byte 0x1D271D2D
	.4byte 0x1D331D38
	.4byte 0x1D3E1D44
	.4byte 0x1D4A1D4F
	.4byte 0x1D551D5B
	.4byte 0x1D611D66
	.4byte 0x1D6C1D72
	.4byte 0x1D781D7D
	.4byte 0x1D831D89
	.4byte 0x1D8E1D94
	.4byte 0x1D9A1DA0
	.4byte 0x1DA51DAB
	.4byte 0x1DB11DB6
	.4byte 0x1DBC1DC2
	.4byte 0x1DC71DCD
	.4byte 0x1DD31DD8
	.4byte 0x1DDE1DE3
	.4byte 0x1DE91DEF
	.4byte 0x1DF41DFA
	.4byte 0x1DFF1E05
	.4byte 0x1E0B1E10
	.4byte 0x1E161E1B
	.4byte 0x1E211E26
	.4byte 0x1E2C1E32
	.4byte 0x1E371E3D
	.4byte 0x1E421E48
	.4byte 0x1E4D1E53
	.4byte 0x1E581E5E
	.4byte 0x1E631E69
	.4byte 0x1E6E1E74
	.4byte 0x1E791E7F
	.4byte 0x1E841E8A
	.4byte 0x1E8F1E94
	.4byte 0x1E9A1E9F
	.4byte 0x1EA51EAA
	.4byte 0x1EB01EB5
	.4byte 0x1EBA1EC0
	.4byte 0x1EC51ECB
	.4byte 0x1ED01ED5
	.4byte 0x1EDB1EE0
	.4byte 0x1EE61EEB
	.4byte 0x1EF01EF6
	.4byte 0x1EFB1F00
	.4byte 0x1F061F0B
	.4byte 0x1F101F16
	.4byte 0x1F1B1F20
	.4byte 0x1F261F2B
	.4byte 0x1F301F36
	.4byte 0x1F3B1F40
	.4byte 0x1F451F4B
	.4byte 0x1F501F55
	.4byte 0x1F5A1F60
	.4byte 0x1F651F6A
	.4byte 0x1F6F1F75
	.4byte 0x1F7A1F7F
	.4byte 0x1F841F8A
	.4byte 0x1F8F1F94
	.4byte 0x1F991F9E
	.4byte 0x1FA41FA9
	.4byte 0x1FAE1FB3
	.4byte 0x1FB81FBD
	.4byte 0x1FC31FC8
	.4byte 0x1FCD1FD2
	.4byte 0x1FD71FDC
	.4byte 0x1FE11FE6
	.4byte 0x1FEC1FF1
	.4byte 0x1FF61FFB
	.4byte 0x20000000

.section .sdata, "wa"  # 0x803DCD20 - 0x803E7820
.global __RTTI__5NLine
__RTTI__5NLine:
  .4byte 0x803e3038
  .4byte 0
  .4byte 0x4e506c61
  .4byte 0x6e650000
