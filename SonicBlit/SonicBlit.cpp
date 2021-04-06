/*
 * SonicBlit.cpp - embeddable loader / player for SonicBlit.
 *
 * This file (along with SonicBlit.hpp) provides a self-contained player for
 * SonicBlit data files; the process of adding support for SonicBlit into your
 * project is explained in the accompanying README.md
 *
 * Copyright (c) 2021 Pete Favelle / fsquared limited <32blit@fsquared.co.uk>
 *
 * This software is distributed under the MIT License; see LICENSE for details.
 */

/* System headers. */

#include <string.h>


/* Local headers. */

#include "32blit.hpp"
#include "SonicBlit.hpp"


/* Functions. */

/*
 * SonicBlit - initialises the SonicBlit player, optionally also loading the
 *             song data at the same time.
 *
 * p_channel_offset - allows the caller to tell SonicBlit to skip the first 'n'
 *             channels, in case there is other audio processing going on.
 *
 * p_data    - the data block (normally via the asset pipeline) which contains
 *             the song data - can be null.
 */

SonicBlit::SonicBlit( uint8_t p_channel_offset, const uint8_t *p_data )
{

  /* If we were given data, load that - otherwise we're done. */
  if ( nullptr != p_data )
  {
    load( p_data );
  }

  /* All done. */
  return;
}


/*
 * ~SonicBlit - shuts down the SonicBlit player, freeing up any memory that has
 *              been allocated and stopping everything from playing.
 */

SonicBlit::~SonicBlit( void )
{
  /* All done. */
  return;
}


/*
 * load   - loads the song data from the provided buffer.
 *
 * p_data - the data block notmally via the asset pipeline.
 *
 * Returns a boolean flag, set to false if any problems were encountered.
 */

bool SonicBlit::load( const uint8_t *p_data )
{
  uint16_t l_cmd_offset;

  /* Clear our current program, copy the first segment over. */
  memset( &c_program, 0, sizeof( sb_program_t ) );
  memcpy( &c_program, p_data, 6 );

  /* Validate the magic number; need to be confident it's valid data. */
  if ( strncmp( c_program.magic, SB_MAGIC, 4 ) != 0 )
  {
    return false;
  }

  /* Point the voice definitions to the appropriate location in the data. */
  c_program.voices = (const sb_voice_t *)( p_data + 6 );

  /* Copy the command count and pointer too, which comes after the voices. */
  l_cmd_offset = 6 + ( c_program.voice_count * sizeof( sb_voice_t ) );
  memcpy( &c_program.command_count, p_data + l_cmd_offset, sizeof( c_program.command_count ) );
  c_program.commands = (const sb_command_t *)( p_data + l_cmd_offset + sizeof( c_program.command_count ) );

  /* Reset the program counter. */
  c_prog_counter = 0;
  c_prog_running = c_inst_running = false;

  /* All worked, then! */
  return true;
}


/*
 * update - called every tick to update the progress of the playing song.
 *          Tracks where we are in the program, triggering notes as defined
 *          by the code and the current time index.
 *
 * p_tick - the millisecond count from the main update handler; used to keep
 *          everything synced up properly.
 *
 * Returns a boolean flag, set to false if any problems were encountered.
 */

bool SonicBlit::update( uint32_t p_tick )
{
  /* If we're not running, then there is no update to do. */
  if ( !c_prog_running )
  {
    return true;
  }

  /* All done. */
  return true;
}


/*
 * start/pause/stop - service functions to control when this program is running
 *                    or not. start will resume from a stopped or paused state.
 */

bool SonicBlit::start( void )
{
  c_prog_running = true;
  return true;
}

bool SonicBlit::pause( void )
{
  c_prog_running = false;
  return true;
}

bool SonicBlit::stop( void )
{
  c_prog_running = false;
  c_prog_counter = 0;
  return true;
}


/*
 * State checking operations. 
 */

bool SonicBlit::is_running( void )
{
  return c_prog_running;
}

bool SonicBlit::is_paused( void )
{
  return !c_prog_running && c_prog_counter > 0;
}

/* End of file SonicBlit.cpp. */
