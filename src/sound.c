#include <SDL.h>
#include "simple_logger.h"
#include <stdio.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "gameSound.h"
#include <io.h>
#include <string.h>

//extern DECLSPEC int SDLCALL Mix_OpenAudioDevice(int frequency, Uint16 format, int nchannels, int chunksize, const char* device, int allowed_changes);

#define TRUE 1 
#define FALSE 0

#define	BLOCK_SIZE 4096

#define maxchunks 100
#define OP_DBL_Digs 18

SDL_AudioDeviceID deviceId;
Uint8 *wavBuffer;

unsigned char buffer4[4];
unsigned char buffer2[2];

int amplitude[maxchunks]; 
int counter = 0;
int *frequency;

struct HEADER header;

long chuncksize;

Mix_Chunk *sample, *sample2, *sample3;

int duration;

void Soundinit(char* input)
{
	FILE * check = fopen("ffmpeg.exe", "r");
	if (check)
	{
		printf("you forgot ffmpeg please download ffmpeg.exe");
		exit(1);
	}
	
	char command[70];
	system("del /f /q audio66.ogg >nul 2>&1");
	system("y");


	strcpy(command, "ffmpeg -i ");
	strcat(command, input);
	strcat(command," audio66.ogg");
	system(command);

	system("del /f /q slowaudio66.ogg >nul 2>&1");
	system("y");
	
	system("ffmpeg -i audio66.ogg -filter:a \"atempo = .7\" -vn slowaudio66.ogg");
	//system("ping 192.0.2.2 -n 1 -w 10000 > nul");
	

	if (SDL_Init(SDL_INIT_AUDIO) == -1) 
	{
		slog("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		slog("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	sample = Mix_LoadMUS("audio66.ogg");
	sample2 = Mix_LoadMUS("slowaudio66.ogg");

	Mix_PlayMusic(sample, 0);	
}


void Soundinit2()
{
	Mix_Chunk *sample, *sample2,*sample3;

	if (SDL_Init(SDL_INIT_AUDIO) == -1)
	{
		slog("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}


	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		slog("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	sample = Mix_LoadWAV("end.wav");

	

	if (Mix_PlayChannel(2, sample, 0) == -1)
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
}
int currlocationslow = 0;
void audiospeedchange(int speed, double time)
{
	if (currlocationslow==0 && speed==0)
	{
		currlocationslow = 1;
		Mix_PlayMusic(sample2,0);
		Mix_SetMusicPosition((time*1.42));
	}

	if (currlocationslow == 1 && speed == 1)
	{
		currlocationslow = 0;
		Mix_PlayMusic(sample, 0);
		Mix_SetMusicPosition(time);
	}
}

void fastforward(int time)
{
	int realtime = time / 1000;
	Mix_SetMusicPosition(realtime);
}



void SoundVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void Soundclose()
{
	memset(amplitude, 0, sizeof(amplitude));
	Mix_CloseAudio();
}



long Soundinfo(FILE *ptr)
{

	    long biggest_amp=0;
	    int innercounter = 0;
		// get file path
		char cwd[1024];
		long size_of_each_sample;
		long num_samples;
		long i = 0;
		char data_buffer[16];
		int  size_is_correct = TRUE;
		// read header parts
		int read = 0;
		long bytes_in_each_channel;
		char format_name[10] = "";
		long low_limit = 0l;
		long high_limit = 0l;
		unsigned int  xchannels = 0;
		int data_in_channel = 0;
		int ampcounter = 0;
		

		if (getcwd(cwd, sizeof(cwd)) != NULL) 
		{
		

			//1-4
			read = fread(header.riff, sizeof(header.riff), 1, ptr);//byte 1-4

			//5-8
			read = fread(buffer4, sizeof(buffer4), 1, ptr);


			// convert little endian to big endian 4 byte int bytes 5-8
			header.size = buffer4[0] |
				(buffer4[1] << 8) |
				(buffer4[2] << 16) |
				(buffer4[3] << 24);


			// 9-12
			read = fread(header.wave, sizeof(header.wave), 1, ptr);


			//13-16
			read = fread(header.fmt_chunk_marker, sizeof(header.fmt_chunk_marker), 1, ptr);


			read = fread(buffer4, sizeof(buffer4), 1, ptr);


			// convert little endian to big endian 4 byte integer
			//17-20
			header.length_of_fmt = buffer4[0] |
				(buffer4[1] << 8) |
				(buffer4[2] << 16) |
				(buffer4[3] << 24);


			//21-22
			read = fread(buffer2, sizeof(buffer2), 1, ptr);

			header.format_type = buffer2[0] | (buffer2[1] << 8);
			
			if (header.format_type == 1)
				strcpy(format_name, "PCM");
			else if (header.format_type == 6)
				strcpy(format_name, "A-law");
			else if (header.format_type == 7)
				strcpy(format_name, "Mu-law");


			//23-24
			read = fread(buffer2, sizeof(buffer2), 1, ptr);


			header.channels = buffer2[0] | (buffer2[1] << 8);

			//25-28
			read = fread(buffer4, sizeof(buffer4), 1, ptr);


			header.sample_rate = buffer4[0] |
				(buffer4[1] << 8) |
				(buffer4[2] << 16) |
				(buffer4[3] << 24);

			//25-28

			read = fread(buffer4, sizeof(buffer4), 1, ptr);


			header.byterate = buffer4[0] |
				(buffer4[1] << 8) |
				(buffer4[2] << 16) |
				(buffer4[3] << 24);

			//29-32
			read = fread(buffer2, sizeof(buffer2), 1, ptr);


			header.block_align = buffer2[0] |
				(buffer2[1] << 8);

			//33-34
			read = fread(buffer2, sizeof(buffer2), 1, ptr);

			//35-36
			header.bits_per_sample = buffer2[0] |
				(buffer2[1] << 8);

			//37-40
			read = fread(header.data_chunk_header, sizeof(header.data_chunk_header), 1, ptr);

			//41-44
			read = fread(buffer4, sizeof(buffer4), 1, ptr);


			header.data_size = buffer4[0] |
				(buffer4[1] << 8) |
				(buffer4[2] << 16) |
				(buffer4[3] << 24);


			// calculate no.of samples
			 num_samples = (8 * header.data_size) / (header.channels * header.bits_per_sample);


			size_of_each_sample = (header.channels * header.bits_per_sample) / 8;



			memset(amplitude, 0, sizeof(amplitude));

			// read each sample from data chunk if PCM
			if (header.format_type == 1) 
			{ // PCM

				i = 0;
				

				// make sure that the bytes-per-sample is completely divisible by num.of channels
				bytes_in_each_channel = (size_of_each_sample / header.channels);
				if ((bytes_in_each_channel  * header.channels) != size_of_each_sample) 
				{
					printf("Error: %ld x %ud <> %ld\n", bytes_in_each_channel, header.channels, size_of_each_sample);
					size_is_correct = FALSE;
				}

					if (size_is_correct)
					{
						// the valid amplitude range for values based on the bits per sample
						

						switch (header.bits_per_sample) 
						{
						case 8:
							low_limit = -128;
							high_limit = 127;
							break;
						case 16:
							low_limit = -32768;
							high_limit = 32767;
							break;

						}


						for (i = 1; i <= num_samples; i++)
						{

							read = fread(data_buffer, sizeof(data_buffer), 1, ptr);
							if (read == 1)
							{

								// dump the data read
							for (xchannels = 0; xchannels < header.channels; xchannels++) 
							{

									// convert data from little endian to big endian based on bytes in each channel sample
									if (bytes_in_each_channel == 4) 
									{
										data_in_channel = data_buffer[0] |
											(data_buffer[1] << 8) |
											(data_buffer[2] << 16) |
											(data_buffer[3] << 24);
									}
									else if (bytes_in_each_channel == 2) 
									{
										data_in_channel = data_buffer[0] |
											(data_buffer[1] << 8);
									}
									else if (bytes_in_each_channel == 1) 
									{
										data_in_channel = data_buffer[0];
									}

								}
									
								amplitude[ampcounter] = data_in_channel;
								ampcounter++;

							}
							else
							{
								printf("Error reading file. %d bytes\n", read);
								break;
							}

						} 

					} 


				} 

				fclose(ptr);

				
					if (amplitude[0]==0)
					{
						slog("your amp is zero stop giving me empty wav files");
					}
					slog("your amp is %li", amplitude[0]);
					return amplitude[0];

				
			}

}





int timeofsong()
{
	// calculate duration of file
	int duration_in_seconds = (float)header.size / header.byterate;
	return duration_in_seconds;
}


int numchuncks()
{
	int counter = 0;
	int i = 0;
	for (i; i < maxchunks; i++)
	{
		if (amplitude[i] != 0)
			counter++;
	}
	slog("\nthe numchunks are %i\n", counter);
	return counter;
}