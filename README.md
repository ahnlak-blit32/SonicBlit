# SonicBlit

![Build](https://github.com/ahnlak-blit32/SonicBlit/workflows/Build/badge.svg)

While the 32Blit is perfectly capable of playing WAV and MP3 audio, thanks to
it's ever-expanding API, the fact remains that audio files can take up a lot
of space once compiled into your project.

In the 'old days' of the C64 (lesser home computers were also available) game
music wasn't encoded this way; it was essentially stored as a sequence of notes
to be played, often wich spectacularly obscure and twisted space-saving tricks
to squeeze every last byte out of the limited memory.

We don't have to go that far any more, but rendering your game music down to
a simple sequence of notes does save a whole lot of memory and, well, it feels
a whole lot more 8 bit!


# The Compiler

Taking inspiration from the likes of SonicPi (but with a much less powerful 
'language' at it's heart), SonicBlit can read text files defining your music
and play them for you to test, reloading when they change and generally making
your music-debugging life as easy as possible.

Once you're done, you can compile those text (source) files into a single binary
data block, which can be added to your normal asset pipeline.


# The Library

Within your game, you will be able to simply drop the `SonicBlit` directory
into your project, add the relavent entries into your `CMakeLists.txt` file, 
and then add appropriate calls into your game code.
