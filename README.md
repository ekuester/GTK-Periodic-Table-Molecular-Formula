# GTK-Periodic-Table-Molecular-Formula

Periodic Table of the elements ( PTE ) combined with information about elements and calculation of molecular formulas and their molecular weight (also named molar mass), the amount of the contained elements in percent is given.
( C++ / Linux / Gnome / GTK / gtkmm / chemistry / PTE / PSE )

The program itself consists of three parts: The table of the periodic system of the elements ( PTE resp. PSE ), information about the elements and a calculator for molecular formulas and molecular weights. The first and second part was written the last months, since I thought it would harmonize with the third.<br/>
For further explanations look at<br/>
&nbsp; <https://nl.wikipedia.org/wiki/Periodiek_systeem> in dutch<br/>
&nbsp; <https://en.wikipedia.org/wiki/Periodic_table> in english<br/>
&nbsp; <https://de.wikipedia.org/wiki/Periodensystem> in german<br/>
&nbsp; <https://it.wikipedia.org/wiki/Tavola_periodica_degli_elementi> in italian <br/>

The third part is accompanying my life since years, I wrote it first in BASIC, followed by versions in Borland Turbo C and Microsoft Visual C# 2005 (both for Windows), switched to Objective C and Swift on Apple Macs and now finally in C++ with use of gtkmm wrapper for Gnome GTK environment of Linux.

The development environment in the moment is Netbeans IDE 8.2 under Fedora 28 Cinnamon. Alternatively you can easily compile and run the program in Terminal with the added shell script:
```
sh ./GTKPeriodicTable.sh
```
The normal making standard using GNUmakefile is working, too. Just type
```
make
```
on a command line. GNUmakefile because the default Makefile is occupied by Netbeans.

Since I am working under Fedora Linux I choose C++ as the programming language in combination with GTK and the gtkmm wrapper. With these you have excellent tools for developing own programs.

I wrote this program to become familiar with the C++ language, especially the GTK-API under the gtkmm wrapper and to get a feeling how to display different widgets on the screen. Take it as example for handling of windows, menus, buttons, labels, entries and textviews.<br/>
Very interesting in GTK 3.0 is the mode of setting colors in widgets: First place to go is<br/>
&nbsp; <https://developer.gnome.org/gtk3/stable/chap-css-overview.html><br/>
It is essential to generate the necessary CSS data in the right syntax.<br/>
Learning the Linux way of localization the dutch/german/italian translation files are added in subdirectories. Under Fedora the right system folder should be /usr/share/locale, but only if you change line 7 in main.cpp to<br/>
```
#define PROGRAMNAME_LOCALEDIR "/usr/share/locale"
```
Usage:</br>
You will find the program mostly self explaining. On start you are confronted with the actual table of elements according with IUPAC (International Union of Pure and Applied Chemistry). Divergent from their nomenclature I choose the latinized element names, which clearly explain the origin of the chemical element symbols, mainly from<br/>
&nbsp; <https://la.wikipedia.org/wiki/Systema_periodicum> in latin as *lingua franca* ...<br/>
By clicking on an element a window with further information about the element is shown. At the end of the list you will find a link to the relevant article in Wikipedia.

Click in the menubar on "Calc" and "Open" and you will see the little calculator for formulas, molecular masses and percent of elements. Input your formula into the topmost field, what you can do in a relatively comfortable way by grouping the formula into formula elements. Formula elements means the combination of an element symbol with an index. The only restriction is that indices can only be set behind the formula element which shall be counted. Then let the program do the necessary calculations for you.<br/>
- use the normal element symbols
- use arabic numerals as indices
- use bonds:&nbsp; `-  :  =  .  · ` (only illustrative, not controlled on correctness)
- use paired brackets and/or parenthesis for more complex formulas:&nbsp; `[  ]  (  )`

examples:<br/>
```
organic:
CH2=CH-CO-ONa              2-Propenoic acid, sodium salt (Sodium acrylate)
(CH2=CH-CO)2O              2-Propenoic acid, anhydride (Acrylic anhydride)
CH2=C(CH3)-CO-NH2          2-Methyl-2-propenamide (Methacrylamide)
HO-CO-CH(OH)-CH(OH)-CO-OH  2,3-Dihydroxybutanedioic acid (Tartaric acid)
HOCH2-CO-(CHOH)3-CH2OH     Pentahydroxyhexan-2-one (Fructose)
C6H6                       Benzene
C10H8                      Naphthalene
C4H4C(CH2)CC4H4            Bicyclo[4.4.1]undeca-1,3,5,7,9-pentaene (1,6-Methano[10]annulene)
CH3-CO-O-C6H4-CO-OH        2-(Acetyloxy)benzoesäure (Acetylsalicylic acid, Aspirin)
HO-C17H22(CH3)2-CH(CH3)-(CH2)3-CH(CH3)2
                           (3ß)-cholest-5-en-3-ol (Cholesterol)
inorganic:
[Cu(NH3)4(H2O)]SO4         Tetraamminecopper(II)sulfate, monohydrate
FeSO4·[H2O]7               Iron(II)sulfate, heptahydrate (containing crystallisation water)
 note: FeSO4·7[H2O] is not recognized correctly
```
Pressing the ENTER key will output the overall molecular formula strictly sorted in alphabetical order, the overall molecular mass and the amount of each element in the molecule in percent.<br/>
For further explanations look at<br/>
&nbsp; <https://en.wikipedia.org/wiki/Chemical_formula#Molecular_formula><br/>
&nbsp; <https://en.wikipedia.org/wiki/Molecular_mass><br/>

Annotation:<br/>
For homology I changed the name of the halogens to end with -inum to match more the official names of IUPAC.

Disclaimer: Use the program for what purpose you like, but hold in mind, that I will not be responsible for any harm it will cause to your hard- or software. It was your decision to use this piece of software.

