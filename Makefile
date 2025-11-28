CXX = g++-14
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -g
COMPILE_HEADER = $(CXX) $(CXXFLAGS) -x c++-system-header -c
EXEC = watan_fun

STDLIB_SENTINEL = .stdlib_precompiled

.PHONY: all clean stdlib

all: stdlib modules implementations main link

stdlib: $(STDLIB_SENTINEL)

$(STDLIB_SENTINEL):
	$(COMPILE_HEADER) iostream
	$(COMPILE_HEADER) sstream
	$(COMPILE_HEADER) fstream
	$(COMPILE_HEADER) utility
	$(COMPILE_HEADER) random
	$(COMPILE_HEADER) vector
	$(COMPILE_HEADER) map
	$(COMPILE_HEADER) memory
	$(COMPILE_HEADER) string
	$(COMPILE_HEADER) optional
	$(COMPILE_HEADER) array
	$(COMPILE_HEADER) algorithm
	$(COMPILE_HEADER) stdexcept
	@touch $(STDLIB_SENTINEL)

modules: $(STDLIB_SENTINEL)
	$(CXX) $(CXXFLAGS) -c WatanTypes.cc -o WatanTypes.o
	$(CXX) $(CXXFLAGS) -c RandomGenerator.cc -o RandomGenerator.o
	$(CXX) $(CXXFLAGS) -c IDiceStrategy.cc -o IDiceStrategy.o
	$(CXX) $(CXXFLAGS) -c FairDiceStrategy.cc -o FairDiceStrategy.o
	$(CXX) $(CXXFLAGS) -c LoadedDiceStrategy.cc -o LoadedDiceStrategy.o
	$(CXX) $(CXXFLAGS) -c Tile.cc -o Tile.o
	$(CXX) $(CXXFLAGS) -c Criterion.cc -o Criterion.o
	$(CXX) $(CXXFLAGS) -c Goal.cc -o Goal.o
	$(CXX) $(CXXFLAGS) -c IBoardSetupStrategy.cc -o IBoardSetupStrategy.o
	$(CXX) $(CXXFLAGS) -c RandomBoardSetupStrategy.cc -o RandomBoardSetupStrategy.o
	$(CXX) $(CXXFLAGS) -c FileBoardSetupStrategy.cc -o FileBoardSetupStrategy.o
	$(CXX) $(CXXFLAGS) -c Player.cc -o Player.o
	$(CXX) $(CXXFLAGS) -c Board.cc -o Board.o
	$(CXX) $(CXXFLAGS) -c Game.cc -o Game.o
	$(CXX) $(CXXFLAGS) -c CommandParser.cc -o CommandParser.o
	$(CXX) $(CXXFLAGS) -c CommandLineParser.cc -o CommandLineParser.o
	$(CXX) $(CXXFLAGS) -c CommandExecutor.cc -o CommandExecutor.o

implementations:
	$(CXX) $(CXXFLAGS) -c WatanTypes-impl.cc -o WatanTypes-impl.o
	$(CXX) $(CXXFLAGS) -c Tile-impl.cc -o Tile-impl.o
	$(CXX) $(CXXFLAGS) -c Criterion-impl.cc -o Criterion-impl.o
	$(CXX) $(CXXFLAGS) -c Goal-impl.cc -o Goal-impl.o
	$(CXX) $(CXXFLAGS) -c RandomGenerator-impl.cc -o RandomGenerator-impl.o
	$(CXX) $(CXXFLAGS) -c IDiceStrategy-impl.cc -o IDiceStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c FairDiceStrategy-impl.cc -o FairDiceStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c LoadedDiceStrategy-impl.cc -o LoadedDiceStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c IBoardSetupStrategy-impl.cc -o IBoardSetupStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c RandomBoardSetupStrategy-impl.cc -o RandomBoardSetupStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c FileBoardSetupStrategy-impl.cc -o FileBoardSetupStrategy-impl.o
	$(CXX) $(CXXFLAGS) -c CommandParser-impl.cc -o CommandParser-impl.o
	$(CXX) $(CXXFLAGS) -c CommandLineParser-impl.cc -o CommandLineParser-impl.o
	$(CXX) $(CXXFLAGS) -c CommandExecutor-impl.cc -o CommandExecutor-impl.o
	$(CXX) $(CXXFLAGS) -c Player-impl.cc -o Player-impl.o
	$(CXX) $(CXXFLAGS) -c Board-impl.cc -o Board-impl.o
	$(CXX) $(CXXFLAGS) -c Game-impl.cc -o Game-impl.o

main:
	$(CXX) $(CXXFLAGS) -c main.cc -o main.o

link:
	$(CXX) $(CXXFLAGS) *.o -o $(EXEC)

clean:
	rm -rf $(EXEC) *.o *.d gcm.cache $(STDLIB_SENTINEL)
