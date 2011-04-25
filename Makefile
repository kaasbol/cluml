# Vertel make welke compiler we willen gebruiken
CCP=g++

#hoe heet het programma?
PROGRAM     := cluml

COMM_H      := $(wildcard ../communication/src/*.h)

# maak een lijstje van alle headers
HEADERS     := $(wildcard src/*/*.h src/*.h )

# maak een lijst van alle sources
SOURCES     := $(wildcard src/*/*.cpp src/*.cpp )

# make bedenkt zo zelf de namen van de .o files
OBJECTS      = $(SOURCES:.cpp=.o)

#welke includes?
#INCDIR       = 

# debug output
CPPFLAGS += -DDEBUG
# extra debugging informatie
CPPFLAGS    += -g
# warnings
CPPFLAGS    += -Wall

# Welke bibliotheken hebben we nodig (en van waar)
#LIBS	       =

# ---------------------------

# Het hoofdoel is programma
MAIN	: ${PROGRAM}

# Hoe maak je app
$(PROGRAM)	: $(OBJECTS)
	$(LINK.cc) -o $(PROGRAM) $(OBJECTS) $(LIBS) $(CPPFLAGS)

# En om opruiming te houden.
clean	:
	-rm -f $(PROGRAM) $(OBJECTS)

install: $(PROGRAM) strip 
	install $(PROGRAM) /usr/local/bin
	install cluml2png /usr/local/bin/cluml2png
	chmod +x /usr/local/bin/cluml2png

strip: $(PROGRAM)
	strip $(PROGRAM)

test: $(PROGRAM)
	./cluml2png.sh doc/cluml.cluml

