/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//
//  entity.cpp
//
// entity parsing and management for client-side
//

#include "hud.h"
#include "cl_util.h"
#include "r_efx.h"
#include "event_api.h"
#include "r_studioint.h"
#include "com_model.h"
#include "pmtrace.h"
#include "pm_defs.h"
#include "common/const.h"
#include "studio.h"
#include "cl_entity.h"
#include "dlight.h"
#include "triangleapi.h"
#include "r_studioint.h"

#include "studio_util.h"
#include "StudioModelRenderer.h"

#include "Exports.h"

#include "discord_integration.h"

#include <string.h>

extern IEngineStudio *g_pStudio;

void Game_AddObjects( void );

extern "C" int CL_DLLEXPORT HUD_AddEntity( int type, struct cl_entity_s *ent, const char *modelname )
{
	switch ( type )
	{
	case ET_NORMAL:
	case ET_PLAYER:
	case ET_BEAM:
	case ET_TEMPENTITY:
	case ET_FRAGMENTED:
	default:
		break;
	}

	// each frame every entity passes this
	return 1;
}

extern "C" void CL_DLLEXPORT HUD_CreateEntities( void )
{
#if defined( _TFC )
	// Add in any Game Specific entities
	Game_AddObjects();
#endif
	
	// Add in any shell casings
	EvHldm_ShellCasingUpdate();
}

extern "C" void CL_DLLEXPORT HUD_StudioEvent( const struct mstudioevent_s *event, const struct cl_entity_s *entity )
{
	switch( event->event )
	{
	case 5001:
		gEngfuncs.pEfxAPI->R_MuzzleFlash((float *)&entity->attachment[0], atoi( event->options) );
		break;
	case 5011:
		gEngfuncs.pEfxAPI->R_MuzzleFlash((float *)&entity->attachment[1], atoi( event->options) );
		break;
	case 5021:
		gEngfuncs.pEfxAPI->R_MuzzleFlash((float *)&entity->attachment[2], atoi( event->options) );
		break;
	case 5031:
		gEngfuncs.pEfxAPI->R_MuzzleFlash((float *)&entity->attachment[3], atoi( event->options) );
		break;
	case 5002:
		gEngfuncs.pEfxAPI->R_SparkEffect( (float *)&entity->attachment[0], atoi( event->options), -100, 100 );
		break;
	// Client side sound
	case 5004:
		gEngfuncs.pfnPlaySoundByNameAtLocation( (char *)event->options, 1.0, (float *)&entity->attachment[0] );
		break;
	default:
		break;
	}
}

extern "C" void CL_DLLEXPORT HUD_TxferLocalOverrides( struct entity_state_s *state, const struct clientdata_s *client )
{
	state->iuser1 = client->iuser1;
	state->iuser2 = client->iuser2;
	state->iuser3 = client->iuser3;
	state->iuser4 = client->iuser4;

	state->fuser1 = client->fuser1;
	state->fuser2 = client->fuser2;
	state->fuser3 = client->fuser3;
}

extern "C" void CL_DLLEXPORT HUD_ProcessPlayerState( struct entity_state_s *dst, const struct entity_state_s *src )
{
	// Copy all the data
	dst->origin					= src->origin;
	dst->angles					= src->angles;
	dst->modelindex				= src->modelindex;
	dst->frame					= src->frame;
	dst->skin					= src->skin;
	dst->effects				= src->effects;
	dst->weaponmodel			= src->weaponmodel;
	dst->movetype				= src->movetype;
	dst->sequence				= src->sequence;
	dst->animtime				= src->animtime;

	dst->aiment					= src->aiment;
	
	dst->solid					= src->solid;

	dst->colormap				= src->colormap;

#if defined( _TFC )
	dst->team					= src->team;
	dst->playerclass			= src->playerclass;
	dst->health					= src->health;
	dst->frags					= src->frags;
	dst->weapons				= src->weapons;
	dst->tf_state				= src->tf_state;

	dst->vuser1					= src->vuser1;
	dst->vuser2					= src->vuser2;
	dst->vuser3					= src->vuser3;
	dst->vuser4					= src->vuser4;

	dst->basevelocity			= src->basevelocity;
	dst->gaitsequence			= src->gaitsequence;
#endif

	dst->iuser1					= src->iuser1;
	dst->iuser2					= src->iuser2;
	dst->iuser3					= src->iuser3;
	dst->iuser4					= src->iuser4;

	dst->fuser1					= src->fuser1;
	dst->fuser2					= src->fuser2;
	dst->fuser3					= src->fuser3;

#if defined( _TFC )
	dst->fuser1					= src->fuser1;
#endif

	// Save off some data so other areas of the Client DLL can get to it
	cl_entity_t *player = gEngfuncs.GetLocalPlayer();	// Get the local player's index
	if ( dst->number == player->index )
	{
		g_iPlayerClass = dst->playerclass;
		g_iTeamNumber = dst->team;

		#ifndef ANDROID
		if (src->iuser1 != 0)
			discord_integration::set_spectating(true);
		else if (g_iUser1 != 0)
			discord_integration::set_spectating(false);
		#endif

		g_iUser1 = src->iuser1;
		g_iUser2 = src->iuser2;
		g_iUser3 = src->iuser3;
	}
}

/*
=========================
HUD_TxferPredictionData

Because we can predict an arbitrary number of frames before the server responds with an update, we need to be able to copy client side prediction data in
 from the state that the server ack'd receiving, which can be anywhere along the predicted frame path ( i.e., we could predict 20 frames into the future and the server ack's
 up through 10 of those frames, so we need to copy persistent client-side only state from the 10th predicted frame to the slot the server
 update is occupying.
=========================
*/
extern "C" void CL_DLLEXPORT HUD_TxferPredictionData ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd )
{
//	RecClTxferPredictionData(ps, pps, pcd, ppcd, wd, pwd);
	ps->oldbuttons			= pcd->oldbuttons;
	ps->flFallVelocity		= ppcd->flFallVelocity;
	ps->iStepLeft			= ppcd->iStepLeft;
	ps->playerclass			= ppcd->playerclass;
	
	ps->angles[ 0 ]			= pcd->viewangles[ 0 ];
	ps->angles[ 1 ]			= pcd->viewangles[ 1 ];
	ps->angles[ 2 ]			= pcd->viewangles[ 2 ];

	ps->gunangles[ 0 ]		= ppcd->viewangles[ 0 ];
	ps->gunangles[ 1 ]		= ppcd->viewangles[ 1 ];
	ps->gunangles[ 2 ]		= ppcd->viewangles[ 2 ];

	ps->number				= pcd->player_index;

	ps->flags				= pcd->flags;

	ps->fuser1				= pcd->flSwimTime;
	ps->fuser2				= pcd->flNextAttack;

	ps->vuser1				= pcd->velocity;
	ps->vuser2				= pcd->view_ofs;
	ps->vuser3				= pcd->punchangle;
	ps->vuser4				= ppcd->punchangle;
	
	ps->weaponanim			= pcd->weaponanim;

	ps->health				= pcd->health;
	ps->frags				= pcd->frags;
	ps->weaponmodel			= pcd->weaponmodel;
	ps->movetype			= pcd->movetype;

	ps->maxspeed			= pcd->maxspeed;
	ps->fov					= pcd->fov;
	ps->team				= pcd->team;
	ps->playerclass			= pcd->playerclass;
	ps->usehull				= pcd->usehull;
	ps->gaitsequence		= pcd->gaitsequence;
	ps->spectator			= pcd->spectator;
	ps->groundentity		= pcd->groundentity;

	ps->spawntime			= pcd->spawntime;
	ps->friction			= pcd->friction;

	ps->custom_int			= pcd->custom_int;

	ps->iuser1				= pcd->iuser1;
	ps->iuser2				= pcd->iuser2;
	ps->iuser3				= pcd->iuser3;
	ps->iuser4				= pcd->iuser4;

	ps->fuser1				= pcd->fuser1;
	ps->fuser2				= pcd->fuser2;
	ps->fuser3				= pcd->fuser3;

	// Wpn data
	memcpy( wd, pwd, 32 * sizeof( weapon_data_t ) );
}

extern "C" void CL_DLLEXPORT HUD_TempEntUpdate (
	double ft,
	double ct,
	double cl,
	void (* pAddTEntity)( struct tempent_s *pEntity ),
	void (* pPlayTEntSound)( struct tempent_s *pEntity, float damp ) )
{
	static int iTempEntCount = 0;

	ALERT( at_aiconsole, "%d tempent models in frame %d\n", iTempEntCount, gEngfuncs.GetScreenInfo()->framecount );

	iTempEntCount = 0;

	// Nothing
}

/*
=========================
HUD_GetUserEntity

If you specify negative numbers for beam start/end, this sets up the 
internal parameters for that entity so you can call 
TE_BeamPoints/TE_BeamEnts later and have it work.
=========================
*/
extern "C" cl_entity_t CL_DLLEXPORT *HUD_GetUserEntity( int index )
{
#if defined( _TFC )
	return gEngfuncs.GetEntityByIndex( index );
#else
	return NULL;
#endif
}
