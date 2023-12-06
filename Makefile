CXXFLAGS = g++ -std=c++11 -DGL_SILENCE_DEPRECATION src/main.cpp src/lib/player.cpp src/lib/mobs.cpp src/lib/bullet.cpp src/lib/texture.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lglut

make: 
	$(CXXFLAGS) -o main

run: ./main
	DISPLAY=:0 ./main

clean:
	rm main
