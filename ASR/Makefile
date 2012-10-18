all:
	g++ -o run main.cpp VoiceBase.cpp -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" ` pkg-config --cflags --libs pocketsphinx sphinxbase `