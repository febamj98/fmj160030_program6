#
#Feba Jacob
#fmj160030@utdallas.edu
#CS 3377.501
#

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk - lcurses
PROJECTNAME = Program6.Backup

EXECFILE = program6

OBJS = myproject.o

all: $(EXECFILE)

#CLEAN
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*

$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

#BACKUP TARGET
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups @$(eval CURDIRNAME := $(shell basename "'pwd'"))
	@$(eval MKBKUPNAME := ~/BACKUPS/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%m:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ./$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
