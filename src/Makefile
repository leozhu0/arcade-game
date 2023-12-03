CXXFLAGS = g++ -std=c++11 -DGL_SILENCE_DEPRECATION main.cpp lib/player.cpp lib/mobs.cpp lib/bullet.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lGL -lglut

make: 
	$(CXXFLAGS) -o main

run: ./main
	DISPLAY=:0 ./main

clean:
	rm main
