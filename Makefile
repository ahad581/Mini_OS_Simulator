CXX = clang++-20
CXXFLAGS = -std=c++17 -pthread -Wall
TARGET = os_simulator
OBJS = main.o Scheduler.o ProducerConsumer.o BankersAlgorithm.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Process.h Scheduler.h ProducerConsumer.h BankersAlgorithm.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Scheduler.o: Scheduler.cpp Scheduler.h Process.h
	$(CXX) $(CXXFLAGS) -c Scheduler.cpp

ProducerConsumer.o: ProducerConsumer.cpp ProducerConsumer.h Process.h
	$(CXX) $(CXXFLAGS) -c ProducerConsumer.cpp

BankersAlgorithm.o: BankersAlgorithm.cpp BankersAlgorithm.h Process.h
	$(CXX) $(CXXFLAGS) -c BankersAlgorithm.cpp

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
