/*
//  Part of GTKPeriodicTable - Periodic Table of the Elements
//  Copyright (C) 2018  Erich Küster
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//  File:   elementschema.h
//  Created on October1, 2018, 19:28
 */

#ifndef ELEMENTSCHEMA_H
#define ELEMENTSCHEMA_H

#include <glibmm.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "formulaparser.h"

using namespace std;

class FormulaParser;

// official <https://iupac.org/what-we-do/periodic-table-of-elements/>
// latin <https://la.wikipedia.org/wiki/Systema_periodicum>
static std::vector< std::vector<std::string> > elements = {
    {"1", "H", "Hydrogenium", "1.00794(4)", "#FFFFFF", "1s1", "2.2", "37", "", "120", "1312", "-73", "-1, 1", "gas", "diatomic", "14", "20", "8.99E-05", "nonmetal", "1766", "https://en.wikipedia.org/wiki/Hydrogen"},
    {"2", "He", "Helium", "4.002602(2)", "#D9FFFF", "1s2", "", "32", "", "140", "2372", "0", "", "gas", "atomic", "", "4", "0.0001785", "noble gas", "1868", "https://en.wikipedia.org/wiki/Helium"},
    {"3", "Li", "Lithium", "6.941(2)", "#CC80FF", "[He] 2s1", "0.98", "134", "76 (+1)", "182", "520", "-60", "1", "solid", "metallic", "454", "1615", "0.535", "alkali metal", "1817", "https://en.wikipedia.org/wiki/Lithium"},
    {"4", "Be", "Beryllium", "9.012182(3)", "#C2FF00", "[He] 2s2", "1.57", "90", "45 (+2)", "", "900", "0", "2", "solid", "metallic", "1560", "2743", "1.848", "alkaline earth metal", "1798", "https://en.wikipedia.org/wiki/Beryllium"},
    {"5", "B", "Borium", "10.811(7)", "#FFB5B5", "[He] 2s2 2p1", "2.04", "82", "27 (+3)", "", "801", "-27", "1, 2, 3", "solid", "covalent network", "2348", "4273", "2.46", "metalloid", "1807", "https://en.wikipedia.org/wiki/Boron"},
    {"6", "C", "Carbonium", "12.0107(8)", "#909090", "[He] 2s2 2p2", "2.55", "77", "16 (+4)", "170", "1087", "-154", "-4, -3, -2, -1, 1, 2, 3, 4", "solid", "covalent network", "3823", "4300", "2.26", "nonmetal", "ancient", "https://en.wikipedia.org/wiki/Carbon"},
    {"7", "N", "Nitrogenium", "14.0067(2)", "#3050F8", "[He] 2s2 2p3", "3.04", "75", "146 (-3)", "155", "1402", "-7", "-3, -2, -1, 1, 2, 3, 4, 5", "gas", "diatomic", "63", "77", "0.001251", "nonmetal", "1772", "https://en.wikipedia.org/wiki/Nitrogen"},
    {"8", "O", "Oxygenium", "15.9994(3)", "#FF0D0D", "[He] 2s2 2p4", "3.44", "73", "140 (-2)", "152", "1314", "-141", "-2, -1, 1, 2", "gas", "diatomic", "55", "90", "0.001429", "nonmetal", "1774", "https://en.wikipedia.org/wiki/Oxygen"},
    {"9", "F", "Fluorinum", "18.9984032(5)", "#90E050", "[He] 2s2 2p5", "3.98", "71", "133 (-1)", "147", "1681", "-328", "-1", "gas", "atomic", "54", "85", "0.001696", "halogen", "1670", "https://en.wikipedia.org/wiki/Fluorine"},
    {"10", "Ne", "Neon", "20.1797(6)", "#B3E3F5", "[He] 2s2 2p6", "", "69", "", "154", "2081", "0", "", "gas", "atomic", "25", "27", "0.0009", "noble gas", "1898", "https://en.wikipedia.org/wiki/Neon"},
    {"11", "Na", "Natrium", "22.98976928(2)", "#AB5CF2", "[Ne] 3s1", "0.93", "154", "102 (+1)", "227", "496", "-53", "-1, 1", "solid", "metallic", "371", "1156", "0.968", "alkali metal", "1807", "https://en.wikipedia.org/wiki/Sodium"},
    {"12", "Mg", "Magnesium", "24.3050(6)", "#8AFF00", "[Ne] 3s2", "1.31", "130", "72 (+2)", "173", "738", "0", "1, 2", "solid", "metallic", "923", "1363", "1.738", "alkaline earth metal", "1808", "https://en.wikipedia.org/wiki/Magnesium"},
    {"13", "Al", "Aluminium", "26.9815386(8)", "#BFA6A6", "[Ne] 3s2 3p1", "1.61", "118", "53.5 (+3)", "", "578", "-43", "1, 3", "solid", "metallic", "933", "2792", "2.7", "metal", "ancient", "https://en.wikipedia.org/wiki/Aluminium"},
    {"14", "Si", "Silicium", "28.0855(3)", "#F0C8A0", "[Ne] 3s2 3p2", "1.9", "111", "40 (+4)", "210", "787", "-134", "-4, -3, -2, -1, 1, 2, 3, 4", "solid", "metallic", "1687", "3173", "2.33", "metalloid", "1854", "https://en.wikipedia.org/wiki/Silicon"},
    {"15", "P", "Phosphorus", "30.973762(2)", "#FF8000", "[Ne] 3s2 3p3", "2.19", "106", "44 (+3)", "180", "1012", "-72", "-3, -2, -1, 1, 2, 3, 4, 5", "solid", "covalent network", "317", "554", "1.823", "nonmetal", "1669", "https://en.wikipedia.org/wiki/Phosphorus"},
    {"16", "S", "Sulphur", "32.065(5)", "#FFFF30", "[Ne] 3s2 3p4", "2.58", "102", "184 (-2)", "180", "1000", "-200", "-2, -1, 1, 2, 3, 4, 5, 6", "solid", "covalent network", "388", "718", "1.96", "nonmetal", "ancient", "https://en.wikipedia.org/wiki/Sulfur"},
    {"17", "Cl", "Chlorinum", "35.453(2)", "#1FF01F", "[Ne] 3s2 3p5", "3.16", "99", "181 (-1)", "175", "1251", "-349", "-1, 1, 2, 3, 4, 5, 6, 7", "gas", "covalent network", "172", "239", "0.003214", "halogen", "1774", "https://en.wikipedia.org/wiki/Chlorine"},
    {"18", "Ar", "Argon", "39.948(1)", "#80D1E3", "[Ne] 3s2 3p6", "", "97", "", "188", "1521", "0", "", "gas", "atomic", "84", "87", "0.001784", "noble gas", "1894", "https://en.wikipedia.org/wiki/Argon"},
    {"19", "K", "Kalium", "39.0983(1)", "#8F40D4", "[Ar] 4s1", "0.82", "196", "138 (+1)", "275", "419", "-48", "1", "solid", "metallic", "337", "1032", "0.856", "alkali metal", "1807", "https://en.wikipedia.org/wiki/Potassium"},
    {"20", "Ca", "Calcium", "40.078(4)", "#3DFF00", "[Ar] 4s2", "1", "174", "100 (+2)", "", "590", "-2", "2", "solid", "metallic", "1115", "1757", "1.55", "alkaline earth metal", "ancient", "https://en.wikipedia.org/wiki/Calcium"},
    {"21", "Sc", "Scandium", "44.955912(6)", "#E6E6E6", "[Ar] 3d1 4s2", "1.36", "144", "74.5 (+3)", "", "633", "-18", "1, 2, 3", "solid", "metallic", "1814", "3103", "2.985", "transition metal", "1876", "https://en.wikipedia.org/wiki/Scandium"},
    {"22", "Ti", "Titanium", "47.867(1)", "#BFC2C7", "[Ar] 3d2 4s2", "1.54", "136", "86 (+2)", "", "659", "-8", "-1, 2, 3, 4", "solid", "metallic", "1941", "3560", "4.507", "transition metal", "1791", "https://en.wikipedia.org/wiki/Titanium"},
    {"23", "V", "Vanadium", "50.9415(1)", "#A6A6AB", "[Ar] 3d3 4s2", "1.63", "125", "79 (+2)", "", "651", "-51", "-1, 2, 3, 4", "solid", "metallic", "2183", "3680", "6.11", "transition metal", "1803", "https://en.wikipedia.org/wiki/Vanadium"},
    {"24", "Cr", "Chromium", "51.9961(6)", "#8A99C7", "[Ar] 3d5 4s1", "1.66", "127", "80 (+2*)", "", "653", "-64", "-2, -1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "2180", "2944", "7.14", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Chromium"},
    {"25", "Mn", "Manganum", "54.938045(5)", "#9C7AC7", "[Ar] 3d5 4s2", "1.55", "139", "67 (+2)", "", "717", "0", "-3, -2, -1, 1, 2, 3, 4, 5, 6, 7", "solid", "metallic", "1519", "2334", "7.47", "transition metal", "1774", "https://en.wikipedia.org/wiki/Manganese"},
    {"26", "Fe", "Ferrum", "55.845(2)", "#E06633", "[Ar] 3d6 4s2", "1.83", "125", "78 (+2*)", "", "763", "-16", "-2, -1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "1811", "3134", "7.874", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Iron"},
    {"27", "Co", "Cobaltum", "58.933195(5)", "#F090A0", "[Ar] 3d7 4s2", "1.88", "126", "74.5 (+2*)", "", "760", "-64", "-1, 1, 2, 3, 4, 5", "solid", "metallic", "1768", "3200", "8.9", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Cobalt"},
    {"28", "Ni", "Niccelium", "58.6934(4)", "#50D050", "[Ar] 3d8 4s2", "1.91", "121", "69 (+2)", "163", "737", "-112", "-1, 1, 2, 3, 4", "solid", "metallic", "1728", "3186", "8.908", "transition metal", "1751", "https://en.wikipedia.org/wiki/Nickel"},
    {"29", "Cu", "Cuprum", "63.546(3)", "#C88033", "[Ar] 3d10 4s1", "1.9", "138", "77 (+1)", "140", "746", "-118", "1, 2, 3, 4", "solid", "metallic", "1358", "3200", "8.92", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Copper"},
    {"30", "Zn", "Zincum", "65.38(2)", "#7D80B0", "[Ar] 3d10 4s2", "1.65", "131", "74 (+2)", "139", "906", "0", "2", "solid", "metallic", "693", "1180", "7.14", "transition metal", "1746", "https://en.wikipedia.org/wiki/Zinc"},
    {"31", "Ga", "Gallium", "69.723(1)", "#C28F8F", "[Ar] 3d10 4s2 4p1", "1.81", "126", "62 (+3)", "187", "579", "-29", "1, 2, 3", "solid", "metallic", "303", "2477", "5.904", "metal", "1875", "https://en.wikipedia.org/wiki/Gallium"},
    {"32", "Ge", "Germanium", "72.64(1)", "#668F8F", "[Ar] 3d10 4s2 4p2", "2.01", "122", "73 (+2)", "", "762", "-119", "-4, 1, 2, 3, 4", "solid", "metallic", "1211", "3093", "5.323", "metalloid", "1886", "https://en.wikipedia.org/wiki/Germanium"},
    {"33", "As", "Arsenicum", "74.92160(2)", "#BD80E3", "[Ar] 3d10 4s2 4p3", "2.18", "119", "58 (+3)", "185", "947", "-78", "-3, 2, 3, 5", "solid", "metallic", "1090", "887", "5.727", "metalloid", "ancient", "https://en.wikipedia.org/wiki/Arsenic"},
    {"34", "Se", "Selenium", "78.96(3)", "#FFA100", "[Ar] 3d10 4s2 4p4", "2.55", "116", "198 (-2)", "190", "941", "-195", "-2, 2, 4, 6", "solid", "metallic", "494", "958", "4.819", "nonmetal", "1817", "https://en.wikipedia.org/wiki/Selenium"},
    {"35", "Br", "Brominum", "79.904(1)", "#A62929", "[Ar] 3d10 4s2 4p5", "2.96", "114", "196 (-1)", "185", "1140", "-325", "-1, 1, 3, 4, 5, 7", "liquid", "covalent network", "266", "332", "3.12", "halogen", "1826", "https://en.wikipedia.org/wiki/Bromine"},
    {"36", "Kr", "Krypton", "83.798(2)", "#5CB8D1", "[Ar] 3d10 4s2 4p6", "", "110", "", "202", "1351", "0", "2", "gas", "atomic", "116", "120", "0.00375", "noble gas", "1898", "https://en.wikipedia.org/wiki/Krypton"},
    {"37", "Rb", "Rubidium", "85.4678(3)", "#702EB0", "[Kr] 5s1", "0.82", "211", "152 (+1)", "", "403", "-47", "1", "solid", "metallic", "312", "961", "1.532", "alkali metal", "1861", "https://en.wikipedia.org/wiki/Rubidium"},
    {"38", "Sr", "Strontium", "87.62(1)", "#00FF00", "[Kr] 5s2", "0.95", "192", "118 (+2)", "", "550", "-5", "2", "solid", "metallic", "1050", "1655", "2.63", "alkaline earth metal", "1790", "https://en.wikipedia.org/wiki/Strontium"},
    {"39", "Y", "Yttrium", "88.90585(2)", "#94FFFF", "[Kr] 4d1 5s2", "1.22", "162", "90 (+3)", "", "600", "-30", "1, 2, 3", "solid", "metallic", "1799", "3618", "4.472", "transition metal", "1794", "https://en.wikipedia.org/wiki/Yttrium"},
    {"40", "Zr", "Zirkonium", "91.224(2)", "#94E0E0", "[Kr] 4d2 5s2", "1.33", "148", "72 (+4)", "", "640", "-41", "1, 2, 3, 4", "solid", "metallic", "2128", "4682", "6.511", "transition metal", "1789", "https://en.wikipedia.org/wiki/Zirconium"},
    {"41", "Nb", "Niobium", "92.90638(2)", "#73C2C9", "[Kr] 4d4 5s1", "1.6", "137", "72 (+3)", "", "652", "-86", "-1, 2, 3, 4, 5", "solid", "metallic", "2750", "5017", "8.57", "transition metal", "1801", "https://en.wikipedia.org/wiki/Niobium"},
    {"42", "Mo", "Molybdenum", "95.96(2)", "#54B5B5", "[Kr] 4d5 5s1", "2.16", "145", "69 (+3)", "", "684", "-72", "-2, -1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "2896", "4912", "10.28", "transition metal", "1778", "https://en.wikipedia.org/wiki/Molybdenum"},
    {"43", "Tc", "Technetium", "98.9063", "#3B9E9E", "[Kr] 4d5 5s2", "1.9", "156", "64.5 (+4)", "", "702", "-53", "-3, -1, 1, 2, 3, 4, 5, 6, 7", "solid", "metallic", "2430", "4538", "11.5", "transition metal", "1937", "https://en.wikipedia.org/wiki/Technetium"},
    {"44", "Ru", "Ruthenium", "101.07(2)", "#248F8F", "[Kr] 4d7 5s1", "2.2", "126", "68 (+3)", "", "710", "-101", "-2, 1, 2, 3, 4, 5, 6, 7, 8", "solid", "metallic", "2607", "4423", "12.37", "transition metal", "1827", "https://en.wikipedia.org/wiki/Ruthenium"},
    {"45", "Rh", "Rhodium", "102.90550(2)", "#0A7D8C", "[Kr] 4d8 5s1", "2.28", "135", "66.5 (+3)", "", "720", "-110", "-1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "2237", "3968", "12.45", "transition metal", "1803", "https://en.wikipedia.org/wiki/Rhodium"},
    {"46", "Pd", "Palladium", "106.42(1)", "#006985", "[Kr] 4d10", "2.2", "131", "59 (+1)", "163", "804", "-54", "2, 4", "solid", "metallic", "1828", "3236", "12.023", "transition metal", "1803", "https://en.wikipedia.org/wiki/Palladium"},
    {"47", "Ag", "Argentum", "107.8682(2)", "#C0C0C0", "[Kr] 4d10 5s1", "1.93", "153", "115 (+1)", "172", "731", "-126", "1, 2, 3", "solid", "metallic", "1235", "2435", "10.49", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Silver"},
    {"48", "Cd", "Cadmium", "112.411(8)", "#FFD98F", "[Kr] 4d10 5s2", "1.69", "148", "95 (+2)", "158", "868", "0", "2", "solid", "metallic", "594", "1040", "8.65", "transition metal", "1817", "https://en.wikipedia.org/wiki/Cadmium"},
    {"49", "In", "Indium", "114.818(3)", "#A67573", "[Kr] 4d10 5s2 5p1", "1.78", "144", "80 (+3)", "193", "558", "-29", "1, 2, 3", "solid", "metallic", "430", "2345", "7.31", "metal", "1863", "https://en.wikipedia.org/wiki/Indium"},
    {"50", "Sn", "Stannum", "118.710(7)", "#668080", "[Kr] 4d10 5s2 5p2", "1.96", "141", "112 (+2)", "217", "709", "-107", "-4, 2, 4", "solid", "metallic", "505", "2875", "7.31", "metal", "ancient", "https://en.wikipedia.org/wiki/Tin"},
    {"51", "Sb", "Stibium", "121.760(1)", "#9E63B5", "[Kr] 4d10 5s2 5p3", "2.05", "138", "76 (+3)", "", "834", "-103", "-3, 3, 5", "solid", "metallic", "904", "1860", "6.697", "metalloid", "ancient", "https://en.wikipedia.org/wiki/Antimony"},
    {"52", "Te", "Tellurium", "127.60(3)", "#D47A00", "[Kr] 4d10 5s2 5p4", "2.1", "135", "221 (-2)", "206", "869", "-190", "-2, 2, 4, 5, 6", "solid", "metallic", "723", "1261", "6.24", "metalloid", "1782", "https://en.wikipedia.org/wiki/Tellurium"},
    {"53", "I", "Iodinum", "126.90447(3)", "#940094", "[Kr] 4d10 5s2 5p5", "2.66", "133", "220 (-1)", "198", "1008", "-295", "-1, 1, 3, 5, 7", "solid", "covalent network", "387", "457", "4.94", "halogen", "1811", "https://en.wikipedia.org/wiki/Iodine"},
    {"54", "Xe", "Xenon", "131.293(6)", "#429EB0", "[Kr] 4d10 5s2 5p6", "", "130", "48 (+8)", "216", "1170", "0", "2, 4, 6, 8", "gas", "atomic", "161", "165", "0.0059", "noble gas", "1898", "https://en.wikipedia.org/wiki/Xenon"},
    {"55", "Cs", "Caesium", "132.9054519(2)", "#57178F", "[Xe] 6s1", "0.79", "225", "167 (+1)", "", "376", "-46", "1", "solid", "metallic", "302", "944", "1.879", "alkali metal", "1860", "https://en.wikipedia.org/wiki/Cesium"},
    {"56", "Ba", "Barium", "137.327(7)", "#00C900", "[Xe] 6s2", "0.89", "198", "135 (+2)", "", "503", "-14", "2", "solid", "metallic", "1000", "2143", "3.51", "alkaline earth metal", "1808", "https://en.wikipedia.org/wiki/Barium"},
    {"57", "La", "Lanthanum", "138.90547(7)", "#70D4FF", "[Xe] 5d1 6s2", "1.1", "169", "103.2 (+3)", "", "538", "-48", "2, 3", "solid", "metallic", "1193", "3737", "6.146", "lanthanoid", "1839", "https://en.wikipedia.org/wiki/Lanthanum"},
    {"58", "Ce", "Cerium", "140.116(1)", "#FFFFC7", "[Xe] 4f1 5d1 6s2", "1.12", "", "102 (+3)", "", "534", "-50", "2, 3, 4", "solid", "metallic", "1071", "3633", "6.689", "lanthanoid", "1803", "https://en.wikipedia.org/wiki/Cerium"},
    {"59", "Pr", "Praseodymium", "140.90765(2)", "#D9FFC7", "[Xe] 4f3 6s2", "1.13", "", "99 (+3)", "", "527", "-50", "2, 3, 4", "solid", "metallic", "1204", "3563", "6.64", "lanthanoid", "1885", "https://en.wikipedia.org/wiki/Praseodymium"},
    {"60", "Nd", "Neodymium", "144.242(3)", "#C7FFC7", "[Xe] 4f4 6s2", "1.14", "", "129 (+2)", "", "533", "-50", "2, 3", "solid", "metallic", "1294", "3373", "7.01", "lanthanoid", "1885", "https://en.wikipedia.org/wiki/Neodymium"},
    {"61", "Pm", "Promethium", "146.9151", "#A3FFC7", "[Xe] 4f5 6s2", "1.13", "", "97 (+3)", "", "540", "-50", "3", "solid", "metallic", "1373", "3273", "7.264", "lanthanoid", "1947", "https://en.wikipedia.org/wiki/Promethium"},
    {"62", "Sm", "Samarium", "150.36(2)", "#8FFFC7", "[Xe] 4f6 6s2", "1.17", "", "122 (+2)", "", "545", "-50", "2, 3", "solid", "metallic", "1345", "2076", "7.353", "lanthanoid", "1853", "https://en.wikipedia.org/wiki/Samarium"},
    {"63", "Eu", "Europium", "151.964(1)", "#61FFC7", "[Xe] 4f7 6s2", "1.2", "", "117 (+2)", "", "547", "-50", "2, 3", "solid", "metallic", "1095", "1800", "5.244", "lanthanoid", "1901", "https://en.wikipedia.org/wiki/Europium"},
    {"64", "Gd", "Gadolinium", "157.25(3)", "#45FFC7", "[Xe] 4f7 5d1 6s2", "1.2", "", "93.8 (+3)", "", "593", "-50", "1, 2, 3", "solid", "metallic", "1586", "3523", "7.901", "lanthanoid", "1880", "https://en.wikipedia.org/wiki/Gadolinium"},
    {"65", "Tb", "Terbium", "158.92535(2)", "#30FFC7", "[Xe] 4f9 6s2", "1.2", "", "92.3 (+3)", "", "566", "-50", "1, 3, 4", "solid", "metallic", "1629", "3503", "8.219", "lanthanoid", "1843", "https://en.wikipedia.org/wiki/Terbium"},
    {"66", "Dy", "Dysprosium", "162.500(1)", "#1FFFC7", "[Xe] 4f10 6s2", "1.22", "", "107 (+2)", "", "573", "-50", "2, 3", "solid", "metallic", "1685", "2840", "8.551", "lanthanoid", "1886", "https://en.wikipedia.org/wiki/Dysprosium"},
    {"67", "Ho", "Holmium", "164.93032(2)", "#00FF9C", "[Xe] 4f11 6s2", "1.23", "", "90.1 (+3)", "", "581", "-50", "3", "solid", "metallic", "1747", "2973", "8.795", "lanthanoid", "1878", "https://en.wikipedia.org/wiki/Holmium"},
    {"68", "Er", "Erbium", "167.259(3)", "#00e675", "[Xe] 4f12 6s2", "1.24", "", "89 (+3)", "", "589", "-50", "3", "solid", "metallic", "1770", "3141", "9.066", "lanthanoid", "1842", "https://en.wikipedia.org/wiki/Erbium"},
    {"69", "Tm", "Thulium", "168.93421(2)", "#00D452", "[Xe] 4f13 6s2", "1.25", "", "103 (+2)", "", "597", "-50", "2, 3", "solid", "metallic", "1818", "2223", "9.321", "lanthanoid", "1879", "https://en.wikipedia.org/wiki/Thulium"},
    {"70", "Yb", "Ytterbium", "173.054(5)", "#00BF38", "[Xe] 4f14 6s2", "1.1", "", "102 (+2)", "", "603", "-50", "2, 3", "solid", "metallic", "1092", "1469", "6.57", "lanthanoid", "1878", "https://en.wikipedia.org/wiki/Ytterbium"},
    {"71", "Lu", "Lutetium", "174.9668(1)", "#00AB24", "[Xe] 4f14 5d1 6s2", "1.27", "160", "86.1 (+3)", "", "524", "-50", "3", "solid", "metallic", "1936", "3675", "9.841", "lanthanoid", "1907", "https://en.wikipedia.org/wiki/Lutetium"},
    {"72", "Hf", "Hafnium", "178.49(2)", "#4DC2FF", "[Xe] 4f14 5d2 6s2", "1.3", "150", "71 (+4)", "", "659", "0", "2, 3, 4", "solid", "metallic", "2506", "4876", "13.31", "transition metal", "1923", "https://en.wikipedia.org/wiki/Hafnium"},
    {"73", "Ta", "Tantalum", "180.94788(2)", "#4DA6FF", "[Xe] 4f14 5d3 6s2", "1.5", "138", "72 (+3)", "", "761", "-31", "-1, 2, 3, 4, 5", "solid", "metallic", "3290", "5731", "16.65", "transition metal", "1802", "https://en.wikipedia.org/wiki/Tantalum"},
    {"74", "W", "Wolframium", "183.84(1)", "#2194D6", "[Xe] 4f14 5d4 6s2", "2.36", "146", "66 (+4)", "", "770", "-79", "-2, -1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "3695", "5828", "19.25", "transition metal", "1783", "https://en.wikipedia.org/wiki/Tungsten"},
    {"75", "Re", "Rhenium", "186.207(1)", "#267DAB", "[Xe] 4f14 5d5 6s2", "1.9", "159", "63 (+4)", "", "760", "-15", "-3, -1, 1, 2, 3, 4, 5, 6, 7", "solid", "metallic", "3459", "5869", "21.02", "transition metal", "1925", "https://en.wikipedia.org/wiki/Rhenium"},
    {"76", "Os", "Osmium", "190.23(3)", "#266696", "[Xe] 4f14 5d6 6s2", "2.2", "128", "63 (+4)", "", "840", "-106", "-2, -1, 1, 2, 3, 4, 5, 6, 7, 8", "solid", "metallic", "3306", "5285", "22.61", "transition metal", "1803", "https://en.wikipedia.org/wiki/Osmium"},
    {"77", "Ir", "Iridium", "192.217(3)", "#175487", "[Xe] 4f14 5d7 6s2", "2.2", "137", "68 (+3)", "", "880", "-151", "-3, -1, 1, 2, 3, 4, 5, 6", "solid", "metallic", "2739", "4701", "22.65", "transition metal", "1803", "https://en.wikipedia.org/wiki/Iridium"},
    {"78", "Pt", "Platinum", "195.084(9)", "#D0D0E0", "[Xe] 4f14 5d9 6s1", "2.28", "128", "86 (+2)", "175", "870", "-205", "2, 4, 5, 6", "solid", "metallic", "2041", "4098", "21.09", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Platinum"},
    {"79", "Au", "Aurum", "196.966569(4)", "#FFD123", "[Xe] 4f14 5d10 6s1", "2.54", "144", "137 (+1)", "166", "890", "-223", "-1, 1, 2, 3, 5", "solid", "metallic", "1337", "3129", "19.3", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Gold"},
    {"80", "Hg", "Hydrargyrum", "200.59(2)", "#B8B8D0", "[Xe] 4f14 5d10 6s2", "2", "149", "119 (+1)", "155", "1007", "0", "1, 2, 4", "liquid", "metallic", "234", "630", "13.534", "transition metal", "ancient", "https://en.wikipedia.org/wiki/Mercury (Element)"},
    {"81", "Tl", "Thallium", "204.3833(2)", "#A6544D", "[Xe] 4f14 5d10 6s2 6p1", "2.04", "148", "150 (+1)", "196", "589", "-19", "1, 3", "solid", "metallic", "577", "1746", "11.85", "metal", "1861", "https://en.wikipedia.org/wiki/Thallium"},
    {"82", "Pb", "Plumbum", "207.2(1)", "#575961", "[Xe] 4f14 5d10 6s2 6p2", "2.33", "147", "119 (+2)", "202", "716", "-35", "-4, 2, 4", "solid", "metallic", "601", "2022", "11.34", "metal", "ancient", "https://en.wikipedia.org/wiki/Lead_(element)"},
    {"83", "Bi", "Bismuthum", "208.98040(1)", "#9E4FB5", "[Xe] 4f14 5d10 6s2 6p3", "2.02", "146", "103 (+3)", "", "703", "-91", "-3, 3, 5", "solid", "metallic", "544", "1837", "9.78", "metal", "ancient", "https://en.wikipedia.org/wiki/Bismuth"},
    {"84", "Po", "Polonium", "208.9824", "#AB5C00", "[Xe] 4f14 5d10 6s2 6p4", "2", "", "94 (+4)", "", "812", "-183", "-2, 2, 4, 6", "solid", "metallic", "527", "1235", "9.196", "metalloid", "1898", "https://en.wikipedia.org/wiki/Polonium"},
    {"85", "At", "Astatinum", "209.9871", "#754F45", "[Xe] 4f14 5d10 6s2 6p5", "2.2", "", "62 (+7)", "", "920", "-270", "-1, 1, 3, 5", "solid", "covalent network", "575", "", "", "halogen", "1940", "https://en.wikipedia.org/wiki/Astatine"},
    {"86", "Rn", "Radon", "222.0176", "#428296", "[Xe] 4f14 5d10 6s2 6p6", "", "145", "", "", "1037", "", "2", "gas", "atomic", "202", "211", "0.00973", "noble gas", "1900", "https://en.wikipedia.org/wiki/Radon"},
    {"87", "Fr", "Francium", "223.0197", "#420066", "[Rn] 7s1", "0.7", "", "180 (+1)", "", "380", "", "1", "solid", "metallic", "", "", "", "alkali metal", "1939", "https://en.wikipedia.org/wiki/Francium"},
    {"88", "Ra", "Radium", "226.0254", "#007D00", "[Rn] 7s2", "0.9", "", "148 (+2)", "", "509", "", "2", "solid", "metallic", "973", "2010", "5", "alkaline earth metal", "1898", "https://en.wikipedia.org/wiki/Radium"},
    {"89", "Ac", "Actinium", "227.0278", "#70ABFA", "[Rn] 6d1 7s2", "1.1", "", "112 (+3)", "", "499", "", "3", "solid", "metallic", "1323", "3473", "10.07", "actinoid", "1899", "https://en.wikipedia.org/wiki/Actinium"},
    {"90", "Th", "Thorium", "232.03806(2)", "#00BAFF", "[Rn] 6d2 7s2", "1.3", "", "94 (+4)", "", "587", "", "2, 3, 4", "solid", "metallic", "2023", "5093", "11.724", "actinoid", "1828", "https://en.wikipedia.org/wiki/Thorium"},
    {"91", "Pa", "Protactinium", "231.03588(2)", "#00A1FF", "[Rn] 5f2 6d1 7s2", "1.5", "", "104 (+3)", "", "568", "", "3, 4, 5", "solid", "metallic", "1845", "4273", "15.37", "actinoid", "1913", "https://en.wikipedia.org/wiki/Protactinium"},
    {"92", "U", "Uranium", "238.02891(3)", "#008FFF", "[Rn] 5f3 6d1 7s2", "1.38", "", "102.5 (+3)", "186", "598", "", "3, 4, 5, 6", "solid", "metallic", "1408", "4200", "19.05", "actinoid", "1789", "https://en.wikipedia.org/wiki/Uranium"},
    {"93", "Np", "Neptunium", "237.0482", "#0080FF", "[Rn] 5f4 6d1 7s2", "1.36", "", "110 (+2)", "", "605", "", "3, 4, 5, 6, 7", "solid", "metallic", "917", "4273", "20.45", "actinoid", "1940", "https://en.wikipedia.org/wiki/Neptunium"},
    {"94", "Pu", "Plutonium", "244.0642", "#006BFF", "[Rn] 5f6 7s2", "1.28", "", "100 (+3)", "", "585", "", "3, 4, 5, 6, 7", "solid", "metallic", "913", "3503", "19.816", "actinoid", "1940", "https://en.wikipedia.org/wiki/Plutonium"},
    {"95", "Am", "Americium", "243", "#545CF2", "[Rn] 5f7 7s2", "1.3", "", "126 (+2)", "", "578", "", "2, 3, 4, 5, 6", "solid", "metallic", "1449", "2284", "", "actinoid", "1944", "https://en.wikipedia.org/wiki/Americium"},
    {"96", "Cm", "Curium", "247", "#785CE3", "[Rn] 5f7 6d1 7s2", "1.3", "", "97 (+3)", "", "581", "", "3, 4", "solid", "metallic", "1618", "3383", "13.51", "actinoid", "1944", "https://en.wikipedia.org/wiki/Curium"},
    {"97", "Bk", "Berkelium", "247", "#8A4FE3", "[Rn] 5f9 7s2", "1.3", "", "96 (+3)", "", "601", "", "3, 4", "solid", "metallic", "1323", "", "14.78", "actinoid", "1949", "https://en.wikipedia.org/wiki/Berkelium"},
    {"98", "Cf", "Californium", "251", "#A136D4", "[Rn] 5f10 7s2", "1.3", "", "95 (+3)", "", "608", "", "2, 3, 4", "solid", "metallic", "1173", "", "15.1", "actinoid", "1950", "https://en.wikipedia.org/wiki/Californium"},
    {"99", "Es", "Einsteinium", "252", "#B31FD4", "[Rn] 5f11 7s2", "1.3", "", "", "", "619", "", "2, 3", "solid", "", "1133", "", "", "actinoid", "1952", "https://en.wikipedia.org/wiki/Einsteinium"},
    {"100", "Fm", "Fermium", "257", "#B31FBA", "[Rn] 5f12 7s2", "1.3", "", "", "", "627", "", "2, 3", "", "", "1800", "", "", "actinoid", "1952", "https://en.wikipedia.org/wiki/Fermium"},
    {"101", "Md", "Mendelevium", "258", "#B30DA6", "[Rn] 5f13 7s2", "1.3", "", "", "", "635", "", "2, 3", "", "", "1100", "", "", "actinoid", "1955", "https://en.wikipedia.org/wiki/Mendelevium"},
    {"102", "No", "Nobelium", "259", "#BD0D87", "[Rn] 5f14 7s2", "1.3", "", "", "", "642", "", "2, 3", "", "", "1100", "", "", "actinoid", "1957", "https://en.wikipedia.org/wiki/Nobelium"},
    {"103", "Lr", "Lawrencium", "266", "#C70066", "[Rn] 5f14 7s2 7p1", "1.3", "", "", "", "", "", "3", "", "", "1900", "", "", "transition metal", "1961", "https://en.wikipedia.org/wiki/Lawrencium"},
    {"104", "Rf", "Rutherfordium", "261.1087", "#CC0059", "[Rn] 5f14 6d2 7s2", "", "", "", "", "", "", "4", "", "", "", "", "", "transition metal", "1969", "https://en.wikipedia.org/wiki/Rutherfordium"},
    {"105", "Db", "Dubnium", "262.1138", "#D1004F", "[Rn] 5f14 6d3 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1967", "https://en.wikipedia.org/wiki/Dubnium"},
    {"106", "Sg", "Seaborgium", "263.1182", "#D90045", "[Rn] 5f14 6d4 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1974", "https://en.wikipedia.org/wiki/Seaborgium"},
    {"107", "Bh", "Bohrium", "262.1229", "#E00038", "[Rn] 5f14 6d5 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1976", "https://en.wikipedia.org/wiki/Bohrium"},
    {"108", "Hs", "Hassium", "270", "#E6002E", "[Rn] 5f14 6d6 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1984", "https://en.wikipedia.org/wiki/Hassium"},
    {"109", "Mt", "Meitnerium", "268", "#EB0026", "[Rn] 5f14 6d7 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1982", "https://en.wikipedia.org/wiki/Meitnerium"},
    {"110", "Ds", "Darmstadtium", "281", "", "[Rn] 5f14 6d9 7s1", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1994", "https://en.wikipedia.org/wiki/Darmstadtium"},
    {"111", "Rg", "Roentgenium", "280", "", "[Rn] 5f14 6d10 7s1", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1994", "https://en.wikipedia.org/wiki/Roentgenium"},
    {"112", "Cn", "Copernicium", "277", "", "[Rn] 5f14 6d10 7s2", "", "", "", "", "", "", "", "", "", "", "", "", "transition metal", "1996", "https://en.wikipedia.org/wiki/Copernicium"},
    {"113", "Nh", "Nihonium", "287", "", "[Rn] 5f14 6d10 7s2 7p1", "", "", "", "", "", "", "", "", "", "", "", "", "post-transition metal", "2003", "https://en.wikipedia.org/wiki/Nihonium"},
    {"114", "Fl", "Flerovium", "289", "", "[Rn] 5f14 6d10 7s2 7p2", "", "", "", "", "", "", "", "", "", "", "", "", "post-transition metal", "1998", "https://en.wikipedia.org/wiki/Flerovium"},
    {"115", "Mc", "Moscovium", "288", "", "[Rn] 5f14 6d10 7s2 7p3", "", "", "", "", "", "", "", "", "", "", "", "", "post-transition metal", "2003", "https://en.wikipedia.org/wiki/Moscovium"},
    {"116", "Lv", "Livermorium", "293", "", "[Rn] 5f14 6d10 7s2 7p4", "", "", "", "", "", "", "", "", "", "", "", "", "post-transition metal", "2000", "https://en.wikipedia.org/wiki/Livermorium"},
    {"117", "Ts", "Tennessinum", "292", "", "[Rn] 5f14 6d10 7s2 7p5", "", "", "", "", "", "", "", "", "", "", "", "", "post-transition metal", "2010", "https://en.wikipedia.org/wiki/Tennessine"},
    {"118", "Og", "Oganesson", "294", "", "[Rn] 5f14 6d10 7s2 7p6", "", "", "", "", "", "", "", "", "", "", "", "", "noble gas", "2002", "https://en.wikipedia.org/wiki/Oganesson"}
};

class ElementSchema {
public:
    ElementSchema();
    ElementSchema(const ElementSchema& orig);
    virtual ~ElementSchema();

    double totalMass = 0.0;
/*
    struct element {
        int ordinal;
        string symbol;
        Glib::ustring name;
        double mass;
    };
 */
    struct FormulaItem {
        string elementSymbol;
        double mass;
        int indexSum;
    };

    std::map<string, FormulaItem> formulaTable;

    std::vector<struct FormulaItem> parseElements(FormulaParser* inputParser);
    string analytics();
    string finalFormula();

private:

};

#endif /* ELEMENTSCHEMA_H */

