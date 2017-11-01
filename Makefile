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

# compileAll:$(OBJS_ORIG)

# $(OBJS_ORIG): GJ_Elim_Orig.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSREP) $($(subst GJ_Elim_Orig_,,$(OBJS_ORIG))) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt


# $(subst ee,EE,feet on the street)

# compileOrig: $(addprefix GJ_Elim_Orig_,$(NAMEFLAG)) 
# 	$(CPP) $(CFLAGS) $(CFLAGSREP) -o $(OUTPUT)$< $< 2>$(ReportErr)report_$@.txt

compileAll: $(OBJS_ORIG)

# # $(addprefix src/,foo bar)

$(addprefix GJ_Elim_Orig_,$(NAMEFLAG)): GJ_Elim_Orig.cpp
	$(CPP) $(CFLAGS) $(CFLAGSREP) $(CFLAGS$(subst GJ_Elim_Orig_,,$@)) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt

$(addprefix GJ_Elim_Double_,$(NAMEFLAG)): GJ_Elim_Double.cpp
	$(CPP) $(CFLAGS) $(CFLAGSREP) $(CFLAGS$(subst GJ_Elim_Double_,,$@)) -o $(OUTPUT)$@ $< 2>$(ReportErr)report_$@.txt	


testKek: $(addprefix test_1800,$(OBJS_ORIG)) 
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

# $(addprefix test_3400,$(OBJS_ORIG))

# testAll: test_$(OBJS_ORIG)_1800 

# # # test_$(OBJS_ORIG)_3400
# test_$(OBJS_ORIG)_1800: test_%_1800: %
# 	cd ./binaries/; \
# 	echo -n $< >> Results.txt;\
# 	echo -n " : " >> Results.txt;\
# 	./$< Zbytocne MatrixFile1800.txt


# $(filter GJ_Elim_Orig_%,$(OBJS_ORIG)): GJ_Elim_Orig_%: GJ_Elim_Orig.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGS%) $(CFLAGSREP) -o $(OUTPUT)$@ $< 2>report_$@.txt

# $(filter GJ_Elim_Double_%,$(OBJS_ORIG)): GJ_Elim_Double_%: GJ_Elim_Double.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGS%) $(CFLAGSREP) -o $(OUTPUT)$@ $< 2>report_$@.txt



# test_$(OBJS_ORIG)_3400: $(OBJS_ORIG)
# 	cd ./binaries/; \
# 	./$< Zbytocne MatrixFile3400.txt

# $(SRCS)_$(NAMEFLAG).o: %.o: $(SRCS).cpp
# compileAll: $(SRCS)_$(NAMEFLAG).o
# 	$(CPP) $(CFLAGS) $(CFLAGS$(NAMEFLAG)) $(CFLAGSREP) -o $(OUTPUT)$(SRCS)_$(NAMEFLAG).o $< 2>report_$(SRCS)_$(NAMEFLAG).txt

# compileAll: $(FILENAMES).o
# echo -n "Compiled: " $<


# compileOrig: $(OBJS_ORIG)

# $(OBJS_ORIG): %.o: .cpp
# 	$(CPP) $(CFLAGS) $(CFLAGS$(NAMEFLAG)) $(CFLAGSREP) -o $(OUTPUT)$@ $< 2>report_$@.txt

# $(FILENAMES).o: $(SRCS).cpp
# $(CPP) $(CFLAGS) $(CFLAGS$(NAMEFLAG)) $(CFLAGSREP) -o $(OUTPUT)$@ $< 2>report_$@.txt

# all: origin originVectorized double doubleVectorized

# init:
# 	mkdir binaries
# 	mkdir report

# origin: GJ_Elim_Orig.cpp
# 	$(CPP) $(CFLAGS) GJ_Elim_Orig.cpp -o ./binaries/GJ_Elim_Orig 2>reportOrig.txt

# originVectorized: GJ_Elim_Orig.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSVECT) GJ_Elim_Orig.cpp -o ./binaries/GJ_Elim_Orig_Vec 2>reportOrigVec.txt

# double: GJ_Elim_Double.cpp
# 	$(CPP) $(CFLAGS) GJ_Elim_Double.cpp -o ./binaries/GJ_Elim_Double 2>reportDouble.txt

# doubleVectorized: GJ_Elim_Double.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSVECT) GJ_Elim_Double.cpp -o ./binaries/GJ_Elim_Double_Vec 2>reportDoubleVec.txt

# test: test1 test2 test3 test4

# test1:
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig Zbytocne MatrixFile3400.txt

# test2:
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig_Vec Zbytocne MatrixFile3400.txt

# test3:
# 	cd ./binaries/; \
# 	./GJ_Elim_Double Zbytocne MatrixFile3400.txt

# test4:
# 	cd ./binaries/; \
# 	./GJ_Elim_Double_Vec Zbytocne MatrixFile3400.txt

# test_1800: test1_1800 test2_1800 test3_1800 test4_1800

# test1_1800:
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig Zbytocne MatrixFile1800.txt

# test2_1800:
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig_Vec Zbytocne MatrixFile1800.txt

# test3_1800:
# 	cd ./binaries/; \
# 	./GJ_Elim_Double Zbytocne MatrixFile1800.txt

# test4_1800:
# 	cd ./binaries/; \
# 	./GJ_Elim_Double_Vec Zbytocne MatrixFile1800.txt

# test_vect: test_vect_1 test_vect_2

# test_vect_1: 
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig_Vec Zbytocne MatrixFile1800.txt

# test_vect_2:
# 	cd ./binaries/; \
# 	./GJ_Elim_Orig_Vec Zbytocne MatrixFile3400.txt



# vectorized: GJ_Elim.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSVECT) GJ_Elim.cpp -o GJ_Elim_Vectorized

# vectorizedReport: GJ_Elim.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSVECT) $(CFLAGSREP) GJ_Elim.cpp -o GJ_Elim_Report 2>./report.txt

# showReport:
# 	cat ./report/report.txt

# skuska: skuska.cpp
# 	$(CPP) $(CFLAGS) $(CFLAGSVECT) $(CFLAGSREP) skuska.cpp -o skuska

clean:
	rm -rf ./reports/*
	rm -rf ./binaries/GJ_Elim*