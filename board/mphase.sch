<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.7.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="maxim">
<description>&lt;b&gt;Maxim Components&lt;/b&gt;&lt;p&gt;

&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL16">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="10.16" y1="2.921" x2="-10.16" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="10.16" y1="2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="2.921" x2="-10.16" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="-10.16" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.016" x2="-10.16" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-10.541" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-7.493" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MAX232">
<wire x1="-10.16" y1="15.24" x2="10.16" y2="15.24" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-17.78" x2="10.16" y2="15.24" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-17.78" x2="-10.16" y2="-17.78" width="0.4064" layer="94"/>
<wire x1="-10.16" y1="15.24" x2="-10.16" y2="-17.78" width="0.4064" layer="94"/>
<text x="-10.16" y="15.875" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-20.32" size="1.778" layer="96">&gt;VALUE</text>
<pin name="C1+" x="-15.24" y="12.7" length="middle"/>
<pin name="C1-" x="-15.24" y="7.62" length="middle"/>
<pin name="C2+" x="-15.24" y="2.54" length="middle"/>
<pin name="C2-" x="-15.24" y="-2.54" length="middle"/>
<pin name="T1IN" x="-15.24" y="-7.62" length="middle" direction="in"/>
<pin name="T2IN" x="-15.24" y="-10.16" length="middle" direction="in"/>
<pin name="R1OUT" x="-15.24" y="-12.7" length="middle" direction="out"/>
<pin name="R2OUT" x="-15.24" y="-15.24" length="middle" direction="out"/>
<pin name="V+" x="15.24" y="10.16" length="middle" rot="R180"/>
<pin name="V-" x="15.24" y="5.08" length="middle" rot="R180"/>
<pin name="T1OUT" x="15.24" y="-7.62" length="middle" direction="out" rot="R180"/>
<pin name="T2OUT" x="15.24" y="-10.16" length="middle" direction="out" rot="R180"/>
<pin name="R1IN" x="15.24" y="-12.7" length="middle" direction="in" rot="R180"/>
<pin name="R2IN" x="15.24" y="-15.24" length="middle" direction="in" rot="R180"/>
</symbol>
<symbol name="VCC-GND">
<text x="1.524" y="-5.08" size="1.016" layer="95" rot="R90">GND</text>
<text x="1.524" y="2.54" size="1.016" layer="95" rot="R90">VCC</text>
<text x="-0.762" y="-0.762" size="1.778" layer="95">&gt;NAME</text>
<pin name="VCC" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
<pin name="GND" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MAX232" prefix="IC">
<description>&lt;b&gt;RS232 TRANSCEIVER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MAX232" x="0" y="0"/>
<gate name="P" symbol="VCC-GND" x="25.4" y="-5.08" addlevel="request"/>
</gates>
<devices>
<device name="" package="DIL16">
<connects>
<connect gate="G$1" pin="C1+" pad="1"/>
<connect gate="G$1" pin="C1-" pad="3"/>
<connect gate="G$1" pin="C2+" pad="4"/>
<connect gate="G$1" pin="C2-" pad="5"/>
<connect gate="G$1" pin="R1IN" pad="13"/>
<connect gate="G$1" pin="R1OUT" pad="12"/>
<connect gate="G$1" pin="R2IN" pad="8"/>
<connect gate="G$1" pin="R2OUT" pad="9"/>
<connect gate="G$1" pin="T1IN" pad="11"/>
<connect gate="G$1" pin="T1OUT" pad="14"/>
<connect gate="G$1" pin="T2IN" pad="10"/>
<connect gate="G$1" pin="T2OUT" pad="7"/>
<connect gate="G$1" pin="V+" pad="2"/>
<connect gate="G$1" pin="V-" pad="6"/>
<connect gate="P" pin="GND" pad="15"/>
<connect gate="P" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MAXIM" constant="no"/>
<attribute name="MPN" value="MAX232ACPE+" constant="no"/>
<attribute name="OC_FARNELL" value="9723773" constant="no"/>
<attribute name="OC_NEWARK" value="68K4544" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="microchip">
<description>&lt;b&gt;Microchip PIC Microcontrollers and other Devices&lt;/b&gt;&lt;p&gt;
Based on the following sources :
&lt;ul&gt;
&lt;li&gt;Microchip Data Book, 1993
&lt;li&gt;THE EMERGING WORLD STANDARD, 1995/1996
&lt;li&gt;Microchip, Technical Library CD-ROM, June 1998
&lt;li&gt;www.microchip.com
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL40">
<description>&lt;B&gt;Dual In Line&lt;/B&gt;&lt;p&gt;
package type P</description>
<wire x1="-25.4" y1="-1.27" x2="-25.4" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="1.27" x2="-25.4" y2="-1.27" width="0.1524" layer="21" curve="-180"/>
<wire x1="25.4" y1="-6.223" x2="25.4" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="6.223" x2="-25.4" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="6.223" x2="25.4" y2="6.223" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-6.223" x2="25.4" y2="-6.223" width="0.1524" layer="21"/>
<pad name="1" x="-24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="-11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="-6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="-3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="-1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="21" x="24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="22" x="21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="23" x="19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="24" x="16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="25" x="13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="26" x="11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="27" x="8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="28" x="6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="29" x="3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="30" x="1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="31" x="-1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="32" x="-3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="33" x="-6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="34" x="-8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="35" x="-11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="36" x="-13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="37" x="-16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="38" x="-19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="39" x="-21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="40" x="-24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<text x="-25.781" y="-6.096" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-21.59" y="-2.2352" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PIC18F4455_40">
<wire x1="-33.02" y1="27.94" x2="33.02" y2="27.94" width="0.254" layer="94"/>
<wire x1="33.02" y1="27.94" x2="33.02" y2="-25.4" width="0.254" layer="94"/>
<wire x1="33.02" y1="-25.4" x2="-33.02" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-33.02" y1="-25.4" x2="-33.02" y2="27.94" width="0.254" layer="94"/>
<text x="-33.02" y="29.21" size="1.778" layer="95">&gt;NAME</text>
<text x="-33.02" y="-27.94" size="1.778" layer="96">&gt;VALUE</text>
<pin name="RC7/RX/DT/SDO" x="35.56" y="-10.16" length="short" rot="R180"/>
<pin name="RD4/SPP4" x="35.56" y="-7.62" length="short" rot="R180"/>
<pin name="RD5/SPP5/P1B" x="35.56" y="-5.08" length="short" rot="R180"/>
<pin name="RD6/SPP6/P1C" x="35.56" y="-2.54" length="short" rot="R180"/>
<pin name="RD7/SPP7/P1D" x="35.56" y="0" length="short" rot="R180"/>
<pin name="VSS" x="-35.56" y="-2.54" length="short" direction="pwr"/>
<pin name="VDD" x="-35.56" y="0" length="short" direction="pwr"/>
<pin name="RB0/AN12/INT0/LFT0/SDI/SDA" x="35.56" y="7.62" length="short" rot="R180"/>
<pin name="RB1/AN10/INT1/SCK/SCL" x="35.56" y="10.16" length="short" rot="R180"/>
<pin name="RB2/AN8/INT2/VMO" x="35.56" y="12.7" length="short" rot="R180"/>
<pin name="RB3/AN9/CCP2/VPO" x="35.56" y="15.24" length="short" rot="R180"/>
<pin name="RB4/AN11/KBI0/CSSPP" x="35.56" y="17.78" length="short" rot="R180"/>
<pin name="RB5/KBI1/PGM" x="35.56" y="20.32" length="short" rot="R180"/>
<pin name="RB6/KBI2/PGC" x="35.56" y="22.86" length="short" rot="R180"/>
<pin name="RB7/BKI3/PGD" x="35.56" y="25.4" length="short" rot="R180"/>
<pin name="!MCLR!/VPP/RE3" x="-35.56" y="25.4" length="short" direction="in"/>
<pin name="RA0/AN0" x="-35.56" y="22.86" length="short"/>
<pin name="RA1/AN1" x="-35.56" y="20.32" length="short"/>
<pin name="RA2/AN2/VREF-/CVREF" x="-35.56" y="17.78" length="short"/>
<pin name="RA3/AN3/VREF+" x="-35.56" y="15.24" length="short"/>
<pin name="RA4/T0CKI/CIOUT/RCV" x="-35.56" y="12.7" length="short"/>
<pin name="RA5/AN4/!SS!/HLVDIN/C2OUT" x="-35.56" y="10.16" length="short"/>
<pin name="RE0/AN5/CK1SPP" x="-35.56" y="7.62" length="short"/>
<pin name="RE1/AN6/CK2SPP" x="-35.56" y="5.08" length="short"/>
<pin name="RE2/AN7/OESPP" x="-35.56" y="2.54" length="short"/>
<pin name="VDD@1" x="35.56" y="5.08" length="short" direction="pwr" rot="R180"/>
<pin name="VSS@1" x="35.56" y="2.54" length="short" direction="pwr" rot="R180"/>
<pin name="OSC1/CLKI" x="-35.56" y="-5.08" length="short" direction="in"/>
<pin name="RA6/OSC2/CLKO" x="-35.56" y="-7.62" length="short" direction="out"/>
<pin name="RC0/TIOSO/T13CKI" x="-35.56" y="-10.16" length="short"/>
<pin name="RC1/T1OSI/ICCP2/!UOE" x="-35.56" y="-12.7" length="short"/>
<pin name="RC2/CCP1/P1A" x="-35.56" y="-15.24" length="short"/>
<pin name="VUSB" x="-35.56" y="-17.78" length="short"/>
<pin name="RD0/SPP0" x="-35.56" y="-20.32" length="short"/>
<pin name="RD1/SPP1" x="-35.56" y="-22.86" length="short"/>
<pin name="RD2/SPP2" x="35.56" y="-22.86" length="short" rot="R180"/>
<pin name="RD3/SPP3" x="35.56" y="-20.32" length="short" rot="R180"/>
<pin name="RC4/D-/VM" x="35.56" y="-17.78" length="short" rot="R180"/>
<pin name="RC5/D+/VP" x="35.56" y="-15.24" length="short" rot="R180"/>
<pin name="RC6/TX/CK" x="35.56" y="-12.7" length="short" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PIC18F4*_40" prefix="IC">
<description>&lt;b&gt;USB Microcontrollers with nanoWatt Technology&lt;/b&gt; High-Performance, Enhanced Flash, 28/40/44-Pin, &lt;p&gt;
Source: http://ww1.microchip.com/downloads/en/devicedoc/39632c.pdf</description>
<gates>
<gate name="G$1" symbol="PIC18F4455_40" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIL40">
<connects>
<connect gate="G$1" pin="!MCLR!/VPP/RE3" pad="1"/>
<connect gate="G$1" pin="OSC1/CLKI" pad="13"/>
<connect gate="G$1" pin="RA0/AN0" pad="2"/>
<connect gate="G$1" pin="RA1/AN1" pad="3"/>
<connect gate="G$1" pin="RA2/AN2/VREF-/CVREF" pad="4"/>
<connect gate="G$1" pin="RA3/AN3/VREF+" pad="5"/>
<connect gate="G$1" pin="RA4/T0CKI/CIOUT/RCV" pad="6"/>
<connect gate="G$1" pin="RA5/AN4/!SS!/HLVDIN/C2OUT" pad="7"/>
<connect gate="G$1" pin="RA6/OSC2/CLKO" pad="14"/>
<connect gate="G$1" pin="RB0/AN12/INT0/LFT0/SDI/SDA" pad="33"/>
<connect gate="G$1" pin="RB1/AN10/INT1/SCK/SCL" pad="34"/>
<connect gate="G$1" pin="RB2/AN8/INT2/VMO" pad="35"/>
<connect gate="G$1" pin="RB3/AN9/CCP2/VPO" pad="36"/>
<connect gate="G$1" pin="RB4/AN11/KBI0/CSSPP" pad="37"/>
<connect gate="G$1" pin="RB5/KBI1/PGM" pad="38"/>
<connect gate="G$1" pin="RB6/KBI2/PGC" pad="39"/>
<connect gate="G$1" pin="RB7/BKI3/PGD" pad="40"/>
<connect gate="G$1" pin="RC0/TIOSO/T13CKI" pad="15"/>
<connect gate="G$1" pin="RC1/T1OSI/ICCP2/!UOE" pad="16"/>
<connect gate="G$1" pin="RC2/CCP1/P1A" pad="17"/>
<connect gate="G$1" pin="RC4/D-/VM" pad="23"/>
<connect gate="G$1" pin="RC5/D+/VP" pad="24"/>
<connect gate="G$1" pin="RC6/TX/CK" pad="25"/>
<connect gate="G$1" pin="RC7/RX/DT/SDO" pad="26"/>
<connect gate="G$1" pin="RD0/SPP0" pad="19"/>
<connect gate="G$1" pin="RD1/SPP1" pad="20"/>
<connect gate="G$1" pin="RD2/SPP2" pad="21"/>
<connect gate="G$1" pin="RD3/SPP3" pad="22"/>
<connect gate="G$1" pin="RD4/SPP4" pad="27"/>
<connect gate="G$1" pin="RD5/SPP5/P1B" pad="28"/>
<connect gate="G$1" pin="RD6/SPP6/P1C" pad="29"/>
<connect gate="G$1" pin="RD7/SPP7/P1D" pad="30"/>
<connect gate="G$1" pin="RE0/AN5/CK1SPP" pad="8"/>
<connect gate="G$1" pin="RE1/AN6/CK2SPP" pad="9"/>
<connect gate="G$1" pin="RE2/AN7/OESPP" pad="10"/>
<connect gate="G$1" pin="VDD" pad="11"/>
<connect gate="G$1" pin="VDD@1" pad="32"/>
<connect gate="G$1" pin="VSS" pad="12"/>
<connect gate="G$1" pin="VSS@1" pad="31"/>
<connect gate="G$1" pin="VUSB" pad="18"/>
</connects>
<technologies>
<technology name="455">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="PIC18F4455-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="9321314" constant="no"/>
<attribute name="OC_NEWARK" value="05K2028" constant="no"/>
</technology>
<technology name="550">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="PIC18F4550-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="9321357" constant="no"/>
<attribute name="OC_NEWARK" value="74K8623" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-garry">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;a href="www.mpe-connector.de"&gt;Menufacturer&lt;/a&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="332-10">
<description>&lt;b&gt;10 Pin - 2mm Dual Row&lt;/b&gt;&lt;p&gt;
Source: www.mpe-connector.de / garry_shortform_2012.pdf</description>
<wire x1="-4.85" y1="-1.9" x2="4.85" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="4.85" y1="-1.9" x2="4.85" y2="-0.4" width="0.2032" layer="21"/>
<wire x1="4.85" y1="0.4" x2="4.85" y2="1.9" width="0.2032" layer="21"/>
<wire x1="4.85" y1="1.9" x2="-4.85" y2="1.9" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="1.9" x2="-4.85" y2="0.4" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-0.4" x2="-4.85" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="0.4" x2="-4.85" y2="-0.4" width="0.2032" layer="21" curve="-129.185"/>
<wire x1="4.85" y1="-0.4" x2="4.85" y2="0.4" width="0.2032" layer="21" curve="-129.185"/>
<pad name="1" x="-4" y="-1" drill="0.9" diameter="1.27"/>
<pad name="2" x="-4" y="1" drill="0.9" diameter="1.27"/>
<pad name="3" x="-2" y="-1" drill="0.9" diameter="1.27"/>
<pad name="4" x="-2" y="1" drill="0.9" diameter="1.27"/>
<pad name="5" x="0" y="-1" drill="0.9" diameter="1.27"/>
<pad name="6" x="0" y="1" drill="0.9" diameter="1.27"/>
<pad name="7" x="2" y="-1" drill="0.9" diameter="1.27"/>
<pad name="8" x="2" y="1" drill="0.9" diameter="1.27"/>
<pad name="9" x="4" y="-1" drill="0.9" diameter="1.27"/>
<pad name="10" x="4" y="1" drill="0.9" diameter="1.27"/>
<text x="-4.65" y="-1.75" size="0.3048" layer="21" font="vector">1</text>
<rectangle x1="-4.25" y1="-1.25" x2="-3.75" y2="-0.75" layer="51"/>
<rectangle x1="-4.25" y1="0.75" x2="-3.75" y2="1.25" layer="51"/>
<rectangle x1="-2.25" y1="-1.25" x2="-1.75" y2="-0.75" layer="51"/>
<rectangle x1="-2.25" y1="0.75" x2="-1.75" y2="1.25" layer="51"/>
<rectangle x1="-0.25" y1="-1.25" x2="0.25" y2="-0.75" layer="51"/>
<rectangle x1="-0.25" y1="0.75" x2="0.25" y2="1.25" layer="51"/>
<rectangle x1="1.75" y1="-1.25" x2="2.25" y2="-0.75" layer="51"/>
<rectangle x1="1.75" y1="0.75" x2="2.25" y2="1.25" layer="51"/>
<rectangle x1="3.75" y1="-1.25" x2="4.25" y2="-0.75" layer="51"/>
<rectangle x1="3.75" y1="0.75" x2="4.25" y2="1.25" layer="51"/>
<text x="-4.62" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="1.73" y="2.54" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="-4" y1="1" x2="-4" y2="-6" width="0.55" layer="51"/>
<wire x1="-2" y1="1" x2="-2" y2="-6" width="0.55" layer="51"/>
<wire x1="0" y1="1" x2="0" y2="-6" width="0.55" layer="51"/>
<wire x1="2" y1="1" x2="2" y2="-6" width="0.55" layer="51"/>
<wire x1="4" y1="1" x2="4" y2="-6" width="0.55" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="332-10" prefix="X">
<description>&lt;b&gt;10 Pin - 2mm Dual Row&lt;/b&gt;&lt;p&gt;
Source: www.mpe-connector.de / garry_shortform_2012.pdf</description>
<gates>
<gate name="-1" symbol="MV" x="-10.16" y="5.08" addlevel="always"/>
<gate name="-2" symbol="MV" x="10.16" y="5.08" addlevel="always"/>
<gate name="-3" symbol="M" x="-10.16" y="2.54" addlevel="always"/>
<gate name="-4" symbol="M" x="10.16" y="2.54" addlevel="always"/>
<gate name="-5" symbol="M" x="-10.16" y="0" addlevel="always"/>
<gate name="-6" symbol="M" x="10.16" y="0" addlevel="always"/>
<gate name="-7" symbol="M" x="-10.16" y="-2.54" addlevel="always"/>
<gate name="-8" symbol="M" x="10.16" y="-2.54" addlevel="always"/>
<gate name="-9" symbol="M" x="-10.16" y="-5.08" addlevel="always"/>
<gate name="-10" symbol="M" x="10.16" y="-5.08" addlevel="always"/>
</gates>
<devices>
<device name="" package="332-10">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-10" pin="S" pad="10"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
<connect gate="-5" pin="S" pad="5"/>
<connect gate="-6" pin="S" pad="6"/>
<connect gate="-7" pin="S" pad="7"/>
<connect gate="-8" pin="S" pad="8"/>
<connect gate="-9" pin="S" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="maxim" deviceset="MAX232" device=""/>
<part name="IC2" library="microchip" deviceset="PIC18F4*_40" device="" technology="550"/>
<part name="X1" library="con-garry" deviceset="332-10" device=""/>
<part name="X2" library="con-garry" deviceset="332-10" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="33.02" y="43.18"/>
<instance part="IC2" gate="G$1" x="99.06" y="43.18"/>
<instance part="X1" gate="-1" x="25.4" y="99.06"/>
<instance part="X1" gate="-2" x="45.72" y="99.06"/>
<instance part="X1" gate="-3" x="25.4" y="96.52"/>
<instance part="X1" gate="-4" x="45.72" y="96.52"/>
<instance part="X1" gate="-5" x="25.4" y="93.98"/>
<instance part="X1" gate="-6" x="45.72" y="93.98"/>
<instance part="X1" gate="-7" x="25.4" y="91.44"/>
<instance part="X1" gate="-8" x="45.72" y="91.44"/>
<instance part="X1" gate="-9" x="25.4" y="88.9"/>
<instance part="X1" gate="-10" x="45.72" y="88.9"/>
<instance part="X2" gate="-1" x="91.44" y="99.06"/>
<instance part="X2" gate="-2" x="111.76" y="99.06"/>
<instance part="X2" gate="-3" x="91.44" y="96.52"/>
<instance part="X2" gate="-4" x="111.76" y="96.52"/>
<instance part="X2" gate="-5" x="91.44" y="93.98"/>
<instance part="X2" gate="-6" x="111.76" y="93.98"/>
<instance part="X2" gate="-7" x="91.44" y="91.44"/>
<instance part="X2" gate="-8" x="111.76" y="91.44"/>
<instance part="X2" gate="-9" x="91.44" y="88.9"/>
<instance part="X2" gate="-10" x="111.76" y="88.9"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
