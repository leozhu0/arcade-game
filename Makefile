CXXFLAGS = -std=c++11 -DGL_SILENCE_DEPRECATION
LDFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lglut

main: src/main.cpp src/lib/player.cpp src/lib/mobs.cpp src/lib/bullet.cpp src/lib/texture.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

run: main
	./main

clean:
	rm -f main
