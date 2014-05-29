CC = gcc

ifeq ($(cc),g++)
  EXT = ++$(PROC)
else
  EXT = $(PROC)
endif

ifeq ($(DEBUG),yes)
  CFLAGS  = -g -Wpointer-arith -Wall -ansi $(INC_MTRACER)=0
  DBG_LIB = $(LIB_MTRACER)
  DBG = .dbg
else
  CFLAGS  = -O2 -ansi
  DBG_LIB = 
  DBG = 
endif

# la lib. <glx>
#G3X_LIB = -L$(HOME)/bin -lg3x$(EXT)$(DBG) -lGL -lGLU -lglut
#G3X_INC = -I$(HOME)/mylibs/g3x/include

lib = -L/usr/lib $(libG3X)#$(G3X_LIB)  $(DBG_LIB) -lm -lpthread
inc = -I./include $(incG3X)# $(G3X_INC) -D_REENTRANT 
src = src/

all : 3Ddemo demo_scene clean

# règle générique de création de xxx.o à partir de src/xxx.c
%.o : $(src)%.c
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	@echo "------------------------"

# règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
% : %.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"
	
.PHONY : clean cleanall ?

# informations sur les paramètres de compilation       
? :
	@echo "---------infos de compilation----------"
	@echo "  processeur     : $(PROCBIT)"
	@echo "  compilateur    : $(CC)"
	@echo "  options        : $(CFLAGS)"
	@echo "  lib g3x/OpenGl : $(libG3X)$(COMP)"
	@echo "  headers        : $(incG3X)"
ifeq ($(DBG),yes)
	@echo "  traceur ACTIF  : $(DBG_LIB)"
	@echo "                   $(DBG_FLAG)"
endif

clean : 
	@rm -f *.o
cleanall :
	@rm -f *.o 3Ddemo demo_scene
	
