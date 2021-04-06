/*
 * SonicBlit.hpp - embeddable loader / player for SonicBlit.
 *
 * This file (along with SonicBlit.cpp) provides a self-contained player for
 * SonicBlit data files; the process of adding support for SonicBlit into your
 * project is explained in the accompanying README.md
 *
 * Copyright (c) 2021 Pete Favelle / fsquared limited <32blit@fsquared.co.uk>
 *
 * This software is distributed under the MIT License; see LICENSE for details.
 */

#ifndef   _SONICBLIT_HPP_
#define   _SONICBLIT_HPP_

/* Constants and Enums. */

#define SB_MAGIC      "BEAM"
#define SB_VERSION    1
#define SB_OPERANDS   1

typedef enum : uint8_t
{
  OPCODE_NOP,
  OPCODE_SET_CHANNEL,
  OPCODE_SET_VOICE,
  OPCODE_PLAY,
  OPCODE_MAX
} sb_opcode_t;


/* Structures. */

#pragma pack(push,1)
/* Voice definition; sets the basic note form. */
typedef struct
{
  uint8_t             waveforms;
  uint16_t            volume;
  uint16_t            attack_ms;
  uint16_t            decay_ms;
  uint16_t            sustain_level;
  uint16_t            sustain_ms;
  uint16_t            release_ms;
  uint16_t            pulse_width;
} sb_voice_t;

/* Command definition; a single instruction in the song 'program'. */
typedef struct
{
  sb_opcode_t         opcode;
  uint16_t            operands[SB_OPERANDS];
} sb_command_t;

/* The structure to hold the complete program. */
typedef struct 
{
  char                magic[4];
  uint8_t             version;
  uint8_t             voice_count;
  const sb_voice_t   *voices;
  uint16_t            command_count;
  const sb_command_t *commands;
} sb_program_t;
#pragma pack(pop)

/* 
 * SonicBlit class; you can create multiple instances, with different channel
 * offsets, and they should play nicely together.
 */

class SonicBlit {

private:

  sb_program_t          c_program;
  uint16_t              c_prog_counter;
  bool                  c_prog_running;
  bool                  c_inst_running;

public:

          SonicBlit     ( uint8_t p_channel_offset = 0, const uint8_t *p_data = nullptr );
         ~SonicBlit     ( void );

  bool    load          ( const uint8_t *p_data );
  bool    update        ( uint32_t p_tick );
  bool    start         ( void );
  bool    pause         ( void );
  bool    stop          ( void );
  bool    is_running    ( void );
  bool    is_paused     ( void );

};

#endif /* _SONICBLIT_HPP_ */

/* End of file SonicBlit.hpp. */
