###########################################################################
## Makefile generated for Simulink model 'ekf_cf'. 
## 
## Makefile     : ekf_cf.mk
## Generated on : Fri Jun 12 00:16:05 2020
## MATLAB Coder version: 3.4 (R2017b)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/ekf_cf.pre.o
## Product type : executable
## Build type   : Top-Level Standalone Executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = ekf_cf
MAKEFILE                  = ekf_cf.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = D:/Program Files/MATLAB
MATLAB_BIN                = D:/Program Files/MATLAB/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = G:/MulticoperDesignAndControl/MulticoperModel/3.4_en/release_teacher/e4/e4.2
ARCH                      = win64
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
MODELREF_LINK_RSPFILE_NAME = ekf_cf_ref.rsp
RELATIVE_PATH_TO_ANCHOR   = ..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Pixhawk Toolchain v4.6.2 | gmake (64-bit Windows)
# Supported Version(s):    
# ToolchainInfo Version:   R2017b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# TARGET_LOAD_CMD_ARGS
# TARGET_LOAD_CMD
# PX4_BASE

#-----------
# MACROS
#-----------

Q                                   = $(if $(V),,@)
PX4_SIMULINK_APP                    = px4_simulink_app
CPFLAGS                             = -O binary
ARCHWARNINGS                        = -Wall \
-Wextra \
-Wdouble-promotion \
-Wshadow \
-Wfloat-equal \
-Wframe-larger-than=1024 \
-Wpointer-arith \
-Wlogical-op \
-Wmissing-declarations \
-Wpacked \
-Wno-unused-parameter \
-Werror=format-security \
-Werror=array-bounds \
-Wfatal-errors \
-Wformat=1
ARCHCWARNINGS                       = $(ARCHWARNINGS) \
-Wbad-function-cast \
-Wstrict-prototypes \
-Wold-style-declaration \
-Wmissing-parameter-type \
-Wmissing-prototypes \
-Wnested-externs
ARCHOPTIMIZATION                    = -O3 \
-fno-strict-aliasing \
-fno-strength-reduce \
-fomit-frame-pointer \
-funsafe-math-optimizations \
-fno-builtin-printf \
-ffunction-sections \
-fdata-sections
ARCHCPUFLAGS_CORTEXM3               = -mcpu=cortex-m4 \
-mthumb \
-march=armv7e-m \
-mfpu=fpv4-sp-d16 \
-ffixed-r10 \
-mfloat-abi=hard
ARCHCPUFLAGS                        = $(ARCHCPUFLAGS_CORTEXM3)
INSTRUMENTATIONDEFINES              = $(ARCHINSTRUMENTATIONDEFINES_CORTEXM3)
ARCHDEFINES                         = -DCONFIG_ARCH_BOARD_PX4FMU_V2
LIBGCC                              = $(shell $(CC) $(ARCHCPUFLAGS) -print-libgcc-file-name)
LIBM                                = $(shell $(CC) $(ARCHCPUFLAGS) -print-file-name=libm.a)
MAKEROOT                            = /bin

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Pixhawk Toolchain C Compiler
CC = echo

# Linker: Pixhawk ToolchainC Pre-Linker
LD = echo

# Archiver: Pixhawk Toolchain Archiver
AR = echo

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = $(MEX_PATH)/mex

# Download: Download
DOWNLOAD =

# Invoke Make: Invoke Make
INVOKE = $(call CALLPX4MK)

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
ENDGRP              = --end-group
OUTPUT_FLAG         = -o
STARTGRP            = --start-group
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -MD \
                       -c \
                       -std=gnu99 \
                       $(ARCHCWARNINGS) \
                       $(ARCHCPUFLAGS) \
                       $(ARCHINCLUDES) \
                       $(INSTRUMENTATIONDEFINES) \
                       $(ARCHDEFINES) \
                       -fno-common \
                       -nodefaultlibs \
                       -nostdlib \
                       -Wframe-larger-than=2000 \
                       -fvisibility=hidden \
                       -include visibility.h \
                       -O0 \
                       -fno-builtin-printf
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
MAKEFILENAME         =
LDFLAGS              = -Ur \
                       -Map $(PRODUCT_NAME).pre.o.map
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE) postdownload_preexecute
SHAREDLIB_LDFLAGS    =

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             = .pre.o
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .mk
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/ekf_cf.pre.o
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(MATLAB_ROOT)/simulink/include/sf_runtime -I$(START_DIR)/ekf_cf_ert_rtw -IG:/MulticoperDesignAndControl/MulticoperModel/3.4_en/release_teacher/e4/e4.3/HardInloop -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/serial -I$(PX4_ROOT)/src/lib/mathlib/CMSIS/Include -I$(PX4_ROOT)/lib/gcc/wingw32/4.6.2.include -I$(PX4_ROOT)/Firmware/src -I$(PX4_ROOT)/Firmware/build_$(PX4PSP_CMAKE_CONFIG) -I$(PX4_ROOT)/Firmware/build_$(PX4PSP_CMAKE_CONFIG)/src -I$(PX4_ROOT)/Firmware/src/modules -I$(PX4_ROOT)/Firmware/src/include -I$(PX4_ROOT)/Firmware/src/lib -I$(PX4_ROOT)/Firmware/src/platforms -I$(PX4_ROOT)/Firmware/src/drivers/boards/px4fmu-v2 -I$(PX4_ROOT)/Firmware/build_$(PX4PSP_CMAKE_CONFIG)/src/modules/px4_messages -I$(PX4_ROOT)/Firmware/build_$(PX4PSP_CMAKE_CONFIG)/src/modules -I$(PX4_ROOT)/Firmware/mavlink/include/mavlink -I$(PX4_ROOT)/Firmware/src/lib/DriverFramework/framework/include -I$(PX4_ROOT)/Firmware/src/lib/matrix -I$(PX4PSP_MODULE_BUILD_OUTPUT)/px4fmu-v2/NuttX/nuttx-export/include -I$(PX4PSP_MODULE_BUILD_OUTPUT)/px4fmu-v2/NuttX/nuttx-export/include/cxx -I$(PX4PSP_MODULE_BUILD_OUTPUT)/px4fmu-v2/NuttX/nuttx-export/arch/chip -I$(PX4PSP_MODULE_BUILD_OUTPUT)/px4fmu-v2/NuttX/nuttx-export/arch/common -I$(PX4PSP_MODULE_BUILD_OUTPUT)/external/Install/include -IC:/Users/MRWANG~1/DOCUME~1/MATLAB/Add-Ons/TOOLBO~1/PX4PSP~1/code/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DMODEL=ekf_cf -DNUMST=2 -DNCSTATES=0 -DHAVESTDIO -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DUSE_STDPERIPH_DRIVER -DPX4 -DCONFIG_ARCH_BOARD_PX4FMU_V2 -DGIT_VERSION=d3398270e101359de9687c2d077d991c9892f573 -D__DF_NUTTX -D__PX4_NUTTX -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DHSE_VALUE=8000000 -DNULL=0 -DEXIT_FAILURE=1 -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLEPRINTF -DSTACK_SIZE=256 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT
DEFINES_BUILD_ARGS = -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0
DEFINES_IMPLIED = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DUSE_STDPERIPH_DRIVER -DPX4 -DCONFIG_ARCH_BOARD_PX4FMU_V2 -DGIT_VERSION=d3398270e101359de9687c2d077d991c9892f573 -D__DF_NUTTX -D__PX4_NUTTX -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DHSE_VALUE=8000000 -DNULL=0 -DEXIT_FAILURE=1 -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLEPRINTF -DSTACK_SIZE=256 -DRT
DEFINES_STANDARD = -DMODEL=ekf_cf -DNUMST=2 -DNCSTATES=0 -DHAVESTDIO

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_IMPLIED) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/ekf_cf_ert_rtw/ekf_cf.c $(START_DIR)/ekf_cf_ert_rtw/ekf_cf_data.c $(START_DIR)/ekf_cf_ert_rtw/rtGetInf.c $(START_DIR)/ekf_cf_ert_rtw/rtGetNaN.c $(START_DIR)/ekf_cf_ert_rtw/rt_nonfinite.c C:/Users/MRWANG~1/DOCUME~1/MATLAB/Add-Ons/TOOLBO~1/PX4PSP~1/code/src/PX4_TA~1.C C:/Users/MRWANG~1/DOCUME~1/MATLAB/Add-Ons/TOOLBO~1/PX4PSP~1/code/src/NUTTXI~1.C

MAIN_SRC = $(START_DIR)/ekf_cf_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = ekf_cf.o ekf_cf_data.o rtGetInf.o rtGetNaN.o rt_nonfinite.o PX4_TaskControl.o nuttxinitialize.o

MAIN_OBJ = ert_main.o

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


define CALLPX4MK 
	@echo "Making Firmware $2" 
	cmd.exe @cmd /c "$(PX4PSP_WIN10_BASH_PATH) -c 'echo Starting PX4 Build;cd $(PX4_BASE);pwd;export PATH=$$HOME/ninja:$$HOME/gcc-arm-none-eabi-7-2017-q4-major/bin:$$PATH;make $(PX4PSP_CMAKE_CONFIG)'" 
	@echo "### Finished calling CMAKE build process ###" 
endef


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild download postdownload_preexecute execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


download : build


postdownload_preexecute : download
	@echo "### Invoking postbuild tool "Invoke Make" ..."
	$(INVOKE) $(MAKEFILENAME)
	@echo "### Done invoking postbuild tool."


execute : postdownload_preexecute
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) $(OBJS) $(MAIN_OBJ) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(START_DIR)/ekf_cf_ert_rtw/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


%.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o $@ $<


PX4_TaskControl.o : C:/Users/MRWANG~1/DOCUME~1/MATLAB/Add-Ons/TOOLBO~1/PX4PSP~1/code/src/PX4_TaskControl.c
	$(CC) $(CFLAGS) -o $@ $<


nuttxinitialize.o : C:/Users/MRWANG~1/DOCUME~1/MATLAB/Add-Ons/TOOLBO~1/PX4PSP~1/code/src/nuttxinitialize.c
	$(CC) $(CFLAGS) -o $@ $<


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### MAKEFILENAME = $(MAKEFILENAME)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


