.PHONY:
CPP         	=   g++
CFLAGS      	=   -Wall -pedantic-errors -std=c++11

CGLAGSORIG		= 	
CFLAGSOPT1		=	-O3
CFLAGSOPT2		=	-O3 -msse3
CFLAGSOPT3		=	-O3 -ffast-math
# CFLAGSOPT4		=	-O3 -msse3
CFLAGSTOGETHER	=	$(CFLAGSOPT1) $(CFLAGSOPT2) $(CFLAGSOPT3) $(CFLAGSOPT4) $(CFLAGSORIG)

CFLAGSREP		=	-fopt-info-vec-missed
# -fopt-info-all -fopt-info-vec-missed

CFLAGSVECT		=	-O2 -ftree-vectorize

CFLAGSOTHER 	= 	-funroll-loops

#CFLAGSVECT  	=   -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-loop-vectorize -ftree-loop-distribution -ftree-loop-distribute-patterns -fsplit-paths -ftree-slp-vectorize -fvect-cost-model -ftree-partial-pre -fpeel-loops -fipa-cp-clone
#CFLAGSREP   	=   -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose	=1 -ffast-math -g -fopt-info-all -fopt-info-missed-all
#DEPS        	=   GJ_Elim.cpp   -funroll-loops -fopt-info -ftree-vectorize -fopt-info-vec-missed -O3 -msse3 -ffast-math

OUTPUT      	=   ./binaries/
RepOutPut		=	./binaries/Results.txt
ReportErr		=	./reports/

SRCS			=	GJ_Elim_Orig 	GJ_Elim_Double
NAMEFLAG		=	ORIG	OPT1	OPT2	OPT3	TOGETHER
OBJS_ORIG		=	GJ_Elim_Orig_ORIG	GJ_Elim_Orig_OPT1 GJ_Elim_Orig_OPT2 GJ_Elim_Orig_OPT3	GJ_Elim_Orig_TOGETHER \
					GJ_Elim_Double_ORIG	GJ_Elim_Double_OPT1	GJ_Elim_Double_OPT2	GJ_Elim_Double_OPT3	GJ_Elim_Double_TOGETHER \
					GJ_Elim_NonIf_ORIG	GJ_Elim_NonIf_OPT1	GJ_Elim_NonIf_OPT2	GJ_Elim_NonIf_OPT3	GJ_Elim_NonIf_TOGETHER
# OBJS_DOUB		=
# FILENAMES		:= $(join $(SRCS),$(NAMEFLAG))
# FILENAMES		:= $(SRCS)_$(NAMEFLAG)
all: 
	echo "WTF?"

compileAll: $(OBJS_ORIG)

# # $(addprefix src/,foo bar)

$(addprefix GJ_Elim_Orig_,$(NAMEFLAG)): GJ_Elim_Orig.cpp
	$(CPP) $(CFLAGS) $(CFLAGSREP) $(CFLAGS$(subst GJ_Elim_Orig_,,$@)) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt

$(addprefix GJ_Elim_Double_,$(NAMEFLAG)): GJ_Elim_Double.cpp
	$(CPP) $(CFLAGS) $(CFLAGSREP) $(CFLAGS$(subst GJ_Elim_Double_,,$@)) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt

$(addprefix GJ_Elim_NonIf_,$(NAMEFLAG)): GJ_Elim_NonIf.cpp
	$(CPP) $(CFLAGS) $(CFLAGSREP) $(CFLAGS$(subst GJ_Elim_NonIf_,,$@)) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt	


testKek: $(addprefix test_1800,$(OBJS_ORIG)) 

testKek2: $(addprefix test_3400,$(OBJS_ORIG))
#$(addprefix test_3400,$(OBJS_ORIG))

$(addprefix test_1800,$(OBJS_ORIG)): 
	 cd ./binaries/; \
	echo -n $(subst test_1800,,$@) >> Results.txt;\
	echo -n " : " >> Results.txt;\
	./$(subst test_1800,,$@) Zbytocne MatrixFile1800.txt

$(addprefix test_3400,$(OBJS_ORIG)): 
	 cd ./binaries/; \
	echo -n $(subst test_1800,,$@) >> Results.txt;\
	echo -n " : " >> Results.txt;\
	./$(subst test_3400,,$@) Zbytocne MatrixFile3400.txt


clearResults:
	echo "" > ./binaries/Results.txt

clean:
	rm -rf ./reports/*
	rm -rf ./binaries/GJ_Elim*