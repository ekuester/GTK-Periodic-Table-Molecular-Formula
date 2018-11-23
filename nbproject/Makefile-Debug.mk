#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/elementproperty.o \
	${OBJECTDIR}/elementschema.o \
	${OBJECTDIR}/formulaparser.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/molecularformula.o \
	${OBJECTDIR}/periodictablewindow.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs gtkmm-3.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkperiodictable

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkperiodictable: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gtkperiodictable ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/elementproperty.o: elementproperty.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elementproperty.o elementproperty.cpp

${OBJECTDIR}/elementschema.o: elementschema.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/elementschema.o elementschema.cpp

${OBJECTDIR}/formulaparser.o: formulaparser.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/formulaparser.o formulaparser.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/molecularformula.o: molecularformula.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/molecularformula.o molecularformula.cpp

${OBJECTDIR}/periodictablewindow.o: periodictablewindow.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g `pkg-config --cflags gtkmm-3.0` -std=c++11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/periodictablewindow.o periodictablewindow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
