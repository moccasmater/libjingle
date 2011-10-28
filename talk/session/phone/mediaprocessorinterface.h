/*
 * libjingle
 * Copyright 2004--2010, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef TALK_SESSION_PHONE_MEDIAPROCESSORINTERFACE_H_
#define TALK_SESSION_PHONE_MEDIAPROCESSORINTERFACE_H_

#include "talk/base/basictypes.h"
#include "talk/base/sigslot.h"
#include "talk/session/phone/videoframe.h"

namespace cricket {

enum MediaProcessorDirection {
    MPD_RX = 1 << 0,
    MPD_TX = 1 << 1,
    MPD_RX_AND_TX = MPD_RX | MPD_TX,
};

struct AudioFrame {
  AudioFrame(int16* audio, size_t audio_length, int sample_freq, bool stereo)
      : audio10ms(audio),
        length(audio_length),
        sampling_freq(sample_freq),
        is_stereo(stereo) {
  }

  int16* audio10ms;
  size_t length;
  int sampling_freq;
  bool is_stereo;
};

class VoiceProcessor : public sigslot::has_slots<> {
 public:
  virtual ~VoiceProcessor() {}
  // Contents of frame may be manipulated by the processor.
  // The processed data is expected to be the same size as the
  // original data
  virtual void OnFrame(uint32 ssrc, AudioFrame* frame) = 0;
};

class VideoProcessor : public sigslot::has_slots<> {
 public:
  virtual ~VideoProcessor() {}
  // Contents of frame may be manipulated by the processor.
  // The processed data is expected to be the same size as the
  // original data
  virtual void OnFrame(uint32 ssrc, VideoFrame* frame) = 0;
};

}  // namespace cricket
#endif  // TALK_SESSION_PHONE_MEDIAPROCESSORINTERFACE_H_
