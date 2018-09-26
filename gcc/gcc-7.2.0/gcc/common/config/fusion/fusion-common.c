/* Common hooks for Fusion-Core.
   Copyright (C) 2018 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "common/common-target.h"
#include "common/common-target-def.h"
#include "opts.h"
#include "flags.h"
#include "diagnostic-core.h"



/* Implentation of TARGET_HANDLE_OPTION */
static bool
riscv_handle_option(struct gcc_options *opts,
				struct gcc_options *opts_set ATTRIBUTE_UBUSED,
				const struct cl_decoded_option *decoded,
				location_t loc)
{
	switch(decoded->opt_index)
	{
		/* architecture inputs, right now return true as no changes */
		case OPT_march_:
			return true;
		default:
			return true;
	}
}

/* Implementation for TARGET_OPTION_OPTIMIZATION_TABLE */
static const struct default_options fusion_option_optimization_table[] = 
{
	{ OPT_LEVELS_1_PLUS, OPT_fsection_anchors, NULL, 1 },
	{ OPT_LEVELS_1_PLUS, OPT_fomit_frame_pointer, NULL, 1},
	{ OPT_LEVELS_2_PLUS, OPT_free, NULL, 1},
	{ OPT_LEVELS_NONE, 0, NULL, 0}

};

#undef TARGET_OPTIMIZATION_TABLE
#define TARGET_OPTIMIZATION_TABLE fusion_option_optimization_table

#undef TARGET_HANDLE_OPTION
#define TARGET_HANDLE_OPTION fusion_handle_option

struct gcc_targetm_common targetm_common = TARGETM_COMMON_INITIALIZER;
