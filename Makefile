CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -MMD
EXEC = watan

IXXS = Board.ixx CommandExecutor.ixx CommandLineParser.ixx CommandParser.ixx \
       Criterion.ixx Goal.ixx Player.ixx Tile.ixx RandomGenerator.ixx \
       FairDiceStrategy.ixx LoadedDiceStrategy.ixx Game.ixx WatanTypes.ixx

CCS = main.cc \
      Board.cc CommandExecutor.cc CommandLineParser.cc CommandParser.cc \
      Criterion.cc Goal.cc Player.cc Tile.cc RandomGenerator.cc \
      FairDiceStrategy.cc LoadedDiceStrategy.cc Game.cc WatanTypes.cc

SRCS = ${IXXS} ${CCS}
OBJS = ${SRCS:.cc=.o}
OBJS := ${OBJS:.ixx=.o}

DEPS = ${OBJS:.o=.d}

${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${EXEC}

%.o: %.ixx
	${CXX} ${CXXFLAGS} -c $< -o $@

%.o: %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} ${EXEC} ${DEPS}

-include ${DEPS}
