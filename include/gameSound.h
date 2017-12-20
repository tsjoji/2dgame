
struct HEADER {
	unsigned char riff[4];						// RIFF string
	unsigned int  size;			         	    // overall size of file in bytes
	unsigned char wave[4];						// WAVE string
	unsigned char fmt_chunk_marker[4];			// fmt string with last is null char
	unsigned int length_of_fmt;					// length of the format data
	unsigned int format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	unsigned int channels;						// tells you how many channels does it use
	unsigned int sample_rate;					// the samples in blocks/sec
	unsigned int byterate;						// SampleRate * NumChannels * BitsPerSample/8
	unsigned int block_align;					// NumChannels * BitsPerSample/8
	unsigned int bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
	unsigned char data_chunk_header[4];	    	// DATA string or FLLR string
	unsigned int data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

/*
*@brief inits SDL MIX
*@param void
*@returns void
*/
void Soundinit();

/*
*@brief inits SDL MIX experimental
*@param void
*@returns void
*/
void Soundinit2();

/*
*@brief slows down/speeds up audio if you ever get too low on health
*@param int speed, double time
*@returns void
*/
void audiospeedchange(int speed, double time);
/*
*@brief skips to that part of the song in seconds
*@param int speed
*@returns void
*/
void fastforward(int time);

/*
*@brief controls volume from 0-128
*@param void
*@returns void
*/
void SoundVolume();

/*
*@brief sets amplitiude back o 0 and closes audio
*@param void
*@returns void
*/
void Soundclose();


/*
*@brief returns all info for the wav file
*@param FILE *ptr
*@returns long
*/
long Soundinfo(FILE *ptr);

/*
*@brief returns length of song
*@param void
*@returns int
*/
int timeofsong();

/*
*@brief returns num chunks
*@param void
*@returns int
*/
int numchuncks();

