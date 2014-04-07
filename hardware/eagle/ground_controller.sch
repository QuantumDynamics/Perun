<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
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
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="10" fill="1" visible="no" active="no"/>
<layer number="58" name="bCAD" color="11" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="no" active="no"/>
<layer number="201" name="201bmp" color="2" fill="1" visible="no" active="no"/>
<layer number="202" name="202bmp" color="3" fill="1" visible="no" active="no"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="stm32f4">
<description>ST Cortex-M3 STM32F101/103 processor family  in LQFP100, 64, 48 and VFQPFN36 pin versions</description>
<packages>
<package name="TQFP100">
<wire x1="-7" y1="6.25" x2="-6.25" y2="7" width="0.254" layer="21"/>
<wire x1="-6.25" y1="7" x2="6.75" y2="7" width="0.254" layer="21"/>
<wire x1="6.75" y1="7" x2="7" y2="6.75" width="0.254" layer="21"/>
<wire x1="7" y1="6.75" x2="7" y2="-6.75" width="0.254" layer="21"/>
<wire x1="7" y1="-6.75" x2="6.75" y2="-7" width="0.254" layer="21"/>
<wire x1="6.75" y1="-7" x2="-6.75" y2="-7" width="0.254" layer="21"/>
<wire x1="-6.75" y1="-7" x2="-7" y2="-6.75" width="0.254" layer="21"/>
<wire x1="-7" y1="-6.75" x2="-7" y2="6.25" width="0.254" layer="21"/>
<circle x="-6" y="6" radius="0.2499" width="0.254" layer="21"/>
<smd name="1" x="-8" y="6" dx="1.5" dy="0.3" layer="1"/>
<smd name="2" x="-8" y="5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="3" x="-8" y="5" dx="1.5" dy="0.3" layer="1"/>
<smd name="4" x="-8" y="4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="5" x="-8" y="4" dx="1.5" dy="0.3" layer="1"/>
<smd name="6" x="-8" y="3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="7" x="-8" y="3" dx="1.5" dy="0.3" layer="1"/>
<smd name="8" x="-8" y="2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="9" x="-8" y="2" dx="1.5" dy="0.3" layer="1"/>
<smd name="10" x="-8" y="1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="11" x="-8" y="1" dx="1.5" dy="0.3" layer="1"/>
<smd name="12" x="-8" y="0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="13" x="-8" y="0" dx="1.5" dy="0.3" layer="1"/>
<smd name="14" x="-8" y="-0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="15" x="-8" y="-1" dx="1.5" dy="0.3" layer="1"/>
<smd name="16" x="-8" y="-1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="17" x="-8" y="-2" dx="1.5" dy="0.3" layer="1"/>
<smd name="18" x="-8" y="-2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="19" x="-8" y="-3" dx="1.5" dy="0.3" layer="1"/>
<smd name="20" x="-8" y="-3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="21" x="-8" y="-4" dx="1.5" dy="0.3" layer="1"/>
<smd name="22" x="-8" y="-4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="23" x="-8" y="-5" dx="1.5" dy="0.3" layer="1"/>
<smd name="24" x="-8" y="-5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="25" x="-8" y="-6" dx="1.5" dy="0.3" layer="1"/>
<smd name="26" x="-6" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="27" x="-5.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="28" x="-5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="29" x="-4.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="30" x="-4" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="31" x="-3.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="32" x="-3" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="33" x="-2.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="34" x="-2" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="35" x="-1.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="36" x="-1" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="37" x="-0.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="38" x="0" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="39" x="0.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="40" x="1" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="41" x="1.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="42" x="2" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="43" x="2.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="44" x="3" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="45" x="3.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="46" x="4" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="47" x="4.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="48" x="5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="49" x="5.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="50" x="6" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="51" x="8" y="-6" dx="1.5" dy="0.3" layer="1"/>
<smd name="52" x="8" y="-5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="53" x="8" y="-5" dx="1.5" dy="0.3" layer="1"/>
<smd name="54" x="8" y="-4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="55" x="8" y="-4" dx="1.5" dy="0.3" layer="1"/>
<smd name="56" x="8" y="-3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="57" x="8" y="-3" dx="1.5" dy="0.3" layer="1"/>
<smd name="58" x="8" y="-2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="59" x="8" y="-2" dx="1.5" dy="0.3" layer="1"/>
<smd name="60" x="8" y="-1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="61" x="8" y="-1" dx="1.5" dy="0.35" layer="1"/>
<smd name="62" x="8" y="-0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="63" x="8" y="0" dx="1.5" dy="0.3" layer="1"/>
<smd name="64" x="8" y="0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="65" x="8" y="1" dx="1.5" dy="0.3" layer="1"/>
<smd name="66" x="8" y="1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="67" x="8" y="2" dx="1.5" dy="0.3" layer="1"/>
<smd name="68" x="8" y="2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="69" x="8" y="3" dx="1.5" dy="0.3" layer="1"/>
<smd name="70" x="8" y="3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="71" x="8" y="4" dx="1.5" dy="0.35" layer="1"/>
<smd name="72" x="8" y="4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="73" x="8" y="5" dx="1.5" dy="0.3" layer="1"/>
<smd name="74" x="8" y="5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="75" x="8" y="6" dx="1.5" dy="0.3" layer="1"/>
<smd name="76" x="6" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="77" x="5.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="78" x="5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="79" x="4.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="80" x="4" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="81" x="3.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="82" x="3" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="83" x="2.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="84" x="2" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="85" x="1.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="86" x="1" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="87" x="0.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="88" x="0" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="89" x="-0.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="90" x="-1" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="91" x="-1.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="92" x="-2" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="93" x="-2.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="94" x="-3" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="95" x="-3.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="96" x="-4" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="97" x="-4.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="98" x="-5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="99" x="-5.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="100" x="-6" y="8" dx="0.3" dy="1.5" layer="1"/>
<text x="-5.76" y="9.2451" size="1.27" layer="25">&gt;NAME</text>
<text x="-5.0851" y="0.8951" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-8.1999" y1="5.8499" x2="-7.1501" y2="6.1501" layer="51"/>
<rectangle x1="-8.1999" y1="5.35" x2="-7.1501" y2="5.65" layer="51"/>
<rectangle x1="-8.1999" y1="4.8499" x2="-7.1501" y2="5.1501" layer="51"/>
<rectangle x1="-8.1999" y1="4.35" x2="-7.1501" y2="4.65" layer="51"/>
<rectangle x1="-8.1999" y1="3.8499" x2="-7.1501" y2="4.1501" layer="51"/>
<rectangle x1="-8.1999" y1="3.35" x2="-7.1501" y2="3.65" layer="51"/>
<rectangle x1="-8.1999" y1="2.8499" x2="-7.1501" y2="3.1501" layer="51"/>
<rectangle x1="-8.1999" y1="2.35" x2="-7.1501" y2="2.65" layer="51"/>
<rectangle x1="-8.1999" y1="1.8499" x2="-7.1501" y2="2.1501" layer="51"/>
<rectangle x1="-8.1999" y1="1.35" x2="-7.1501" y2="1.65" layer="51"/>
<rectangle x1="-8.1999" y1="0.8499" x2="-7.1501" y2="1.1501" layer="51"/>
<rectangle x1="-8.1999" y1="0.35" x2="-7.1501" y2="0.65" layer="51"/>
<rectangle x1="-8.1999" y1="-0.1501" x2="-7.1501" y2="0.1501" layer="51"/>
<rectangle x1="-8.1999" y1="-0.65" x2="-7.1501" y2="-0.35" layer="51"/>
<rectangle x1="-8.1999" y1="-1.1501" x2="-7.1501" y2="-0.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-1.65" x2="-7.1501" y2="-1.35" layer="51"/>
<rectangle x1="-8.1999" y1="-2.1501" x2="-7.1501" y2="-1.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-2.65" x2="-7.1501" y2="-2.35" layer="51"/>
<rectangle x1="-8.1999" y1="-3.1501" x2="-7.1501" y2="-2.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-3.65" x2="-7.1501" y2="-3.35" layer="51"/>
<rectangle x1="-8.1999" y1="-4.1501" x2="-7.1501" y2="-3.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-4.65" x2="-7.1501" y2="-4.35" layer="51"/>
<rectangle x1="-8.1999" y1="-5.1501" x2="-7.1501" y2="-4.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-5.65" x2="-7.1501" y2="-5.35" layer="51"/>
<rectangle x1="-8.1999" y1="-6.1501" x2="-7.1501" y2="-5.8499" layer="51"/>
<rectangle x1="-6.1501" y1="-8.1999" x2="-5.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-5.65" y1="-8.1999" x2="-5.35" y2="-7.1501" layer="51"/>
<rectangle x1="-5.1501" y1="-8.1999" x2="-4.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-4.65" y1="-8.1999" x2="-4.35" y2="-7.1501" layer="51"/>
<rectangle x1="-4.1501" y1="-8.1999" x2="-3.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-3.65" y1="-8.1999" x2="-3.35" y2="-7.1501" layer="51"/>
<rectangle x1="-3.1501" y1="-8.1999" x2="-2.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-2.65" y1="-8.1999" x2="-2.35" y2="-7.1501" layer="51"/>
<rectangle x1="-2.1501" y1="-8.1999" x2="-1.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-1.65" y1="-8.1999" x2="-1.35" y2="-7.1501" layer="51"/>
<rectangle x1="-1.1501" y1="-8.1999" x2="-0.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-0.65" y1="-8.1999" x2="-0.35" y2="-7.1501" layer="51"/>
<rectangle x1="-0.1501" y1="-8.1999" x2="0.1501" y2="-7.1501" layer="51"/>
<rectangle x1="0.35" y1="-8.1999" x2="0.65" y2="-7.1501" layer="51"/>
<rectangle x1="0.8499" y1="-8.1999" x2="1.1501" y2="-7.1501" layer="51"/>
<rectangle x1="1.35" y1="-8.1999" x2="1.65" y2="-7.1501" layer="51"/>
<rectangle x1="1.8499" y1="-8.1999" x2="2.1501" y2="-7.1501" layer="51"/>
<rectangle x1="2.35" y1="-8.1999" x2="2.65" y2="-7.1501" layer="51"/>
<rectangle x1="2.8499" y1="-8.1999" x2="3.1501" y2="-7.1501" layer="51"/>
<rectangle x1="3.35" y1="-8.1999" x2="3.65" y2="-7.1501" layer="51"/>
<rectangle x1="3.8499" y1="-8.1999" x2="4.1501" y2="-7.1501" layer="51"/>
<rectangle x1="4.35" y1="-8.1999" x2="4.65" y2="-7.1501" layer="51"/>
<rectangle x1="4.8499" y1="-8.1999" x2="5.1501" y2="-7.1501" layer="51"/>
<rectangle x1="5.35" y1="-8.1999" x2="5.65" y2="-7.1501" layer="51"/>
<rectangle x1="5.8499" y1="-8.1999" x2="6.1501" y2="-7.1501" layer="51"/>
<rectangle x1="7.1501" y1="-6.1501" x2="8.1999" y2="-5.8499" layer="51"/>
<rectangle x1="7.1501" y1="-5.65" x2="8.1999" y2="-5.35" layer="51"/>
<rectangle x1="7.1501" y1="-5.1501" x2="8.1999" y2="-4.8499" layer="51"/>
<rectangle x1="7.1501" y1="-4.65" x2="8.1999" y2="-4.35" layer="51"/>
<rectangle x1="7.1501" y1="-4.1501" x2="8.1999" y2="-3.8499" layer="51"/>
<rectangle x1="7.1501" y1="-3.65" x2="8.1999" y2="-3.35" layer="51"/>
<rectangle x1="7.1501" y1="-3.1501" x2="8.1999" y2="-2.8499" layer="51"/>
<rectangle x1="7.1501" y1="-2.65" x2="8.1999" y2="-2.35" layer="51"/>
<rectangle x1="7.1501" y1="-2.1501" x2="8.1999" y2="-1.8499" layer="51"/>
<rectangle x1="7.1501" y1="-1.65" x2="8.1999" y2="-1.35" layer="51"/>
<rectangle x1="7.1501" y1="-1.1501" x2="8.1999" y2="-0.8499" layer="51"/>
<rectangle x1="7.1501" y1="-0.65" x2="8.1999" y2="-0.35" layer="51"/>
<rectangle x1="7.1501" y1="-0.1501" x2="8.1999" y2="0.1501" layer="51"/>
<rectangle x1="7.1501" y1="0.35" x2="8.1999" y2="0.65" layer="51"/>
<rectangle x1="7.1501" y1="0.8499" x2="8.1999" y2="1.1501" layer="51"/>
<rectangle x1="7.1501" y1="1.35" x2="8.1999" y2="1.65" layer="51"/>
<rectangle x1="7.1501" y1="1.8499" x2="8.1999" y2="2.1501" layer="51"/>
<rectangle x1="7.1501" y1="2.35" x2="8.1999" y2="2.65" layer="51"/>
<rectangle x1="7.1501" y1="2.8499" x2="8.1999" y2="3.1501" layer="51"/>
<rectangle x1="7.1501" y1="3.35" x2="8.1999" y2="3.65" layer="51"/>
<rectangle x1="7.1501" y1="3.8499" x2="8.1999" y2="4.1501" layer="51"/>
<rectangle x1="7.1501" y1="4.35" x2="8.1999" y2="4.65" layer="51"/>
<rectangle x1="7.1501" y1="4.8499" x2="8.1999" y2="5.1501" layer="51"/>
<rectangle x1="7.1501" y1="5.35" x2="8.1999" y2="5.65" layer="51"/>
<rectangle x1="7.1501" y1="5.8499" x2="8.1999" y2="6.1501" layer="51"/>
<rectangle x1="5.8499" y1="7.1501" x2="6.1501" y2="8.1999" layer="51"/>
<rectangle x1="5.35" y1="7.1501" x2="5.65" y2="8.1999" layer="51"/>
<rectangle x1="4.8499" y1="7.1501" x2="5.1501" y2="8.1999" layer="51"/>
<rectangle x1="4.35" y1="7.1501" x2="4.65" y2="8.1999" layer="51"/>
<rectangle x1="3.8499" y1="7.1501" x2="4.1501" y2="8.1999" layer="51"/>
<rectangle x1="3.35" y1="7.1501" x2="3.65" y2="8.1999" layer="51"/>
<rectangle x1="2.8499" y1="7.1501" x2="3.1501" y2="8.1999" layer="51"/>
<rectangle x1="2.35" y1="7.1501" x2="2.65" y2="8.1999" layer="51"/>
<rectangle x1="1.8499" y1="7.1501" x2="2.1501" y2="8.1999" layer="51"/>
<rectangle x1="1.35" y1="7.1501" x2="1.65" y2="8.1999" layer="51"/>
<rectangle x1="0.8499" y1="7.1501" x2="1.1501" y2="8.1999" layer="51"/>
<rectangle x1="0.35" y1="7.1501" x2="0.65" y2="8.1999" layer="51"/>
<rectangle x1="-0.1501" y1="7.1501" x2="0.1501" y2="8.1999" layer="51"/>
<rectangle x1="-0.65" y1="7.1501" x2="-0.35" y2="8.1999" layer="51"/>
<rectangle x1="-1.1501" y1="7.1501" x2="-0.8499" y2="8.1999" layer="51"/>
<rectangle x1="-1.65" y1="7.1501" x2="-1.35" y2="8.1999" layer="51"/>
<rectangle x1="-2.1501" y1="7.1501" x2="-1.8499" y2="8.1999" layer="51"/>
<rectangle x1="-2.65" y1="7.1501" x2="-2.35" y2="8.1999" layer="51"/>
<rectangle x1="-3.1501" y1="7.1501" x2="-2.8499" y2="8.1999" layer="51"/>
<rectangle x1="-3.65" y1="7.1501" x2="-3.35" y2="8.1999" layer="51"/>
<rectangle x1="-4.1501" y1="7.1501" x2="-3.8499" y2="8.1999" layer="51"/>
<rectangle x1="-4.65" y1="7.1501" x2="-4.35" y2="8.1999" layer="51"/>
<rectangle x1="-5.1501" y1="7.1501" x2="-4.8499" y2="8.1999" layer="51"/>
<rectangle x1="-5.65" y1="7.1501" x2="-5.35" y2="8.1999" layer="51"/>
<rectangle x1="-6.1501" y1="7.1501" x2="-5.8499" y2="8.1999" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="COMPLETE_100_F4XX">
<wire x1="0" y1="147.32" x2="68.58" y2="147.32" width="0.254" layer="94"/>
<wire x1="68.58" y1="147.32" x2="68.58" y2="0" width="0.254" layer="94"/>
<wire x1="68.58" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="147.32" width="0.254" layer="94"/>
<text x="0" y="148.59" size="1.778" layer="95">&gt;NAME</text>
<text x="68.58" y="-1.27" size="1.778" layer="96" rot="R180">STM32F40x</text>
<pin name="PA0/ETH_MII_CRS/ADC123_IN0(5T)" x="-5.08" y="83.82" length="middle"/>
<pin name="PA1/ETH_RMII_RX_CLK/ADC123_IN1(5T)" x="-5.08" y="81.28" length="middle"/>
<pin name="PA2/ETH_MDIO/ADC123_IN2(5T)" x="-5.08" y="78.74" length="middle"/>
<pin name="PA3/ETH_MII_COL/ADC123_IN2(5T)" x="-5.08" y="76.2" length="middle"/>
<pin name="PA4/ADC12_IN4" x="-5.08" y="73.66" length="middle"/>
<pin name="PA5/SPI1_SCK/ADC12_IN5" x="-5.08" y="71.12" length="middle"/>
<pin name="PA6/SPI1_MISO/ADC12_IN6(5T)" x="-5.08" y="68.58" length="middle"/>
<pin name="PA7/ETH_MII_RX_DV/ADC12_IN7(5T)" x="-5.08" y="66.04" length="middle"/>
<pin name="PA8/MCO1(5T)" x="-5.08" y="63.5" length="middle"/>
<pin name="PA9/USART1_TX(5T)" x="-5.08" y="60.96" length="middle"/>
<pin name="PA10/USART1_RX(5T)" x="-5.08" y="58.42" length="middle"/>
<pin name="PA11/USART1_CTS(5T)" x="-5.08" y="55.88" length="middle"/>
<pin name="PA12/USART1_RTS(5T)" x="-5.08" y="53.34" length="middle"/>
<pin name="PA13/JTMS-SWDAT(5T)" x="-5.08" y="50.8" length="middle"/>
<pin name="PA14/JTCK-SWCLK(5T)" x="-5.08" y="48.26" length="middle"/>
<pin name="PA15/JTDI(5T)" x="-5.08" y="45.72" length="middle"/>
<pin name="PB0/ETH_MII_RXD2/ADC12_IN8(5T)" x="-5.08" y="40.64" length="middle"/>
<pin name="PB1/ETH_MII_RXD3/ADC12_IN9(5T)" x="-5.08" y="38.1" length="middle"/>
<pin name="PB2/BOOT1(5T)" x="-5.08" y="35.56" length="middle"/>
<pin name="PB3/JTDO(5T)" x="-5.08" y="33.02" length="middle"/>
<pin name="PB4/JNTRST(5T)" x="-5.08" y="30.48" length="middle"/>
<pin name="PB5/TIM3_CH2(5T)" x="-5.08" y="27.94" length="middle"/>
<pin name="PB6/I2C1_SCL(5T)" x="-5.08" y="25.4" length="middle"/>
<pin name="PB7/I2C1_SDA(5T)" x="-5.08" y="22.86" length="middle"/>
<pin name="PB8/TIM10_CH1(5T)" x="-5.08" y="20.32" length="middle"/>
<pin name="PB9/TIM11_CH1(5T)" x="-5.08" y="17.78" length="middle"/>
<pin name="PB10/ETH_MII_RX_ER(5T)" x="-5.08" y="15.24" length="middle"/>
<pin name="PB11/ETH_MII_TX_EN(5T)" x="-5.08" y="12.7" length="middle"/>
<pin name="PB12/ETH_MII_TXD0(5T)" x="-5.08" y="10.16" length="middle"/>
<pin name="PB13/ETH_MII_TXD1(5T)" x="-5.08" y="7.62" length="middle"/>
<pin name="PB14/TIM8_CH2N(5T)" x="-5.08" y="5.08" length="middle"/>
<pin name="PB15/TIM8_CH3N(5T)" x="-5.08" y="2.54" length="middle"/>
<pin name="VBAT" x="-5.08" y="144.78" length="middle"/>
<pin name="VDD_1" x="-5.08" y="119.38" length="middle"/>
<pin name="VDD_2" x="-5.08" y="116.84" length="middle"/>
<pin name="VDD_3" x="-5.08" y="114.3" length="middle"/>
<pin name="VSS_1" x="-5.08" y="99.06" length="middle"/>
<pin name="VSS_2" x="-5.08" y="96.52" length="middle"/>
<pin name="VSS_3" x="-5.08" y="93.98" length="middle"/>
<pin name="VSSA" x="-5.08" y="127" length="middle"/>
<pin name="BOOT0" x="73.66" y="5.08" length="middle" rot="R180"/>
<pin name="NRST" x="73.66" y="2.54" length="middle" rot="R180"/>
<pin name="VDDA" x="-5.08" y="129.54" length="middle"/>
<pin name="PC13(5T)" x="73.66" y="111.76" length="middle" rot="R180"/>
<pin name="PC14/OSC32_IN(5T)" x="73.66" y="109.22" length="middle" rot="R180"/>
<pin name="PC15/OSC32_OUT(5T)" x="73.66" y="106.68" length="middle" rot="R180"/>
<pin name="PD0/CAN1_RX(5T)" x="73.66" y="101.6" length="middle" rot="R180"/>
<pin name="PD1/CAN1_TX(5T)" x="73.66" y="99.06" length="middle" rot="R180"/>
<pin name="PC0/ADC123_IN10(5T)" x="73.66" y="144.78" length="middle" rot="R180"/>
<pin name="PC1/ETH_MDC/ADC123_IN11(5T)" x="73.66" y="142.24" length="middle" rot="R180"/>
<pin name="PC2/ETH_MII_TXD2/ADC123_IN12(5T)" x="73.66" y="139.7" length="middle" rot="R180"/>
<pin name="PC3/ETH_MII_TX_CLK/ADC123_IN13(5T)" x="73.66" y="137.16" length="middle" rot="R180"/>
<pin name="PC4/ETH_MII_RXD0/ADC12_IN14(5T)" x="73.66" y="134.62" length="middle" rot="R180"/>
<pin name="PC5/ETH_MII_RXD1/ADC12_IN15(5T)" x="73.66" y="132.08" length="middle" rot="R180"/>
<pin name="PC6/TIM3_CH1(5T)" x="73.66" y="129.54" length="middle" rot="R180"/>
<pin name="PC7/TIM8_CH2(5T)" x="73.66" y="127" length="middle" rot="R180"/>
<pin name="PC8/TIM8_CH3(5T)" x="73.66" y="124.46" length="middle" rot="R180"/>
<pin name="PC9/TIM3_CH4(5T)" x="73.66" y="121.92" length="middle" rot="R180"/>
<pin name="PC10/UART4_TX(5T)" x="73.66" y="119.38" length="middle" rot="R180"/>
<pin name="PC11/UART4_RX(5T)" x="73.66" y="116.84" length="middle" rot="R180"/>
<pin name="PC12/UART5_TX(5T)" x="73.66" y="114.3" length="middle" rot="R180"/>
<pin name="VDD_4" x="-5.08" y="111.76" length="middle"/>
<pin name="VSS_4" x="-5.08" y="91.44" length="middle"/>
<pin name="PD2/UART5_RX(5T)" x="73.66" y="96.52" length="middle" rot="R180"/>
<pin name="PE0(5T)" x="73.66" y="58.42" length="middle" rot="R180"/>
<pin name="PE1(5T)" x="73.66" y="55.88" length="middle" rot="R180"/>
<pin name="PE2/ETH_MII_TXD3(5T)" x="73.66" y="53.34" length="middle" rot="R180"/>
<pin name="PE3(5T)" x="73.66" y="50.8" length="middle" rot="R180"/>
<pin name="PE4(5T)" x="73.66" y="48.26" length="middle" rot="R180"/>
<pin name="PE5/TIM9_CH1(5T)" x="73.66" y="45.72" length="middle" rot="R180"/>
<pin name="PE6/TIM9_CH2(5T)" x="73.66" y="43.18" length="middle" rot="R180"/>
<pin name="PE7/TIM1_ETR(5T)" x="73.66" y="40.64" length="middle" rot="R180"/>
<pin name="PE8/TIM1_CH1N(5T)" x="73.66" y="38.1" length="middle" rot="R180"/>
<pin name="PE9/TIM1_CH1(5T)" x="73.66" y="35.56" length="middle" rot="R180"/>
<pin name="PH0-OSC_IN(5T)" x="73.66" y="15.24" length="middle" rot="R180"/>
<pin name="PH1-OSC_OUT(5T)" x="73.66" y="12.7" length="middle" rot="R180"/>
<pin name="VREF+" x="-5.08" y="132.08" length="middle"/>
<pin name="PE10/TIM1_CH2N(5T)" x="73.66" y="33.02" length="middle" rot="R180"/>
<pin name="PE11/TIM1_CH2(5T)" x="73.66" y="30.48" length="middle" rot="R180"/>
<pin name="PE12/TIM1_CH3N(5T)" x="73.66" y="27.94" length="middle" rot="R180"/>
<pin name="PE13/TIM1_CH3(5T)" x="73.66" y="25.4" length="middle" rot="R180"/>
<pin name="PE14/TIM1_CH4(5T)" x="73.66" y="22.86" length="middle" rot="R180"/>
<pin name="PE15/TIM1_BKIN(5T)" x="73.66" y="20.32" length="middle" rot="R180"/>
<pin name="PD8/USART3_TX(5T)" x="73.66" y="81.28" length="middle" rot="R180"/>
<pin name="PD9/USART3_RX(5T)" x="73.66" y="78.74" length="middle" rot="R180"/>
<pin name="PD10(5T)" x="73.66" y="76.2" length="middle" rot="R180"/>
<pin name="PD11(5T)" x="73.66" y="73.66" length="middle" rot="R180"/>
<pin name="PD12/TIM4_CH1(5T)" x="73.66" y="71.12" length="middle" rot="R180"/>
<pin name="VCAP1" x="-5.08" y="142.24" length="middle"/>
<pin name="VCAP2" x="-5.08" y="139.7" length="middle"/>
<pin name="PD14/TIM4_CH3(5T)" x="73.66" y="66.04" length="middle" rot="R180"/>
<pin name="PD13/TIM4_CH2(5T)" x="73.66" y="68.58" length="middle" rot="R180"/>
<pin name="PD15/TIM4_CH4(5T)" x="73.66" y="63.5" length="middle" rot="R180"/>
<pin name="PD3(5T)" x="73.66" y="93.98" length="middle" rot="R180"/>
<pin name="PD4(5T)" x="73.66" y="91.44" length="middle" rot="R180"/>
<pin name="PD5/USART2_TX(5T)" x="73.66" y="88.9" length="middle" rot="R180"/>
<pin name="PD6/USART2_RX(5T)" x="73.66" y="86.36" length="middle" rot="R180"/>
<pin name="PD7(5T)" x="73.66" y="83.82" length="middle" rot="R180"/>
<pin name="VDD_5" x="-5.08" y="109.22" length="middle"/>
<pin name="VDD_6" x="-5.08" y="106.68" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="STM32F407V">
<description>STM32F407 100 pin LQFP&lt;br&gt;
&lt;br&gt;
reviewed: YES&lt;br&gt;
tested: YES&lt;br&gt;</description>
<gates>
<gate name="G$1" symbol="COMPLETE_100_F4XX" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP100">
<connects>
<connect gate="G$1" pin="BOOT0" pad="94"/>
<connect gate="G$1" pin="NRST" pad="14"/>
<connect gate="G$1" pin="PA0/ETH_MII_CRS/ADC123_IN0(5T)" pad="23"/>
<connect gate="G$1" pin="PA1/ETH_RMII_RX_CLK/ADC123_IN1(5T)" pad="24"/>
<connect gate="G$1" pin="PA10/USART1_RX(5T)" pad="69"/>
<connect gate="G$1" pin="PA11/USART1_CTS(5T)" pad="70"/>
<connect gate="G$1" pin="PA12/USART1_RTS(5T)" pad="71"/>
<connect gate="G$1" pin="PA13/JTMS-SWDAT(5T)" pad="72"/>
<connect gate="G$1" pin="PA14/JTCK-SWCLK(5T)" pad="76"/>
<connect gate="G$1" pin="PA15/JTDI(5T)" pad="77"/>
<connect gate="G$1" pin="PA2/ETH_MDIO/ADC123_IN2(5T)" pad="25"/>
<connect gate="G$1" pin="PA3/ETH_MII_COL/ADC123_IN2(5T)" pad="26"/>
<connect gate="G$1" pin="PA4/ADC12_IN4" pad="29"/>
<connect gate="G$1" pin="PA5/SPI1_SCK/ADC12_IN5" pad="30"/>
<connect gate="G$1" pin="PA6/SPI1_MISO/ADC12_IN6(5T)" pad="31"/>
<connect gate="G$1" pin="PA7/ETH_MII_RX_DV/ADC12_IN7(5T)" pad="32"/>
<connect gate="G$1" pin="PA8/MCO1(5T)" pad="67"/>
<connect gate="G$1" pin="PA9/USART1_TX(5T)" pad="68"/>
<connect gate="G$1" pin="PB0/ETH_MII_RXD2/ADC12_IN8(5T)" pad="35"/>
<connect gate="G$1" pin="PB1/ETH_MII_RXD3/ADC12_IN9(5T)" pad="36"/>
<connect gate="G$1" pin="PB10/ETH_MII_RX_ER(5T)" pad="47"/>
<connect gate="G$1" pin="PB11/ETH_MII_TX_EN(5T)" pad="48"/>
<connect gate="G$1" pin="PB12/ETH_MII_TXD0(5T)" pad="51"/>
<connect gate="G$1" pin="PB13/ETH_MII_TXD1(5T)" pad="52"/>
<connect gate="G$1" pin="PB14/TIM8_CH2N(5T)" pad="53"/>
<connect gate="G$1" pin="PB15/TIM8_CH3N(5T)" pad="54"/>
<connect gate="G$1" pin="PB2/BOOT1(5T)" pad="37"/>
<connect gate="G$1" pin="PB3/JTDO(5T)" pad="89"/>
<connect gate="G$1" pin="PB4/JNTRST(5T)" pad="90"/>
<connect gate="G$1" pin="PB5/TIM3_CH2(5T)" pad="91"/>
<connect gate="G$1" pin="PB6/I2C1_SCL(5T)" pad="92"/>
<connect gate="G$1" pin="PB7/I2C1_SDA(5T)" pad="93"/>
<connect gate="G$1" pin="PB8/TIM10_CH1(5T)" pad="95"/>
<connect gate="G$1" pin="PB9/TIM11_CH1(5T)" pad="96"/>
<connect gate="G$1" pin="PC0/ADC123_IN10(5T)" pad="15"/>
<connect gate="G$1" pin="PC1/ETH_MDC/ADC123_IN11(5T)" pad="16"/>
<connect gate="G$1" pin="PC10/UART4_TX(5T)" pad="78"/>
<connect gate="G$1" pin="PC11/UART4_RX(5T)" pad="79"/>
<connect gate="G$1" pin="PC12/UART5_TX(5T)" pad="80"/>
<connect gate="G$1" pin="PC13(5T)" pad="7"/>
<connect gate="G$1" pin="PC14/OSC32_IN(5T)" pad="8"/>
<connect gate="G$1" pin="PC15/OSC32_OUT(5T)" pad="9"/>
<connect gate="G$1" pin="PC2/ETH_MII_TXD2/ADC123_IN12(5T)" pad="17"/>
<connect gate="G$1" pin="PC3/ETH_MII_TX_CLK/ADC123_IN13(5T)" pad="18"/>
<connect gate="G$1" pin="PC4/ETH_MII_RXD0/ADC12_IN14(5T)" pad="33"/>
<connect gate="G$1" pin="PC5/ETH_MII_RXD1/ADC12_IN15(5T)" pad="34"/>
<connect gate="G$1" pin="PC6/TIM3_CH1(5T)" pad="63"/>
<connect gate="G$1" pin="PC7/TIM8_CH2(5T)" pad="64"/>
<connect gate="G$1" pin="PC8/TIM8_CH3(5T)" pad="65"/>
<connect gate="G$1" pin="PC9/TIM3_CH4(5T)" pad="66"/>
<connect gate="G$1" pin="PD0/CAN1_RX(5T)" pad="81"/>
<connect gate="G$1" pin="PD1/CAN1_TX(5T)" pad="82"/>
<connect gate="G$1" pin="PD10(5T)" pad="57"/>
<connect gate="G$1" pin="PD11(5T)" pad="58"/>
<connect gate="G$1" pin="PD12/TIM4_CH1(5T)" pad="59"/>
<connect gate="G$1" pin="PD13/TIM4_CH2(5T)" pad="60"/>
<connect gate="G$1" pin="PD14/TIM4_CH3(5T)" pad="61"/>
<connect gate="G$1" pin="PD15/TIM4_CH4(5T)" pad="62"/>
<connect gate="G$1" pin="PD2/UART5_RX(5T)" pad="83"/>
<connect gate="G$1" pin="PD3(5T)" pad="84"/>
<connect gate="G$1" pin="PD4(5T)" pad="85"/>
<connect gate="G$1" pin="PD5/USART2_TX(5T)" pad="86"/>
<connect gate="G$1" pin="PD6/USART2_RX(5T)" pad="87"/>
<connect gate="G$1" pin="PD7(5T)" pad="88"/>
<connect gate="G$1" pin="PD8/USART3_TX(5T)" pad="55"/>
<connect gate="G$1" pin="PD9/USART3_RX(5T)" pad="56"/>
<connect gate="G$1" pin="PE0(5T)" pad="97"/>
<connect gate="G$1" pin="PE1(5T)" pad="98"/>
<connect gate="G$1" pin="PE10/TIM1_CH2N(5T)" pad="41"/>
<connect gate="G$1" pin="PE11/TIM1_CH2(5T)" pad="42"/>
<connect gate="G$1" pin="PE12/TIM1_CH3N(5T)" pad="43"/>
<connect gate="G$1" pin="PE13/TIM1_CH3(5T)" pad="44"/>
<connect gate="G$1" pin="PE14/TIM1_CH4(5T)" pad="45"/>
<connect gate="G$1" pin="PE15/TIM1_BKIN(5T)" pad="46"/>
<connect gate="G$1" pin="PE2/ETH_MII_TXD3(5T)" pad="1"/>
<connect gate="G$1" pin="PE3(5T)" pad="2"/>
<connect gate="G$1" pin="PE4(5T)" pad="3"/>
<connect gate="G$1" pin="PE5/TIM9_CH1(5T)" pad="4"/>
<connect gate="G$1" pin="PE6/TIM9_CH2(5T)" pad="5"/>
<connect gate="G$1" pin="PE7/TIM1_ETR(5T)" pad="38"/>
<connect gate="G$1" pin="PE8/TIM1_CH1N(5T)" pad="39"/>
<connect gate="G$1" pin="PE9/TIM1_CH1(5T)" pad="40"/>
<connect gate="G$1" pin="PH0-OSC_IN(5T)" pad="12"/>
<connect gate="G$1" pin="PH1-OSC_OUT(5T)" pad="13"/>
<connect gate="G$1" pin="VBAT" pad="6"/>
<connect gate="G$1" pin="VCAP1" pad="49"/>
<connect gate="G$1" pin="VCAP2" pad="73"/>
<connect gate="G$1" pin="VDDA" pad="22"/>
<connect gate="G$1" pin="VDD_1" pad="11"/>
<connect gate="G$1" pin="VDD_2" pad="19"/>
<connect gate="G$1" pin="VDD_3" pad="28"/>
<connect gate="G$1" pin="VDD_4" pad="50"/>
<connect gate="G$1" pin="VDD_5" pad="75"/>
<connect gate="G$1" pin="VDD_6" pad="100"/>
<connect gate="G$1" pin="VREF+" pad="21"/>
<connect gate="G$1" pin="VSSA" pad="20"/>
<connect gate="G$1" pin="VSS_1" pad="10"/>
<connect gate="G$1" pin="VSS_2" pad="27"/>
<connect gate="G$1" pin="VSS_3" pad="74"/>
<connect gate="G$1" pin="VSS_4" pad="99"/>
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
<part name="U$1" library="stm32f4" deviceset="STM32F407V" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="7.62" y="2.54"/>
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
