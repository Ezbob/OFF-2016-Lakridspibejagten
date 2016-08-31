#include <vector>
#include <iostream>
#include <AL/alc.h>
#include <AL/al.h>
#include <vorbis/vorbisfile.h>

namespace audio {
	decltype(alcOpenDevice(0)) device;
	decltype(alcCreateContext(0, 0)) context;

	struct clip {

		clip() : buffer{new std::vector<char>()} { }
		~clip() { delete buffer; }

		std::vector<char> *  buffer;
		ALenum format;
		ALsizei frequency;
	};

	clip load_ogg(char const * filename) {
		clip ogg_clip;
		static int const buffer_size = 32768;
		static int const endian = 0;
		static char ogg_buffer[buffer_size];
		static OggVorbis_File ogg_file;

		int bit_stream;
		long bytes;

		std::FILE * file = std::fopen(filename, "rb");

		ov_open(file, &ogg_file, NULL, 0);

		auto ogg_info = ov_info(&ogg_file, -1);
		
		if (ogg_info->channels == 1)
			ogg_clip.format = AL_FORMAT_MONO16;
		else
			ogg_clip.format = AL_FORMAT_STEREO16;

		ogg_clip.frequency = ogg_info->rate;

		while ((bytes = ov_read(&ogg_file, ogg_buffer, buffer_size, endian, 2, 1, &bit_stream)) > 0)
			ogg_clip.buffer->insert(ogg_clip.buffer->end(), ogg_buffer, ogg_buffer + bytes);

		ov_clear(&ogg_file);
	
		return ogg_clip;
	}
}

int main(int argc, char ** argv) {

	if (argc == 1) {
		std::cerr << "usage: " << argv[0] << " <filename>\n";
		return -1;
	}
	audio::device = alcOpenDevice(0);
	if (audio::device == 0) {
		std::cerr << "audio: no device found\n";
		return -1;
	}

	audio::context = alcCreateContext(audio::device, 0);

	if (audio::context == 0) {
		std::cerr << "audio: failed to get context\n";
		return -1;
	}

	alcMakeContextCurrent(audio::context);

	auto clip = audio::load_ogg(argv[1]);
	ALuint buffer_id;

	alGenBuffers(1, &buffer_id);
	alBufferData(buffer_id, clip.format, &(*clip.buffer)[0], static_cast<ALsizei>(clip.buffer->size()), clip.frequency);

	ALuint source_id;
	alGenSources(1, &source_id);
	alSourcei(source_id, AL_BUFFER, buffer_id);


	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source_id, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(source_id, AL_LOOPING, AL_TRUE);

	alSourcePlay(source_id);

	ALint state;

	while (state != AL_STOPPED)
		alGetSourcei(source_id, AL_SOURCE_STATE, &state);

	alDeleteSources(1, &source_id);
	alDeleteBuffers(1, &buffer_id);

	alcDestroyContext(audio::context);
	alcCloseDevice(audio::device);
	return 0;
}
